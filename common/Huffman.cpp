#include <iostream>
#include <queue>
#include <vector>
#include <functional>
#include <cassert>
#include <map>
#include <cmath>
#include <exception>

#include "Huffman.h"

long bin_to_dec(const std::vector<bool>& bin) {
	long res = 0;
	for (int i = bin.size() - 1; i > -1; --i) {
		if (bin[i]) {
			res += pow(2, bin.size() - (i + 1));
		}
	}
	return res;
}

std::vector<bool> dec_to_bin(long l) {
	std::vector<bool> bin;
	while (l) {
		bin.push_back(l % 2);
		l /= 2;
	}
	for (size_t i = 0; i < bin.size() / 2; ++i) {
		std::swap(bin[i], bin[bin.size() - i - 1]);
	}
	return bin;
}

class bit_output {
 public:
	bit_output(IOutputStream& stream) 
		: stream(stream)
		, buf(0)
		, bit_count(0)
	{}

	void write_bit(byte bit) {
		buf |= (bit & 1) << (7 - (bit_count++));
		if (bit_count == 8) {
			flush();
		}
	}

	void flush() {
		stream.Write(buf);
		buf = 0;
		bit_count = 0;
	}

private:
	IOutputStream& stream;
	byte buf;
	byte bit_count;
};

class bit_input {
 public:
	bit_input(IInputStream& input)
		: input(input)
		, buf(0)
		, bit_pos(8)
	{}

	bool read_bit(byte& bit) {
		if (bit_pos == 8) {
			bool res = input.Read(buf);
			bit_pos = 0;
			if (!res) {
				return false;
			}
		}
		bit = (buf >> (7 - (bit_pos++))) & 1;
		return true;
	}

	bool read_long(long& l) {
		return true;
	}
private:
	IInputStream& input;
	byte buf;
	byte bit_pos;
};

#define ALPHABET_SIZE 256

struct node {
	long freq;
	byte val;
	node* left;
	node* right;

	node()
		: freq(0)
		, val(0)
		, left{nullptr}
		, right{nullptr}
	{}
	explicit node(long freq, byte val = 0)
		: freq{freq}
		, val{val}
		, left{nullptr}
		, right{nullptr}
	{}
};

typedef std::priority_queue<node*, std::vector<node*>, std::function<bool(const node* l, const node* r)>> min_priority_queue;

static node* create_huffman_thee(const std::vector<long>& freq_val) {
	min_priority_queue q([](const node* l, const node* r) { return l->freq > r->freq; });
	for (size_t val = 0; val < freq_val.size(); ++val) {
		long freq = freq_val[val];
		if (freq) {
			q.emplace(new node(freq, val));
		}
	}

	if (!q.size()) {
		return nullptr;
	}

	while (true) {
		node* left = q.top(); q.pop();
		if (q.empty()) {
			return left;
		}
		node* right = q.top(); q.pop();

		node* root = new node(left->freq + right->freq);
		root->left = left;
		root->right = right;
		q.push(root);
	}
}

static void set_code(node* _node, std::map<byte, std::vector<bool>>& codes) {
	if (!_node) {
		return;
	}
	static std::vector<bool> code;
	if (_node->left) {
		code.push_back(0);
		set_code(_node->left, codes);
	}
	if (_node->right) {
		code.push_back(1);
		set_code(_node->right, codes);
	}

	if (!code.empty()) {
		codes[_node->val] = code;
		code.pop_back();
	}
}

static void del_thee(node*& _node) {
	if (!_node) {
		return;
	}
	del_thee(_node->left);
	del_thee(_node->right);
	delete _node;
}

static void print(node* _node) {
	if (!_node) return;
	std::cout << "freq = " << _node->freq << " val = " << (size_t)_node->val << std::endl;
	print(_node->left);
	print(_node->right);
}

static void packing_stream(IInputStream& original, IOutputStream& compressed) {
		std::vector<byte> input;

		{
			byte val = 0;
			while (original.Read(val)) {
				input.push_back(val);
			}
		}

		std::vector<long> freq_val(ALPHABET_SIZE, 0);
		for (auto& val : input) {
			++freq_val[val];
		}

		node* root = create_huffman_thee(freq_val);

		std::map<byte, std::vector<bool>> table_codes;
		set_code(root, table_codes);
		del_thee(root);

		// заголовок
		compressed.Write(table_codes.size() - 1);

		// таблица частот символов:
		// символ_1, длина в двоичной системе счисления_1, ... символ_n, длина в двоичной системе счисления_n
		// символ_1 в двоичной системе, символ_2 в двоичной системе..
		for (size_t val = 0; val < freq_val.size(); ++val) {
			long freq = freq_val[val];
			if (freq) {
				compressed.Write(val);
				std::vector<bool> tmp = dec_to_bin(freq);
				compressed.Write(tmp.size());
			}
		}

		bit_output _bit_output(compressed);
		for (size_t val = 0; val < freq_val.size(); ++val) {
			long freq = freq_val[val];
			if (freq) {
				std::vector<bool> tmp = dec_to_bin(freq);
				for (const auto& t : tmp) {
					_bit_output.write_bit(t);
				}
			}
		}

		// сообщение
		for (auto& elem : input) {
			for (const auto& bit : table_codes[elem]) {
				_bit_output.write_bit(bit);
			}
		}
		_bit_output.flush();
}

// Метод архивирует данные из потока original
void Encode(IInputStream& original, IOutputStream& compressed) {
	packing_stream(original, compressed);
}

static void unpacking_stream(IInputStream& compressed, IOutputStream& original) {
		byte num_symbols = 0;
		compressed.Read(num_symbols);

		std::vector<long> freq_val(ALPHABET_SIZE, 0);
		for (size_t idx = 0; idx < num_symbols; ++idx) {
			byte val = 0;
			compressed.Read(val);
			byte tmp = 0;
			compressed.Read(tmp);
			freq_val[val] = tmp;
		}

		bit_input _bit_input(compressed);
		for (size_t val = 0; val < freq_val.size(); ++val) {
			long& freq = freq_val[val];
			if (freq) {
				std::vector<bool> tmp;
				for (size_t i = 0; i < freq; ++i) {
					byte val = 0;
					assert(_bit_input.read_bit(val));
					tmp.push_back(val);
				}
				freq = bin_to_dec(tmp);
			}
		}

		node* root = create_huffman_thee(freq_val);

		node* _node = root;
		for (long idx = 0; idx < root->freq;) {
			if (_node->left && _node->right) {
				byte val = 0;
				// тут валится на 5 тесте assert(_bit_input.read_bit(val));
				if (!_bit_input.read_bit(val)) {
					//original.Write(_node->val);
					break;
				}
				if ((size_t)val == 1) {
					_node = _node->right;
				}
				else {
					_node = _node->left;
				}
			} else {
				//std::cout << "val " << (size_t)_node->val << std::endl;
				original.Write(_node->val);
				_node = root;
				++idx;
			}
		}

		del_thee(root);
}

// Метод восстанавливает оригинальные данные
void Decode(IInputStream& compressed, IOutputStream& original) {
	unpacking_stream(compressed, original);
}

/*--------------------------------------------------------*/

class VectorInputStream : public IInputStream
{
 public:
	VectorInputStream(std::vector <byte>& vec) : vec(vec), pos(0)
	{}

	virtual bool Read(byte& value) override
	{
		if (pos < vec.size())
		{
			value = vec[pos++];
			return true;
		}
		return false;
	}
 private:
	std::vector <byte>& vec;
	int pos;
};

class VectorOutputStream : public IOutputStream
{
 public:
	VectorOutputStream(std::vector <byte>& vec) : vec(vec)
	{}

	virtual void Write(byte value) override
	{
		vec.push_back(value);
	}
 private:
	std::vector <byte>& vec;
};


int main(int argc, const char * argv[]) {
	//std::cout <<  bin_to_dec({ 1, 0 , 1 });

	std::string str("abcdefg");
	std::vector<byte> vec = { 'r', 'v', 2, 3, 4, 1, 3, 4, 5, 8, 63, 8, 5, 76, 34, 7, 8,
		5, 'c', 8, 'c', 45, 23, 65, 43, 57, 1, 3, 77, 1, 2, 3, 4, 4};
	//std::vector<byte>(str.begin(), str.end());
	//for (auto& v : vec) {
	//	std::cout << (size_t)v << " ";
	//}
	//std::cout << std::endl << std::endl;

	VectorInputStream in{vec};
	VectorOutputStream out{vec};
	Encode(in, out);
	Decode(in, out);

	return 0;
}



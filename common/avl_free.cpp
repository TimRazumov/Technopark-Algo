#include <cassert>
#include <iostream>
#include <functional>
#include <vector>

/*
 Task 4

 Дано число N и N строк. Каждая строка содержит команду добавления или удаления натуральных чисел, 
 а также запрос на получение k-й порядковой статистики. Команда добавления числа A задается 
 положительным числом A, команда удаления числа A задается отрицательным числом “-A”. 
 Запрос на получение k-й порядковой статистики задается числом k.
 Требования: скорость выполнения запроса - O(log n).
*/

template <class type>
class avl_tree {
	struct node {
		type key;
		uint8_t height;
		node* left;
		node* right;

		explicit node(const type& key)
			: key(key)
			, height(1)
			, left(nullptr)
			, right(nullptr)
		{}
	};
 public:
	avl_tree(const std::function<int(const type& l, const type& r)>& comp =
		[](const type& l, const type& r) {
		    if (l < r) {
			    return -1;
		    }
		    if (l > r) {
			    return 1;
		    }
		    return 0;
	    })
		: root(nullptr)
		, comp(comp)
	{}

	avl_tree(const avl_tree&) = delete;
	avl_tree(avl_tree&&) = delete;
	avl_tree& operator=(const avl_tree&) = delete;
	avl_tree& operator=(avl_tree&&) = delete;

	~avl_tree() {
		_del(root);
	}

	void insert(const type& key) {
		root = _insert(root, key);
	}

	void erase(const type& key) {
		root = _erase(root, key);
	}

	friend
	type get_ord_stat(const avl_tree& tree, size_t k) {
		return tree._get_ord_stat(tree.root, k);
	}

 private:
	node* root;
	std::function<int(const type& l, const type& r)> comp;

	node* _insert(node* _node, const type& key) {
		if (!_node) {
			return new node(key);
		}
		int comp_res = comp(key, _node->key);
		if (comp_res == -1) {
			_node->left = _insert(_node->left, key);
		}
		else {
			_node->right = _insert(_node->right, key);
		}
		return balance(_node);
	}

	node* _erase(node* _node, const type& key) {
		if (!_node) {
			return nullptr;
		}

		int comp_res = comp(key, _node->key);
		if (comp_res == -1) {
			_node->left = _erase(_node->left, key);
		} else if (comp_res == 1) {
			_node->right = _erase(_node->right, key);
		} else {
			node* left = _node->left;
			node* right = _node->right;

			delete _node;

			if (!right) {
				return left;
			}

			node* min_node = exclude_min_node(right);
			min_node->right = right;
			min_node->left = left;
			return balance(min_node);
		}
		return balance(_node);
	}

	node* exclude_min_node(node*& _node) {
		node* min_node = nullptr;
		if (!_node->left) {
			min_node = _node;
			_node = _node->right;
			min_node->right = nullptr;
			return min_node;
		}
		min_node = exclude_min_node(_node->left);
		_node = balance(_node);
		return min_node;
	}

	uint8_t height(node* _node) const {
		return _node ? _node->height : 0;
	}

	void fix_height(node* _node) {
		if (!_node) {
			return;
		}
		_node->height = (height(_node->left) < height(_node->right)
			? height(_node->right) : height(_node->left)) + 1;
	}

	int bfactor(node* _node) const {
		assert(_node);
		return height(_node->right) - height(_node->left);
	}

	node* balance(node* _node) {
		if (!_node) {
			return nullptr;
		}
		fix_height(_node);
		int bf = bfactor(_node);

		if (bf == 2) {
			if (bfactor(_node->right) < 0) {
				_node->right = rotate_right(_node->right);
			}
			return rotate_left(_node);
		}

		if (bf == -2) {
			if (bfactor(_node->left) > 0) {
				_node->left = rotate_left(_node->left);
			}
			return rotate_right(_node);
		}

		return _node;
	}

	node* rotate_right(node* _node) {
		if (!_node) {
			return nullptr;
		}
		node* tmp = _node->left;
		_node->left = tmp->right;
		tmp->right = _node;
		fix_height(_node);
		fix_height(tmp);
		return tmp;
	}

	node* rotate_left(node* _node) {
		if (!_node) {
			return nullptr;
		}
		node* tmp = _node->right;
		_node->right = tmp->left;
		tmp->left = _node;
		fix_height(_node);
		fix_height(tmp);
		return tmp;
	}

	void _del(node*& _node) {
		if (!_node) {
			return;
		}
		_del(_node->left);
		_del(_node->right);
		delete _node;
	}

	size_t count(node* _node) const {
		if (!_node) {
			return 0;
		}
		size_t num_elems = 1;
		num_elems += count(_node->left);
		num_elems += count(_node->right);
		return num_elems;
	}

	type _get_ord_stat(node* _node, size_t k) const {
		assert(_node);
		size_t ord_stat = 0;
		size_t num_elems = count(_node->left);
		if (num_elems > k) {
			ord_stat = _get_ord_stat(_node->left, k);
		} else if (num_elems < k) {
			ord_stat = _get_ord_stat(_node->right, k - num_elems - 1);
		} else {
			ord_stat = _node->key;
		}
		return ord_stat;
	}
};

void run() {
	avl_tree<size_t> tree;
	size_t num_command = 0;
	std::cin >> num_command;
	for (int i = 0; i < num_command; ++i) {
		int key = 0;
		size_t num_stat = 0;
		std::cin >> key >> num_stat;
		if (key < 0) {
			tree.erase(abs(key));
		} else {
			tree.insert(key);
		}
		std::cout << get_ord_stat(tree, num_stat) << std::endl;
	}
}

int main() {
	run();
	return 0;
}
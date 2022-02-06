#include <iostream>
#include <functional>
#include <vector>
#include <string>

#define INIT_SIZE 8

/*

Task 1.2

Реализуйте структуру данных типа “множество строк” на основе динамической 
хеш-таблицы с открытой адресацией. Хранимые строки непустые и состоят из строчных латинских букв.
Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
Начальный размер таблицы должен быть равным 8-ми.
Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3/4.
Структура данных должна поддерживать операции добавления строки в множество,
удаления строки из множества и проверки принадлежности данной строки множеству.

Для разрешения коллизий используйте двойное хеширование.

Требования: В таблице запрещено хранение указателей на описатель элемента.

*/

template<class type>
class hash_table {
public:
	hash_table() = delete;
	hash_table(const hash_table&) = delete;
	hash_table& operator=(const hash_table&) = delete;
	hash_table(hash_table&&) = delete;
	hash_table& operator=(hash_table&&) = delete;

	explicit
	hash_table(const std::function<size_t(const type&, size_t)>& hash_func)
		: hash_func(hash_func)
		, elems(INIT_SIZE)
		, num_elems(0)
		, elems_status(INIT_SIZE, empty)
	{}

	~hash_table() {}

	bool add(const type& elem) {
		if (4 * num_elems > 3 * elems.size()) { // таблица заполнена на 75%
			grow();
		}
		for (size_t i = 0; i < elems.size(); i++) {
			size_t hash = hash_func(elem, i) % elems.size();
			if (elems_status[hash] == busy && elems[hash] == elem) {
				break;
			} else if (elems_status[hash] == empty || 
				(elems_status[hash] == deleted && !in_table(elem))) {
				elems[hash] = elem;
				elems_status[hash] = busy;
				num_elems++;
				return true;
			}
		}
		return false;
	}
	bool in_table(const type& elem) const {
		for (size_t i = 0; i < elems.size(); i++) {
			size_t hash = hash_func(elem, i) % elems.size();
			if (elems_status[hash] == busy && elems[hash] == elem) {
				return true;
			}
			if (elems_status[hash] == empty) {
				break;
			}
		}
		return false;
	}
	bool del(const type& elem) {
		for (size_t i = 0; i < elems.size(); i++) {
			size_t hash = hash_func(elem, i) % elems.size();
			if (elems_status[hash] == busy && elems[hash] == elem) {
				elems_status[hash] = deleted;
				// num_elems--;
				return true;
			}
			if (elems_status[hash] == empty) {
				break;
			}
		}
		return false;
	}

private:
	std::function<size_t(type, size_t)> hash_func;
	std::vector<type> elems;
	size_t num_elems;
	enum status {
		empty, busy, deleted
	};
	std::vector<status> elems_status;
	void grow() {
        std::vector<type> new_elems(2 * elems.size());
		std::vector<status> new_elems_status(2 * elems_status.size(), empty);
		for (size_t i = 0; i < elems.size(); i++) {
			if (elems_status[i] == busy) {
				for (size_t j = 0; j < new_elems.size(); j++) {
					size_t hash = hash_func(elems[i], j) % new_elems.size();
					if (new_elems_status[hash] != busy) {
						new_elems[hash] = elems[i];
						new_elems_status[hash] = busy;
						break;
					}
				}
			}
		}
        elems = std::move(new_elems);
		elems_status = std::move(new_elems_status);
	}
};

int main() {
	hash_table<std::string> table(
		[](const std::string& word, size_t num_prob) {
		    size_t hash = 0, hash_probe = 0;
		    for (const char& ch : word) {
			    hash = 7 * hash + ch;
		    }
		    if (num_prob) {
			    for (const char& ch : word) {
				    hash_probe = 13 * hash_probe + ch;
			    }
			    hash_probe = 2 * hash_probe + 1;
		    }
		    return hash + num_prob * hash_probe;
	    }
	);
	char operation;
	std::string word;
	while (std::cin >> operation >> word) {
		if (operation == '+') {
			std::cout << (table.add(word) ? "OK" : "FAIL") << std::endl;
		} else if (operation == '?') {
			std::cout << (table.in_table(word) ? "OK" : "FAIL") << std::endl;
		} else if (operation == '-') {
			std::cout << (table.del(word) ? "OK" : "FAIL") << std::endl;
		} else {
			std::cout << "FAIL" << std::endl;
		}
	}
	return 0;
}
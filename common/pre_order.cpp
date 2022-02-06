#include <iostream>
#include <vector>
#include <stack>
#include <functional>

/*

Task 2.2

Дано число N < 106 и последовательность целых чисел из[-231..231] длиной N.
Требуется построить бинарное дерево, заданное наивным порядком вставки.
Т.е., при добавлении очередного числа K в дерево с корнем root, 
если root?Key ? K, то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
Требования: Рекурсия запрещена.Решение должно поддерживать передачу функции сравнения снаружи.

Выведите элементы в порядке pre-order (сверху вниз).
*/

template<class type>
class binary_free {
 public:
	explicit binary_free(const std::function<bool(const type&, const type&)>& comp)
		: comp(comp), root(nullptr)
	{}
	binary_free() = delete;
	binary_free(const binary_free&) = delete;
	binary_free& operator=(const binary_free&) = delete;
	binary_free(binary_free&&) = delete;
	binary_free& operator=(binary_free&&) = delete;
	~binary_free() {
		if (root) {
		    std::stack<node*> stack;
		    stack.push(root);
		    while (!stack.empty()) {
			    node* tmp = stack.top();
			    stack.pop();
			    if (tmp->right) {
				    stack.push(tmp->right);
			    }
			    if (tmp->left) {
				    stack.push(tmp->left);
			    }
			    delete tmp;
		    }
		}
	}
	void add(const type& elem) {
		if (!root) {
			root = new node(elem);
			return;
		}
		node* tmp = root;
		while (true) {
			if (comp(tmp->data, elem)) {
				if (!tmp->right) {
					tmp->right = new node(elem);
					break;
				}
				tmp = tmp->right;
			} else {
				if (!tmp->left) {
					tmp->left = new node(elem);
					break;
				}
				tmp = tmp->left;
			}
		}
		return;
	}
	std::vector<type> pre_order() const {
		std::vector<type> res;
		if (!root) {
			return res;
		}
		std::stack<node*> stack;
		stack.push(root);
		while (!stack.empty()) {
			node* tmp = stack.top();
			stack.pop();
			if (tmp->right) {
				stack.push(tmp->right);
			}
			if (tmp->left) {
				stack.push(tmp->left);
			}
			res.push_back(tmp->data);
		}
		return res;
	}
 private:
	 std::function<bool(const type&, const type&)> comp;
	 struct node {
		 node* left;
		 node* right;
		 type data;
		 node() : left(nullptr), right(nullptr) {}
		 explicit node(const type& data) : left(nullptr), right(nullptr), data(data) {}
	 };
	 node* root;
};

int main() {
	binary_free<int> tree([](const int& l, const int& r) {
		                   return r > l; 
	                     });
	int num_elems = 0;
	std::cin >> num_elems;
	for (int i = 0; i < num_elems; ++i) {
		int elem = 0;
		std::cin >> elem;
		tree.add(elem);
	}
	std::vector<int> elems = tree.pre_order();
	for (const auto& elem : elems) {
		std::cout << elem << " ";
	}
	return 0;
}
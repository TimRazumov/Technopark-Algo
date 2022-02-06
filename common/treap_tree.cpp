#include <iostream>
#include <functional>
#include <vector>
#include <stack>

template<class type>
class binary_free {
public: 
	explicit
	binary_free(const std::function<bool(const int& l, const int& r)>& comp)
		: root(nullptr)
		, comp(comp)
	{}

	binary_free()
		: root(nullptr)
		, comp([](const int& l, const int& r) {
		        return l < r;
	           })
	{}

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
		node* new_node = new node(elem);
		if (!root) {
			root = new_node;
			return;
		}
		node* tmp = root;
		while (true) {
			if (comp(tmp->data, elem)) {
				if (!tmp->right) {
					tmp->right = new_node;
					break;
				}
				tmp = tmp->right;
			}
			else {
				if (!tmp->left) {
					tmp->left = new_node;
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
	size_t height() const {
		return _height(root);
	}
private:
	std::function<bool(const type&, const type&)> comp;
	struct node {
		node* left;
		node* right;
		type data;
		node() : left(nullptr), right(nullptr) {}
		explicit 
		node(const type& data) : left(nullptr), right(nullptr), data(data) {}
	};
	node* root;

	size_t _height(node* _node) const {
		if (_node) {
			size_t l = _node->left ? _height(_node->left) : 0;
			size_t r = _node->right ? _height(_node->right) : 0;
			return ((l > r) ? l : r) + 1;
		}
		return 0;
	}
};

template<class type>
class treap_tree {
	struct node {
		type key;
		size_t priority;
		node* left;
		node* right;
		node()
			: left(nullptr)
			, right(nullptr)
		{}
		node(const type& key, size_t priority)
			: key(key)
			, priority(priority)
			, left(nullptr)
			, right(nullptr)
		{}
	};
 public:
	explicit
	treap_tree(const std::function<bool(const type& l, const type& r)>& comp)
		: root(nullptr)
		, comp(comp)
	{}

	treap_tree()
		: root(nullptr)
		, comp([](const type& l, const type& r) {
		            return l < r;
	           })
	{}
	treap_tree(const treap_tree&) = delete;
	treap_tree& operator=(const treap_tree&) = delete;
	treap_tree(treap_tree&&) = delete;
	treap_tree& operator=(treap_tree&&) = delete;

	~treap_tree() {}

	void add(const type& key, size_t priority) {
		node* new_node = new node(key, priority);
		if (!root || root->priority < priority) {
			split(root, key, new_node->left, new_node->right);
			root = new_node;
			return;
		}
		node* tmp = root;
		while (true) {
			if (comp(tmp->key, key)) {
				if (!tmp->right) {
					tmp->right = new_node;
					break;
				}
				if (tmp->right->priority < priority) {
					split(tmp->right, key, new_node->left, new_node->right);
					tmp->right = new_node;
					break;
				}
				tmp = tmp->right;
			} else {
				if (!tmp->left) {
					tmp->left = new_node;
					break;
				}
				if (tmp->left->priority < priority) {
					split(tmp->left, key, new_node->left, new_node->right);
					tmp->left = new_node;
					break;
				}
				tmp = tmp->left;
			}
		}
		return;
	}

	size_t height() const {
		return _height(root);
	}

 private:
	 node* root;
	 std::function<bool(const type& l, const type& r)> comp;

	 void split(node* _node, const type& key, node*& left, node*& right) {
		 if (!_node) {
			 left = nullptr;
			 right = nullptr;
		 } else if (!comp(key, _node->key)) {
			 split(_node->right, key, _node->right, right);
			 left = _node;
		 } else {
			 split(_node->left, key, left, _node->left);
			 right = _node;
		 }
	 }

	 node* merge(node* left, node* right) {
		 if (!left) {
			 return right;
		 } else if (!right) {
			 return left;
		 } else if (left->priority > right->priority) {
			 left->right = merge(left->right, right);
			 return left;
		 } else {
			 right->left = merge(left, right->left);
			 return right;
		 }
	 }

	 size_t _height(node* _node) const {
		 if (_node) {
			 size_t l = _node->left ? _height(_node->left) : 0;
			 size_t r = _node->right ? _height(_node->right) : 0;
			 return ((l > r) ? l : r) + 1;
		 }
		 return 0;
	 }
};

void run() {
	size_t num_command = 0;
	std::cin >> num_command;
	binary_free<int> _binary_tree;
	treap_tree<int> _treap_tree;
	for (size_t i = 0; i < num_command; i++) {
		int key = 0;
		size_t priority = 0;
		std::cin >> key >> priority;
		_binary_tree.add(key);
		_treap_tree.add(key, priority);
	}
	std::cout << (int)_binary_tree.height() - (int)_treap_tree.height();
}

int main() {
	run();
	return 0;
}
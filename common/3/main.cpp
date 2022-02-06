#include <iostream>
#include <cassert>

/*

Task 3.3.

Реализовать очередь с помощью двух стеков.
Использовать стек, реализованный с помощью динамического буфера.

*/

class Stack {
private:
	int size;
	int last; // индекс последнего элемента в стэке 
	int* elems;
public:
	Stack(int size = 4)
		: size(size)
		, last(-1)
		, elems(new int[size])
	{}
	~Stack() {
		delete[] elems;
	}
	bool IsEmpty() {
		if (last < 0) {
			return true;
		}
		return false;
	}
	int Pop() {
		assert(!IsEmpty());
		return elems[last--];
	}
	void Push(int elem) {
		if (last + 1 >= size) {
			size *= 2;
			int* tmp = new int[size];
			for (int i = 0; i <= last; i++) {
				tmp[i] = elems[i];
			}
			delete[] elems;
			elems = tmp;
		}
		elems[++last] = elem;
	}
};

class Queue {
private:
	Stack stack_in;
	Stack stack_out;
public:
	Queue(int size = 4)
		: stack_in(size)
		, stack_out(size)
	{}
	~Queue() {}
	bool IsEmpty() {
		return (stack_in.IsEmpty() && stack_out.IsEmpty());
	}
	void Enqueue(int elem) {
		stack_in.Push(elem);
	}
	int Dequeue() {
		if (stack_out.IsEmpty()) {
			while (!stack_in.IsEmpty()) {
				int tmp = stack_in.Pop();
				stack_out.Push(tmp);
			}
		}
		return stack_out.Pop();
	}
};

bool CommandMain(int num_commands) {
	Queue queue;
	for (int i = 0; i < num_commands; i++) {
		int command(0);
		int value(0);
		std::cin >> command >> value;
		if (command == 2) {
			int deq_val(-1);
			if (!queue.IsEmpty()) {
				deq_val = queue.Dequeue();
			}
			if (deq_val != value) {
				return false;
			}
		}
		else if (command == 3) {
			queue.Enqueue(value);
		}
		else {
			return false;
		}
	}
	return true;
}


int main() {
	int n(0);
	std::cin >> n;
	assert(n);
	if (CommandMain(n)) {
		std::cout << "YES";
	}
	else {
		std::cout << "NO";
	}
	return 0;
}
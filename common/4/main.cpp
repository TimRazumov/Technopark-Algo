#include <iostream>
#include <cassert>
#include <memory>
#include <functional>

/*

Task 4.1.

Решение всех задач данного раздела предполагает использование кучи, реализованной в виде класса. 
Решение должно поддерживать передачу функции сравнения снаружи.

Вовочка ест фрукты из бабушкиной корзины. В корзине лежат фрукты разной массы. 
Вовочка может поднять не более K грамм. Каждый фрукт весит не более K грамм. 
За раз он выбирает несколько самых тяжелых фруктов, которые может поднять одновременно, 
откусывает от каждого половину и кладет огрызки обратно в корзину. 
Если фрукт весит нечетное число грамм, он откусывает большую половину. 
Фрукт массы 1гр он съедает полностью.
Определить за сколько подходов Вовочка съест все фрукты в корзине.
Формат входных данных. Вначале вводится n - количество фруктов и n строк с массами фруктов. 
Затем K - "грузоподъемность".

*/

template <class Type>
class Vector {
private:
	int size;
	int capacity;
	Type* elems;
	void Copy(const Type* elems_copy) {
		for (int i = 0; i < size; i++) {
			elems[i] = elems_copy[i];
		}
	}
public:
	Vector(int sz = 0)
		: size(sz)
		, capacity(sz ? 2 * sz : 2)
		, elems(new Type[capacity])
	{}
	Vector(const Vector<Type>& vec)
		: size(vec.size)
		, capacity(vec.capacity)
		, elems(new Type[vec.capacity])
	{
		Copy(vec.elems);
	}
	~Vector() {
		delete[] elems;
	}
	int Size() const {
		return size;
	}
	bool IsEmpty() const {
		return !size;
	}
	Type PopBack() { // извлекает последний элемент и удаляет
		assert(size > 0);
		return elems[--size];
	}
	void PushBack(int elem) {
		if (size == capacity) {
			capacity *= 2;
			auto tmp = elems;
			elems = new Type[capacity];
			Copy(tmp);
			delete[] tmp;
		}
		elems[size++] = elem;
	}
	Type& operator[](int idx) const {
		assert(size > idx);
		return elems[idx];
	}
	friend
	std::istream& operator>>(std::istream& input, Vector<Type>& vec) {
		for (size_t i = 0; i < vec.size; i++) {
			input >> vec.elems[i];
		}
		return input;
	}
	friend
	std::ostream& operator<<(std::ostream& output, const Vector<Type>& vec) {
		for (size_t i = 0; i < vec.size; i++) {
			output << vec.elems[i] << " ";
		}
		return output;
	}
};

template <class Type>
class Heap {
 private:
	Vector<Type> vec;
	std::function<bool(const Type&, const Type&)> compare;
	void SiftDown(int idx) {
		int idx_l = 2 * idx + 1;
		int idx_r = 2 * idx + 2;
		int idx_max = idx;
		int size = vec.Size();
		if (idx_l < size && compare(vec[idx], vec[idx_l])) {
			idx_max = idx_l;
		}
		if (idx_r < size && compare(vec[idx_max], vec[idx_r])) {
			idx_max = idx_r;
		}
		if (idx_max != idx) {
			std::swap(vec[idx_max], vec[idx]);
			SiftDown(idx_max);
		}
	}
	void SiftUp(int idx) {
		while (idx > 0) {
			int idx_parent = (idx - 1) / 2;
			if (!compare(vec[idx_parent], vec[idx])) {
				return;
			}
			std::swap(vec[idx], vec[idx_parent]);
			idx = idx_parent;
		}
	}
	void MakeHeap() {
		for (int i = vec.Size() / 2 - 1; i >= 0; i--) {
			SiftDown(i);
		}
	}
 public:
	Heap(const Vector<Type>& vec, 
		    std::function<bool(const Type&, const Type&)> compare 
		    = [](const Type& left, const Type& right) {
		        return left < right;
	        }
	    )
		: vec(vec)
		, compare(compare)
	{
		MakeHeap();
	}
	~Heap() {}
	Type PopMax() { // извлекает максимум и удаляет
		assert(!vec.IsEmpty());
		Type res = vec[0];
		Type last = vec.PopBack();
		if (!vec.IsEmpty()) {
			vec[0] = last;
			SiftDown(0);
		}
		return res;
	}
	Type GetMax() const {
		assert(!vec.IsEmpty());
		return vec[0];
	}
	void Set(int elem) {
		vec.PushBack(elem);
		SiftUp(vec.Size() - 1);
	}
	bool IsEmpty() const {
		return vec.IsEmpty();
	}
};

Vector<int> InitHeap(int size) {
	Vector<int> vec(size);
	std::cin >> vec;
	return vec;
}

void Run() {
	int num(0);
	std::cin >> num;
	assert(num);
	Heap<int> elems(InitHeap(num));
	int power(0);
	std::cin >> power;
	assert(power);
	int num_rise(0);
	while (!elems.IsEmpty()) {
		Vector<int> remainders; // остатки с захода
		for (int rais = 0;
			!elems.IsEmpty() && rais < power;) {
			int curr_elem = elems.GetMax();
			if (curr_elem + rais > power) {
				break;
			}
			rais += elems.PopMax();
			int remainder = curr_elem / 2;
			if (remainder) {
				remainders.PushBack(remainder);
			}
		}
		for (int i = 0; i < remainders.Size(); i++) { // кладем обратно
			elems.Set(remainders[i]);
		}
		num_rise++;
	}
	std::cout << num_rise;
}

int main() {
	Run();
	return 0;
}
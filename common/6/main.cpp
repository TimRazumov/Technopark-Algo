#include <iostream>
#include <cassert>
#include <random>
#include <functional>

/*

Task 6.4.

Реализуйте стратегию выбора опорного элемента “случайный элемент”.
Функцию Partition реализуйте методом прохода двумя итераторами от конца массива к началу.

*/

template <class Type>
class Vector {
private:
	int size;
	int capacity;
	Type* elems;
	void Copy(const Type* elems_from) {
		for (int i = 0; i < size; i++) {
			elems[i] = elems_from[i];
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
	void PushBack(const Type& elem) {
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
		for (int i = 0; i < vec.size; i++) {
			input >> vec.elems[i];
		}
		return input;
	}
	friend
	std::ostream& operator<<(std::ostream& output, const Vector<Type>& vec) {
		for (int i = 0; i < vec.size; i++) {
			output << vec.elems[i] << " ";
		}
		return output;
	}
};

int GetRandomElem(int idx_lower, int idx_upper) {  // интервал [idx_lower, idx_upper]
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(idx_lower, idx_upper);
	return dis(gen);
}

template <class Type>
int Partition(Vector<Type>& vec, int idx_lower, int idx_upper,  // интервал [idx_lower, idx_upper)
	std::function<bool(const Type&, const Type&)> compare =
	[](const Type& left, const Type& right) {
	return left < right;
})
{
	int idx_sup_elem = GetRandomElem(idx_lower, idx_upper - 1);
	Type sup_elem = vec[idx_sup_elem];
	std::swap(vec[idx_lower], vec[idx_sup_elem]); // ставим опорный элемент в первую позицию
	int i = idx_upper - 1;
	for (int j = idx_upper - 1; j > idx_lower; j--) {
		if (!compare(vec[j], sup_elem)) {
			std::swap(vec[i], vec[j]);
			i--;
		}
	}
	std::swap(vec[i], vec[idx_lower]);
	return i;
}

template <class Type>
int GetOrdStat(Vector<Type> vec, const int idx_ord , 
	    std::function<bool(const Type&, const Type&)> compare =
	        [](const Type& left, const Type& right) {
	            return left < right;
            }) 
{
	assert(idx_ord < vec.Size());
	int idx_lower(0), idx_upper(vec.Size());
	int idx_res(0);
	while (true) {
		idx_res = Partition(vec, idx_lower, idx_upper, compare);
		if (idx_ord == idx_res) {
			break;
		}
		else if (idx_ord < idx_res) {
			idx_upper = idx_res;
		}
		else {
			idx_lower = idx_res + 1;
		}
	}
	return vec[idx_res];
}

int main() {
	int size(0), ord_stat(0);
	std::cin >> size >> ord_stat;
	assert(size > 0 && ord_stat >= 0);
	Vector<int> vec(size);
	std::cin >> vec;
	std::cout << GetOrdStat(vec, ord_stat);
	return 0;
}
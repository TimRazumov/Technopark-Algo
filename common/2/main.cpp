#include <iostream>
#include <sstream>
#include <cassert>

/*

Task 2.3.

Даны два массива неповторяющихся целых чисел, упорядоченные по возрастанию.
A[0..n - 1] и B[0..m - 1].n >> m. Найдите их пересечение.
Требования: Время работы : O(m * log k),
где k - позиция элемента B[m - 1] в массиве A.
В процессе поиска очередного элемента B[i] в массиве A пользуйтесь
результатом поиска элемента B[i - 1].
Внимание! В этой задаче для каждого B[i] сначала нужно определить
диапазон для бинарного поиска размером порядка k, а потом уже в нем делать бинарный поиск.

*/

class Vector {
private:
	size_t size;
	int* elems;
public:
	Vector(size_t sz)
		: size(sz)
		, elems(new int[sz])
	{}
	~Vector() {
		delete[] elems;
	}
	friend
	std::istream& operator>>(std::istream& input, Vector& vec) {
		for (size_t i = 0; i < vec.size; i++) {
			input >> vec.elems[i];
		}
		return input;
	}
	friend
	std::ostream& operator<<(std::ostream& output, const Vector& vec) {
		for (size_t i = 0; i < vec.size; i++) {
			output << vec.elems[i] << " ";
		}
		return output;
	}
	int BinarySearch(int search_elem, size_t lower_idx = 0,
		size_t upper_idx = -1) const {
		if (upper_idx > size) {
			upper_idx = size;
		}
		size_t search_idx = lower_idx, last = upper_idx;
		while (search_idx < last) {
			size_t mid = (search_idx + last) / 2;
			if (elems[mid] < search_elem) {
				search_idx = mid + 1;
			}
			else {
				last = mid;
			}
		}
		return (search_idx == upper_idx // вышли за границу диапозона
			|| elems[search_idx] != search_elem) ? -1 : search_idx;
	}
	void Intersection(const Vector& vec, std::ostream& output) const {
		size_t lower_idx = 0, upper_idx = 2; // начальное приближение диапозона
		for (size_t i = 0; i < vec.size; i++) {
			while (elems[upper_idx] <= vec.elems[i]) {
				upper_idx *= 2;
				if (upper_idx > size) {
					upper_idx = size;
					break;
				}
			}
			int search_idx = BinarySearch(vec.elems[i], lower_idx, upper_idx);
			if (search_idx != -1) {
				output << vec.elems[i] << " ";
				lower_idx = search_idx + 1;
			}
		}
	}
};


int main() {
	size_t n(0), m(0);
	std::cin >> n >> m;
	assert(n && m);
	Vector a(n), b(m);
	std::cin >> a >> b;
	a.Intersection(b, std::cout);
	std::cin.get();
	std::cin.get();
	return 0;
}
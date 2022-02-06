#include <iostream>
#include <sstream>
#include <cassert>

/*

Task 2.3.

���� ��� ������� ��������������� ����� �����, ������������� �� �����������.
A[0..n - 1] � B[0..m - 1].n >> m. ������� �� �����������.
����������: ����� ������ : O(m * log k),
��� k - ������� �������� B[m - 1] � ������� A.
� �������� ������ ���������� �������� B[i] � ������� A �����������
����������� ������ �������� B[i - 1].
��������! � ���� ������ ��� ������� B[i] ������� ����� ����������
�������� ��� ��������� ������ �������� ������� k, � ����� ��� � ��� ������ �������� �����.

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
		return (search_idx == upper_idx // ����� �� ������� ���������
			|| elems[search_idx] != search_elem) ? -1 : search_idx;
	}
	void Intersection(const Vector& vec, std::ostream& output) const {
		size_t lower_idx = 0, upper_idx = 2; // ��������� ����������� ���������
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
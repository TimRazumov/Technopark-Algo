#include <iostream>
#include <cassert>
#include <functional>

/*

Task 5.2.

�� ���� ������� ������� ������� ���������� ����������� � ������������ ���������� ��������.
������� ������ ������������ �������� ������� ��������� �������.
����� ����� ������ ��������� O(n log n).

������������.

������ ����� ���������� �������������� ���� ��� ����� ������, ����� ��� ����� ��������� ������. 
��� ����� � ���� ������ ������� �� ��� ������ ����  ��� ����������� 18 ���, �� ��� �� ����������� 80 ���.
��� ������ ����� ������� �����. ���������� �������� ������������ ���������� �������������. 
� ���� 18-����� ������� ��� ����� ��������� ������� � ���������, � � ���� 80-����� � � ���� ������ ��� �� �����.
���������. ������� ��� �� ������ �� 18-�����, ���� ������� � ���� 18-�����. 
� ���� ������� ��������� ������� � ��������� �� �� ���.

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
	Type PopBack() { // ��������� ��������� ������� � �������
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

template <class Type>
void Merge(Vector<Type>& vec, int lower_bound_left, int upper_bound_left, int upper_bound_right, 
	std::function<bool(const Type&, const Type&)> compare = 
	    [](const Type& left, const Type& right) {
	        return left < right;
        }) 
{
	int size = upper_bound_right - lower_bound_left;
	Vector<Type> tmp(size);
	int i = lower_bound_left, j = upper_bound_left, idx = 0;
	while (idx < size) {
		if (i == upper_bound_left || (j < upper_bound_right && compare(vec[j], vec[i]))) {
			tmp[idx++] = vec[j++];
		} else {
			tmp[idx++] = vec[i++];
		}
	}
	for (int k = 0; k < size; k++) {
		vec[k + lower_bound_left] = tmp[k];
	}
}

template <class Type>
void MergeSort(Vector<Type>& vec, std::function<bool(const Type&, const Type&)> compare =
	             [](const Type& left, const Type& right) {
	                 return left < right;
                 }, int lower_bound = 0, int upper_bound = -1)
{
	if (upper_bound < 0) {
		upper_bound = vec.Size();
	}
	int size = upper_bound - lower_bound;
	if (size <= 1) {
		return;
	}
	int size_left = size / 2;
	int size_right = size - size_left;
	int upper_bound_left = lower_bound + size_left;
	int upper_bound_right = upper_bound_left + size_right;
	MergeSort(vec, compare, lower_bound, upper_bound_left);
	MergeSort(vec, compare, upper_bound_left, upper_bound_right);
	Merge(vec, lower_bound, upper_bound_left, upper_bound_right, compare);
}

struct Date {
	bool life;
	size_t day;
	size_t month;
	int year;
	Date(bool life = false, size_t day = 0, size_t month = 0, size_t year = 0)
		: life(life)
		, day(day)
		, month(month)
		, year(year)

	{}
	bool operator<(const Date& date) {
		if (year < date.year) {
			return true;
		} else if (year == date.year) {
			if (month < date.month) {
				return true;
			} else if (month == date.month) {
				if (day < date.day) {
					return true;
				} else if (day == date.day) {
					if (life < date.life) {
						return true;
					}
				}
			}
		}
		return false;
	}
	friend
	std::istream& operator>>(std::istream& input, Date& date) {
		input >> date.day >> date.month >> date.year;
		return input;
	}
	friend
	std::ostream& operator<<(std::ostream& output, const Date& date) {
		output << date.day << " " << date.month << " " << date.year;
		return output;
	}
};


int Count(const Vector<Date>& vec) {
	int max = 0;
	for (int i = 0, num = 0; i < vec.Size(); i++) {
		if (vec[i].life) {
			num++;
			if (num > max) {
				max = num;
			}
		} else {
			num--;
		}
	}
	return max;
}

void Run() {
	size_t num_people = 0;
	std::cin >> num_people;
	assert(num_people);
	size_t adulthood = 18, old = 80;
	Vector<Date> dates;
	for (size_t i = 0; i < num_people; i++) {
		Date birth(true), dead(false);
		std::cin >> birth >> dead;
		if (dead.year - birth.year > old) {
			dead.day = birth.day;
			dead.month = birth.month;
			dead.year = birth.year + old;
		} // ������� �� ��������������� � ����� 80-�� �� ���������
		birth.year += adulthood;
		if (birth < dead) {
			dates.PushBack(birth);
			dates.PushBack(dead);
		}
	}
	MergeSort<Date>(dates,
		[](const Date& left, const Date& right) {
		    if (left.year < right.year) {
			    return true;
		    } else if (left.year == right.year) {
			    if (left.month < right.month) {
				    return true;
			    } else if (left.month == right.month) {
			        if (left.day < right.day) {
					    return true;
			        } else if (left.day == right.day) {
				        if (left.life < right.life) {
					        return true;
				        }
			        }
			    }
		    }
		    return false;
	    });
	std::cout << Count(dates);
}


int main() {
	Run();
	return 0;
}
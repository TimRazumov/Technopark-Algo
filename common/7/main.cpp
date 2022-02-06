#include <iostream>
#include <cassert>
#include <string>

#define ALPHABET_SIZE 256

/*

Task 7.1.

Дан массив строк. Количество строк не больше 105.
Отсортировать массив методом поразрядной сортировки MSD по символам.
Размер алфавита - 256 символов. Последний символ строки = ‘\0’.

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
	Vector<Type>& operator=(const Vector<Type>& vec) {
		size = vec.size;
		if (vec.size > capacity) {
			delete[] elems;
			elems = new Type[vec.capacity];
			capacity = vec.capacity;
		}
		Copy(vec.elems);
		return *this;
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
};

Vector<int> Counting(Vector<Vector<char>>& words, int lower_idx,
	int upper_idx, int pos_in_str = 0) { // интервал [lower_idx, int upper_idx) 
	Vector<int> count(ALPHABET_SIZE + 1);
	for (int i = 0; i < count.Size(); i++) { // считаем кол-во вхождений каждой буквы
		count[i] = 0;
	}
	for (int i = lower_idx; i < upper_idx; i++) {
		// std::cout << " i = " << i << " pos_in_str = " << pos_in_str;
		count[words[i][pos_in_str]]++;
	}
	int sum = 0;
	for (int i = 0; i < count.Size(); i++) { // вычисление границ групп элементов
		int tmp = count[i];
		count[i] = sum;
		sum += tmp;
	}
	Vector<Vector<char>> res(upper_idx - lower_idx);
	for (int i = 0; i < res.Size(); i++) { // сортировка
		int& j = count[words[i + lower_idx][pos_in_str]];
		res[j] = words[i + lower_idx];
		j++;
	}
	for (int i = 0; i < res.Size(); i++) {
		words[i + lower_idx] = res[i];
	}
	return count;
}

void MDSSortWords(Vector<Vector<char>>& words, int lower_idx,
	int upper_idx, int pos_in_str = 0) { // интервал [lower_idx, int upper_idx)
	auto intervals = Counting(words, lower_idx, upper_idx, pos_in_str);
	for (int i = 0; i < intervals.Size() - 1; i++) {
		int group_sz = intervals[i + 1] - intervals[i];
		if (group_sz > 1) {
			lower_idx += intervals[i];
			MDSSortWords(words, lower_idx, lower_idx + group_sz, pos_in_str + 1);
		}
	}
}

int main() {
	std::string str;
	Vector<Vector<char>> words;
	while (std::cin >> str) {
		Vector<char> word;
		for (size_t i = 0; i < str.length(); i++) {
			word.PushBack(str[i]);
		}
		word.PushBack('\0');
		words.PushBack(word);
	}
	MDSSortWords(words, 0, words.Size());
	for (int i = 0; i < words.Size(); i++) {
		for (int j = 0; j < words[i].Size() - 1; j++) {
			std::cout << words[i][j];
		}
		std::cout << std::endl;
	}
	return 0;
};
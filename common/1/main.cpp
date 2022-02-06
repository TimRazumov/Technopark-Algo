#include <iostream>
#include <cassert>

/*

Task 1.4.

“Считалочка”.В круг выстроено N человек, пронумерованных числами от 1 до N.
Будем исключать каждого k - ого до тех пор, пока не уцелеет только один человек. 
(Например, если N = 10, k = 3, то сначала умрет 3 - й, потом 6 - й, 
	затем 9 - й, затем 2 - й, затем 7 - й, 
	потом 1 - й, потом 8 - й, за ним - 5 - й, 
	и потом 10 - й.Таким образом, уцелеет 4 - й.) 
Необходимо определить номер уцелевшего. N, k ? 10000.
Требования:  Решить перебором.

*/


class ListPeople {
 private:
	struct Node {
		size_t value;
		Node* next;
		Node(size_t val = 0) : value(val), next(nullptr) 
		{};
	};
	Node* head;
	Node* tail;
 public:
	 ListPeople(const size_t& num_people) 
		 : head(nullptr)
		 , tail(nullptr)
	 {
		 if (num_people) {
			 head = new Node(1);
			 tail = head;
			 for (size_t i = 2; i <= num_people; i++) {
				 tail->next = new Node(i);
				 tail = tail->next;
			 }
			 tail->next = head; // закольцованный список
		 }
	 };
	 ~ListPeople() {
		 Counting(1);
		 delete tail;  
	 };
	 size_t Counting(const size_t& freq) { // "считалочка"
		 Node* prev = tail;
		 Node* curr = head;
		 while (prev != curr) {
			 for (size_t i = 1; i < freq; i++)
			 {
				 prev = curr;
				 curr = curr->next;
			 }
			 prev->next = curr->next;
			 delete curr;
			 curr = prev->next;
		 }
		 head = curr;
		 tail = curr;
		 return head->value;
	 };
};

int main() {
	size_t num_people(0); // количество человек
	std::cin >> num_people;
	assert(num_people); // num_people == 0
	ListPeople list(num_people);
	size_t freq(0); // частота пересчета
	std::cin >> freq;
	assert(freq);
	std::cout << list.Counting(freq);
	return 0;
}
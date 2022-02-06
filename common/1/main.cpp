#include <iostream>
#include <cassert>

/*

Task 1.4.

������������.� ���� ��������� N �������, ��������������� ������� �� 1 �� N.
����� ��������� ������� k - ��� �� ��� ���, ���� �� ������� ������ ���� �������. 
(��������, ���� N = 10, k = 3, �� ������� ����� 3 - �, ����� 6 - �, 
	����� 9 - �, ����� 2 - �, ����� 7 - �, 
	����� 1 - �, ����� 8 - �, �� ��� - 5 - �, 
	� ����� 10 - �.����� �������, ������� 4 - �.) 
���������� ���������� ����� ����������. N, k ? 10000.
����������:  ������ ���������.

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
			 tail->next = head; // �������������� ������
		 }
	 };
	 ~ListPeople() {
		 Counting(1);
		 delete tail;  
	 };
	 size_t Counting(const size_t& freq) { // "����������"
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
	size_t num_people(0); // ���������� �������
	std::cin >> num_people;
	assert(num_people); // num_people == 0
	ListPeople list(num_people);
	size_t freq(0); // ������� ���������
	std::cin >> freq;
	assert(freq);
	std::cout << list.Counting(freq);
	return 0;
}
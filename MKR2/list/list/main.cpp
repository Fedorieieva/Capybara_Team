#include <iostream>

using namespace std;

/*Create a template class (collection) List for working with a singly linked list.
Define several constructors (including a default constructor that creates an 
empty list), methods for accessing the first and last element of the array, 
a print method, and possibly other methods. For the list of strings, provide
their lexicographic sorting. Write a program that demonstrates the use of this 
template for lists of integers and strings. The program should create two arrays 
of List class objects (one for each type) and pass each of them to an external 
function that performs the reversal of each element of the array (list), i.e., 
the reversal of pointers in the list in reverse order. For the resulting array 
of string lists (reversed), perform lexicographic ordering of their elements
(strings). The program should provide a visual display of all input, output, 
and intermediate data, as well as control of possible errors. Use exception 
handling to process errors (including incorrect data entry).*/

/*Створити шаблонний клас (колекцію) List для роботи з 
однозв'язним списком.Визначити у ньому декілька конструкторів 
(у тому числі конструктор за замовчуванням, який створюе порожній список),
методи звертання до першого та останнього елемента масиву, метод виведення, 
можливо інші методи. Для списку рядків передбачити їх лексикографічне 
сортування.Написати програму, що демонструє роботу з цим  шаблоном для 
списків цілих чисел і рядків. У програмі передбачити створення двох 
масивів об'єктів класу List(по одному кожного виду) і передачу 
кожного з них (масивів) у зовнішню функцію, яка виконує перевертання
кожного елемента масиву (списку), тобто, перевстановлення покажчиків у 
списку в зворотному порядку. Для отриманого масиву списків - 
рядків(перевернутих) виконати лексикографічне упорядкування 
їх елементів(рядків). Програма повинна забезпечувати наочне виведення 
усіх вхідних, вихідних та проміжних даних, а також контроль можливих помилок.
Для обробки помилок (у тому числі і не коректного введення даних) використати 
виключні ситуації.*/

template<typename T>
class Node {
public:
	T data;
	Node* next;

	Node() {
		data = 0;
		next = NULL;
	}

	Node(T d) : Node() {
		data = d;
	}
};

template<typename T>
class List {
	Node<T>* head;

public:
	List() { head = NULL; }

	void push(T val) {
		Node* new_node = new Node(val);

		if (head == NULL) {
			head = new_node;
			return;
		}

		Node* temp = head;
		while (temp->next != NULL) {
			temp = temp->next;
		}

		temp->next = new_node;
	}

	void delete_node(T idx) {
		Node* temp1 = head;
		Node* temp2 = NULL;

		int size = 0;

		if (head == NULL) {
			cout << "List is empty" << endl;
			return;
		}

		while (temp1 != NULL) {
			temp1 = temp1->next;
			size++;
		}

		if (size < idx) {
			cout << "index out of range" << endl;
			return;
		}

		temp1 = head;

		if (idx == 1) {
			head = head->next;
			delete temp1;
			return;
		}

		while (idx-- > 1) {
			temp2 = temp1;
			temp1 = temp1->next;
		}

		temp2->next = temp1->next;

		delete temp1;
	}

	void print() {
		Node* temp = head;

		if (head == NULL) {
			cout << "List is empty" << endl;
			return;
		}

		while (temp != NULL) {
			cout << temp->data << " ";
			temp = temp->next;
		}
	}
};

template<typename T>
Node<T>* reverse_linked_list(Node<T>* head) {
	if (head == NULL) {
		return NULL;
	}

	if (head->next == NULL) {
		return head;
	}

	Node<T>* temp1 = head->next;
	Node<T>* temp2 = reverse_linked_list(temp1);
	Node<T>* temp3 = temp2;

	while (temp3->next != NULL) {
		temp3 = temp3->next;
	}

	temp3->next = head;

	head->next = NULL;

	return temp2;
}
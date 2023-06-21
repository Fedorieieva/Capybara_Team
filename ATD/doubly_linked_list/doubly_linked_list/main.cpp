#include <iostream>
#include <stdexcept>

using namespace std;

class DoublyLinkedList {
	class Node {
	public:
		int data;
		Node* next;
		Node* prev;

		Node(int d) {
			data = d;
			next = nullptr;
			prev = nullptr;
		}
	};

	Node* head;
	Node* tail;
	int size;

public:
	class Iterator {
		Node* current;

	public:
		Iterator(Node* n) { current = n; }

		int& operator*() const {
			return current->data;
		}

		Iterator& operator++() {
			if (current != nullptr) {
				current = current->next;
			}
			return *this;
		}

		Iterator& operator--() {
			if (current != nullptr) {
				current = current->prev;
			}
			return *this;
		}

		bool operator!=(const Iterator& other) {
			return current != other.current;
		}
	};

	DoublyLinkedList() {
		size = 0;
		head = nullptr;
		tail = nullptr;
	}

	~DoublyLinkedList() { clear(); }

	void append(int& d) {
		Node* new_node = new Node(d);

		if (head == nullptr) {
			head = new_node;
			tail = new_node;
		}
		else {
			tail->next = new_node;
			new_node->prev = tail;
			tail = new_node;
		}

		size++;
	}

	void preappend(int& d) {
		Node* new_node = new Node(d);

		if (head == nullptr) {
			head = new_node;
			tail = new_node;
		}
		else {
			new_node->next = head;
			head->prev = new_node;
			head = new_node;
		}

		size++;
	}

	void remove(int& idx) {
		if (idx < 0 || idx >= size) {
			throw out_of_range("Index out of bound.");
		}

		Node* current = head;
		for (int i = 0; i < idx; i++) {
			current = current->next;
		}

		if (current == head) {
			head = head->next;
		}
		else if (current == tail) {
			tail = tail->prev;
		}
		else {
			current->prev->next = current->next;
			current->next->prev = current->prev;
		}

		delete current;
		size--;
	}

	int get(int& idx) {
		if (idx < 0 || idx >= size) {
			throw out_of_range("Index out of bound.");
		}

		Node* current = head;
		for (int i = 0; i < idx; i++) {
			current = current->next;
		}

		return current->data;
	}

	int length() { return size; }

	void clear() {
		Node* current = head;

		while (current) {
			Node* temp = current->next;
			delete current;
			current = temp;
		}

		size = 0;
		head = nullptr;
		tail = nullptr;
	}

	void print() {
		if (head == nullptr) {
			throw out_of_range("List is empty");
		}

		for (Iterator it = begin(); it != end(); ++it) {
			cout << *it << " ";
		}
		cout << endl;
	}

	void reverse_print() {
		if (head == nullptr) {
			throw out_of_range("List is empty");
		}

		Iterator it(tail);
		while (it != end()) {
			cout << *it << " ";
			--it;
		}
		cout << endl;
	}

	Iterator begin() {
		return Iterator(head);
	}

	Iterator end() {
		return Iterator(nullptr);
	}
};

int main() {
	try {
		DoublyLinkedList l;
		int size, num;

		cout << "Enter size of the list: ";
		cin >> size;

		if (cin.fail() || size <= 0) {
			throw runtime_error("Expected an int number grater than zero.");
		}

		cout << "Enter elements: " << endl;
		for (int i = 0; i < size; i++) {
			cin >> num;
			if (cin.fail() || size <= 0) {
				throw runtime_error("Expected an int number.");
			}
			l.append(num);
		}

		cout << endl << "Here you can see your list:" << endl;
		l.print();

		cout << "Enter idx to remove element: ";
		cin >> num;

		if (cin.fail() || num < 0) {
			throw runtime_error("Expected an int number grater or equal to zero.");
		}

		l.remove(num);

		cout << endl << "Here you can see your list after deleting an element:" << endl;
		l.print();

		cout << endl << "Reverse print:" << endl;
		l.reverse_print();
	}
	catch (exception& e) {
		cerr << "An exception occured: " << e.what() << endl;
	}

	return 0;
}
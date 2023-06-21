#include <iostream>
#include <stdexcept>

using namespace std;

class CircularDoublyLinkedList {
	class Node {
	public:
		int data;
		Node* prev;
		Node* next;

		Node(int d) {
			data = d;
			prev = nullptr;
			next = nullptr;
		}
	};

	Node* head;
	int size;

public:
	class Iterator{
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

		bool operator !=(const Iterator& other) {
			return current != other.current;
		}
	};

	CircularDoublyLinkedList() {
		size = 0;
		head = nullptr;
	}

	~CircularDoublyLinkedList() { clear(); }

	void append(int& d) {
		Node* new_node = new Node(d);

		if (head == nullptr) {
			head = new_node;
			head->next = head;
			head->prev = head;
		}
		else {
			Node* tail = head->prev;
			tail->next = new_node;
			new_node->prev = tail;
			new_node->next = head;
			head->prev = new_node;
		}

		size++;
	}

	void remove(int& idx) {
		if (idx < 0 || idx >= size) {
			throw out_of_range("Idx out of bound.");
		}

		if (size == 1) {
			delete head;
			head = nullptr;
		}
		else {
			Node* current = head;
			for (int i = 0; i < idx; i++) {
				current = current->next;
			}

			if (current == head) {
				head = head->next;
			}

			Node* prev_node = current->prev;
			Node* next_node = current->next;

			prev_node->next = next_node;
			next_node->prev = prev_node;

			delete current;
		}
	}

	int get(int& idx) {
		if (idx < 0 || idx >= size) {
			throw out_of_range("Idx out of bound.");
		}

		Node* current = head;
		for (int i = 0; i < idx; i++) {
			current = current->next;
		}

		return current->data;
	}

	int length() { return size; }

	void print() {
		if (head == nullptr) {
			throw out_of_range("List is empty.");
		}

		Node* current = head;

		do {
			cout << current->data << " ";
			current = current->next;
		} while (current != head);

		cout << endl;
	}

	void clear() {
		Node* current = head;

		while (current) {
			Node* temp = current->next;
			delete current;
			current = temp;

			if (current == head) {
				break;
			}
		}

		size = 0;
		head = nullptr;
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
		CircularDoublyLinkedList l;
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
	}
	catch (exception& e) {
		cerr << "An exception occured: " << e.what() << endl;
	}

	return 0;
}
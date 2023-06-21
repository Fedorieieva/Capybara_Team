#include <iostream>
#include <stdexcept>
#include <fstream>

using namespace std;

class CircularLinkedList {
	class Node {
	public:
		int data;
		Node* next;

		Node(int d) {
			data = d;
			next = nullptr;
		}
	};

	Node* head;
	Node* tail;

public:
	class Iterator {
		Node* current;

	public:
		Iterator(Node* n) { current = n; }

		int& operator*() const {
			return current->data;
		}

		Iterator& operator++() {
			current = current->next;
			return *this;
		}

		bool operator!=(const Iterator& other) {
			return current != other.current;
		}
	};

	CircularLinkedList() {
		head = nullptr;
		tail = nullptr;
	}

	~CircularLinkedList() { clear(); }

	void append(int d) {
		Node* new_node = new Node(d);

		if (head == nullptr) {
			head = new_node;
			tail = new_node;
			new_node->next = head;
		}
		else {
			tail->next = new_node;
			tail = new_node;
			tail->next = head;
		}
	}

	void print() {
		if (head == nullptr) {
			cout << "List is empty" << endl;
			return;
		}

		Node* current = head;
		do {
			cout << current->data << " ";
			current = current->next;
		} while (current != head);

		cout << endl;
	}

	bool empty() { return head == nullptr; }

	void clear() {
		if (head == nullptr) {
			return;
		}

		Node* current = head;
		while (current != tail) {
			Node* temp = current->next;
			delete current;
			current = temp;
		}

		delete tail;
		head = nullptr;
		tail = nullptr;
	}

	void erase(int& idx) {
		if (head == nullptr) {
			return;
		}
		else if (idx == 0) {
			Node* remove = head;
			head = head->next;
			tail->next = head;
			delete remove;
			return;
		}

		Node* current = head;
		Node* prev = nullptr;
		int current_idx = 0;

		while (current != tail && current_idx != idx) {
			prev = current; 
			current = current->next;
			current_idx++;
		}

		if (current_idx == idx) {
			prev->next = current->next;

			if (current == tail) {
				tail = prev;
			}

			delete current;
		}
	}

	void save_to_file() {
		ofstream file("circular_list");
		if (!file.is_open()) {
			throw runtime_error("Error opening file");
		}

		if (head == nullptr) {
			file << "List is empty" << endl;
			return;
		}

		Node* current = head;
		do {
			file << current->data << " ";
			current = current->next;
		} while (current != head);

		file << endl;
	}

	Iterator begin() {
		return Iterator(head);
	}

	Iterator end() {
		return Iterator(tail->next);
	}
};

int main() {
	try {
		CircularLinkedList l;
		int size, num;

		cout << "Enter size of the list: ";
		cin >> size;

		if (cin.fail() || size <= 0) {
			throw runtime_error("Expected an int number grater than zero.");
		}

		cout << "Enter elements for the list:" << endl;
		for (int i = 0; i < size; i++) {
			cin >> num;

			if (cin.fail()) {
				throw runtime_error("Expected an int number.");
			}

			l.append(num);
		}

		cout << "Original List: ";
		l.print();
		l.save_to_file();

		cout << "Iterating over the list: " << endl;
		for (auto it = l.begin(); it != l.end(); ++it) {
			cout << *it << " ";
		}
		cout << endl;

		cout << "Is the list empty? " << (l.empty() ? "Yes" : "No") << endl;

		cout << "Enter idx to delete element: ";
		cin >> num;

		l.erase(num);

		cout << "Updated List: ";
		l.print();

		l.clear();

		cout << "Is the list empty? " << (l.empty() ? "Yes" : "No") << endl;
	}
	catch (exception& e) {
		cerr << "Ann error occured: " << e.what() << endl;
	}
	return 0;
}

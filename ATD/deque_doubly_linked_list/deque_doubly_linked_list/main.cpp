#include <iostream>
#include <stdexcept>

using namespace std;

class Deque {
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

	Node* front;
	Node* rear;
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

		bool operator==(const Iterator& other) {
			return current == other.current;
		}
	};

	Deque() {
		size = 0;
		front = nullptr;
		rear = nullptr;
	}

	~Deque() { clear(); }

	bool empty() { return front == nullptr; }

	int length() { return size; }

	void push_front(int d) {
		Node* new_node = new Node(d);

		if (empty()) {
			front = new_node;
			rear = new_node;
		}
		else {
			new_node->next = front;
			front->prev = new_node;
			front = new_node;
		}

		size++;
	}

	void push_back(int d) {
		Node* new_node = new Node(d);

		if (empty()) {
			front = new_node;
			rear = new_node;
		}
		else {
			new_node->prev = rear;
			rear->next = new_node;
			rear = new_node;
		}

		size++;
	}

	int pop_front() {
		if (empty()) {
			throw runtime_error("Deque is empty");
		}

		int d = front->data;
		Node* temp = front;

		if (front == rear) {
			front = nullptr;
			rear = nullptr;
		}
		else {
			front = front->next;
			if (front != nullptr) {
				front->prev = nullptr;
			}
			else {
				rear = nullptr;
			}
		}

		delete temp;
		size--;
		return d;
	}

	int pop_back() {
		if (empty()) {
			throw runtime_error("Deque is empty");
		}

		int d = rear->data;
		Node* temp = rear;

		if (front == rear) {
			front = nullptr;
			rear = nullptr;
		}
		else {
			rear = rear->prev;
			if (rear != nullptr) {
				rear->next = nullptr;
			}
			else {
				front = nullptr;
			}
		}

		delete temp;
		size--;
		return d;
	}

	int get_front() {
		if (empty()) {
			throw runtime_error("Deque is empty");
		}

		return front->data;
	}

	int get_back() {
		if (empty()) {
			throw runtime_error("Deque is empty");
		}

		return rear->data;
	}

	void clear() {
		Node* current = front;

		while (current) {
			Node* temp = current->next;
			delete current;
			current = temp;
		}

		front = nullptr;
		rear = nullptr;
		size = 0;
	}

	void print() {
		if (front == nullptr) {
			throw out_of_range("List is empty");
		}

		for (Iterator it = begin(); it != end(); ++it) {
			cout << *it << " ";
		}
		cout << endl;
	}

	void reverse_print() {
		if (rear == nullptr) {
			throw out_of_range("Deque is empty");
		}

		Iterator it(rear);
		while (true) {
			cout << *it << " ";
			if (it == begin()) {
				break;
			}
			--it;
		}
		cout << endl;
	}

	Iterator begin() {
		return Iterator(front);
	}

	Iterator end() {
		return Iterator(nullptr);
	}
};

int main() {
	try {
		Deque deque;
		int size, num;

		cout << "Enter deque size: ";
		cin >> size;

		if (cin.fail() || size <= 0) {
			throw runtime_error("An int number grater than zero is expected");
		}

		cout << "Enter elements:" << endl;
		for (int i = 0; i < size; i++) {
			cin >> num;

			if (cin.fail() || size <= 0) {
				throw runtime_error("An int number grater than zero is expected");
			}

			deque.push_back(num);
		}

		cout << "Deque elements: ";
		deque.print();

		cout << "Reverse Deque elements: ";
		deque.reverse_print();

		cout << "Deque length: " << deque.length() << endl;

		cout << "Front element: " << deque.get_front() << endl;
		cout << "Back element: " << deque.get_back() << endl;

		deque.pop_front();
		deque.pop_back();

		cout << "Deque elements after pop: ";
		deque.print();
	}
	catch (exception& e) {
		cerr << "An exception occured: " << e.what() << endl;
	}

	return 0;
}
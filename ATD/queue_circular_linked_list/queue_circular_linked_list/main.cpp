#include <iostream>
#include <stdexcept>

using namespace std;

class Queue {
	class Node {
	public:
		int data;
		Node* next;

		Node(int d) {
			data = d;
			next = nullptr;
		}
	};

	Node* rear;
	int count;

public:
	class Iterator {
		Node* current;

	public:
		Iterator(Node* node) : current(node) {}

		int& operator*() const {
			return current->data;
		}

		Iterator& operator++() {
			current = current->next;
			return *this;
		}

		bool operator!=(const Iterator& other) const {
			return current != other.current;
		}
	};

	Queue() { rear = nullptr; count = 0; }

	~Queue() { clear(); }

	void enqueue(int& d) {
		Node* new_node = new Node(d);

		if (rear == nullptr) {
			rear = new_node;
			rear->next = rear;
		}
		else {
			new_node->next = rear->next;
			rear->next = new_node;
			rear = new_node;
		}

		count++;
	}

	int size() { return count; }

	int dequeue() {
		if (empty()) {
			throw runtime_error("Queue is empty.");
		}

		int val;
		Node* front = rear->next;
		val = front->data;

		if (front == rear) {
			rear = nullptr;
		}
		else {
			rear->next = front->next;
		}

		delete front;
		count--;
		return val;
	}

	int front() { return rear->next->data; }

	bool empty() { return  rear == nullptr; }

	void clear() {
		while (!empty()) {
			dequeue();
		}
	}

	Iterator begin() const {
		return rear == nullptr ? Iterator(nullptr) : Iterator(rear->next);
	}

	Iterator end() const {
		return Iterator(nullptr);
	}
};

int main() {
	try {
		Queue q;
		int size, num;

		cout << "Enter number of elements of the queue: ";
		cin >> size;
		if (cin.fail()) {
			throw runtime_error("Expected an int number grater than zero.");
		}


		cout << "Enter elements for the queue: " << endl;
		for (int i = 0; i < size; i++) {
			cin >> num;
			if (cin.fail()) {
				throw runtime_error("Expected an int number.");
			}

			q.enqueue(num);
		}

		cout << "Size: " << q.size() << endl;
		cout << "front element: " << q.front() << endl;

		q.dequeue();

		cout << "new size: " << q.size() << endl;
		cout << "new front element: " << q.front() << endl;

	}
	catch (exception& e) {
		cerr << "An error has occured: " << e.what() << endl;
	}
	return 0;
}
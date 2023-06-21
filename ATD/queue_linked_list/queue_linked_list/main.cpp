#include <iostream>
#include <stdexcept>

using namespace std;

class Queue {
	class Node {
	public:
		Node* next;
		int data;

		Node(int val) {
			data = val;
			next = nullptr;
		}
	};

	Node* head;
	int count;

public:
	Queue() { head = nullptr; count = 0; }

	~Queue(){
		for (int i = 0; i < count; i++) {
			dequeue();
		}
	}

	void enqueue(int& val) {
		Node* new_node = new Node(val);
		if (head == nullptr) {
			head = new_node;
		}
		else {
			Node* current = head;
			while (current->next) {
				current = current->next;
			}
			current->next = new_node;
		}
		count++;
	}

	void dequeue() {
		if (head == nullptr) {
			throw out_of_range("Queue is empty");
		}
		else {
			Node* temp = head;
			head = head->next;
			delete temp;
			count--;
		}
	}

	int size() { return count; }

	int front() const {
		if (head == nullptr) {
			throw out_of_range("Queue is empty");
		}

		return head->data;
	}

	bool empty() { return head == nullptr; }
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

		cout << "Size :" << q.size() << endl;
		cout << "front element: " << q.front() << endl;

		q.dequeue();

		cout << "new size :" << q.size() << endl;
		cout << "new front element: " << q.front() << endl;

	}
	catch (exception& e) {
		cerr << "An error has occured: " << e.what() << endl;
	}
	return 0;
}
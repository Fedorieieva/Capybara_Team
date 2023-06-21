#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

class Stack {
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

	Stack() { head = nullptr;  count = 0; }

	~Stack() {
		for (int i = 0; i < count; i++) {
			pop();
		}
	}

	void push(int val) {
		Node* new_node = new Node(val);
		if (head == nullptr) {
			head = new_node;
		}
		else {
			new_node->next = head;
			head = new_node;
		}
		count++;
	}

	int pop() {
		if (head == nullptr) {
			cout << "stack is empty" << endl;
		}
		else {
			int r;
			Node* temp = head;
			r = temp->data;
			head = head->next;
			delete temp;
			count--;
			return r;
		}
	}

	int peek() {
		if (head == nullptr) {
			cout << "stack is empty" << endl;
		}
		else {
			return head->data;
		}
	}

	void save_to_file(const string& filename) {
		ofstream file(filename);
		if (!file.is_open()) {
			throw runtime_error("Error opening file\n");
		}

		Node* current = head;
		while (current) {
			file << current->data << " ";
			current = current->next;
		}

		file.close();
	}

	bool is_empty() {
		return head == nullptr;
	}
};

int main() {
	try {
		Stack s;
		int num, el;

		cout << "Enter the number of elements for the stack: ";
		cin >> num;

		if (cin.fail()) {
			throw runtime_error("Invalid input. Expected int");
		}

		cout << "Enter elements for stack:" << endl;
		for (int i = 0; i < num; i++) {
			cin >> el;
			if (cin.fail()) {
				throw runtime_error("Invalid input. Expected int");
			}
			s.push(el);
		}

		cout << "Peek: " << s.peek() << endl;
		cout << "Pop: " << s.pop() << endl;
		cout << "Pop: " << s.pop() << endl;

		cout << "Is stack empty? " << (s.is_empty() ? "true" : "false") << endl;

		s.save_to_file("stack.txt");

	}
	catch (const exception& e) {
		cerr << "An error occured: " << e.what() << endl;
	}
}
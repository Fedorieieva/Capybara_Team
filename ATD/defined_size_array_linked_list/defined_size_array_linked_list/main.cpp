#include <iostream>
#include <stdexcept>

using namespace std;

class Array {
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
	int size;
	int count;

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

		bool operator!=(const Iterator& other) {
			return current != other.current;
		}
	};

	Array() { head = nullptr; size = 0; count = 0; }

	Array(int n) { head = nullptr; size = n; count = 0; }

	~Array() { clear(); }

	void Set_size(int n) { size = n; }

	int Get_size() { return size; }
	
	void clear() {
		Node* current = head;
		while (current) {
			Node* temp = current->next;
			delete current;
			current = temp;
		}
		head = nullptr;
	}

	void insert(int& n) {
		Node* new_node = new Node(n);

		if (count == size) {
			throw out_of_range("Array is full");
		}
		else if (head == nullptr) {
			head = new_node;
			count++;
		}
		else {
			Node* current = head;
			while (current->next) {
				current = current->next;
			}
			current->next = new_node;
			count++;
		}
	}

	void print() {
		for (Iterator it = begin(); it != end(); ++it) {
			cout << *it << " ";
		}
		cout << endl;
	}

	int& operator[](int& idx) const {
		if (idx < 0 || idx >= size) {
			throw out_of_range("Indet out of bound");
		}
		else {
			int i = 0;
			Node* current = head;
			while (current) {
				if (i == idx) {
					return current->data;
				}
				current = current->next;
				i++;
			}
		}
	}

	bool empty() { return head == nullptr; }

	void remove_at(int idx) {
		if (idx < 0 || idx >= size) {
			throw out_of_range("Index out of bounds");
		}
		else {
			int i = 0;
			Node* current = head;
			Node* prev = nullptr;

			while (current) {
				if (i == idx) {
					if (prev == nullptr) {
						head = current->next;
					}
					else {
						prev->next = current->next;
					}
					delete current;
					count--;
					return;
				}
				prev = current;
				current = current->next;
				i++;
			}
		}
		throw out_of_range("Index out of bounds");
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
		Array a;
		int size;

		cout << "Enter array size: ";
		cin >> size;

		if (cin.fail() || size <= 0) {
			throw runtime_error("Expected a positive integer for array size.");
		}

		a.Set_size(size);

		cout << "Enter array elements:" << endl;
		for (int i = 0; i < size; i++) {
			int num;
			cin >> num;

			if (cin.fail()) {
				throw runtime_error("Invalid input. Expected an integer.");
			}

			a.insert(num);
		}

		cout << "Array elements: ";
		a.print();

		cout << "Enter element index to remove: ";
		int index;
		cin >> index;

		a.remove_at(index);

		cout << "Array elements after removal: ";
		a.print();
	}
	catch (exception& e) {
		cerr << "An error occurred: " << e.what() << endl;
	}

	return 0;
}
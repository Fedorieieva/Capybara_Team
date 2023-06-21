#include <iostream>
#include <stdexcept>

using namespace std;

class Multiset {
private:
	class Node {
	public:
		int data;
		int count;
		Node* next;

		Node(int d) {
			data = d;
			count = 1;
			next = nullptr;
		}
	};

	Node* head;

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

	Multiset() { head = nullptr; }

	~Multiset() { clear(); }

	void add(int& d) {
		if (head == nullptr) {
			head = new Node(d);
		}
		else {
			Node* current = head;

			while (current->next != nullptr && current->data != d) {
				current = current->next;
			}

			if (current->data == d) {
				current->count++;
			}
			else{
				current->next = new Node(d);
			}
		}
	}

	void remove(int& d) {
		if (head == nullptr) {
			return;
		}

		if (head->data == d) {
			if (head->count > 1) {
				head->count--;
			}
			else {
				Node* temp = head;
				head = head->next;
				delete temp;
			}
		}
		else {
			Node* current = head;

			while (current->next != nullptr && current->next->data != d) {
				current = current->next;
			}

			if (current->next != nullptr) {
				if (current->next->count > 1) {
					current->next->count--;
				}
				else {
					Node* temp = current->next;
					current->next = current->next->next;
					delete temp;
				}
			}
		}
	}

	int count(int& d) {
		Node* current = head;

		while (current) {
			if (current->data == d) {
				return current->count;
			}
			current = current->next;
		}
		return 0;
	}

	bool in_set(int& d) {
		Node* current = head;

		while (current) {
			if (current->data == d) {
				return true;
			}
			current = current->next;
		}
		return false;
	}

	void print() {
		for (Iterator it = begin(); it != end(); ++it) {
			cout << *it << " ";
		}
		cout << endl;
	}

	bool empty() { return head == nullptr; }

	void clear() {
		Node* current = head;

		while (current) {
			Node* temp = current->next;
			delete current;
			current = temp;
		}

		head = nullptr;
	}

	Multiset intersection(Multiset& otherSet) {
		Multiset res;

		Node* current = head;

		while (current != nullptr) {
			int data = current->data;

			if (otherSet.in_set(data) && !res.in_set(data)) {
				int count = min(current->count, otherSet.count(data));
				for (int i = 0; i < count; ++i) {
					res.add(data);
				}
			}

			current = current->next;
		}

		return res;
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
		Multiset s;
		int size, num;

		cout << "Enter size of multiset: ";
		cin >> size;

		if (cin.fail() || size <= 0) {
			throw runtime_error("An int number grater that zero is expected.");
		}

		cout << "Enter elements:" << endl;
		for (int i = 0; i < size; i++) {
			cin >> num;

			if (cin.fail()) {
				throw runtime_error("An int number is expected.");
			}
			s.add(num);
		}
		cout << "Set elements: ";
		s.print();

		cout << "Enter element to count: ";
		cin >> num;
		int count = s.count(num);
		cout << "Count of " << num << ": " << count << endl;

		cout << "Enter element to check if present in the set: ";
		cin >> num;
		cout << "Element " << num << " exists in the set: " << (s.in_set(num) ? "true" : "false") << endl;

		cout << "Enter element to remove: ";
		cin >> num;
		s.remove(num);

		cout << "Set elements after removal: ";
		s.print();

		cout << "Set is empty: " << (s.empty() ? "true" : "false") << endl;

		s.clear();

		cout << "Set elements after clearing: ";
		s.print();
	}
	catch (exception& e) {
		cerr << "An exception occured: " << e.what() << endl;
	}

	return 0;
}

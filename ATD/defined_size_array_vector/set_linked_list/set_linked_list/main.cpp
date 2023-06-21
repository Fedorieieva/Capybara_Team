#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

class Set {
	class Node {
	public:
		int data;
		Node* next;

		Node(int val) {
			data = val;
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

	Set() { head = nullptr; }

	~Set() {
		Node* current = head;
		while (current) {
			Node* temp = current;
			current = current->next;
			delete temp;
		}
		head = nullptr;
	}

	bool is_present(int val) const {
		Node* current = head;
		while (current && current->data <= val) {
			if (current->data == val) {
				return true;
			}
			current = current->next;
		}
		return false;
	}

	void insert(int val) {
		if (is_present(val)) {
			return;
		}

		Node* new_node = new Node(val);

		if (!head || val < head->data) {
			new_node->next = head;
			head = new_node;
		}
		else {
			Node* current = head;
			while (current->next && current->next->data < val) {
				current = current->next;
			}
			new_node->next = current->next;
			current->next = new_node;
		}
	}

	void remove(int val) {
		if (!head || val < head->data) {
			return;
		}

		if (head->data == val) {
			Node* temp = head;
			head = head->next;
			delete temp;
			return;
		}

		Node* current = head;
		while (current->next && current->next->data < val) {
			current = current->next;
		}

		if (current->next && current->next->data == val) {
			Node* temp = current->next;
			current->next = current->next->next;
			delete temp;
		}
	}

	void display() const {
		Node* current = head;
		while (current) {
			cout << current->data << " ";
			current = current->next;
		}
		cout << endl;
	}

	Set operator+(const Set& otherSet) const {
		Set resultSet = *this;

		Node* current = otherSet.head;
		while (current != nullptr) {
			resultSet.insert(current->data);
			current = current->next;
		}

		return resultSet;
	}

	Set operator*(const Set& otherSet) const {
		Set resultSet;

		Node* current = head;
		while (current != nullptr) {
			if (otherSet.is_present(current->data))
				resultSet.insert(current->data);
			current = current->next;
		}

		return resultSet;
	}

	Set operator/(const Set& otherSet) const {
		Set resultSet = *this;

		Node* current = otherSet.head;
		while (current != nullptr) {
			resultSet.remove(current->data);
			current = current->next;
		}

		return resultSet;
	}

	void write_to_file(const string& filename) const {
		ofstream file(filename);
		if (!file.is_open()) {
			throw runtime_error("Error opening file");
		}
		Node* current = head;
		while (current) {
			file << current->data;
			if (current->next) {
				file << ":";
			}
			current = current->next;
		}
		file.close();
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
		Set set1;
		Set set2;

		int numElements;
		std::cout << "Enter the number of elements for set1: ";
		std::cin >> numElements;

		if (std::cin.fail()) {
			throw std::runtime_error("Invalid input. Expected an integer.");
		}

		std::cout << "Enter the elements for set1:" << std::endl;
		for (int i = 0; i < numElements; ++i) {
			int element;
			std::cin >> element;

			if (std::cin.fail()) {
				throw std::runtime_error("Invalid input. Expected an integer.");
			}

			set1.insert(element);
		}

		std::cout << "Enter the number of elements for set2: ";
		std::cin >> numElements;

		if (std::cin.fail()) {
			throw std::runtime_error("Invalid input. Expected an integer.");
		}

		std::cout << "Enter the elements for set2:" << std::endl;
		for (int i = 0; i < numElements; ++i) {
			int element;
			std::cin >> element;

			if (std::cin.fail()) {
				throw std::runtime_error("Invalid input. Expected an integer.");
			}

			set2.insert(element);
		}

		Set unionSet = set1 + set2;
		std::cout << "Union: ";
		for (const auto& element : unionSet) {
			std::cout << element << " ";
		}
		std::cout << std::endl;

		Set intersectionSet = set1 * set2;
		std::cout << "Intersection: ";
		for (const auto& element : intersectionSet) {
			std::cout << element << " ";
		}
		std::cout << std::endl;

		Set differenceSet = set1 / set2;
		std::cout << "Difference: ";
		for (const auto& element : differenceSet) {
			std::cout << element << " ";
		}
		std::cout << std::endl;

		unionSet.write_to_file("output.txt");
	}
	catch (const std::exception& e) {
		std::cerr << "An error occurred: " << e.what() << std::endl;
	}

	return 0;
}
#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

class Hashmap {
    class Node {
    public:
        int key;
        string value;
        Node* next;

        Node(int k, const string& v) : key(k), value(v), next(nullptr) {}
    };

    Node** table;
    int size;

    int hash(int key) const {
        return key % size;
    }

public:
    Hashmap(int size) : size(size) {
        table = new Node * [size];
        for (int i = 0; i < size; i++) {
            table[i] = nullptr;
        }
    }

    ~Hashmap() {
        clear();
        delete[] table;
    }

    void insert(int key, const string& value) {
        int idx = hash(key);
        Node* newNode = new Node(key, value);

        if (table[idx] == nullptr) {
            table[idx] = newNode;
        }
        else {
            Node* current = table[idx];
            while (current->next != nullptr) {
                if (current->key == key) {
                    delete newNode;
                    throw runtime_error("Key already exists.");
                }
                current = current->next;
            }
            if (current->key == key) {
                delete newNode;
                throw runtime_error("Key already exists.");
            }
            current->next = newNode;
        }
    }

    string get(int key) const {
        int idx = hash(key);
        Node* current = table[idx];
        while (current != nullptr) {
            if (current->key == key) {
                return current->value;
            }
            current = current->next;
        }
        throw out_of_range("Key not found.");
    }

    void remove(int key) {
        int idx = hash(key);
        Node* current = table[idx];
        Node* prev = nullptr;

        while (current != nullptr) {
            if (current->key == key) {
                if (prev == nullptr) {
                    table[idx] = current->next;
                }
                else {
                    prev->next = current->next;
                }
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }

        throw out_of_range("Key not found.");
    }

    bool contains(int key) const {
        int idx = hash(key);
        Node* current = table[idx];
        while (current != nullptr) {
            if (current->key == key) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void clear() {
        for (int i = 0; i < size; i++) {
            Node* current = table[i];
            while (current != nullptr) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
            table[i] = nullptr;
        }
    }

    void print_table() const {
        for (int i = 0; i < size; i++) {
            Node* current = table[i];
            while (current != nullptr) {
                cout << "[" << current->key << " - " << current->value << "]\n";
                current = current->next;
            }
        }
    }

    void print_pair(int key) const {
        int idx = hash(key);
        Node* current = table[idx];
        while (current != nullptr) {
            if (current->key == key) {
                cout << "[" << current->key << " - " << current->value << "]\n";
                return;
            }
            current = current->next;
        }
        throw runtime_error("Key not found.");
    }
};

int main() {
	try {
		int size;

		cout << "Enter size of the table: ";
		cin >> size;

		if (cin.fail() || size <= 0) {
			throw runtime_error("An int number grater than zero is expected.");
		}

        Hashmap h(size);

		int key;
		string val;

		cout << "Enter the hash table:" << endl;
		for (int i = 0; i < size; i++) {
			cout << endl << "Enter key: ";
			cin >> key;

			if (cin.fail()) {
				throw runtime_error("An int number grater than zero is expected.");
			}

			cout << "Enter value: ";
			cin >> val;
			h.insert(key, val);
		}

		cout << endl << "Enter key to print key-value pair: ";
		cin >> key;

		if (cin.fail()) {
			throw runtime_error("An int number is expected.");
		}
		cout << "Found pair: ";
		h.print_pair(key);

		cout << endl << "Whole table: " << endl;
		h.print_table();

	}
	catch (exception& e) {
		cerr << "An error occured: " << e.what() << endl;
	}

	return 0;
}
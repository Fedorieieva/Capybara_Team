#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

class hashmap {
	vector<vector<pair<int, string>>> t;

	int hash(int& key, int size) const {
		return key % size;
	}

public:
	hashmap(int size) {
		t.resize(size);
	}

	void insert(int& key, const string& val) {
		int idx = hash(key, t.size());
		for (const auto& el : t[idx]) {
			if (el.first == key) {
				throw runtime_error("Key already exists.");
			}
		}
		t[idx].push_back(make_pair(key, val));
	}

	string get(int& key) const {
		int idx = hash(key, t.size());
		for (const auto& el : t[idx]) {
			if (el.first == key) {
				return el.second;
			}
		}
		throw out_of_range("Key not found.");
	}

	void remove(int& key) {
		int idx = hash(key, t.size());
		vector<pair<int, string>>& el = t[idx];
		for (auto it = el.begin(); it != el.end(); it++) {
			if (it->first == key) {
				el.erase(it);
				return;
			}
		}
		throw out_of_range("Key not found.");
	}

	bool contains(int& key) {
		int idx = hash(key, t.size());
		for (auto& el : t[idx]) {
			if (el.first == key) {
				return true;
			}
		}
		return false;
	}

	void print_table() {
		for (int i = 0; i < t.size(); i++) {
			for (auto& el : t[i]) {
				cout << "[" << el.first << " - " << el.second << "]\n";
			}
		}
	}

	void print_pair(int& key) {
		if (contains(key)) {
			cout << "[" << key << " - " << get(key) << "]\n";
		}
		else {
			throw runtime_error("Key not found.");
		}
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

		hashmap h(size);

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
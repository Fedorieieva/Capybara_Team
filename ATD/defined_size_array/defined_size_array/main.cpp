#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

class Array {
	int size;
	int* a;

public:
	Array() {
		size = 0;
		a = nullptr;
	}

	Array(int n) {
		size = n;
		a = new int[size];
	}

	~Array() { delete[] a; }

	int Get_size() { return size; }

	void Set_size(const int& n) {
		delete[] a;
		size = n;
		a = new int[size];
	}

	int& operator[](int idx) {
		if (idx >= size || idx < 0) {
			throw out_of_range("Index is out of bound");
		}
		else {
			return a[idx];
		}
	}

	void clear() {
		delete[] a;
		a = new int[size];
	}

	bool empty() {
		for (int i = 0; i < size; i++) {
			if (a[i] != 0) {
				return false;
			}
		}

		return true;
	}

	void remove_at(int& idx) {
		if (idx >= size || idx < 0) {
			throw out_of_range("Index is out of bound");
		}
		else {
			for (int i = idx; i < size - 1; i++) {
				a[i] = a[i + 1];
			}
			size--;
		}
	}

	void print() {
		for (int i = 0; i < size; i++) {
			cout << a[i] << " ";
		}
		cout << endl;
	}
};

int main() {
	try {
		Array a;
		int size, num;

		cout << "Enter size of the array: ";
		cin >> size;

		if (cin.fail() || size <= 0) {
			throw runtime_error("Expected an int number grater than zero.");
		}

		a.Set_size(size);

		cout << "Enter array elements:" << endl;
		for (int i = 0; i < size; i++) {
			cin >> num;

			if (cin.fail() || size <= 0) {
				throw runtime_error("Expected an int number grater than zero.");
			}

			a[i] = num;
		}

		a.print();

		cout << "Enter element idx to remove: ";
		cin >> num;

		a.remove_at(num);

		a.print();

	}
	catch (exception& e) {
		cerr << "An error occured: " << e.what() << endl;
	}


	return 0;
}
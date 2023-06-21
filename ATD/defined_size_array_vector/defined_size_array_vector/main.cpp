#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

class Array {
    int size;
    int count;
    vector<int> a;

public:
    Array() { size = 0; count = 0; }

    Array(int n) { size = n; count = 0; }

    void Set_size(int n) { size = n; }

    int Get_size() { return size; }

    int& operator[](int idx) {
        if (idx >= size || idx < 0) {
            throw out_of_range("Index is out of bound");
        }
        else {
            return a[idx];
        }
    }

    void clear() { a.clear(); size = 0; count = 0; }

    bool empty() { return a.empty(); }

    void remove_at(int idx) {
        if (idx >= size || idx < 0) {
            throw out_of_range("Index out of bound");
        }
        else {
            a.erase(a.begin() + idx);
            size--;
            count--;
        }
    }

    void print() {
        for (int i = 0; i < size; i++) {
            cout << a[i] << " ";
        }
        cout << endl;
    }

    void push_back(int& num) {
        if (count >= size) {
            throw out_of_range("Array is full");
        }
        else {
            a.push_back(num);
        }
    }
};

int main() {
    try {
        Array a;
        int size, num;

        cout << "Enter array size: ";
        cin >> size;

        if (cin.fail() || size <= 0) {
            throw runtime_error("Expected an int number greater than zero");
        }

        a.Set_size(size);

        cout << "Enter array elements:" << endl;
        for (int i = 0; i < size; i++) {
            cin >> num;

            if (cin.fail()) {
                throw runtime_error("Invalid input. Expected an integer.");
            }

            a.push_back(num);
        }

        a.print();

        cout << "Enter element index to remove: ";
        cin >> num;

        if (cin.fail()) {
            throw runtime_error("Invalid input. Expected an integer.");
        }

        a.remove_at(num);
        a.print();
    }
    catch (exception& e) {
        cerr << "An error occurred: " << e.what() << endl;
    }

    return 0;
}

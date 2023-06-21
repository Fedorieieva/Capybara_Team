#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

class Queue {
	vector<int> a;

public:
	void enqueue(int& val) { a.push_back(val); }

	void dequeue() {
		if (a.empty()) {
			throw out_of_range("Queue s empty");
		}
		a.erase(a.begin());
	}

	int front() const {
		if (a.empty()) {
			throw out_of_range("Queue s empty");
		}
		return a.front();
	}

	int size() { return a.size(); }

	bool empty() { return a.empty(); }
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
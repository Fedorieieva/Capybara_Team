#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/*Створити бінарний файл, що являє собою список поїздів і містить наступну інформацію: 
номер поїзда, пункт призначення, дату і час відправлення.

Спроєктувати клас Train, що має поля: номер поїзда, пункт призначення, дату і час відправлення.

На його основі розробити клас Train_schedule, який містить базу даних рейсів поїздів та інформацію про них.

Також спроєктувати клас List, елементами якого є об'єкти класу Train.

Класи повинні мати конструктори, методи доступу, методи виведення об’єктів, методи для виконання поставленого завдання, можливо інші методи.

Розробити програму, яка створює об'єкт класу Train_schedule, ініціалізуючи його даними із відповідного файлу.
Визначити кількість поїздів, які слідують щоденно у вказаний пункт призначення.
Використовуючи клас List, сформувати список поїздів, які відправляються із вокзалу у вказаний інтервал часу.
Додавання елементів у List здійснювати за допомогою перевантаженого оператора “<<”, наприклад, список << елемент.
Програма повинна забезпечувати наочне виведення усіх вхідних, вихідних та проміжних даних, а також контроль можливих помилок.
Для обробки помилок використати виключні ситуації.*/

class Train {
	string number;
	string direction;
	string date;
	string departure_time;

	void write_to_file() {
		ofstream file("train_binary_file", ios::binary | ios::app);
		if (!file.is_open()) {
			throw runtime_error("Error opening file");
		}
		else {
			file.write(reinterpret_cast<const char*>(this), sizeof(*this));
			file.close();
		}
	}

public:
	Train() {
		number = "";
		direction = "";
		date = "";
		departure_time = "";
	}

	Train(string n, string dir, string dat, string dep) {
		number = n;
		direction = dir;
		date = dat;
		departure_time = dep;
		write_to_file();
	}

	string Get_number() { return number; }
	void Set_number(string n){ number = n; }

	string Get_direction() { return direction; }
	void Set_direction(string n) { direction = n; }

	string Get_date() { return date; }
	void Set_date(string n) { date = n; }

	string Get_departure_time() { return departure_time; }
	void Set_departure_time(string n) { departure_time = n; }

	void print_train() {
		cout << "number: " << number << endl;
		cout << "direction: " << direction << endl;
		cout << "date: " << date << endl;
		cout << "departure_time: " << departure_time << endl;
	}
};

class Train_schedule {
	Train* t;
	int size = 10;
	int count;

public:
	Train_schedule() {
		t = new Train[size];
		count = 0;
	}

	~Train_schedule() {
		delete[] t;
	}

	void print_train_schedule() {
		for (int i = 0; i < count - 1; i++) {
			t[i].print_train();
			cout << endl;
		}
	}

	void add_train(Train& tr) {
		if (count == size) {
			size *= 2;
			Train* new_t = new Train[size];
			for (int i = 0; i < count - 1; i++) {
				new_t[i] = t[i];
			}
			delete[] t;
			t = new_t;
		}

		t[count] = tr;
		count++;
	}

	void read_train_from_file() {
		ifstream file("train_binary_file", ios::binary);
		if (!file.is_open()) {
			throw runtime_error("Error opening file");
		}
		else {
			while(!file.eof()){
				Train tr;
				file.read(reinterpret_cast<char*>(&tr), sizeof(Train));
				add_train(tr);
			}
			file.close();
		}
	}

	Train& operator[](const int& idx) {
		if (idx < 0 || idx >= count) {
			throw out_of_range("Index out of range");
		}
		return t[idx];
	}
};

class List {
	class Node {
	public:
		Node* next;
		Train data;

		Node(Train& t) {
			data = t;
			next = nullptr;
		}
	};

	void add(Train& t) {
		Node* new_node = new Node(t);
		if (head == nullptr) {
			head = new_node;
		}
		else {
			Node* current = head;
			while (current->next != nullptr) {
				current = current->next;
			}
			current->next = new_node;
		}
	}

	bool compare_time(string& t1, string& t2) {
		int pos1 = t1.find(":");
		int pos2 = t2.find(":");

		int h1 = stoi(t1.substr(0, pos1));
		int m1 = stoi(t1.substr(pos1 + 1));

		int h2 = stoi(t2.substr(0, pos2));
		int m2 = stoi(t2.substr(pos2 + 1));

		if (h1 > h2) {
			return true;
		}
		else if (h1 == h2) {
			if (m1 >= m2) {
				return true;
			}
		}
		return false;
	}

	Node* head;

public:
	class Iterator {
		Node* current;

	public:
		Iterator(Node* node) { current = node; }

		Train& operator*() const {
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

	List() { head = nullptr; }

	List& operator<<(Train& t) {
		add(t);
		return *this;
	}

	List trains_left_in_interval(string interval) {
		int pos = interval.find("-");
		string start = interval.substr(0, pos);
		string end_time = interval.substr(pos + 1);
		string train_departure;
		List res;
		bool departure1, departure2;

		for (Iterator it = begin(); it != end(); ++it) {
			train_departure = (*it).Get_departure_time();
			departure1 = compare_time(train_departure, start);
			departure2 = compare_time(end_time, train_departure);
			if (departure1 && departure2) {
				res << *it;
			}
		}
		return res;
	}

	void print_list() {
		for (Iterator it = begin(); it != end(); ++it) {
			(*it).print_train();
			cout << endl;
		}
	}

	Iterator begin() {
		return Iterator(head);
	}

	Iterator end() {
		return Iterator(nullptr);
	}
};

int main() {
	return 0;
}
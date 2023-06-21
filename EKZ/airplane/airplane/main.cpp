#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/*Створити бінарний файл, що являє собою список рейсів літаків 
і містить наступну інформацію: номер рейсу, тип літака, пункт
призначення, дні і час вильоту. 

Спроєктувати клас Flight, що має поля: номер рейсу, тип літака, пункт 
призначення, дні і час вильоту. 

На його основі розробити клас Airplane_Flight_Schedule, який містить базу
даних рейсів літаків та інформацію про них. 

Також спроєктувати клас List, елементами якого є об'єкти класу Flight. 

Класи повинні мати конструктори, методи доступу, методи виведення об’єктів, 
методи для виконання поставленого завдання, можливо інші методи. 

Розробити програму, яка створює об'єкт класу Airplane_Flight_Schedule, 
ініціалізуючи його даними із відповідного файлу. Визначити кількість 
рейсів до вказаного пункту призначення у заданий день тижня.
Використовуючи клас List, сформувати список рейсів, які відлітають 
із аеропорту у вказаний інтервал часу (з вказанням дня тижня).
Додавання елементів у List здійснювати за допомогою перевантаженого 
оператора “<<”, наприклад, список << елемент.
Програма повинна забезпечувати наочне виведення усіх вхідних, вихідних та проміжних даних,
а також контроль можливих помилок. Для обробки помилок використати виключні ситуації.*/

class Flight {
	void write_to_file() {
		ofstream file("flight_binaty_file", ios::binary | ios::app);
		if (!file.is_open()) {
			throw runtime_error("Error opening file");
		}
		else {
			file.write(reinterpret_cast<const char*>(this), sizeof(*this));
			file.close();
		}
	}

	string number;
	string airplane;
	string destination;
	string day;
	string time;

public:
	Flight() {
		number = "";
		airplane = "";
		destination = "";
		day = "";
		time = "";
	}

	Flight(string n, string a, string d, string da, string t) {
		number = n;
		airplane = a;
		destination = d;
		day = da;
		time = t;
		write_to_file();
	}

	string Get_number() { return number; }
	void Set_number(string n) { number = n; }

	string Get_airplane() { return airplane; }
	void Set_airplane(string n) { airplane = n; }

	string Get_destination() { return destination; }
	void Set_destination(string n) { destination = n; }

	string Get_day() { return day; }
	void Set_day(string n) { day = n; }

	string Get_time() { return time; }
	void Set_time(string n) { time = n; }

	void print_flight() {
		cout << "number: " << number << endl;
		cout << "airplane: " << airplane << endl;
		cout << "destination: " << destination << endl;
		cout << "day: " << day << endl;
		cout << "time: " << time << endl << endl;
	}
};

class Airplane_Flight_Schedule {
	int size = 10;
	int count;
	Flight* f;

public:
	Airplane_Flight_Schedule() {
		f = new Flight[size];
		count = 0;
	}

	~Airplane_Flight_Schedule() { delete[] f; }

	void add_airplane(Flight& a) {
		if (size == count) {
			size *= 2;
			Flight* new_f = new Flight[size];
			for (int i = 0; i < count - 1; i++) {
				new_f[i] = f[i];
			}
			delete[] f;
			f = new_f;
		}

		f[count] = a;
		count++;
	}

	void read_schedule_from_file() {
		ifstream file("flight_binaty_file", ios::binary);
		if (!file.is_open()) {
			throw runtime_error("Error opening file");
		}
		else {
			while (!file.eof()) {
				Flight a;
				file.read(reinterpret_cast<char*>(&a), sizeof(Flight));
				add_airplane(a);
			}			
			file.close();
		}
	}

	void print_airplane_flight_schedule() {
		for (int i = 0; i < count - 1; i++) {
			f[i].print_flight();
		}
	}

	Flight& operator[](const int& idx) {
		if (idx < 0 || idx >= count) {
			throw out_of_range("Index out of range");
		}
		return f[idx];
	}

	int number_of_flights_on_day(string flight_day, string flight_destination) {
		int res = 0;
		for (int i = 0; i < count - 1; i++) {
			if (f[i].Get_destination() == flight_destination && f[i].Get_day() == flight_day) {
				res++;
			}
		}
		return res;
	}
};

class List {
	class Node {
	public:
		Node* next;
		Flight data;

		Node(Flight& f) {
			data = f;
			next = nullptr;
		}
	};

	void add(Flight& f) {
		Node* new_node = new Node(f);
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
		Iterator(Node* n) { current = n; }

		Flight& operator*() const {
			return current->data;
		}

		Iterator& operator++() {
			if (current != nullptr) {
				current->next;
			}
			return *this;
		}

		bool operator!=(const Iterator& other) {
			return current != other.current;
		}
	};

	List() { head = nullptr; }

	List& operator<<(Flight& f) {
		add(f);
		return *this;
	}

	Iterator begin() {
		return Iterator(head);
	}

	Iterator end() {
		return Iterator(nullptr);
	}

	void print_list() {
		for (Iterator it = begin(); it != end(); ++it) {
			(*it).print_flight();
		}
	}

	List flight_departure(string interval, string flight_day) {
		int pos = interval.find("-");
		string start = interval.substr(0, pos);
		string end_time = interval.substr(pos + 1);
		string flight_departure;
		List res;
		bool departure1, departure2;

		for (Iterator it = begin(); it != end(); ++it) {
			flight_departure = (*it).Get_time();
			departure1 = compare_time(flight_departure, start);
			departure2 = compare_time(end_time, flight_departure);
			if ((departure1 && departure2) && flight_day == (*it).Get_day()) {
				res << *it;
			}
		}

		return res;
	}
};


int main() {
	return 0;
}
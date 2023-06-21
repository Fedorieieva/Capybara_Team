#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/*Створити бінарний файл, що являє собою список речей і інформації про 
них (назва речі, її інвентарний номер, дата здачі на зберігання та термін 
зберігання). 

Спроектувати клас Thing, що має наступні поля: назва речі, 
Інвентарний номер, дата здачі на зберігання, термін зберігання. 

На основі даного класу розробити клас Cloakroom, який містить базу даних 
речей, зданих на збереження. 

Також спроектувати клас List, елементами якого є об'єкти класу Thing. 

Класи повинні мати конструктори, методи доступу, 
методи виведення об'єктів, методи для виконання поставленого завдання, 
можливо інші методи. 

Розробити програму, яка створює об'єкт класу Cloakroom, 
ініціалізуючи його даними із відповідного файлу. Визначити кількість речей, 
які здані на зберігання у заданий період (вказується з клавіатури). 
Використовуючи клас List, сформувати список речей, термін зберігання яких закінчився. 
Додавання елементів у List здійснювати за допомогою перевантаженого оператора "<<", 
наприклад, список << елемент. Програма повинна забезпечувати наочне виведення 
усіх вхідних, вихідних та проміжних даних, а також контроль можливих помилок. 
Для обробки помилок використати виключні ситуації.*/

class Date {
private:
	int year;
	int month;
	int day;

	bool is_leap_year(int y) {
		return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
	}

	int Get_days_in_month(int& y, int& m) {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		if (month == 2 && is_leap_year(year)) {
			return 29;
		}
		return days[month - 1];
	}

public:
	Date(int y, int m, int d) {
		year = y;
		month = m;
		day = d;
	}

	int get_days_between_dates(Date& start, Date& end) {
		int days = 0;

		for (int year = start.year + 1; year < end.year; ++year) {
			days += is_leap_year(year) ? 366 : 365;
		}

		for (int month = start.month + 1; month <= 12; ++month) {
			days += Get_days_in_month(start.year, month);
		}
		days += Get_days_in_month(start.year, start.month) - start.day;

		for (int month = 1; month < end.month; ++month) {
			days += Get_days_in_month(end.year, month);
		}
		days += end.day;

		return days;
	}

	Date addDays(int add) {
		Date result = *this;

		while (add > 0) {
			int daysInMonth = Get_days_in_month(result.year, result.month);
			int daysLeftInMonth = daysInMonth - result.day + 1;

			if (add <= daysLeftInMonth) {
				result.day += add;
				break;
			}

			result.month++;
			if (result.month > 12) {
				result.year++;
				result.month = 1;
			}

			result.day = 1;
			add -= daysLeftInMonth;
		}

		return result;
	}

	bool operator>=(const Date& otherDate) {
		if (year >= otherDate.year)
			return true;
		else if (year <= otherDate.year)
			return false;

		if (month >= otherDate.month)
			return true;
		else if (month <= otherDate.month)
			return false;

		return day >= otherDate.day;
	}

	bool operator>(const Date& otherDate) {
		if (year > otherDate.year)
			return true;
		else if (year < otherDate.year)
			return false;

		if (month > otherDate.month)
			return true;
		else if (month < otherDate.month)
			return false;

		return day > otherDate.day;
	}

	bool operator<=(const Date& otherDate) {
		if (year <= otherDate.year)
			return true;
		else if (year >= otherDate.year)
			return false;

		if (month <= otherDate.month)
			return true;
		else if (month >= otherDate.month)
			return false;

		return day <= otherDate.day;
	}

	static void split_date(string range, int& start_y, int& start_m, int& start_d, int& end_y, int& end_m, int& end_d) {
		int dash_pos = range.find('-');

		string start_date = range.substr(0, dash_pos);
		string end_date = range.substr(dash_pos + 1);

		int pos1 = start_date.find('.');
		int pos2 = start_date.rfind('.');

		start_y = stoi(start_date.substr(0, pos1));
		start_m = stoi(start_date.substr(pos1 + 1, pos2 - pos1 - 1));
		start_y = stoi(start_date.substr(pos2 + 1));


		pos1 = start_date.find('.');
		pos2 = start_date.rfind('.');

		end_y = stoi(end_date.substr(0, pos1));
		end_m = stoi(end_date.substr(pos1 + 1, pos2 - pos1 - 1));
		end_d = stoi(end_date.substr(pos2 + 1));
	}

	static void split_date(string range, int& start_y, int& start_m, int& start_d) {
		int pos1 = range.find('.');
		int pos2 = range.rfind('.');

		start_y = stoi(range.substr(0, pos1));
		start_m = stoi(range.substr(pos1 + 1, pos2 - pos1 - 1));
		start_y = stoi(range.substr(pos2 + 1));
	}
};

class Thing {
	string name;
	string id;
	string date;
	string period;

	void save_thing_to_file() {
		ofstream file("thing_binary_file", ios::binary | ios::app);
		if (!file.is_open()) {
			throw runtime_error("Error opening file");
		}
		else {
			file.write(reinterpret_cast<const char*>(this), sizeof(*this));
			file.close();
		}
	}

public:
	Thing() {
		name = "";
		id = "";
		date = "";
		period = "";
	}

	Thing(string n, string i, string d, string t) {
		name = n;
		id = i;
		date = d;
		period = t;
		save_thing_to_file();
	}

	void print_thing() {
		cout << "name: " << name << endl;
		cout << "id: " << id << endl;
		cout << "date: " << date << endl;
		cout << "time: " << period << endl;
	}

	string Get_name() { return name; }
	void Set_name(string n) { name = n; }

	string Get_id() { return id; }
	void Set_id(string n) { id = n; }

	string Get_date() { return date; }
	void Set_date(string n) { date = n; }

	string Get_period() { return period; }
	void Set_period(string n) { period = n; }
};

class Cloakroom {
	Thing* t;
	int size = 10;
	int count;	

public:
	Cloakroom() {
		t = new Thing[size];
		count = 0;
	}

	~Cloakroom() { delete[] t; }

	void add(Thing& thing) {
		if (count == size) {
			size *= 2;
			Thing* new_t = new Thing[size];
			for (int i = 0; i < count; i++) {
				new_t[i] = t[i];
			}
			delete[] t;
			t = new_t;
		}

		t[count] = thing;
		count++;
	}

	void read_from_file() {
		ifstream file("thing_binary_file", ios::binary);
		if (!file.is_open()) {
			throw runtime_error("Error opening file");
		}
		else {
			while (!file.eof()) {
				Thing th;
				file.read(reinterpret_cast<char*>(&th), sizeof(Thing));
				add(th);
			}
		}
		file.close();
	}

	void print_cloakroom() {
		for (int i = 0; i < count - 1; i++) {
			t[i].print_thing();
			cout << endl;
		}
	}

	int num_of_things_in_period(string period) {
		int s_y = 0, s_m = 0, s_d = 0, e_y = 0, e_m = 0, e_d = 0;
		int c_y = 0, c_m = 0, c_d = 0;
		int num_count;
		string date;
		Date::split_date(period, s_y, s_m, s_d, e_y, e_m, e_d);
		Date d1(s_y, s_m, s_d);
		Date d2(e_y, e_m, e_d);
		for (int i = 0; i < count - 1; i++) {
			date = t[i].Get_date();
			Date::split_date(date, c_y, c_m, c_d);
			Date thing_date(c_y, c_m, c_d);
			if (d1 <= thing_date && d2 >= thing_date) {
				num_count++;
			}
		}
		return num_count;
	}

	Thing& operator[](const int& idx) {
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
		Thing data;

		Node(Thing& t) {
			data = t;
			next = nullptr;
		}
	};

	void add(Thing& thing) {
		Node* new_node = new Node(thing);
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

	Node* head;

public:
	class Iterator {
	private:
		Node* current;

	public:
		Iterator(Node* n) { current = n; }

		Thing& operator*() {
			return current->data;
		}

		Iterator& operator++() {
			if (current != nullptr) {
				current = current->next;
			}
			return *this;
		}

		bool operator !=(const Iterator& other) {
			return current != other.current;
		}
	};

	List& operator <<(Thing& other) {
		add(other);
		return *this;
	}

	void print_list() {
		for (Iterator it = begin(); it != end(); ++it) {
			(*it).print_thing();
			cout << endl;
		}
	}

	List expired_things() {
		int c_y = 0, c_m = 0, c_d = 0;
		int days_to_add, period;
		string date;
		Date today(12, 06, 2023);
		List expired;
		for (Iterator it = begin(); it != end(); ++it) {
			date = (*it).Get_date();
			period = stoi((*it).Get_period());
			Date::split_date(date, c_y, c_m, c_d);
			Date thing_date(c_y, c_m, c_d);
			Date period_thing_date = thing_date.addDays(period);
			if (period_thing_date > today) {
				expired << (*it);
			}			
		}
		return expired;
	}

	Iterator begin() {
		return Iterator(head);
	}

	Iterator end() {
		return Iterator(nullptr);
	}
};

void thing_input_for_file(Thing* t, int& num, int& init) {
	string name;
	string id;
	string date;
	string period;
	char choice = 'y';
	int max_size = init;
	do {
		if (num == max_size) {
			max_size *= 2;
			Thing* new_t = new Thing[max_size];
			for (int i = 0; i < num; i++) {
				new_t[i] = t[i];
			}
			delete[] t;
			t = new_t;
		}

		cout << "name = ";
		cin >> name;
		cout << "id = ";
		cin >> id;
		cout << "date = ";
		cin >> date;
		cout << "period in days = ";
		cin >> period;

		new(&t[num])  Thing(name, id, date, period);
		num++;

		cout << "continue input [y/n]";
		cin >> choice;
		cin.ignore();
		cout << endl;
	} while (choice != 'n' && choice != 'N');
}

int main() {
	int num = 0, initial = 10;
	Thing* t = new Thing[initial];
	thing_input_for_file(t, num, initial);
	cout << "-------------------------------------------------------------" << endl;
	cout << "Thing" << endl;
	for (int i = 0; i < num; i++) {
		t[i].print_thing();
		cout << endl;
	}
	cout << "-------------------------------------------------------------" << endl;
	cout << "Cloakroom" << endl;
	Cloakroom c;
	c.read_from_file();
	c.print_cloakroom();
	int num_things_in_period = c.num_of_things_in_period("12.12.2023-29.12.2023");
	cout << "Number of things left on period: " << num_things_in_period << endl << endl;
	cout << "-------------------------------------------------------------" << endl;
	cout << "List" << endl;
	List l;
	for (int i = 0; i < num; i++) {
		l << c[i];
	}
	l.print_list();
	List things_expired = l.expired_things();
	cout << "Expipred things:" << endl;
	things_expired.print_list();

	return 0;
}
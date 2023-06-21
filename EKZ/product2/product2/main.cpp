#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/*Створити бінарний файл, що являє собою список продуктів 
магазину і містить наступну інформацію: найменування продукту, 
дату його поставки, ціну, термін зберігання, кількість одиниць.

Спроєктувати клас Product, що має поля: найменування продукту, 
дата поставки, ціна, термін зберігання, кількість одиниць.

На його основі розробити клас Product_Catalog, який містить перелік 
продуктів магазину та інформацію про них.

Також спроєктувати клас List, елементами якого є об'єкти класу Product.

Класи повинні мати конструктори, методи доступу, методи виведення об’єктів, 
методи для виконання поставленого завдання, можливо інші методи. 

Розробити програму, яка створює об'єкт класу Product_Catalog, 
ініціалізуючи його даними із відповідного файлу. Визначити сумарну вартість продуктів,
термін зберігання яких не закінчився. Використовуючи клас List, сформувати список 
продукції, термін зберігання якої закінчився. Додавання елементів у List 
здійснювати за допомогою перевантаженого оператора “<<”, наприклад, список << елемент.
Програма повинна забезпечувати наочне виведення усіх вхідних, вихідних 
та проміжних даних, а також контроль можливих помилок.
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

class Product {
	void save_to_file() {
		ofstream file("product_binaru_file", ios::binary | ios::app);
		if (!file.is_open()) {
			throw runtime_error("Error opening file");
		}
		else {
			file.write(reinterpret_cast<const char*>(this), sizeof(*this));
			file.close();
		}
	}

	string name;
	string date;
	float price;
	int expire_in;
	int quantity;

public:
	Product() {
		name = "";
		date = "";
		price = 0;
		expire_in = 0;
		quantity = 0;
	}

	Product(string n, string d, float p, int e, int q) {
		name = n;
		date = d;
		price = p;
		expire_in = e;
		quantity = q;
		save_to_file();
	}

	string Get_name() { return name; }
	void Set_name(string n) { name = n; }

	string Get_date() { return date; }
	void Set_date(string n) { date = n; }

	float Get_price() { return price; }
	void Set_price(float n) { price = n; }

	int Get_expire_in() { return expire_in; }
	void Set_expire_in(int n) { expire_in = n; }

	int Get_quantity() { return quantity; }
	void Set_quantity(int n) { quantity = n; }

	void print_product() {
		cout << "name: " << name << endl;
		cout << "date: " << date << endl;
		cout << "price: " << price << endl;
		cout << "expire_in: " << expire_in << endl;
		cout << "quantity: " << quantity << endl << endl;
	}
};

class Product_Catalog {
	Product* p;
	int size = 10;
	int count;

public:
	Product_Catalog() {
		p = new Product[size];
		count = 0;
	}

	~Product_Catalog() { delete[] p; }

	void add_product_to_catalog(Product& pr) {
		if (size == count) {
			size *= 2;
			Product* new_p = new Product[size];
			for (int i = 0; i < count - 1; i++) {
				new_p[i] = p[i];
			}
			delete[] p;
			p = new_p;
		}
		else {
			p[count] = pr;
			count++;
		}
	}

	void read_product_from_file() {
		ifstream file("product_binaru_file", ios::binary);
		if (!file.is_open()) {
			throw runtime_error("Error opening file");
		}
		else {
			while (!file.eof()) {
				Product pr;
				file.read(reinterpret_cast<char*>(&pr), sizeof(Product));
				add_product_to_catalog(pr);
			}
			file.close();
		}
	}

	void print_product_catalog() {
		for (int i = 0; i < count - 1; i++) {
			p[i].print_product();
		}
	}

	Product& operator[](const int idx) {
		if (idx < 0 || idx >= count) {
			throw out_of_range("Index out of range");
		}
		return p[idx];
	}

	float non_expired_product_price() {
		float res = 0;
		string product_d;
		int start_y = 0, start_m = 0, start_d = 0, end_y = 0, end_m = 0, end_d = 0;

		Date::split_date("13.06.2023", end_y, end_m, end_d);
		Date today_date(end_y, end_m, end_d);

		for (int i = 0; i < count - 1; i++) {
			product_d = p[i].Get_date();
			Date::split_date(product_d, start_y, start_m, start_d);
			Date product_date(start_y, start_m, start_d);

			if (today_date > product_date.addDays(p[i].Get_expire_in())) {
				res += p[i].Get_price();
			}
		}
		return res;
	}
};

class List {
	class Node {
	public:
		Node* next;
		Product data;

		Node(Product& p) {
			data = p;
			next = nullptr;
		}
	};

	void add(Product& p) {
		Node* new_node = new Node(p);
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
		Node* current;

	public:
		Iterator(Node* n) { current = n; }

		Product& operator*() const {
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

	void print_list() {
		for (Iterator it = begin(); it != end(); ++it) {
			(*it).print_product();
		}
	}

	List& operator<<(Product& p) {
		add(p);
		return *this;
	}

	List expired_product() {
		List res;
		string product_d;
		int start_y = 0, start_m = 0, start_d = 0, end_y = 0, end_m = 0, end_d = 0;

		Date::split_date("13.06.2023", end_y, end_m, end_d);
		Date today_date(end_y, end_m, end_d);

		for (Iterator it = begin(); it != end(); ++it) {
			product_d = (*it).Get_date();
			Date::split_date(product_d, start_y, start_m, start_d);
			Date product_date(start_y, start_m, start_d);

			if (product_date.addDays((*it).Get_expire_in()) > today_date) {
				res << *it;
			}
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
	return 0;
}
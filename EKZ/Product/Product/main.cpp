#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/*Створити бінарний файл, що являє собою каталог товарів магазину і 
містить наступну інформацію про товари, які є в наявності: назву товару, 
дату його оформлення, вартість одиниці товару, кількість одиниць даного товару. 

Спроєктувати клас Product, що характеризується назвою товару, датою його оформлення, 
вартістю одиниці товару, кількістю одиниць даного товару. 

На його основі розробити клас Stock, який містить масив товарів, що зберігаються на складі. 

Також спроєктувати клас List, елементами якого є об'єкти класу Product. 

Класи повинні мати конструктори, методи доступу, методи виведення об’єктів, 
методи для виконання поставленого завдання, можливо інші методи. АТД List реалізувати 
на основі зв’язного списку.

Розробити програму, яка створює об'єкт класу Stock, ініціалізуючи його даними із 
відповідного файлу. Визначити загальну вартість товару, який на поточний момент 
(вказану дату) зберігається на складі більше вказаного терміну (задається кількістю днів). 
Використовуючи клас List, сформувати список товарів на складі, вартість яких належить
заданому діапазону цін (вказується з клавіатури). Додавання елементів у List 
здійснювати за допомогою перевантаженого оператора “<<”, наприклад, список << елемент. 
Програма повинна забезпечувати наочне виведення усіх вхідних, вихідних та проміжних даних, 
а також контроль можливих помилок. Для обробки помилок використати виключні ситуації.*/

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
	string name;
	string date;
	float price;
	int quantity;
	int duration;

	void write_product_to_file() {
		ofstream file("product_binary_file", ios::binary | ios::app);
		if (!file.is_open()) {
			throw runtime_error("Error opening file");
		}
		else {
			file.write(reinterpret_cast<const char*>(this), sizeof(*this));
			file.close();
		}
	}

public:
	Product() {
		name = "";
		date = "";
		price = 0;
		quantity = 0;
		duration = 0;
	}

	Product(string n, string d, float p, int q, int dur) {
		name = n;
		date = d;
		price = p;
		quantity = q;
		duration = dur;
		write_product_to_file();
	}

	string Get_name() { return name; }
	void Set_name(string n){ name = n; }

	string Get_date() { return date; }
	void Set_date(string n) { date = n; }

	float Get_price() { return price; }
	void Set_price(float n) { price = n; }

	int Get_quantity() { return quantity; }
	void Set_quantity(int n) { quantity = n; }

	int Get_duration() { return duration; }
	void Set_duration(int n) { duration = n; }

	void print_product() {
		cout << "name: " << name << endl;
		cout << "date: " << date << endl;
		cout << "price: " << price << endl;
		cout << "quantity: " << quantity << endl;
		cout << "duration: " << duration << endl;
	}
};

class Stock {
	Product* p;
	int size = 10;
	int count;

public:
	Stock() {
		p = new Product[size];
		count = 0;
	}

	~Stock() { delete[] p; }

	void add_product(Product& pr) {
		if (count == size) {
			size *= 2;
			Product* new_pr = new Product[size];
			for (int i = 0; i < count - 1; i++) {
				new_pr[i] = p[i];
			}
			delete[] p; 
			p = new_pr;
		}
		p[count] = pr;
		count++;
	}

	void read_product_from_file() {
		ifstream file("product_binary_file", ios::binary);
		if (!file.is_open()) {
			throw runtime_error("Error opening file");
		}
		else {
			while (!file.eof()) {
				Product pr;
				file.read(reinterpret_cast<char*>(&pr), sizeof(Product));
				add_product(pr);
			}
			file.close();
		}
	}

	Product& operator[](const int& idx) {
		if (idx < 0 || idx >= count) {
			throw out_of_range("Index out of range");
		}
		return p[idx];
	}

	void print_stock() {
		for (int i = 0; i < count - 1; i++) {
			p[i].print_product();
			cout << endl;
		}
	}

	float all_expired_product_price() {
		int start_y = 0, start_m = 0, start_d = 0, end_y = 0, end_m = 0, end_d = 0;
		string product_date;
		Date::split_date("13.06.2023", end_y, end_m, end_d);
		Date d2(end_y, end_m, end_d);
		float res = 0;
		for (int i = 0; i < count - 1; i++) {
			product_date = p[i].Get_date();
			Date::split_date(product_date, start_y, start_m, start_d);
			Date d1(start_y, start_m, start_d);
			if (d1.addDays(p[i].Get_duration()) > d2) {
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
		Iterator(Node* node) { current = node; }

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

	List& operator<<(Product& p) {
		add(p);
		return *this;
	}

	void print_list() {
		for (Iterator it = begin(); it != end(); ++it) {
			(*it).print_product();
			cout << endl;
		}
	}

	List products_in_price_range(float r1, float r2) {
		List res;
		for (Iterator it = begin(); it != end(); ++it) {
			if (r1 <= (*it).Get_price() && r2 >= (*it).Get_price()) {
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

void input_product(Product* p, int& num, int& init) {
	int size = init;
	string name;
	string date;
	float price;
	int quantity;
	int duration;
	char choice = 'y';

	do {
		if (size == num) {
			size *= 2;
			Product* new_p = new Product[size];
			for (int i = 0; i < num; i++) {
				new_p[i] = p[i];
			}
			delete[] p;
			p = new_p;
		}

		cout << "name = ";
		cin >> name;
		cout << "date = ";
		cin >> date;
		cout << "price = ";
		cin >> price;
		cout << "quantity = ";
		cin >> quantity;
		cout << "duration = ";
		cin >> duration;

		new(&p[num]) Product(name, date, price, quantity, duration);
		num++;

		cout << "continue input [y/n]";
		cin >> choice;
		cin.ignore();
		cout << endl;
	} while (choice != 'n' && choice != 'N');
}

int main() {
	int num = 0, init = 10;
	Product* p = new Product[init];
	input_product(p, num, init);
	cout << "-------------------------------------------------------------" << endl;
	cout << "Product" << endl;
	for (int i = 0; i < num; i++) {
		p[i].print_product();
		cout << endl;
	}
	cout << "-------------------------------------------------------------" << endl;
	cout << "Stock" << endl;
	Stock s;
	s.read_product_from_file();
	s.print_stock();
	cout << "All expired product price: " << s.all_expired_product_price() << endl;
	cout << "-------------------------------------------------------------" << endl;
	cout << "List" << endl;
	List l;
	for (int i = 0; i < num; i++) {
		l << s[i];
	}
	l.print_list();
	List product_price_range = l.products_in_price_range(12.5, 15.68);
	cout << "Products in price range:" << endl;
	product_price_range.print_list();
	return 0;
}
#include <iostream>
#include<fstream>
using namespace std;

/*Створити бінарний файл, що являє собою список абонентів телекомунікаційної компанії
і містить наступну інформацію: ПІБ абонента, його домашня адреса, телефон, дата 
заключення контракту. 

Спроектувати клас Abonent, що має поля: ПІБ абонента, його домашня адреса, телефон. 

На його основі розробити клас Phone_book, який містить базу даних абонентів. 

Також спроектувати клас List, елементами якого є об'єкти класу Abonent. 

Класи повинні мати конструктори, методи доступу, методи виведення 
об'єктів, методи для виконання поставленого завдання, можливо інші методи. 

АТД List реалізувати на основі зв'язного списку. 

Розробити програму, яка створює об'єкт класу Phone_book, 
ініціалізуючи його даними із відповідного файлу. Визначити загальну кількість 
абонентів заданого населеного пункту (вводиться з клавіатури). 

Використовуючи клас List, сформувати список абонентів з якими 
заключено контракт на протязі останнього року. Додавання елементів у List 
здійснювати за допомогою перевантаженого оператора "<<", наприклад, 
список << елемент. Програма повинна забезпечувати наочне виведення усіх вхідних, 
вихідних та проміжних даних, а також контроль можливих помилок. Для обробки 
помилок використати виключні ситуації*/

class Abonent {
	string pib;
	string address;
	string number;
	string town;
	string date;

public:
	Abonent() {
		pib = "";
		address = "";
		number = "";
		town = "";
		date = "";
	}

	Abonent(string p) : Abonent() {
		pib = p;
	}

	Abonent(string p, string a) : Abonent(p) {
		address = a;
	}

	Abonent(string p, string a, string n) : Abonent(p, a) {
		number = n;
	}

	Abonent(string p, string a, string n, string t) : Abonent(p, a, n) {
		town = t;
	}

	Abonent(string p, string a, string n, string t, string d) : Abonent(p, a, n, t) {
		date = d;
	}

	string Get_pib() { return pib; }
	void Set_pib(string p) { pib = p; }

	string Get_address() { return address; }
	void Set_address(string p) { address = p; }

	string Get_number() { return number; }
	void Set_number(string p) { number = p; }

	string Get_town() { return town; }
	void Set_town(string p) { town = p; }

	string Get_date() { return date; }
	void Set_date(string p) { date = p; }

	void print_abonent() {
		cout << "pib: " << pib << endl;
		cout << "address: " << address << endl;
		cout << "phone number: " << number << endl;
		cout << "town: " << town << endl;
		cout << "date: " << date << endl;
	}

	void save_abonent_to_file() {
		ofstream file("abonent_binary_file", ios::binary | ios::app);
		if (!file.is_open()) {
			throw("Error opening file");
		}
		else {
			file.write(reinterpret_cast<const char*>(this), sizeof(*this));
			file.close();
		}
	}
};

class Phone_book {
	int size = 10;
	Abonent* a;
	int count;

public:
	Phone_book() {
		a = new Abonent[size];
		count = 0;
	}

	~Phone_book() { delete[] a; }

	void add_abonent(Abonent& abonent) {
		if (count == size) {
			size *= 2;
			Abonent* new_a = new Abonent[size];
			for (int i = 0; i < count; i++) {
				new_a[i] = a[i];
			}
			delete[] a;
			a = new_a;
		}

		a[count] = abonent;
		count++;
	}

	void read_from_file() {
		ifstream file("abonent_binary_file", ios::binary);
		if (!file.is_open()) {
			throw runtime_error("Error opening file");
		}
		Abonent b;
		while (file.read(reinterpret_cast<char*>(&b), sizeof(Abonent))) {
			add_abonent(b);
		}

		file.close();
	}

	int people_in_area(string t) {
		int areaCount = 0;
		for (int i = 0; i < count; i++) {
			if (a[i].Get_town() == t) {
				areaCount++;
			}
		}
		return areaCount;
	}

	void print_Phone_book() {
		for (int i = 0; i < count - 1; i++) {
			a[i].print_abonent();
			cout << endl;
		}
	}

	Abonent& operator[](const int& idx) {
		if (idx < 0 || idx >= count) {
			throw out_of_range("Index out of range");
		}
		return a[idx];
	}

	int length() { return count; }
};

class List {
	class Node {
	public:
		Node* next;
		Abonent data;

		Node(Abonent& a) {
			data = a;
			next = nullptr;
		}
	};

	void add(Abonent& a) {
		Node* new_node = new Node(a);
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
		Iterator(Node* node) { current = node; }

		Abonent& operator *() const{
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

	List() { head = nullptr; }

	~List() { clear(); }

	void print_list() {
		//Node* current = head;
		for (Iterator it = begin(); it != end(); ++it) {
			(*it).print_abonent();
			cout << endl;
		}
	}

	void clear() {
		Node* current = head;
		while (current) {
			Node* next = current->next;
			delete current;
			current = next;
		}
		head = nullptr;
	}

	List& operator <<(Abonent & a) {
		add(a);
		return *this;
	}

	List current_year_contracts() {
		List res;
		for (Iterator it = begin(); it != end(); ++it) {
			if ((*it).Get_date().find("2023") != string::npos) {
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

void input_abonent_for_file(Abonent* a, int& num, int& init) {
	string pib;
	string address;
	string number;
	string town;
	string date;
	char choice = 'y';
	int max_size = init;
	do {
		if (max_size == num) {
			max_size *= 2;
			Abonent* new_a = new Abonent[max_size];
			for (int i = 0; i < num; i++) {
				new_a[i] = a[i];
			}
			delete[] a;
			a = new_a;
		}

		cout << "pib = ";
		cin >> pib;
		cout << "address = ";
		cin >> address;
		cout << "phone number = ";
		cin >> number;
		cout << "town = ";
		cin >> town; 
		cout << "date = ";
		cin >> date;
		new (&a[num]) Abonent(pib, address, number, town, date);
		a[num].save_abonent_to_file();
		num++;

		cout << "continue input [y/n]";
		cin >> choice;
		cin.ignore();
		cout << endl;
	} while (choice != 'n' && choice != 'N');
}

int main() {
	int num = 0;
	int initial = 10;
	Abonent* a = new Abonent[initial];
	input_abonent_for_file(a, num, initial);
	cout << "-------------------------------------------------------------" << endl;
	cout << "Abonent" << endl;
	for (int i = 0; i < num; i++) {
		a[i].print_abonent();
		cout << endl;
	}
	cout << "-------------------------------------------------------------" << endl;
	cout << "Phone_book" << endl;
	Phone_book p;
	p.read_from_file();
	p.print_Phone_book();
	int people_in_area = p.people_in_area("town");
	cout << "Number of people in area: " << people_in_area << endl << endl;
	cout << "-------------------------------------------------------------" << endl;
	cout << "List" << endl;
	List l;
	for (int i = 0; i < p.length(); i++) {
		l << p[i];
	}
	l.print_list();
	List current_year_contracts = l.current_year_contracts();
	cout << "current year contracts: " << endl;
	current_year_contracts.print_list();
	return 0;
}
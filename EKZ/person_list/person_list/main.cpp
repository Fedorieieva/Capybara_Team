#include<iostream>
#include <fstream>

using namespace std;

/*Створити бінарний файл, що являє собою список контактів
і містить наступну інформацію: ПІБ людини, її домашня
адреса, телефон, електронна пошта.

Спроектувати клас Person, що має поля: прізвище, ім'я,
домашня адреса, телефон, електронна пошта.

На його основі розробити клас Notebook, який містить список людей.

Також спроектувати клас List, елементами якого є об'єкти класу Person.

Класи повинні мати конструктори, методи доступу,
методи виведення об'єктів, методи для виконання поставленого
завдання, можливо інші методи. АТД List реалізувати на основі
зв'язного списку.

Розробити програму, яка створює об'єкт класу
Notebook, ініціалізуючи його даними із відповідного файлу.
Визначити загальну кількість людей, які проживають у заданому
населеному пункті (вводиться з клавіатури).

Використовуючи клас List, сформувати список людей, які мають електронну
пошту Gmail. Додавання елементів у List здійснювати за
допомогою перевантаженого оператора "<<", наприклад,
список << елемент.

Програма повинна забезпечувати наочне
виведення усіх вхідних, вихідних та проміжних даних, а також
контроль можливих помилок. Для обробки помилок використати виключні ситуації*/

class Person {
private:
	string pib;
	string address;
	string phone_number;
	string e_mail;
	string town;

public:
	Person() {
		pib = "";
		address = "";
		phone_number = "";
		e_mail = "";
		town = "";
	}

	Person(string p) : Person() {
		pib = p;
	}

	Person(string p, string a) : Person(p) {
		address = a;
	}

	Person(string p, string a, string num) : Person(p, a) {
		phone_number = num;
	}

	Person(string p, string a, string num, string e) : Person(p, a, num) {
		e_mail = e;
	}

	Person(string p, string a, string num, string e, string t) : Person(p, a, num, e) {
		town = t;
	}

	string Get_pib() { return pib; }
	string Get_address() { return address; }
	string Get_phone_number() { return phone_number; }
	string Get_e_mail() { return e_mail; }
	string Get_town() { return town; }

	string Set_pib(string p) { pib = p; }
	string Set_address(string a) { address = a; }
	string Set_phone_number(string num) { phone_number = num; }
	string Set_e_mail(string e) { e_mail = e; }
	string Set_town(string t) { town = t; }

	void print_person() {
		cout << "pib: " << pib << endl;
		cout << "addreess: " << address << endl;
		cout << "phone number" << phone_number << endl;
		cout << "e-mail: " << e_mail << endl;
		cout << "town: " << town << endl;
	}

	void save_person_to_file() {
		ofstream file("people_binary_file", ios::binary | ios::app);
		if (!file.is_open()){
			throw("Error opening file");
		}
		else {
			file.write(reinterpret_cast<const char*>(this), sizeof(*this));
			file.close();
		}
	}
};

class Notebook {
private:
	int size = 10;
	Person* contacts;
	int count_contacts;

public:
	Notebook() {
		contacts = new Person[size];
		count_contacts = 0;
	}

	~Notebook() { delete[] contacts; }

	void add_contact(Person& p) {
		if (count_contacts == size) {
			size *= 2;
			Person* new_contacts = new Person[size];
			for (int i = 0; i < count_contacts; i++) {
				new_contacts[i] = contacts[i];
			}

			delete[] contacts;
			contacts = new_contacts;
		}

		contacts[count_contacts] = p;
		count_contacts++;
	}

	int num_people_in_area(string t) {
		int count = 0;
		for (int i = 0; i < count_contacts; i++) {
			if (contacts[i].Get_town() == t) {
				count++;
			}
		}
		return count;
	}

	int Get_count() { return count_contacts; }

	Person& operator[](const int& idx) {
		if (idx < 0 || idx >= count_contacts) {
			throw out_of_range("Index out of range");
		}
		return contacts[idx];
	}

	void print_notebook() {
		for (int i = 0; i < count_contacts; i++) {
			contacts[i].print_person();
			cout << endl;
		}
	}

	void read_from_file() {
		ifstream file("people_binary_file", ios::binary);
		if (!file.is_open()) {
			throw runtime_error("Error opening file");
		}
		while (!file.eof()) {
			Person p;
			file.read(reinterpret_cast<char*>(&p), sizeof(Person));
			add_contact(p);
		}
		file.close();
	}
};

class List {
private:
	class Node {
	public:
		Person data;
		Node* next;

		Node(Person& p) {
			data = p;
			next = nullptr;
		}
	};

	void add(Person& p) {
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
	private:
		Node* current;

	public:
		Iterator(Node* node) { current = node; }

		Person& operator*() const {
			return current->data;
		}

		Iterator& operator++() {
			if (current != nullptr) {
				current = current->next;
			}
			return *this;
		}

		bool operator!=(const Iterator& other) const {
			return current != other.current;
		}		
	};

	List() { head = nullptr; }

	List& operator <<(Person& p) {
		add(p);
		return *this;
	}

	void print_list () {
		Node* current = head;
		while (current != nullptr) {
			cout << "pib: " << current->data.Get_pib() << endl;
			cout << "address: " << current->data.Get_address() << endl;
			cout << "phone number: " << current->data.Get_phone_number() << endl;
			cout << "e-mail: " << current->data.Get_e_mail() << endl;
			cout << "town: " << current->data.Get_town() << endl << endl;
			current = current->next;
		}
	}

	List gmail_list() {
		List gmail_people;
		for (Iterator it = begin(); it != end(); ++it) {
			if ((*it).Get_e_mail().find("gmail") != string::npos) {
				gmail_people << *it;
			}
		}
		return gmail_people;
	}

	Iterator begin() {
		return Iterator(head);
	}

	Iterator end() {
		return Iterator(nullptr);
	}
};

void people_file_input(Person* p, int& count, int& init) {
	string pib;
	string address;
	string phone_number;
	string e_mail;
	string town;
	char choice = 'y';
	int max_size = init;
	do {
		if (max_size == count) {
			max_size *= 2;
			Person* new_p = new Person[max_size];
			for (int i = 0; i < count; i++) {
				new_p[i] = p[i];
			}
			delete[] p;
			p = new_p;
		}
		cout << "pib = ";
		cin >> pib;
		cout << "address = ";
		cin >> address;
		cout << "phone number = ";
		cin >> phone_number;
		cout << "e-mail = ";
		cin >> e_mail;
		cout << "town = ";
		cin >> town;

		new (&p[count]) Person (pib, address, phone_number, e_mail, town);
		p[count].save_person_to_file();
		count++;

		cout << "continue input [y/n]";
		cin >> choice;
		cin.ignore();
		cout << endl;
	} while (choice != 'n' && choice != 'N');
	cout << "-------------------------------------------------------------" << endl;
	cout << "Person" << endl;
	for (int i = 0; i < 5; i++) {
		p[i].print_person();
		cout << endl;
	}
}

int main() {
	int num = 0;
	int initial = 10;
	Person* people = new Person[initial];
	people_file_input(people, num, initial);
	Notebook n;
	n.read_from_file();
	cout << "-------------------------------------------------------------" << endl;
	cout << "Notebook" << endl;
	n.print_notebook();
	int num_people_in_area = n.num_people_in_area("town");
	cout << "Number of people in area: " << num_people_in_area << endl << endl;
	List l;
	for (int i = 0; i < num; i++) {
		l << n[i];
	}
	cout << "-------------------------------------------------------------" << endl;
	cout << "List" << endl;
	l.print_list();
	List gmail_list = l.gmail_list();
	cout << "People with gmail list: " << endl;
	gmail_list.print_list();


	return 0;
}
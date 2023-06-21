#include <iostream>
#include <fstream>

using namespace std;

/*Створити структуру для представлення дому з атрибутами міста, 
назви вулиці та номеру будинку. 

Створити структуру даних множина, що містить  унікальні об’єкти 
структури дім та підтримує операції додавання, видалення та перевірки 
наявності елементу та метод виведення множини у консоль.

Прийняти на вхід дані про задану кількість домів, внести
створені об’єкти у множину, але, якщо елементи повторюються, то вносити 
об’єкти у іншу множину і видаляти з першої. Після цього попросити користувача 
змінити інформацію про доми, що повторюються, і внести змінені об’єкти домів 
у першу множину.*/

class House {
	string street;
	string town;
	string house_number;

public:
	House() {
		street = "";
		town = "";
		house_number = "";
	}

	House(string s, string t, string h) {
		street = s;
		town = t;
		house_number = h;
	}

	string Get_street() { return street; }
	void Set_street(string s) { street = s; }

	string Get_town() { return town; }
	void Set_town(string s) { town = s; }

	string Get_house_number() { return house_number; }
	void Set_house_number(string s) { house_number = s; }

	void print_house() {
		cout << "street: " << street << endl;
		cout << "town: " << town << endl;
		cout << "house_number: " << house_number << endl << endl;
	}

	bool operator==(House& other) {
		return street == other.Get_street() && town == other.Get_town() && house_number == other.Get_house_number();
	}
};

class set_house {
	class Node {
	public:
		Node* next;
		House data;

		Node(House& h) {
			data = h;
			next = nullptr;
		}
	};

	Node* head;

public:
	set_house() { head = nullptr; }

	~set_house() { clear(); }

	void clear() {
		Node* curr = head;
		while (curr) {
			Node* tmp = curr;
			curr = curr->next;
			delete tmp;
		}
		head = nullptr;
	}

	bool is_present(House& h) {
		Node* curr = head;
		while (curr) {
			if (curr->data == h) {
				return true;
			}
			curr = curr->next;
		}
		return false;
	}

	void insert(House& h) {
		if (is_present(h)) {
			return;
		}

		Node* new_node = new Node(h);
		if (!head) {
			new_node->next = head;
			head = new_node;
		}
		else {
			Node* curr = head;
			while (curr->next) {
				curr = curr->next;
			}
			new_node->next = curr->next;
			curr->next = new_node;
		}
	}

	void remove(House& h) {
		if (!head || !is_present(h)) {
			return;
		}
		Node* curr = head;
		while (curr->next && !is_present(h)) {
			curr = curr->next;
		}

		if (curr->next && curr->next->data == h) {
			Node* tmp = curr->next;
			curr->next = curr->next->next;
			delete tmp;
		}
	}

	void display() {
		Node* curr = head;
		while (curr) {
			curr->data.print_house();
			curr = curr->next;
		}
	}
};

int main() {
	set_house set_h;
	House h1("time", "vin", "6464f");
	House h2("string", "four", "54558");
	House h3("little", "hire", "48de");
	set_h.insert(h1);
	set_h.insert(h2);
	set_h.insert(h3);
	set_h.remove(h2);
	set_h.display();
	return 0;
}

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/*Спроектувати клас «Множина цілих чисел» (АТД), який є спадкоємцем 
абстрактного класу «Структура даних». 

Визначити для базового класу абстрактну функцію Операція,
перевизначивши її в дочірньому класі для визначення перетину двох множин. 

Класи повинні також мати конструктори, у тому числі порожній, метод 
виведення об’єктів даного класу,

Розробити програму, яка створює два об’єкта-множини, кожна з яких є
символами, введеного з клавіатури, слова, і визначає їх перетин.

Записати кожну вхідну множину і отриманий їх перетин у окремі рядки 
текстового файлу, відділивши елементи множин двокрапкою. Вивести 
(програмно) вміст створеного файлу для перегляду*/

class int_set;

class data_structure {
public:
	virtual int_set operation(int_set& i_set) = 0;
};

class int_set : public data_structure {
	class Node {
	public:
		int data;
		Node* next;

		Node(int val) {
			data = val;
			next = nullptr;
		}
	};

	Node* head;

public:
	int_set() { head = nullptr; }

	~int_set() { clear(); }

	bool is_present(int val) {
		Node* current = head;
		while (current && current->data <= val) {
			if (current->data == val) {
				return true;
			}
			current = current->next;
		}
		return false;
	}

	void insert(int val) {
		if (is_present(val)) {
			return;
		}

		Node* new_node = new Node(val);

		if (!head || val < head->data) {
			new_node->next = head;
			head = new_node;
		}
		else {
			Node* current = head;
			while (current->next && current->next->data < val) {
				current = current->next;
			}
			new_node->next = current->next;
			current->next = new_node;
		}
	}

	void clear() {
		Node* current = head;
		while (current) {
			Node* temp = current;
			current = current->next;
			delete temp;
		}
		head = nullptr;
	}

	void remove(int val) {
		if (!head || val < head->data) {
			return;
		}

		if (head->data == val) {
			Node* temp = head;
			head = head->next;
			delete temp;
			return;
		}

		Node* current = head;
		while (current->next && current->next->data < val) {
			current = current->next;
		}

		if (current->next && current->next->data == val) {
			Node* temp = current->next;
			current->next = current->next->next;
			delete temp;
		}
	}

	void display() const {
		Node* current = head;
		while (current) {
			cout << current->data << " ";
			current = current->next;
		}
		cout << endl;
	}

	int_set operation(int_set& i_set) {
		int_set res;
		Node* current = head;
		while (current) {
			if (i_set.is_present(current->data)) {
				res.insert(current->data);
			}
			current = current->next;
		}
		return res;
	}

	void write_to_file() {
		ofstream file("int_set_file");
		if (!file.is_open()) {
			throw runtime_error("Error opening file");
		}
		Node* current = head;
		while (current) {
			file << current->data;
			if (current->next) {
				file << ":";
			}
			current = current->next;
		}
		file.close();
	}

	void display_file_constents() {
		ifstream file("int_set_file");
		if (!file.is_open()) {
			throw runtime_error("Error opening file");
		}
		string line;
		while (getline(file, line))	{
			cout << line << endl;
		}
		cout << endl;
		file.close();
	}
};

int main() {
	int_set a;
	int_set b;
	a.insert(1);
	a.insert(2);
	a.insert(3);

	b.insert(2);
	b.insert(3);
	b.insert(4);

	int_set c = a.operation(b);
	c.display();

	return 0;
}
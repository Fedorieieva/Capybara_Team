#include <iostream>
#include <fstream>

using namespace std;

/*�������� ������� ����, �� ����� ����� ������ ������� � ������ ��� 
����� �������� �� �����, �����, ���� �������� �����������.

����������� ���� Program, �� ��������������� ������ ��������, 
�� �������, ����� �������� �����������. 

�� ����� ������ ����� ��������� ���� Program_archive, 
���� ������ ��� ��� ��������� �������. 

����� ����������� ���� List, ���������� ����� � ��'���� ����� Program. 

����� ������ ���� ������������, ������ �������, ������ ��������� �ᒺ���,
������ ��� ��������� ������������ ��������, ������� ���� ������. 

��������� ��������, ��� ������� ��'��� ����� Program_archive, '
����������� ���� ������ �� ���������� �����.
��������� ������� �������, �� ������� ��� ����������� � ������� ����� 
(��������� � ���������). �������������� ���� List, 
���������� ������ �������, ����� ���� �������� ������� (��������� � ���������). 
��������� �������� � List ���������� ��
��������� ��������������� ��������� �<<�, ���������, ������ << �������.�������� 
������� ������������� ������ ��������� ��� �������,
�������� �� �������� �����, � ����� �������� �������� �������.
��� ������� ������� ����������� ������� ��������.*/

class Program {
	string name;
	string size;
	string date;

	void add_to_file() {
		ofstream file("program_binry_file", ios::binary | ios::app);
		if (!file.is_open()) {
			throw("Error opening file");
		}
		else {
			file.write(reinterpret_cast<const char*>(this), sizeof(*this));
			file.close();
		}
	}

public:
	Program() {
		name = "";
		size = "";
		date = "";
	}

	Program(string n, string s, string d) {
		name = n;
		size = s;
		date = d;
		add_to_file();
	}

	string Get_name() { return name; }
	void Set_name(string n) { name = n; }

	string Get_size() { return size; }
	void Set_size(string n) { size = n; }

	string Get_date() { return date; }
	void Set_date(string n) { date = n; }

	void print_program() {
		cout << "name: " << name << endl;
		cout << "size: " << size << endl;
		cout << "date: " << date << endl << endl;
	}
};

class Program_archive {
	int size = 10;
	int count;
	Program* p;

public:
	Program_archive() {
		p = new Program[size];
		count = 0;
	}

	~Program_archive() { delete[] p; }

	void add_program(Program& pr) {
		if (count == size) {
			size *= 2;
			Program* new_p = new Program[size];
			for (int i = 0; i < count; i++) {
				new_p[i] = p[i];
			}
			delete[] p;
			p = new_p;
		}

		p[count] = pr;
		count++;
	}

	void read_from_file() {
		ifstream file("program_binry_file", ios::binary);
		if (!file.is_open()) {
			throw runtime_error("Error opening file");
		}
		Program b;
		while (file.read(reinterpret_cast<char*>(&b), sizeof(Program))) {
			
			add_program(b);
		}
		file.close();
	}

	void print_program_archive() {
		for (int i = 0; i < count; i++) {
			p[i].print_program();
		}
	}

	Program& operator[](const int& idx) {
		if (idx < 0 || idx >= count) {
			throw out_of_range("Index out of range");
		}
		return p[idx];
	}
};

class double_linked_list {
	class Node {
	public:
		Program data;
		Node* next;
		Node* prev;

		Node(Program& p) {
			data = p;
			next = nullptr;
			prev = nullptr;
		}
	};

	Node* head;
	Node* tail;

public:
	class Iterator {
		Node* current;

	public:
		Iterator(Node* n) { current = n; }

		Program& operator*() const {
			return current->data;
		}

		Iterator& operator++() {
			if (current != nullptr) {
				current = current->next;
			}
			return *this;
		}

		Iterator& operator--() {
			if (current != nullptr) {
				current = current->prev;
			}
			return *this;
		}

		bool operator!=(const Iterator& other) {
			return current != other.current;
		}
	};

	double_linked_list() {
		head = nullptr;
		tail = nullptr;
	}

	~double_linked_list() { clear(); }

	void insert_At_begining(Program& p) {
		Node* new_node = new Node(p);

		if (head == nullptr) {
			head = new_node;
			tail = new_node;
		}
		else {
			new_node->next = head;
			head->prev = new_node;
			head = new_node;
		}
	}

	void insert_end(Program& p) {
		Node* new_node = new Node(p);

		if (tail == nullptr) {
			head = new_node;
			tail = new_node;
		}
		else {
			new_node->prev = tail;
			tail->next = new_node;
			tail = new_node;
		}
	}

	void clear() {
		Node* curr = head;
		while (curr) {
			Node* tmp = curr;
			curr = curr->next;
			delete tmp;
		}
		head = nullptr;
	}

	void print_list() {
		for (Iterator it = begin(); it != end(); ++it) {
			(*it).print_program();
		}
	}

	void print_list_reverse() {
		Iterator it(tail);
		while (it != end()) {
			(*it).print_program();
			--it;
		}
	}

	double_linked_list& operator<<(Program& p) {
		insert_At_begining(p);
		return *this;
	}

	Iterator begin() {
		return Iterator(head);
	}

	Iterator end() {
		return Iterator(nullptr);
	}
};

void input_abonent_for_file(Program* a, int& num, int& init) {
	string name;
	string size;
	string date;
	char choice = 'y';
	int max_size = init;
	do {
		if (max_size == num) {
			max_size *= 2;
			Program* new_a = new Program[max_size];
			for (int i = 0; i < num; i++) {
				new_a[i] = a[i];
			}
			delete[] a;
			a = new_a;
		}

		cout << "name = ";
		cin >> name;
		cout << "size = ";
		cin >> size;
		cout << "date = ";
		cin >> date;
		new (&a[num]) Program(name, size, date);
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
	Program* a = new Program[initial];
	input_abonent_for_file(a, num, initial);
	cout << "-------------------------------------------------------------" << endl;
	cout << "Program" << endl;
	for (int i = 0; i < num; i++) {
		a[i].print_program();
	}
	cout << "-------------------------------------------------------------" << endl;
	cout << "Program_archive" << endl;
	Program_archive p;
	p.read_from_file();
	p.print_program_archive();
	cout << "-------------------------------------------------------------" << endl;
	cout << "List" << endl;
	double_linked_list l;
	for (int i = 0; i < num; i++) {
		l << p[i];
	}
	l.print_list();
	cout << "-------------------------------------------------------------" << endl;
	cout << "Reverse List" << endl;
	l.print_list_reverse();
	return 0;
}
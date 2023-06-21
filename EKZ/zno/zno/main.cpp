#include <iostream>
#include <fstream>

using namespace std;

/*Створити бінарний файл, що являє собою список абітурієнтів і містить наступну
інформацію: ПІБ абітурієнта, його домашню адресу, предмети, по яким здавалося 
ЗНО, та відповідні бали. 

Спроєктувати клас Entrant, що має поля: ПІБ абітурієнта,його домашню адресу, 
предмети, по яким здавалося ЗНО, та відповідні бали. 

На його основі розробити клас Entrants_rating, який містить список абітурієнтів 
та інформацію про них. 

Також спроектувати клас List, елементами якого є об'єкти класу Entrant. 

Класи повинні мати конструктори, методи доступу, методи виведення об'єктів, 
методи для виконання поставленого завдання, можливо інші методи. 

Розробити програму, яка створює об'єкт класу Entrants_rating, ініціалізуючи його даними 
із відповідного файлу. Визначити кількість абітурієнтів, середній рейтинговий 
бал яких менше 150. Використовуючи клас List, сформувати список абітурієнтів, 
що стали студентами (сума балів у яких більша за заданий прохідний бал), 
впорядкований за спаданням їхнього сумарного балу ЗНО. 

Програма повинна забезпечувати наочне виведення усіх вхідних, вихідних та проміжних даних 
(з використанням перевантаженого стандартного оператора потокового виведення «<<»), 
а також контроль можливих помилок. Для обробки помилок використати виключні ситуації.*/

class Entrant {
	string pib;
	string address;
	string sugject1;
	string sugject2;
	string sugject3;
	int grade1;
	int grade2;
	int grade3;

	void save_entrant_to_file() {
		ofstream file("entrant_biinary_file", ios::binary | ios::app);
		if (!file.is_open()) {
			throw runtime_error("Error opening file");
		}
		else {
			file.write(reinterpret_cast<const char*>(this), sizeof(*this));
			file.close();
		}
	}

public:
	Entrant() {
		pib = "";
		address = "";
		sugject1 = "";
		sugject2 = "";
		sugject3 = "";
		grade1 = 0;
		grade2 = 0;
		grade3 = 0;
	}

	Entrant(string& p, string& a, string& s1, string& s2, string& s3, int& g1, int& g2, int& g3) {
		pib = p;
		address = a;
		sugject1 = s1;
		sugject2 = s2;
		sugject3 = s3;
		grade1 = g1;
		grade2 = g2;
		grade3 = g3;
		save_entrant_to_file();
	}

	string Get_pib() { return pib; }
	void Set_pib(string p) { pib = p; }

	string Get_address() { return address; }
	void Set_address(string p) { address = p; }

	string Get_sugject1() { return sugject1; }
	void Set_sugject1(string p) { sugject1 = p; }

	string Get_sugject2() { return sugject2; }
	void Set_sugject2(string p) { sugject2 = p; }

	string Get_sugject3() { return sugject3; }
	void Set_sugject3(string p) { sugject3 = p; }

	int Get_grade1() { return grade1; }
	void Set_grade1(int p) { grade1 = p; }

	int Get_grade2() { return grade2; }
	void Set_grade2(int p) { grade2 = p; }

	int Get_grade3() { return grade3; }
	void Set_grade3(int p) { grade3 = p; }

	void print_entrant() {
		cout << "pib: " << pib << endl;
		cout << "address: " << address << endl;
		cout << "sugject1: " << sugject1 << endl;
		cout << "sugject2: " << sugject2 << endl;
		cout << "sugject3: " << sugject3 << endl;
		cout << "grade1: " << grade1 << endl;
		cout << "grade2: " << grade2 << endl;
		cout << "grade3: " << grade3 << endl;
	}
};

class Entrants_rating {
	Entrant* e;
	int size = 10;
	int count;

public:
	Entrants_rating() {
		e = new Entrant[size];
		count = 0;
	}

	~Entrants_rating() { delete[] e; }

	void add_entrant(Entrant& en) {
		if (count == size) {
			size *= 2;
			Entrant* new_e = new Entrant[size];
			for (int i = 0; i < count; i++) {
				new_e[i] = e[i];
			}
			delete[] e;
			e = new_e;
		}
		e[count] = en;
		count++;
	}

	void read_from_file() {
		ifstream file("entrant_biinary_file", ios::binary);
		if (!file.is_open()) {
			throw runtime_error("Error opening file");
		}
		else {
			while (!file.eof()) {
				Entrant en;
				file.read(reinterpret_cast<char*>(&en), sizeof(Entrant));
				add_entrant(en);
			}
			file.close();
		}
	}

	void print_entrant_rating() {
		for (int i = 0; i < count - 1; i++) {
			e[i].print_entrant();
			cout << endl;
		}
	}

	int num_entrants_worst_rating() {
		int rating = 0, average = 0;
		for (int i = 0; i < count - 1; i++) {
			average = (e[i].Get_grade1() + e[i].Get_grade2() + e[i].Get_grade3()) / 2;
			if (average < 150) {
				rating++;
			}
		}
		return average;
	}

	Entrant& operator[](const int& idx) {
		if (idx < 0 || idx >= count) {
			throw out_of_range("Index out of range");
		}
		return e[idx];
	}
};

class List {
	class Node {
	public:
		Node* next;
		Entrant data;

		Node(Entrant& e) {
			data = e;
			next = nullptr;
		}
	};

	void add(Entrant& en) {
		Node* new_node = new Node(en);
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

	void sort() {
		Node* current = head;
		int length = 0;

		while (current != nullptr) {
			length++;
			current = current->next;
		}

		Node** node_arr = new Node * [length];
		current = head;
		for (int i = 0; i < length; i++) {
			node_arr[i] = current;
			current = current->next;
		}

		for (int i = 0; i < length - 1; i++) {
			for (int j = 0; j < length - i - 1; j++) {
				int sum1 = node_arr[i]->data.Get_grade1() + node_arr[i]->data.Get_grade2() + node_arr[i]->data.Get_grade3();
				int sum2 = node_arr[j + 1]->data.Get_grade1() + node_arr[j + 1]->data.Get_grade2() + node_arr[j + 1]->data.Get_grade3();
				if (sum1 < sum2) {
					Node* temp = node_arr[j];
					node_arr[j] = node_arr[j + 1];
					node_arr[j + 1] = temp;
				}
			}
		}

		head = node_arr[0];
		current = head;
		for (int i = 0; i < length; i++) {
			current->next = node_arr[i];
			current = current->next;
		}
		current->next = nullptr;
		delete[] node_arr;
	}

	Node* head;

public:
	class Iterator {
	private:
		Node* current;

	public:
		Iterator(Node* n) { current = n; }

		Entrant& operator*() const {
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

	List& operator<<(Entrant& en) {
		add(en);
		return *this;
	}

	void print_list() {
		for (Iterator it = begin(); it != end(); ++it) {
			(*it).print_entrant();
			cout << endl;
		}
	}

	List entrant_rating_above(int& num) {
		int sum_rating = 0;
		List res;
		for (Iterator it = begin(); it != end(); ++it) {
			sum_rating = (*it).Get_grade1() + (*it).Get_grade2() + (*it).Get_grade3();
			if (sum_rating > num) {
				res << *it;
			}
		}

		res.sort();
		return res;
	}

	Iterator begin() {
		return Iterator(head);
	}

	Iterator end() {
		return Iterator(nullptr);
	}
};

void input_entrant(Entrant* e, int& num, int& init) {
	string pib;
	string address;
	string sugject1;
	string sugject2;
	string sugject3;
	int grade1;
	int grade2;
	int grade3;
	char choice = 'y';
	int size = init;

	do {
		if (num == size) {
			size *= 2;
			Entrant* new_e = new Entrant[size];
			for (int i = 0; i < num; i++) {
				new_e[i] = e[i];
			}

			delete[] e;
			e = new_e;
		}

		cout << "pib = ";
		cin >> pib;
		cout << "address = ";
		cin >> address;
		cout << "sugject1 = ";
		cin >> sugject1;
		cout << "sugject2 = ";
		cin >> sugject2;
		cout << "sugject3 = ";
		cin >> sugject3;
		cout << "grade1 = ";
		cin >> grade1;
		cout << "grade2 = ";
		cin >> grade2;
		cout << "grade3 = ";
		cin >> grade3;

		new(&e[num]) Entrant(pib, address, sugject1, sugject2, sugject3, grade1, grade2, grade3);
		num++;
		cout << "continue input [y/n]";
		cin >> choice;
		cin.ignore();
		cout << endl;
	} while (choice != 'n' && choice != 'N');

}

int main() {
	int num = 0, initial = 10;
	Entrant* e = new Entrant[initial];
	input_entrant(e, num, initial);
	cout << "-------------------------------------------------------------" << endl;
	cout << "Entrant" << endl;
	for (int i = 0; i < num; i++) {
		e[i].print_entrant();
		cout << endl;
	}
	cout << "-------------------------------------------------------------" << endl;
	cout << "Entrants rating" << endl;
	Entrants_rating er;
	er.read_from_file();
	er.print_entrant_rating();
	int num_worst_rating = er.num_entrants_worst_rating();
	cout << "number of entrants with grade < 150: " << num_worst_rating << endl;
	cout << "-------------------------------------------------------------" << endl;
	cout << "List" << endl;
	List l;
	for (int i = 0; i < num; i++) {
		l << er[i];
	}
	l.print_list();
	List best_rating = l.entrant_rating_above(num_worst_rating);
	cout << "list entrants with best rating:" << endl;
	best_rating.print_list();

	return 0;
}
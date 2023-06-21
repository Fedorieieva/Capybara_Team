#include <iostream>

using namespace std;

class Node {
public:
	string data;
	Node* next;

	Node() {
		data = "";
		next = NULL;
	}

	Node(string val) {
		data = val;
		next = NULL;
	}
};

class Spisok {
private:
	Node* head;

public:
	Spisok() { head = NULL; }

	void push(string val) {
		Node* new_node = new Node(val);

		if (head == NULL) {
			head = new_node;
			return;
		}

		Node* temp = head;

		while (temp->next != NULL) {
			temp = temp->next;
		}

		temp = temp->next;
	}

	void delete_at_idx(int idx) {
		Node* temp1 = head;
		Node* temp2 = NULL;
		int size = 0;

		if (head == NULL) {
			cout << "list empty" << endl;
			return;
		}

		while (temp1 != NULL) {
			temp1 = temp1->next;
			size++;
		}

		if (size < idx) {
			cout << "idx put of range" << endl;
			return;
		}

		temp1 = head;

		if (idx == 1) {
			head = head->next;
			delete temp1;
			return;
		}

		while (idx-- > 1) {
			temp2 = temp1;
			temp1 = temp1->next;
		}

		temp2->next = temp1->next;

		delete temp1;
	}

	void print() {
		Node* temp = head;

		if (head == NULL) {
			cout << "list empty" << endl;
			return;
		}

		while (temp != NULL) {
			cout << temp->data << " ";
			temp = temp->next;
		}
	}
};

class B {
private:
	string s;
	
public:
	B() { s = ""; }

	B(string val) { s = val; }

	void virtual output() {
		cout << "class B: " << s << endl;
	}
};

class D1 : public B {
private:
	string s1;

public:
	D1() { s1 = ""; }

	D1(string val) { s1 = val; }

	void output() override {
		cout << "class D1: " << s1 << endl;
	}
};

class D2 : private virtual B {
private:
	string s2;

public:
	D2() { s2 = ""; }

	D2(string val) { s2 = val; }

	void output() override {
		cout << "class D2: " << s2 << endl;
	}
};

class D3 : private virtual B {
private:
	string s3;

public:
	D3() { s3 = ""; }

	D3(string val) { s3 = val; }

	void output() override {
		cout << "class D3: " << s3 << endl;
	}
};

class D4 : private D1 {
private:
	string s4;

public:
	D4() { s4 = ""; }

	D4(string val) { s4 = val; }

	string get_s4() { return s4; }

	void output() override {
		cout << "class D4: " << s4 << endl;
	}
};

class D5 : public D2, private D3 {
private:
	string s5;

public:
	D5() { s5 = ""; }

	D5(string val) { s5 = val; }

	string get_s5() { return s5; }

	void output() override {
		cout << "class D5: " << s5 << endl;
	}
};

int main() {
	D4 d4("class");
	D5 d5("MKR");
	Spisok res;
	res.push(d4.get_s4());
	res.push(d5.get_s5());
	res.print();
	return 0;
}
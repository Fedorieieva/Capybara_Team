#include <iostream>
#include <fstream>
#include <string>

/*Develop a class "Geometric Progression", 
which is defined by the first term a0, the 
common ratio q, and the number of terms n. 
Create an array of objects of this class. 
Determine the progression (its number) that 
has the largest last term. Write to files.*/

using namespace std;

class Progression {
	double b;
	double q;
	int n;

	void check_input() {
		if (b == 0 || q == 0) {
			cout << "[Error] b and q cannot be equal to 0 " << endl;
			exit(1);
		}
	}

public:
	Progression() { b = 0; q = 0; n = 0; }

	Progression(double bval, double qval, int nval) {
		b = bval;
		q = qval;
		n = nval;
		check_input();
	}

	double last_el() {
		return b * pow(q, n - 1);
	}

	friend ostream& operator <<(ostream& os, const Progression& p) {
		os << "b = " << p.b << endl;
		os << "q = " << p.q << endl;
		os << "n = " << p.n << endl;
		return os;
	}

	friend ofstream& operator <<(ofstream& of, const Progression& p) {
		of << "b = " << p.b << endl;
		of << "q = " << p.q << endl;
		of << "n = " << p.n << endl;
		return of;
	}
};

void progression_input(double& b, double& q, int& num) {
	cout << "Please provide input for your geometric progression:" << endl;
	cout << "b = ";
	cin >> b;
	cout << "q = ";
	cin >> q;
	cout << "n = ";
	cin >> num;
}

void input(Progression* p, int& n, int initial) {
	int num, choice = 1;
	double b, q;
	int max_size = initial;

	do {
		if (n == max_size) {
			max_size *= 2;
			Progression* new_p = new Progression[max_size];
			for (int i = 0; i < n; i++){
				new_p[i] = p[i];
			}
			delete[] p;
			p = new_p;
		}

		progression_input(b, q, num);
		new(&p[n]) Progression(b, q, num);
		n++;

		cout << "Enter 0 if you want to stop providing input: ";
		cin >> choice;
		cin.ignore();
		cout << endl;

	} while (choice != 0);

}

void print_input(Progression* p, int n) {
	cout << "Here you can see the input you`ve provided: " << endl;
	for (int i = 0; i < n; i++) {
		cout << endl << "Geometric progression " << i + 1 << ":" << endl;
		cout << p[i];
	}
	cout << endl;
}

int count_last_el(Progression* p, int n) {
	double temp = p[0].last_el();
	int max_el = 0;
	cout << "Here you can see the last element of each progression: " << endl;
	for (int i = 0; i < n; i++) {
		cout << endl << "Last element of each progression " << i + 1 << ":" << endl;
		cout << "Last element " << i + 1 << " = " << p[i].last_el() << endl;
		if (p[i].last_el() > temp) {
			temp = p[i].last_el();
			max_el = i;
		}
	}
	return max_el;
}

void write_to_file_txt(Progression* p, int n) {
	ofstream file;
	file.open("file.txt");

	for (int i = 0; i < n; i++) {
		file << "Geometric progression " << i + 1 << ":" << endl;
		file << p[i];
		file << "Last element " << i + 1 << " = " << p[i].last_el() << endl;		
	}
	file.close();
}

void write_to_file_bin(Progression* p, int n) {
	string str1, str2;
	ofstream file("file2.dat", ios::binary);
	for (int i = 0; i < n; i++) {
		str1 = "Geometric progression " + to_string(i + 1) + ":\n";
		file.write(reinterpret_cast<const char*>(&str1[0]), str1.size());
		file.write(reinterpret_cast<const char*>(&p[i]), sizeof(Progression));
		str2 = "Last element " + to_string(i + 1) + " = " + to_string(p[i].last_el()) + "\n";
		file.write(reinterpret_cast<const char*>(&str2[0]), str2.size());
	}
	file.close();
}

int main() {
	int num = 0, initial = 10;

	Progression* p = new Progression[initial];

	input(p, num, initial);

	print_input(p, num);

	int i = count_last_el(p, num);

	cout << endl << "Here you can see the greatest last element of all geometric progressions:" << endl;
	cout << "Last element of geometric progression " << i + 1 << " = " << p[i].last_el() << endl;

	write_to_file_txt(p, num);
	write_to_file_bin(p, num);

	return 0;
}

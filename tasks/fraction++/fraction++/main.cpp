#include <iostream>
#include <string>

/*Design a class to represent a proper fraction, 
which is defined by its numerator and denominator. 
The class should have a constructor with a parameter 
that is a string of the form "numerator/denominator" 
(for example, "7/9"), as well as possibly other 
constructors, a method to output the fraction object, 
possibly other input/output methods, and methods to 
perform the required tasks. Develop a program that 
creates two proper fractions and increments the value 
of the larger one (using the overloaded operator "++>"). 
The program should provide a clear display of all input, 
output, and intermediate data (using the overloaded 
standard output stream operator "<<<").*/

using namespace std;

class Fraction {
	string fraction;

	void check_input() {
		int pos = fraction.find("/");
		if (stoi(fraction.substr(pos + 1)) == 0) {
			cout << "[Error] division by 0" << endl;
			exit(1);
		}
	}

public:
	Fraction() { fraction = ""; }

	Fraction(string str) { fraction = str; }

	bool operator >(const Fraction& other) {
		int n1, n2, d1, d2;
		int pos = this->fraction.find("/");
		n1 = stoi(this->fraction.substr(0, pos));
		d1 = stoi(this->fraction.substr(pos + 1));

		pos = other.fraction.find("/");
		n2 = stoi(other.fraction.substr(0, pos));
		d2 = stoi(other.fraction.substr(pos + 1));

		n1 *= d2, n2 *= d1;

		return n1 > n2;
	}

	Fraction& operator ++() {
		int pos = this->fraction.find("/");
		int n1 = stoi(this->fraction.substr(0, pos));
		int d1 = stoi(this->fraction.substr(pos + 1));

		this->fraction = to_string(n1 + d1) + "/" + to_string(d1);
		return *this;
	}

	friend ostream& operator << (ostream& os, const Fraction& f) {
		os << f.fraction;
		return os;
	}
};

int main() {
	string str;

	cout << "Enter your fraction (example 3/7)" << endl;
	cout << "Fraction 1 = ";
	cin >> str;
	Fraction frac1(str);

	cout << endl << "Enter your fraction (example 3/7)" << endl;
	cout << "Fraction 2 = ";
	cin >> str;
	Fraction frac2(str);

	cout << endl << "Fraction 1 = " << frac1 << endl;
	cout << "Fraction 2 = " << frac2 << endl;

	cout << endl << "The greater fraction is: ";
	if (frac1 > frac2) {
		cout << frac1 << endl;
		++frac1;
	}
	else {
		cout << frac2 << endl;
		++frac2;
	}

	cout << endl << "Fraction 1 = " << frac1 << endl;
	cout << "Fraction 2 = " << frac2 << endl;


	return 0;
}
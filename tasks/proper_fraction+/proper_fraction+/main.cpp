#include <iostream>
#include <string>

/*Design a class to represent a proper fraction, 
which is defined by its numerator and denominator. 
The class should have a constructor that takes a 
string in the form "numerator/denominator" 
(for example, "3/5"), as well as possibly 
other constructors, a method to output the 
fraction object, possibly other input/output 
methods, and methods to perform the required 
operations. Develop a program that creates two 
proper fractions and finds their sum (using the 
overloaded "+" operator). The program should provide 
clear output of all input, output, and intermediate 
data (using the overloaded standard output operator "<<").*/

using namespace std;

class Fraction {
	string fraction;

	void check_input() {
		int pos = fraction.find('/');
		if (stoi(fraction.substr(pos + 1)) == 0) {
			cout << "[Error] division by 0" << endl;
			exit(1);
		}
	}

public:
	Fraction() { fraction = ""; }

	Fraction(string str) {
		fraction = str;
		check_input();
	}

	Fraction operator +(const Fraction& other) {
		Fraction temp;
		int n1, n2, n3, d1, d2, d3;

		int pos = this->fraction.find('/');
		n1 = stoi(this->fraction.substr(0, pos));
		d1 = stoi(this->fraction.substr(pos + 1));

		pos = other.fraction.find('/');
		n2 = stoi(other.fraction.substr(0, pos));
		d2 = stoi(other.fraction.substr(pos + 1));

		if (d1 != d2) {
			d3 = d1 * d2;
			n3 = (n1 * d2) + (n2 * d1);
		}
		else {
			n3 = n1 + n2;
			d3 = d1;
		}
		temp.fraction = to_string(n3) + "/" + to_string(d3);
		return temp;
	}

	friend ostream& operator <<(ostream& os, const Fraction& f) {
		os << f.fraction;
		return os;
	}
};

int main() {
	string f;

	cout << "Please enter you fraction like this 3/5" << endl;
	cout << "Fraction 1 = ";
	getline(cin, f);
	Fraction frac1(f);

	cout << endl << "Please enter you fraction like this 3/5" << endl;
	cout << "Fraction 2 = ";
	getline(cin, f);
	Fraction frac2(f);

	cout << endl << "Fraction 1 = " << frac1 << endl;
	cout << "Fraction 2 = " << frac2 << endl << endl;

	cout << frac1 << " + " << frac2 << " = " << frac1 + frac2 << endl;

	return 0;
}

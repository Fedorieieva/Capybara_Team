#include <iostream>
#include <string>

/*Design a class to represent an improper fraction, 
which is defined by its numerator and denominator. 
The class should have a constructor with a parameter 
which is a string of the form "numerator / denominator" 
(for example, "11/3"), and possibly other constructors. 
It should have a method to output the fraction object, 
as well as other input/output methods and methods to 
perform the required tasks. Develop a program that 
creates two improper fractions and increases each of 
them by a specified integer value (using the overloaded 
operator <+>). The program should provide a visual 
display of all input, output, and intermediate data 
(using the overloaded standard output stream operator «<<»).*/

using namespace std;

class Fraction {
	string fraction;

	void check_input() {
		int pos = fraction.find("/");
		if (stoi(fraction.substr(0, pos)) == 0) {
			cout << "[Error] division by 0";
			exit(1);
		}
	}

public:
	Fraction() { fraction = ""; }

	Fraction(string str) { fraction = str; }

	Fraction& operator +(int num) {
		int pos = this->fraction.find("/");

		int n = stoi(this->fraction.substr(0, pos));
		int d = stoi(this->fraction.substr(pos + 1));

		n += (num * d);

		this->fraction = to_string(n) + "/" + to_string(d);

		return *this;
	}

	friend ostream& operator <<(ostream& os, const Fraction& f) {
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

	int add;
	cout << endl << "Enter an integer number you want to add to your fractions" << endl;
	cout << "Number to add = ";
	cin >> add;

	cout << endl << "Fraction 1 = " << frac1 << endl;
	cout << "Fraction 2 = " << frac2 << endl;
	cout << "Number to add = " << add << endl;

	cout << endl << frac1 << " + " << add << " = " << frac1 + add << endl;
	cout << frac2 << " + " << add << " = " << frac2 + add << endl;

	return 0;
}
#include <iostream>
//#include <iomanip>

/*Design a class for representing an improper fraction,
which is defined by a numerator and a denominator.
The class should have a constructor with a parameter
in the format "numerator:denominator" (for example, "11:5"),
as well as other constructors, a method for printing the fraction
object, other input/output methods, and methods for performing tasks.
Develop a program that creates two improper fractions and finds their
product (using the overloaded operator "*"). The program should provide
clear output of all input, output, and intermediate data (using the overloaded
standard output stream operator "<<").*/

using namespace std;

class Fraction {
	int numerator;
	int denominator;

public:
	Fraction() {};
	Fraction(int nume, int denome) {
		numerator = nume;
		denominator = denome;
	}

	Fraction operator *(const Fraction& other) {
		Fraction temp;
		temp.numerator = this->numerator * other.numerator;
		temp.denominator = this->denominator * other.denominator;
		return temp;
	}

	friend ostream& operator <<(ostream& os, const Fraction& f) {
		os << f.numerator << ":" << f.denominator;
		return os;
	}
};

int main() {
	int nume, denome;

	cout << "Please enter numerator for the first fraction: " << endl;
	cout << "numerator = ";
	cin >> nume;
	cout << "Please enter denominator for the first fraction: " << endl;
	cout << "denominator = ";
	cin >> denome;
	Fraction frac1(nume, denome);

	cout << endl << "Please enter numerator for the second fraction: " << endl;
	cout << "numerator = ";
	cin >> nume;
	cout << "Please enter denominator for the second fraction: " << endl;
	cout << "denominator = ";
	cin >> denome;
	Fraction frac2(nume, denome);

	cout << endl << "Fraction 1 = " << frac1 << endl;
	cout << "Fraction 2 = " << frac2 << endl;

	Fraction mult = frac1 * frac2;

	cout << "(" << frac1 << ") * (" << frac2 << ") = " << mult << endl;

	return 0;
}
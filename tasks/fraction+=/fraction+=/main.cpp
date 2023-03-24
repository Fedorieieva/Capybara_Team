#include <iostream>

using namespace std;

class Fraction {
	int numerator;
	int denominator;

public:
	Fraction(){
		numerator = 0;
		denominator = 0;
	}

	Fraction(int nume, int denomi) {
		numerator = nume;
		denominator = denomi;
	}

	Fraction& operator +=(int num) {
		numerator += (denominator * num);
		return *this;
	}

	friend ostream& operator <<(ostream& os, const Fraction& f) {
		os << f.numerator << "/" << f.denominator;
		return os;
	}
};

int main() {
	int nume, denome, n;

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

	cout << endl << "Please enter a number to add to your fructions: " << endl;
	cout << "number = ";
	cin >> n;

	cout << endl << "Fraction 1 = " << frac1 << endl;
	cout << "Fraction 2 = " << frac2 << endl << endl;

	cout << frac1 << " + " << n << " = ";
	frac1 += n;
	cout << frac1 << endl;

	cout << frac2 << " + " << n << " = ";
	frac2 += n;
	cout << frac2 << endl;	

	return 0;
}
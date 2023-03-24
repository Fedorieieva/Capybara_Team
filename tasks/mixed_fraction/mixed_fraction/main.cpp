#include <iostream>

/*Design a class to represent an improper fraction, 
which is represented as a mixed number: the integer 
part, the numerator of the fractional part, and the 
denominator of the fractional part. The class should 
have a constructor with a parameter that is a string 
of the form "integer_part numerator_fractional_part: 
denominator_fractional_part" (for example, "1 2:3"), 
possibly other constructors, a method for outputting 
a fraction object, possibly other input/output methods, 
methods for performing assigned tasks.
Develop a program that creates two improper fractions 
and increments the value of the smaller one (using the 
overloaded "++" operator). The program should provide 
a visual output of all input, output, and intermediate 
data (using the overloaded standard output stream operator "<<").*/

using namespace std;

class Fraction {
	int num;
	int numerator;
	int denominator;

	void check_input() {
		if (denominator == 0) {
			cout << "[Error] Division by 0" << endl;
			exit(1);
		}
	}

public:
	Fraction() {
		num = 0;
		numerator = 0;
		denominator = 0;
	}

	Fraction(int n, int nume, int denomi) {
		num = n;
		numerator = nume;
		denominator = denomi;
		check_input();
	}

	bool operator >(const Fraction& other) {
		return (this->num > other.num) &&
			   (this->numerator > other.numerator) &&
			   (this->denominator < other.denominator);
	}

	Fraction& operator ++() {
		this->num++;
		return *this;
	}

	friend ostream& operator <<(ostream& os, const Fraction& f) {
		os << f.num << " " << f.numerator << ":" << f.denominator;
		return os;
	}
};

void input(int& n, int& nume, int& denomi) {
	cout << endl << "Please enter the integer part of a mixed number fot the first mixed fraction: ";
	cout << endl << "integer = ";
	cin >> n;
	cout << "Please enter numerator for the first fraction: " << endl;
	cout << "numerator = ";
	cin >> nume;
	cout << "Please enter denominator for the first fraction: " << endl;
	cout << "denominator = ";
	cin >> denomi;
}

void output(Fraction frac1, Fraction frac2) {
	cout << endl << "Mixed fraction 1 = " << frac1 << endl;
	cout << "Mixed fraction 2 = " << frac2 << endl << endl;
}

int main() {
    int n, nume, denomi;

	input(n, nume, denomi);
	Fraction frac1(n, nume, denomi);

	input(n, nume, denomi);
	Fraction frac2(n, nume, denomi);

	output(frac1, frac2);

    frac1 > frac2 ? ++frac1 : ++frac2;

    cout << endl << "Your mixed fractions after incrementing the largest one:" << endl;
	output(frac1, frac2);

	return 0;
}
#include <iostream>

/*Design a class for representing an improper fraction,
which is specified by a mixed number: the integer part,
the numerator of the fractional part, and the denominator
of the fractional part. The class should have a constructor
with a parameter that is a string of the form "integer_part
numerator_fractional_part: denominator_fractional_part"
(for example, "2 1:5"), as well as other constructors, a 
method for outputting the fraction object, other input/output 
methods, and methods for performing the required tasks. 
Develop a program that creates two improper fractions 
and finds their product (using the overloaded "*" operator). 
The program should provide a clear display of all input, 
output, and intermediate data (using the overloaded 
standard output stream operator "<<").*/

using namespace std;

class Fraction {
	int num;
	int numerator;
	int denomirator;

	void check_input() {
		if (denomirator == 0) {
			cout << "[Error] division by 0" << endl;
			exit(1);
		}
	}

public:
	Fraction() {
		num = 0;
		numerator = 0;
		denomirator = 0;
	}

	Fraction(int n, int nume, int denomi) {
		num = n;
		numerator = nume;
		denomirator = denomi;
		check_input();
	}

	Fraction operator *(Fraction& other) {
		Fraction temp;
		int n1, n2, nume;
		n1 = (this->num * this->denomirator) + this->numerator;
		n2 = (other.num * other.denomirator) + other.numerator;
		nume = n1 * n2;
		temp.denomirator = this->denomirator * other.denomirator;		
		temp.num = nume / temp.denomirator;
		temp.numerator = nume - (temp.num * temp.denomirator);
		return temp;
	}

	friend ostream& operator <<(ostream& os, const Fraction& f) {
		os << f.num << " " << f.numerator << ":" << f.denomirator;
		return os;
	}
};

void input(int& n, int& nume, int& denomi) {
	cout << endl << "Please enter the integer part of a improper fraction: ";
	cout << endl << "integer = ";
	cin >> n;
	cout << "Please enter numerator for the fraction: " << endl;
	cout << "numerator = ";
	cin >> nume;
	cout << "Please enter denominator for the fraction: " << endl;
	cout << "denominator = ";
	cin >> denomi;
}

void output(Fraction frac1, Fraction frac2) {
	cout << endl << "Improper fraction 1 = " << frac1 << endl;
	cout << "Improper fraction 2 = " << frac2 << endl << endl;
}

int main() {
	int n, nume, denomi;

	input(n, nume, denomi);
	Fraction frac1(n, nume, denomi);

	input(n, nume, denomi);
	Fraction frac2(n, nume, denomi);

	output(frac1, frac2);

	cout << "(" << frac1 << ") * (" << frac2 << ") = " << frac1 * frac2;
	return 0;
}
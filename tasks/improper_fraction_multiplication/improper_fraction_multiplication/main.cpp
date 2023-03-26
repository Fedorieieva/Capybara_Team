#include <iostream>
#include <string>

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
	string fraction;

	void check_input() {
		int pos = fraction.find(":");
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

	Fraction operator *(Fraction& other) {
		Fraction temp;

		int pos1 = this->fraction.find(" ");
		int num1 = stoi(this->fraction.substr(0, pos1));
		int pos2 = this->fraction.find(":");
		int numerator1 = stoi(this->fraction.substr(pos1 + 1, pos2));
		int denomirator1 = stoi(this->fraction.substr(pos2 + 1));
		
		int n1 = (num1 * denomirator1) + numerator1;

		pos1 = other.fraction.find(" ");
		int num2 = stoi(other.fraction.substr(0, pos1));
		pos2 = other.fraction.find(":");
		int numerator2 = stoi(other.fraction.substr(pos1 + 1, pos2));
		int denomirator2 = stoi(other.fraction.substr(pos2 + 1));

		int n2 = (num2 * denomirator2) + numerator2;

		int nume = n1 * n2;

		int res_d = denomirator1 * denomirator2;
		int res_num = nume / res_d;
		int res_nume = nume - (res_num * res_d);

		temp.fraction = to_string(res_num) + " " + to_string(res_nume) + ":" + to_string(res_d);
		return temp;
	}

	friend ostream& operator <<(ostream& os, const Fraction& f) {
		os << f.fraction;
		return os;
	}
};

void output(Fraction frac1, Fraction frac2) {
	cout << endl << "Improper fraction 1 = " << frac1 << endl;
	cout << "Improper fraction 2 = " << frac2 << endl << endl;
}

int main() {
	string str;

	cout << "Enter your fraction (example '2 3:7')" << endl;
	cout << "Improper fraction 1 = ";
	getline(cin, str);
	Fraction frac1(str);

	cout << endl << "Enter your fraction (example '2 3:7')" << endl;
	cout << "Improper fraction 2 = ";
	getline(cin, str);
	Fraction frac2(str);

	output(frac1, frac2);

	cout << "(" << frac1 << ") * (" << frac2 << ") = " << frac1 * frac2;
	return 0;
}
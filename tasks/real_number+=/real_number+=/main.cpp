#include <iostream>
#include <string>

/*"Design a class to represent a real number, 
whose attributes are its integer and fractional parts.
The class should have a constructor with a parameter 
that is a string-number (real) in the format of 
"integer_part.fractional_part" (for example, "23.45"), 
possibly other constructors, a method for displaying 
the fraction object, possibly other input/output methods, 
methods for performing the assigned tasks.
Develop a program that creates two number objects and 
increases each of them by a specified amount (using 
the overloaded "+=" operator).
The program should provide a visual display of all 
input, output, and intermediate data (using the 
overloaded standard output stream operator "<<")."*/

using namespace std;

class Number {
	string number;

public:
	Number() { number = ""; }

	Number(string n) { number = n; }

	Number& operator +=(double n) {
		double temp = stod(number);
		temp += n;
		number = to_string(temp);
		return *this;
	}

	friend ostream& operator <<(ostream& os, const Number& n) {
		os << n.number;
		return os;
	}
};

int main() {
	string n;
	double add;

	cout << "Enter number like 20.5" << endl;
	cout << "number1 = ";
	cin >> n;
	Number num1(n);

	cout << endl << "Enter number like 20.5" << endl;
	cout << "number2 = ";
	cin >> n; 
	Number num2(n);

	cout << endl << "Enter a number you want to add to your prevoius input" << endl;
	cout << "add = ";
	cin >> add;

	cout << endl << "number1 = " << num1 << endl;
	cout << "number2 = " << num2 << endl;
	cout << "Number to add = " << add << endl;

	cout << endl << num1 << " + " << add << " = ";
	num1 += add;
	cout << num1 << endl;

	cout << num2 << " + " << add << " = ";
	num2 += add;
	cout << num2 << endl;

	return 0;
}

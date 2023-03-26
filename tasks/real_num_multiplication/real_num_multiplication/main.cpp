#include <iostream>
#include <string>

/*Design a class to represent a real number, 
which has attributes for its integer and decimal
parts. The class should have a constructor with 
a parameter that is a string-number (real) of the 
form "integer_part, decimal_part" 
(for example, "32,15"), possibly other constructors, 
a method for displaying the object as a fraction, 
possibly other input/output methods, and methods 
for performing assigned tasks. Develop a program 
that creates two number objects and finds their 
product (using the overloaded <*> operator). 
The program should provide a clear display of 
all input, output, and intermediate data 
(using the overloaded standard output stream operator "<<").*/

using namespace std;

class Number {
	string num;

public:
	Number() { num = ""; }

	Number(string str) { num = str; }

	Number operator *(const Number& other) {
		int pos = this->num.find(",");
		string num1 = this->num.substr(0, pos) + "." + this->num.substr(pos + 1);

		pos = other.num.find(",");
		string num2 = other.num.substr(0, pos) + "." + other.num.substr(pos + 1);

		Number temp;
		temp.num = to_string(stod(num1) * stod(num2));
		return temp;
	}

	friend ostream& operator <<(ostream& os, const Number& n) {
		os << n.num;
		return os;
	}
};

int main() {
	string n;

	cout << "Enter number (for example 20,5)" << endl;
	cout << "number1 = ";
	cin >> n;
	Number num1(n);

	cout << endl << "Enter number (for example 20,5)" << endl;
	cout << "number2 = ";
	cin >> n;
	Number num2(n);

	cout << endl << "number1 = " << num1 << endl;
	cout << "number2 = " << num2 << endl;

	cout << endl << num1 << " * " << num2 << " = " << num1 * num2 << endl;

	return 0;
}
#include <iostream>
#include <string>

/*Design a class to represent a real number with
attributes representing its integer and fractional
parts. The class should have a constructor with a 
parameter, which is a string-number (real) of the 
form "integer_part.fractional_part" 
(for example, "13.52"), other constructors are 
possible, a method for displaying the object-number, 
other input/output methods, methods for performing 
the assigned tasks. Develop a program that creates 
two number-objects and increments the value of the 
larger one (using the overloaded "++" operator). 
The program should provide a clear display of all 
input, output and intermediate data (using the 
overloaded standard output stream operator "<<").*/

using namespace std;

class Number {
	string num;

public:
	Number() { num = ""; }

	Number(string str) { num = str; }

	bool operator >(const Number& other) {
		return stof(this->num) > stof(other.num);
	}

	Number& operator ++() {
		double n = stod(this->num) + 1;
		this->num = to_string(n);
		return *this;
	}

	friend ostream& operator <<(ostream& os, const Number& n) {
		os << n.num;
		return os;
	}
};

int main() {
	string n;

	cout << "Enter number (for example 20.5)" << endl;
	cout << "number1 = ";
	cin >> n;
	Number num1(n);

	cout << endl << "Enter number (for example 20.5)" << endl;
	cout << "number2 = ";
	cin >> n;
	Number num2(n);

	cout << endl << "number1 = " << num1 << endl;
	cout << "number2 = " << num2 << endl;

	num1 > num2 ? ++num1 : ++num2;

	cout << endl << "This is what your numbers look like after incrementing the greater one:" << endl;
	cout << endl << "number1 = " << num1 << endl;
	cout << "number2 = " << num2 << endl;

	return 0;
}
#include <iostream>
#include <string>

/*Design a class to represent a real number with
attributes of its integer and fractional parts. 
The class should have a constructor with a 
parameter that is a string-number (real) in 
the form of "integer_part,fractional_part" 
(for example, "13,25"), as well as possible 
other constructors, a method for outputting 
the fraction object, and possible other input/output 
methods, methods for performing the assigned tasks. 
Develop a program that creates two number objects 
and finds the value of the larger one (using the 
overloaded ">" operator). The program should provide 
a visual display of all input, output, and intermediate 
data (using the overloaded standard output stream operator "<<").*/

using namespace std;

class Number {
	string num;

public:
	Number() { num = ""; }

	Number(string str) { num = str; }

	bool operator >(const Number& other) {
		int pos = this->num.find(",");
		string num1 = this->num.substr(0, pos) + "." + this->num.substr(pos + 1);

		pos = other.num.find(",");
		string num2 = other.num.substr(0, pos) + "." + other.num.substr(pos + 1);

		double n1 = stod(num1);
		double n2 = stod(num2);

		return num1 > num2;
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

	cout << endl << "The greater number is: ";
	if (num1 > num2) cout << num1 << endl;
	else cout << num2 << endl;


	return 0;
}
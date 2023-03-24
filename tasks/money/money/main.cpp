#include <iostream>
#include <iomanip>

/*Design a "Money" class to work with money amounts, 
which has two fields to represent hryvnias and kopecks. 
The class should have a constructor with a parameter that 
is a string of the form "hryvnias, kopecks", and possibly 
other constructors, a method for outputting an object of the 
"Money" type, possibly other input/output methods, methods for 
performing tasks. Develop a program that creates two "Money" 
objects and increments the value of the larger one (using the 
overloaded "++<<" operator). The program should provide a clear 
display of all input, output, and intermediate data (using the 
overloaded standard output stream operator "<<").*/

using namespace std;

class Money {
    int hryvnias;
    int pennies;

    void normalize() {
        int total_pennies = hryvnias * 100 + pennies;
        hryvnias = total_pennies / 100;
        pennies = total_pennies % 100;
    }

public:
    Money() {}
    Money(int hr, int pn) {
        hryvnias = hr;
        pennies = pn;
        normalize();
    }

    int Gethr() { return hryvnias; }
    int Getpn() { return pennies; }

    Money& operator ++() {
        this->hryvnias++;
        return *this;
    }

    friend ostream& operator<<(ostream& os, const Money& b) {
        os << "You have " << b.hryvnias << " hryvnias and " << b.pennies << " pennies." << endl;
        return os;
    }
};

int main() {
    int hr, pn;

    cout << "Please enter how many hryvnias you have: " << endl;
    cout << "hryvnias = ";
    cin >> hr;
    cout << "Please enter how many pennies you have: " << endl;
    cout << "pennies = ";
    cin >> pn;
    Money m1(hr, pn);

    cout << endl << "Please enter how many hryvnias you have: " << endl;
    cout << "hryvnias = ";
    cin >> hr;
    cout << "Please enter how many pennies you have: " << endl;
    cout << "pennies = ";
    cin >> pn;
    Money m2(hr, pn);

    cout << endl << "Budget 1:" << endl;
    cout << m1;
    cout << "Budget 2:" << endl;
    cout << m2;

    (m1.Gethr() > m2.Gethr() && m1.Getpn() > m2.Getpn()) ? ++m1 : ++m2;

    cout << endl << "Your budget after incrementing the one with more money:" << endl;

    cout << "Budget 1:" << endl;
    cout << m1;
    cout << "Budget 2:" << endl;
    cout << m2;
    return 0;
}
#include <iostream>
#include <iomanip>

/*Design a "Budget" class to work with money amounts, 
which has two fields to represent hryvnias and pennies. 
The class should have a constructor with a parameter that 
is a string of the form "hryvnias, pennies", and possibly other 
constructors, a method for outputting an object of the "Budget" type, 
possibly other input/output methods, methods for performing tasks. 
Develop a program that creates two "Budget" objects and finds their sum 
(using the overloaded "+" operator). 
The program should provide a clear display of all input, output, 
and intermediate data (using the overloaded standard output stream operator "<<").*/

using namespace std;

class Budget {
    int hryvnias;
    int pennies;

    void normalize() {
        int total_pennies = hryvnias * 100 + pennies;
        hryvnias = total_pennies / 100;
        pennies = total_pennies % 100;
    }

public:
    Budget() {
        hryvnias = 0;
        pennies = 0;
    }

    Budget(int hr, int pn) {
        hryvnias = hr;
        pennies = pn;
        normalize();
    }

    Budget operator+ (const Budget& other) {
        Budget temp;
        temp.hryvnias = this->hryvnias + other.hryvnias;
        temp.pennies = this->pennies + other.pennies;
        temp.normalize();
        return temp;
    }

    friend ostream& operator<<(ostream& os, const Budget& b) {
        os << "You have " << b.hryvnias << " hryvnias and " << b.pennies << " pennies." << endl;
        return os;
    }
};

void input(Budget* budget, int initial, int& num) {
    int hr, pn, choice = 1;
    int max_size = initial;

    do {
        if (num == max_size)
            max_size *= 2;
            Budget* new_budget = new Budget[max_size];

            for (int i = 0; i < num; i++) {
                new_budget[i] = budget[i];
            }

            delete[] budget;
            budget = new_budget;

            cout << "Please enter how many hryvnias you have: " << endl;
            cout << "hryvnias = ";
            cin >> hr;
            cout << "Please enter how many pennies you have: " << endl;
            cout << "pennies = ";
            cin >> pn;

            new (&budget[num]) Budget(hr, pn);
            num++;

            cout << "Enter 0, if you want to stop providing input: ";
            cin >> choice;
            cin.ignore();
            cout << endl;

    } while (choice != 0);

}

void total_budget(Budget* budget, int num) {
    Budget total = budget[0];

    for (int i = 0; i < num; i++) {
        if (i != 0) {
            total = total + budget[i];
        }
        cout << "Budget " << i + 1 << ": " << budget[i];
    }
    cout << endl << "Here you can see your total budget:" << endl;
    cout << total;
}

int main() {
    int num = 0, initial = 10;
    Budget* budget = new Budget[initial];

    input(budget, initial, num);
    total_budget(budget, num);

    delete[] budget;
    return 0;
}

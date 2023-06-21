#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>

using namespace std;

class Stack {
private:
    std::vector<int> stack;

public:
    Stack() {}

    void push(int element) {
        stack.push_back(element);
    }

    int pop() {
        if (is_empty()) {
            throw std::runtime_error("Stack is empty");
        }
        int element = stack.back();
        stack.pop_back();
        return element;
    }

    int peek() {
        if (is_empty()) {
            throw std::runtime_error("Stack is empty");
        }
        return stack.back();
    }

    bool is_empty() {
        return stack.empty();
    }

    void save_to_file(const std::string& file_name) {
        std::ofstream file(file_name);
        if (file.is_open()) {
            for (int element : stack) {
                file << element << '\n';
            }
            file.close();
        }
    }
};

int main() {
    try {
        Stack stack;
        int numElements;

        std::cout << "Enter the number of elements for stack: ";
        std::cin >> numElements;

        if (std::cin.fail()) {
            throw std::runtime_error("Invalid input. Expected an integer.");
        }

        std::cout << "Enter the elements for stack:" << std::endl;
        for (int i = 0; i < numElements; ++i) {
            int element;
            std::cin >> element;

            if (std::cin.fail()) {
                throw std::runtime_error("Invalid input. Expected an integer.");
            }

            stack.push(element);
        }

        std::cout << "Peek: " << stack.peek() << std::endl;

        std::cout << "Pop: " << stack.pop() << std::endl;
        std::cout << "Pop: " << stack.pop() << std::endl;

        std::cout << "Is empty: " << (stack.is_empty() ? "true" : "false") << std::endl;

        stack.save_to_file("stack.txt");
    }
    catch (const exception& e) {
        cerr << "An error occured: " << e.what() << endl;
    }
    return 0;
}

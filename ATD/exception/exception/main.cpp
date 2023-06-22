#include <iostream>
#include <exception>
#include <string>

class MyException : public std::exception {
private:
    std::string message;
    int errorCode;

public:
    MyException(const std::string& msg, int code) : message(msg), errorCode(code) {}

    const char* what() const noexcept override {
        return message.c_str();
    }

    int getErrorCode() const {
        return errorCode;
    }

    std::string getErrorMessage() const {
        return message;
    }
};

int main() {
    try {
        throw MyException("An exception", 20);
    }
    catch (const MyException& e) {
        std::cout << "Exception code: " << e.getErrorCode() << std::endl;
        std::cout << "Exception message: " << e.what() << std::endl;
    }

    return 0;
}

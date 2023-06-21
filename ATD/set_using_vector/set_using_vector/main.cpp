#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <stdexcept>

class Set {
private:
    std::vector<int> elements;

public:
    Set() {} // default constructor

    void addElement(int element) {
        if (!contains(element)) {
            elements.push_back(element);
            std::sort(elements.begin(), elements.end());
        }
    }

    void removeElement(int element) {
        elements.erase(std::remove(elements.begin(), elements.end(), element), elements.end());
    }

    Set operator+(const Set& other) const {
        Set result;
        std::merge(elements.begin(), elements.end(), other.elements.begin(), other.elements.end(),
            std::back_inserter(result.elements));
        std::sort(result.elements.begin(), result.elements.end());
        result.elements.erase(std::unique(result.elements.begin(), result.elements.end()), result.elements.end());
        return result;
    }


    Set operator*(const Set& other) const {
        Set result;
        for (const auto& element : elements) {
            if (other.contains(element)) {
                result.addElement(element);
            }
        }
        return result;
    }

    Set operator/(const Set& other) const {
        Set result;
        for (const auto& element : elements) {
            if (!other.contains(element)) {
                result.addElement(element);
            }
        }
        return result;
    }

    void saveToFile(const std::string& filename) const {
        std::ofstream file(filename);
        if (file.is_open()) {
            for (const auto& element : elements) {
                file << element << std::endl;
            }
            file.close();
            std::cout << "Set saved to file: " << filename << std::endl;
        }
        else {
            throw std::runtime_error("Failed to open the file");
        }
    }

    std::vector<int>::const_iterator begin() const {
        return elements.begin();
    }

    std::vector<int>::const_iterator end() const {
        return elements.end();
    }

private:
    bool contains(int element) const {
        return std::binary_search(elements.begin(), elements.end(), element);
    }
};

int main() {
    try {
        Set set1;
        Set set2;

        int numElements;

        // Input number of elements for set1
        std::cout << "Enter the number of elements for set1: ";
        std::cin >> numElements;

        if (std::cin.fail()) {
            throw std::runtime_error("Invalid input. Expected an integer.");
        }

        std::cout << "Enter the elements for set1:" << std::endl;
        for (int i = 0; i < numElements; ++i) {
            int element;
            std::cin >> element;

            if (std::cin.fail()) {
                throw std::runtime_error("Invalid input. Expected an integer.");
            }

            set1.addElement(element);
        }

        // Input number of elements for set2
        std::cout << "Enter the number of elements for set2: ";
        std::cin >> numElements;

        if (std::cin.fail()) {
            throw std::runtime_error("Invalid input. Expected an integer.");
        }

        std::cout << "Enter the elements for set2:" << std::endl;
        for (int i = 0; i < numElements; ++i) {
            int element;
            std::cin >> element;

            if (std::cin.fail()) {
                throw std::runtime_error("Invalid input. Expected an integer.");
            }

            set2.addElement(element);
        }

        // Union of sets
        Set unionSet = set1 + set2;
        std::cout << "Union: ";
        for (const auto& element : unionSet) {
            std::cout << element << " ";
        }
        std::cout << std::endl;

        // Intersection of sets
        Set intersectionSet = set1 * set2;
        std::cout << "Intersection: ";
        for (const auto& element : intersectionSet) {
            std::cout << element << " ";
        }
        std::cout << std::endl;

        // Set difference
        Set differenceSet = set1 / set2;
        std::cout << "Difference: ";
        for (const auto& element : differenceSet) {
            std::cout << element << " ";
        }
        std::cout << std::endl;

        // Save the set to a file
        unionSet.saveToFile("output.txt");
    }
    catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    }

    return 0;
}

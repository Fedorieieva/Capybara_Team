#include <iostream>
#include <string>

using namespace std;

/*Create a template class (collection) Stack for working with a stack. 
Define several constructors in it (including a default constructor 
that creates an empty stack), a method for adding an element to the 
stack, a display method, and possibly other methods. For the string 
stack, provide the ability to reverse the characters of each string 
in reverse order. Write a program that demonstrates working with 
this template for stacks of real numbers and strings. In the program, 
create an array of stacks of real numbers and pass it to an external 
function that merges these objects into a single stack. Using the 
string stack, reverse the characters of each word in a sentence 
entered from the keyboard in reverse order. The program should 
provide visual output of all input, output, and intermediate data, 
as well as control over possible errors. Use exception handling to 
handle errors (including incorrect data input).*/

/*Створити шаблонний клас (колекцію) Stack для роботи із стеком. 
Визначити у ньому декілька конструкторів (у тому числі конструктор 
за замовчуванням, який створює порожній стек), метод додавання 
елемента у стек, метод виведення, можливо інші методи. Для 
стеку рядків передбачити можливість перевертання символів 
кожного рядка в зворотному порядку. Написати програму, що 
демонструє роботу з цим шаблоном для стеків дійсних чисел 
рядків. У програмі передбачити створення масиву стеків дійсних 
чисел i передачу його в зовнішню функцію, яка виконує злиття 
цих об'єктів у єдиний стек. За допомогою ж стеку рядків 
перевернути символи кожного слова речення, введеного з клавіатури, 
в зворотному порядку. Програма повинна забезпечувати наочне 
виведення усіх вхідних, вихідних та проміжних даних, а також 
контроль можливих помилок. Для обробки помилок (у тому числі і 
не коректного введення даних) використати виключні ситуації.*/

template<typename T>
class Stack {
private:
	T* arr;
	int size;
	int capacity;

public:
	Stack() {
		arr = new T[1];
		capacity = 1;
		size = 0;
	}

	~Stack() { delete[] arr; }

	int length() { return size; }

	void push(T val) {
		if (size == capacity) {
			T* temp = new T[capacity * 2];

			for (int i = 0; i < size; i++) {
				temp[i] = arr[i];
			}

			delete[] arr;
			capacity *= 2;
			arr = temp;
		}

		arr[size] = val;
		size++;
	}

	T pop() { size--; return arr[size]; }

	string reverse_last_el_in_stack() {
		string temp = arr[size - 1];
		string res = "";
		for (int i = temp.size - 1; i >= 0 ; i--) {
			res += temp[i];
		}

		return res;
	}
};

template<typename T>
Stack<T> merge(Stack<T>* s, int size) {
	Stack<T> res;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < s[i].length(); j++) {
			res.push(s[i].pop());
		}
	}

	return res;
}
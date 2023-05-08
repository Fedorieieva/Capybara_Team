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

/*�������� ��������� ���� (��������) Stack ��� ������ �� ������. 
��������� � ����� ������� ������������ (� ���� ���� ����������� 
�� �������������, ���� ������� ������� ����), ����� ��������� 
�������� � ����, ����� ���������, ������� ���� ������. ��� 
����� ����� ����������� ��������� ������������ ������� 
������� ����� � ���������� �������. �������� ��������, �� 
��������� ������ � ��� �������� ��� ����� ������ ����� 
�����. � ������� ����������� ��������� ������ ����� ������ 
����� i �������� ���� � ������� �������, ��� ������ ������ 
��� ��'���� � ������ ����. �� ��������� � ����� ����� 
����������� ������� ������� ����� �������, ��������� � ���������, 
� ���������� �������. �������� ������� ������������� ������ 
��������� ��� �������, �������� �� �������� �����, � ����� 
�������� �������� �������. ��� ������� ������� (� ���� ���� � 
�� ���������� �������� �����) ����������� ������� ��������.*/

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
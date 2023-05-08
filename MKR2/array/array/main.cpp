#include <iostream>
#include <vector>

using namespace std;

/*Create a template class Array based on a one-dimensional array
Create a constructor, overload indexing, and create a display method 
	in the class
Create a method to calculate the sum of an integer array
In the main program, create several integer and character Arrays, 
	calculate the sum of the integer array
Create an external method that merges two Arrays into one
Merge two array objects into one and calculate the sum of the 
	resulting elements
Enter k. Remove the kth element from the last array. Calculate the sum 
	of the elements of this array
Display all intermediate data
Use exception handling for inputting incorrect data*/

/*- Створити шаблонний класс Array на основі 
	одновимірного масиву
- У ньому створити конструктор, перегрузити індексування, 
	створити метод виведення
- Створити метод підрахунку суми цілочисельного масиву
- В основній програмі створити кілька цілочисельних та 
	символьних Array, підрахувати суму цілочисельних
- Створили зовнішній метод, що сувмістить два Array в один
- Сувмістити два об'єкти-масиви в один і підрахувати 
	суму елементів результуючого
- Ввести k. Видалити k-тий елемент з останнього масиву. 
	Порахувати суму елементів цього масиву
- Виводити усі проміжкові дані
- Використовувати виключні випадки при введенні некорректних данних*/

template<typename T>
class Array {
private:
	T* array;
	int size;
	int capacity;

public:
	Array() {
		array = new T[1];
		capacity = 1;
		size = 0;
	}

	~Array() { delete[] array; }

	int length() { return size; }

	void push(T val) {
		if (size == capacity) {
			T* temp = new T[capacity * 2];

			for (int i = 0; i < size; i++) {
				temp[i] = array[i];
			}

			delete[] array;
			capacity *= 2;
			array = temp;
		}

		array[size] = val;
		size++;
	}

	void erase(int idx) {
		if (idx >= size) {
			cout << "index out of range" << endl;
			exit(1);
		}

		T* temp = new T[capacity];

		for (int i = 0; i < capacity; i++) {
			if (i != idx) {
				temp[i] = array[i];
			}
		}
		delete[] array;
		array = temp;
	}

	T pop() { size--; return array[size]; }

	T sum_of_elements() {
		T res = 0;
		for (int i = 0; i < size; i++) {
			res += array[i];
		}
		return res;
	}

	int operator[](int idx) {
		if (idx < 0 || idx > size - 1) {
			cout << "index out of range" << endl;
			exit(1);
		}

		return array[idx];
	}

	friend ostream& operator <<(ostream& os, const Array& a) {
		for (int i = 0; i < size; i++) {
			os << array[i] << " ";
		}
		cout << endl;
		return os;
	}
};

template<typename T>
Array<T> merge(Array<T> a1, Array<T> a2) {
	Array<T> res;

	for (int i = 0; i < a1.length; i++) {
		res.push(a1[i]);
	}

	for (int i = res.length; i < a2.length + res.length; i++) {
		res.push(a2[i]);
	}

	return res;
}
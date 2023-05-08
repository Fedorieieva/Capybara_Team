#include <iostream>
using namespace std;

/*Create a template class (collection) Queue for working with queues.
Define several constructors in it (including a default constructor
that creates an empty queue), a method for adding an element to the
queue, a display method, and possibly other methods. For the character
queue, provide the ability to cyclically shift its elements to the right
by a specified number of positions (using the ">>" operation). Write a
program that demonstrates the use of this template for queues of real
numbers and characters. The program should create two arrays of Queue
class objects (one for each type) and pass each of them to an external
function that merges these objects into a single queue. The elements of
the resulting character queue should be cyclically shifted to the right
by k positions (k is entered from the keyboard).*/

/*�������� ��������� ���� (��������) ����� ��� ������ � ������.
��������� � ����� ������� ������������ (� ���� ���� ����������� 
�� �������������, ���� ������� ������� �����), ����� ��������� 
�������� � �����, ����� ���������, ������� ���� ������. ��� ����� 
������� ����������� ��������� ��������� ����� �� �������� �� 
������ ������� ������� ������ (�� ��������� �������� �>>�).
�������� ��������, �� ��������� ������ � ��� �������� ��� 
���� ������ ����� � �������. � ������� ����������� ��������� 
���� ������ �ᒺ��� ����� ����� (�� ������ ������� ����) � 
�������� ������� � ��� (������) � ������� �������, ��� ������ 
������ ��� �ᒺ��� � ����� �����. �������� �������� ����� 
������� ������� ������� �� k ������� ������ (k - ��������� 
� ���������). �������� ������� ������������� ������ ��������� 
��� �������, �������� �� �������� �����, � ����� �������� 
�������� �������. ��� ������� ������� (� ���� ���� � �� ���������� 
�������� �����) ����������� ������� ��������.*/

template<typename T>
class Queue {
private:
    T* arr;
    int capacity;
    int first;
    int last;
    int count;

public:
    Queue() : Queue(10) {}

    Queue(int size) {
        arr = new T[size];
        capacity = size;
        first = 0;
        last = -1;
        count = 0;
    }

    ~Queue() {
        delete[] arr;
    }

    int Get_count() { return count; }

    void push(T item) {
        if (isFull()) {
            cout << "Queue is full\n";
            return;
        }
        last = (last + 1) % capacity;
        arr[last] = item;
        count++;
    }

    T pop() {
        if (isEmpty()) {
            cout << "Queue is empty\n";
            return T();
        }
        T item = arr[first];
        first = (first + 1) % capacity;
        count--;
        return item;
    }

    bool isFull() {
        return count == capacity;
    }

    bool isEmpty() {
        return count == 0;
    }

    void print() {
        if (isEmpty()) {
            cout << "Queue is empty\n";
            return;
        }
        for (int i = 0; i < count; i++) {
            int index = (first + i) % capacity;
            cout << arr[index] << " ";
        }
        cout << endl;
    }

    void operator <<(int k) {
        if (isEmpty()) {
            cout << "Queue is empty\n";
            return;
        }
        k %= count;
        for (int i = 0; i < k; i++) {
            T item = arr[last];
            for (int j = count - 1; j > 0; j--) {
                arr[j] = arr[j - 1];
            }
            arr[first] = item;
        }
    }
};

template<typename T>
void merge(Queue<T> q1, Queue<T> q2) {
    Queue<T> q3(q1.Get_count() + q2.Get_count());
    while (!q1.isEmpty()) {
        q3.push(q1.pop());
    }
    while (!q2.isEmpty()) {
        q3.push(q2.pop());
    }
    q3.print();

    int k;
    cout << "Enter the number of positions to shift: ";
    cin >> k;
    q3.operator<<(k);
    q3.print();
}

int main() {
    Queue<char> q1(5);
    q1.push('f');
    q1.push('t');
    q1.push('k');
    q1.print();

    Queue<char> q2(5);
    q2.push('a');
    q2.push('b');
    q2.push('c');
    q2.print();

    merge(q1, q2);

    return 0;
}

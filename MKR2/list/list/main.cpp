#include <iostream>
#include <string>

using namespace std;

template<typename T>
class Node {
public:
    T data;
    Node* next;

    Node() {
        data = T();
        next = nullptr;
    }

    Node(T d) : data(d), next(nullptr) {}
};

template<typename T>
class List {
    Node<T>* head;

public:
    List() {
        head = nullptr;
    }

    void push(T val) {
        Node<T>* new_node = new Node<T>(val);

        if (head == nullptr) {
            head = new_node;
            return;
        }

        Node<T>* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }

        temp->next = new_node;
    }

    void delete_node(T idx) {
        Node<T>* temp1 = head;
        Node<T>* temp2 = nullptr;

        int size = 0;

        if (head == nullptr) {
            cout << "List is empty" << endl;
            return;
        }

        while (temp1 != nullptr) {
            temp1 = temp1->next;
            size++;
        }

        if (size < idx) {
            cout << "index out of range" << endl;
            return;
        }

        temp1 = head;

        if (idx == 1) {
            head = head->next;
            delete temp1;
            return;
        }

        while (idx-- > 1) {
            temp2 = temp1;
            temp1 = temp1->next;
        }

        temp2->next = temp1->next;

        delete temp1;
    }

    void print() {
        Node<T>* temp = head;

        if (head == nullptr) {
            cout << "List is empty" << endl;
            return;
        }

        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }

        cout << endl;
    }

    Node<T>* getHead() const {
        return head;
    }
};

template<typename T>
Node<T>* reverse_linked_list(Node<T>* head) {
    if (head == nullptr) {
        return nullptr;
    }

    if (head->next == nullptr) {
        return head;
    }

    Node<T>* temp1 = head->next;
    Node<T>* temp2 = reverse_linked_list(temp1);
    Node<T>* temp3 = temp2;

    while (temp3->next != nullptr) {
        temp3 = temp3->next;
    }

    temp3->next = head;
    head->next = nullptr;

    return temp2;
}

template<typename T>
void reverse_list_elements(List<T>& list) {
    Node<T>* head = list.getHead();
    Node<T>* reversed = reverse_linked_list(head);
    list = List<T>();

    while (reversed != nullptr) {
        list.push(reversed->data);
        reversed = reversed->next;
    }
}

int main() {
    List<int> intList;
    intList.push(1);
    intList.push(2);
    intList.push(3);
    intList.push(4);
    intList.push(5);

    cout << "Original integer list: ";
    intList.print();

    reverse_list_elements(intList);

    cout << "Reversed integer list: ";
    intList.print();

    List<string> stringList;
    stringList.push("apple");
    stringList.push("banana");
    stringList.push("orange");

    cout << "Original string list: ";
    stringList.print();

    reverse_list_elements(stringList);

    cout << "Reversed list: ";
    stringList.print();
}


#include <iostream>

using namespace std;


class BinaryTree {
private:
    class Node {
    public:
        int data;
        Node* left;
        Node* right;

        Node(int value) {
            data = value;
            left = nullptr;
            right = nullptr;
        }
    };

    Node* insertRecursive(Node* currentNode, int value) {
        if (currentNode == nullptr) {
            return new Node(value);
        }

        if (value < currentNode->data) {
            currentNode->left = insertRecursive(currentNode->left, value);
        }
        else if (value > currentNode->data) {
            currentNode->right = insertRecursive(currentNode->right, value);
        }

        return currentNode;
    }

    bool searchRecursive(Node* currentNode, int value) {
        if (currentNode == nullptr) {
            return false;
        }

        if (value == currentNode->data) {
            return true;
        }
        else if (value < currentNode->data) {
            return searchRecursive(currentNode->left, value);
        }
        else {
            return searchRecursive(currentNode->right, value);
        }
    }

    void printPreOrderRecursive(Node* currentNode) {
        if (currentNode != nullptr) {
            cout << currentNode->data << " ";
            printPreOrderRecursive(currentNode->left);
            printPreOrderRecursive(currentNode->right);
        }
    }

    void printInOrderRecursive(Node* currentNode) {
        if (currentNode != nullptr) {
            printInOrderRecursive(currentNode->left);
            cout << currentNode->data << " ";
            printInOrderRecursive(currentNode->right);
        }
    }

    void printPostOrderRecursive(Node* currentNode) {
        if (currentNode != nullptr) {
            printPostOrderRecursive(currentNode->left);
            printPostOrderRecursive(currentNode->right);
            cout << currentNode->data << " ";
        }
    }

    void clearRecursive(Node* currentNode) {
        if (currentNode != nullptr) {
            clearRecursive(currentNode->left);
            clearRecursive(currentNode->right);
            delete currentNode;
        }
    }

    Node* root;
    int size;

public:
    BinaryTree() {
        root = nullptr;
        size = 0;
    }

    ~BinaryTree() { clear(); }

    void insert(int value) {
        root = insertRecursive(root, value);
        size++;
    }

    bool search(int value) {
        return searchRecursive(root, value);
    }

    void printPreOrder() {
        printPreOrderRecursive(root);
    }

    void printInOrder() {
        printInOrderRecursive(root);
    }

    void printPostOrder() {
        printPostOrderRecursive(root);
    }

    int getSize() {
        return size;
    }

    void clear() {
        clearRecursive(root);
        root = nullptr;
        size = 0;
    }
};

int main() {
    BinaryTree tree;

    // Insert elements
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);

    cout << "Pre-order traversal: ";
    tree.printPreOrder();
    cout << endl;

    cout << "In-order traversal: ";
    tree.printInOrder();
    cout << endl;

    cout << "Post-order traversal: ";
    tree.printPostOrder();
    cout << endl;

    int searchValue = 6;
    bool found = tree.search(searchValue);
    if (found) {
        cout << searchValue << " found in the tree." << endl;
    }
    else {
        cout << searchValue << " not found in the tree." << endl;
    }

    int size = tree.getSize();
    cout << "Size of the tree: " << size << endl;

    tree.clear();
    size = tree.getSize();
    cout << "Size of the tree after clearing: " << size << endl;

    return 0;
}


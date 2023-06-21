#include <iostream>
#include <stack>

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

    Node* root;
    int size;

public:
    BinaryTree() {
        root = nullptr;
        size = 0;
    }

    ~BinaryTree() { clear(); }

    void insert(int value) {
        Node* newNode = new Node(value);

        if (root == nullptr) {
            root = newNode;
        }
        else {
            Node* currentNode = root;
            while (true) {
                if (value < currentNode->data) {
                    if (currentNode->left == nullptr) {
                        currentNode->left = newNode;
                        break;
                    }
                    else {
                        currentNode = currentNode->left;
                    }
                }
                else if (value > currentNode->data) {
                    if (currentNode->right == nullptr) {
                        currentNode->right = newNode;
                        break;
                    }
                    else {
                        currentNode = currentNode->right;
                    }
                }
                else {
                    delete newNode;
                    throw runtime_error("Key already exists.");
                }
            }
        }

        size++;
    }

    bool search(int value) {
        Node* currentNode = root;
        while (currentNode != nullptr) {
            if (value == currentNode->data) {
                return true;
            }
            else if (value < currentNode->data) {
                currentNode = currentNode->left;
            }
            else {
                currentNode = currentNode->right;
            }
        }

        return false;
    }

    void printPreOrder() {
        if (root == nullptr) {
            return;
        }

        stack<Node*> nodes;
        nodes.push(root);

        while (!nodes.empty()) {
            Node* currentNode = nodes.top();
            nodes.pop();

            cout << currentNode->data << " ";

            if (currentNode->right != nullptr) {
                nodes.push(currentNode->right);
            }

            if (currentNode->left != nullptr) {
                nodes.push(currentNode->left);
            }
        }
    }

    void printInOrder() {
        if (root == nullptr) {
            return;
        }

        stack<Node*> nodes;
        Node* currentNode = root;

        while (!nodes.empty() || currentNode != nullptr) {
            if (currentNode != nullptr) {
                nodes.push(currentNode);
                currentNode = currentNode->left;
            }
            else {
                currentNode = nodes.top();
                nodes.pop();
                cout << currentNode->data << " ";
                currentNode = currentNode->right;
            }
        }
    }

    void printPostOrder() {
        if (root == nullptr) {
            return;
        }

        stack<Node*> nodes;
        Node* currentNode = root;
        Node* lastVisitedNode = nullptr;

        while (!nodes.empty() || currentNode != nullptr) {
            if (currentNode != nullptr) {
                nodes.push(currentNode);
                currentNode = currentNode->left;
            }
            else {
                Node* peekNode = nodes.top();

                if (peekNode->right != nullptr && lastVisitedNode != peekNode->right) {
                    currentNode = peekNode->right;
                }
                else {
                    cout << peekNode->data << " ";
                    lastVisitedNode = peekNode;
                    nodes.pop();
                }
            }
        }
    }

    int getSize() {
        return size;
    }

    void clear() {
        clearRecursive(root);
        root = nullptr;
        size = 0;
    }

private:
    void clearRecursive(Node* currentNode) {
        if (currentNode != nullptr) {
            clearRecursive(currentNode->left);
            clearRecursive(currentNode->right);
            delete currentNode;
        }
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
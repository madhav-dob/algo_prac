#include <iostream>
using namespace std;

// Define a Node structure for the tree
struct Node {
    int key;
    Node *left, *right;

    Node(int value) {
        key = value;
        left = right = nullptr;
    }
};

// Class for Binary Search Tree (BST)
class BinaryTree {
    Node *root;

    // Utility function to insert a new key in the tree
    Node *insert(Node *node, int key) {
        if (node == nullptr) {
            return new Node(key);
        }

        if (key < node->key) {
            node->left = insert(node->left, key);
        } else if (key > node->key) {
            node->right = insert(node->right, key);
        }

        return node;
    }

    // Utility function to search for a key in the tree
    Node *search(Node *node, int key) {
        if (node == nullptr || node->key == key) {
            return node;
        }

        if (key < node->key) {
            return search(node->left, key);
        }

        return search(node->right, key);
    }

    // Utility function to print the tree (in-order traversal)
    void inOrderTraversal(Node *node) {
        if (node != nullptr) {
            inOrderTraversal(node->left);
            cout << node->key << " ";
            inOrderTraversal(node->right);
        }
    }

public:
    BinaryTree() {
        root = nullptr;
    }

    // Function to insert a key in the tree
    void insert(int key) {
        cout << "Inserting: " << key << "\n";
        root = insert(root, key);
        cout << "Tree after insertion: ";
        printTree();
    }

    // Function to search for a key in the tree
    void search(int key) {
        cout << "Searching for: " << key << "\n";
        Node *result = search(root, key);
        if (result != nullptr) {
            cout << "Element " << key << " found in the tree." << "\n";
        } else {
            cout << "Element " << key << " not found in the tree." << "\n";
        }
    }

    // Function to print the tree
    void printTree() {
        inOrderTraversal(root);
        cout << "\n";
    }
};

int main() {
    BinaryTree tree;

    // Insert elements into the tree
    tree.insert(50);
    tree.insert(30);
    tree.insert(20);
    tree.insert(40);
    tree.insert(70);
    tree.insert(60);
    tree.insert(80);

    // Search for elements in the tree
    tree.search(40);
    tree.search(90);

    return 0;
}

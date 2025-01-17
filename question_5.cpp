#include <iostream>
using namespace std;

// A BTree node
class BTreeNode {
    int *keys;      // An array of keys
    int t;          // Minimum degree (defines the range for the number of keys)
    BTreeNode **C;  // An array of child pointers
    int n;          // Current number of keys
    bool leaf;      // True if the node is a leaf

public:
    BTreeNode(int _t, bool _leaf);

    // Function to traverse all nodes in a subtree rooted with this node
    void traverse();

    // Function to search a key in the subtree rooted with this node
    BTreeNode *search(int k);

    // A utility function to insert a new key in the sub-tree rooted with this node
    void insertNonFull(int k);

    // A utility function to split the child y of this node
    void splitChild(int i, BTreeNode *y);

    friend class BTree;
};

class BTree {
    BTreeNode *root; // Pointer to the root node
    int t;           // Minimum degree

public:
    BTree(int _t) {
        root = nullptr;
        t = _t;
    }

    // Function to traverse the tree
    void traverse() {
        if (root != nullptr)
            root->traverse();
    }

    // Function to search a key in the tree
    BTreeNode *search(int k) {
        return (root == nullptr) ? nullptr : root->search(k);
    }

    // The main function that inserts a new key in the B-Tree
    void insert(int k);
};

BTreeNode::BTreeNode(int t1, bool leaf1) {
    t = t1;
    leaf = leaf1;
    keys = new int[2 * t - 1];
    C = new BTreeNode *[2 * t];
    n = 0;
}

void BTreeNode::traverse() {
    int i;
    for (i = 0; i < n; i++) {
        if (!leaf)
            C[i]->traverse();
        cout << " " << keys[i];
    }
    if (!leaf)
        C[i]->traverse();
}

BTreeNode *BTreeNode::search(int k) {
    int i = 0;
    while (i < n && k > keys[i])
        i++;

    if (keys[i] == k)
        return this;

    if (leaf)
        return nullptr;

    return C[i]->search(k);
}

void BTree::insert(int k) {
    if (root == nullptr) {
        root = new BTreeNode(t, true);
        root->keys[0] = k;
        root->n = 1;
    } else {
        if (root->n == 2 * t - 1) {
            BTreeNode *s = new BTreeNode(t, false);
            s->C[0] = root;
            s->splitChild(0, root);

            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->C[i]->insertNonFull(k);

            root = s;
        } else
            root->insertNonFull(k);
    }
}

void BTreeNode::insertNonFull(int k) {
    int i = n - 1;
    if (leaf) {
        while (i >= 0 && keys[i] > k) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = k;
        n = n + 1;
    } else {
        while (i >= 0 && keys[i] > k)
            i--;

        if (C[i + 1]->n == 2 * t - 1) {
            splitChild(i + 1, C[i + 1]);

            if (keys[i + 1] < k)
                i++;
        }
        C[i + 1]->insertNonFull(k);
    }
}

void BTreeNode::splitChild(int i, BTreeNode *y) {
    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;

    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];

    if (!y->leaf) {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j + t];
    }

    y->n = t - 1;

    for (int j = n; j >= i + 1; j--)
        C[j + 1] = C[j];

    C[i + 1] = z;

    for (int j = n - 1; j >= i; j--)
        keys[j + 1] = keys[j];

    keys[i] = y->keys[t - 1];
    n = n + 1;
}

int main() {
    BTree t(3); // A B-Tree with minimum degree 3
    t.insert(10);
    t.insert(20);
    t.insert(5);
    t.insert(6);
    t.insert(12);
    t.insert(30);
    t.insert(7);
    t.insert(17);

    cout << "Traversal of the constructed B-Tree is:" << endl;
    t.traverse();
    cout << "\n";

    int k = 6;
    cout << "\nSearching for element: " << k << "\n";
    (t.search(k) != nullptr) ? cout << "Present\n"
                             : cout << "Not Present\n";

    k = 15;
    cout << "\nSearching for element: " << k << "\n";
    (t.search(k) != nullptr) ? cout << "Present\n"
                             : cout << "Not Present\n";

    return 0;
}

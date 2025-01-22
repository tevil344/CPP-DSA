#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string key;
    string value;
    Node* left;
    Node* right;
    Node(string k, string v) : key(k), value(v), left(nullptr), right(nullptr) {}
};

class Tree {
public:
    Node* root;
    Tree() : root(nullptr) {}

    void insert(string key, string value) {
        root = insert(root, key, value);
    }

    void levelWiseTraversal() {
        int height = calculateHeight(root);
        for (int level = 1; level <= height; ++level) {
            cout << "Level " << level << ": ";
            printLevel(root, level);
            cout << endl;
        }
    }

private:
    Node* insert(Node* node, string key, string value) {
        if (!node) return new Node(key, value);
        if (key < node->key)
            node->left = insert(node->left, key, value);
        else if (key > node->key)
            node->right = insert(node->right, key, value);
        else
            node->value = value; // Update value if duplicate key
        return node;
    }

    int calculateHeight(Node* node) {
        if (!node) return 0;
        int leftHeight = calculateHeight(node->left);
        int rightHeight = calculateHeight(node->right);
        return max(leftHeight, rightHeight) + 1;
    }

    void printLevel(Node* node, int level) {
        if (!node) return;
        if (level == 1)
            cout << node->key << ": " << node->value << "  ";
        else if (level > 1) {
            printLevel(node->left, level - 1);
            printLevel(node->right, level - 1);
        }
    }
};

int main() {
    Tree t;
    t.insert("apple", "fruit");
    t.insert("banana", "fruit");
    t.insert("carrot", "vegetable");
    t.insert("dog", "animal");
    t.insert("elephant", "animal");

    cout << "Level-wise Traversal of Tree:\n";
    t.levelWiseTraversal();

    return 0;
}

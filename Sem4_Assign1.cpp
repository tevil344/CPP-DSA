#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
    Node(int d) {
        data = d;
        left = nullptr;
        right = nullptr;
    }
};

int height(Node *root) {
    if (root == nullptr)
        return -1;

    // compute the height of left and right subtrees
    int lHeight = height(root->left);
    int rHeight = height(root->right);

    return max(lHeight, rHeight) + 1;
}

int main() {
    // Initialize and allocate memory for tree nodes
    Node* firstNode = new Node(2);
    Node* secondNode = new Node(3);
    Node* thirdNode = new Node(4);
    Node* fourthNode = new Node(5);

    // Connect binary tree nodes
    firstNode->left = secondNode;
    firstNode->right = thirdNode;
    secondNode->left = fourthNode;

    // Pass the root node to the height function
    cout << height(firstNode);
    return 0;
}

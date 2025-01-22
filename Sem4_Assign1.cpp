#include <iostream>
#include <queue>
using namespace std;

struct Node {
    string key;
    string value;
    Node* left;
    Node* right;

    Node(string k, string v) : key(k), value(v), left(nullptr), right(nullptr) {}
};

class Dictionary {
private:
    Node* root;

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

    Node* findMin(Node* node) {
        while (node && node->left) node = node->left;
        return node;
    }

    Node* deleteNode(Node* node, string key) {
        if (!node) return nullptr;
        if (key < node->key)
            node->left = deleteNode(node->left, key);
        else if (key > node->key)
            node->right = deleteNode(node->right, key);
        else {
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = findMin(node->right);
            node->key = temp->key;
            node->value = temp->value;
            node->right = deleteNode(node->right, temp->key);
        }
        return node;
    }

    Node* search(Node* node, string key) {
        if (!node || node->key == key) return node;
        if (key < node->key)
            return search(node->left, key);
        return search(node->right, key);
    }

    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->key << ": " << node->value << endl;
        inorder(node->right);
    }

    void mirror(Node* node) {
        if (!node) return;
        swap(node->left, node->right);
        mirror(node->left);
        mirror(node->right);
    }

    Node* copy(Node* node) {
        if (!node) return nullptr;
        Node* newNode = new Node(node->key, node->value);
        newNode->left = copy(node->left);
        newNode->right = copy(node->right);
        return newNode;
    }

    void levelOrder(Node* node) {
        if (!node) return;
        queue<Node*> q;
        q.push(node);
        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            cout << current->key << ": " << current->value << endl;
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
    }

public:
    Dictionary() : root(nullptr) {}

    void insert(string key, string value) {
        root = insert(root, key, value);
    }

    void deleteWord(string key) {
        root = deleteNode(root, key);
    }

    void search(string key) {
        Node* result = search(root, key);
        if (result)
            cout << "Found: " << result->key << ": " << result->value << endl;
        else
            cout << "Key not found." << endl;
    }

    void display() {
        inorder(root);
    }

    void mirrorImage() {
        mirror(root);
    }

    Dictionary* createCopy() {
        Dictionary* newDict = new Dictionary();
        newDict->root = copy(root);
        return newDict;
    }

    void displayLevelWise() {
        levelOrder(root);
    }
};

int main() {
    Dictionary dict;
    dict.insert("apple", "fruit");
    dict.insert("banana", "fruit");
    dict.insert("carrot", "vegetable");
    dict.insert("dog", "animal");

    cout << "Dictionary (Inorder Traversal):\n";
    dict.display();

    cout << "\nSearch for 'banana':\n";
    dict.search("banana");

    cout << "\nDelete 'carrot':\n";
    dict.deleteWord("carrot");
    dict.display();

    cout << "\nMirror Image of Dictionary:\n";
    dict.mirrorImage();
    dict.display();

    cout << "\nLevel-wise Display:\n";
    dict.displayLevelWise();

    cout << "\nCreate a Copy of Dictionary:\n";
    Dictionary* copyDict = dict.createCopy();
    copyDict->display();

    delete copyDict;
    return 0;
}

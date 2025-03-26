#include <iostream>
using namespace std;

struct Node {
    string key;
    string value;
    Node* left;
    Node* right;

    Node(string k, string v) : key(k), value(v), left(nullptr), right(nullptr) {}
};

class Queue {
private:
    struct QueueNode {
        Node* treeNode;
        QueueNode* next;
        QueueNode(Node* node) : treeNode(node), next(nullptr) {}
    };
    QueueNode *front, *rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}

    void push(Node* node) {
        QueueNode* temp = new QueueNode(node);
        if (!rear) {
            front = rear = temp;
            return;
        }
        rear->next = temp;
        rear = temp;
    }

    void pop() {
        if (!front) return;
        QueueNode* temp = front;
        front = front->next;
        if (!front) rear = nullptr;
        delete temp;
    }

    Node* getFront() {
        return front ? front->treeNode : nullptr;
    }

    bool empty() {
        return front == nullptr;
    }
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
            node->value = value;
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
        Queue q;
        q.push(node);
        while (!q.empty()) {
            Node* current = q.getFront();
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
    int choice;
    string key, value;
    do {
        cout << "\nDictionary Operations:\n";
        cout << "1. Insert\n2. Delete\n3. Search\n4. Display (Inorder)\n5. Mirror Image\n6. Display Level-wise\n7. Create Copy\n8. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter key: "; cin >> key;
                cout << "Enter value: "; cin >> value;
                dict.insert(key, value);
                break;
            case 2:
                cout << "Enter key to delete: "; cin >> key;
                dict.deleteWord(key);
                break;
            case 3:
                cout << "Enter key to search: "; cin >> key;
                dict.search(key);
                break;
            case 4:
                cout << "Dictionary (Inorder Traversal):\n";
                dict.display();
                break;
            case 5:
                dict.mirrorImage();
                cout << "Mirrored Dictionary:\n";
                dict.display();
                break;
            case 6:
                cout << "Level-wise Display:\n";
                dict.displayLevelWise();
                break;
            case 7: {
                Dictionary* copyDict = dict.createCopy();
                cout << "Copy of Dictionary:\n";
                copyDict->display();
                delete copyDict;
                break;
            }
            case 8:
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 8);
    return 0;
}

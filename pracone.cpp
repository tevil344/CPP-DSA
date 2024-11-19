/*implement stack of book using array*/

#include <iostream>
#include <string>
using namespace std;

class BookStack {
private:
    static const int MAX_SIZE = 100; // Maximum size of the stack
    string data[MAX_SIZE];           // Array to store book names
    int top;                         // Index of the top element

public:
    // Constructor to initialize the stack
    BookStack() {
        top = -1; // Stack is initially empty
    }

    // Push a book onto the stack
    void push(string bookName) {
        if (top >= MAX_SIZE - 1) {
            cout << "Stack overflow. Cannot push more books.\n";
        } else {
            data[++top] = bookName;
        }
    }

    // Pop and return the top book from the stack
    string pop() {
        if (isEmpty()) {
            cout << "Stack is empty. Cannot pop.\n";
            return "";
        } else {
            return data[top--];
        }
    }

    // Return the top book of the stack without removing it
    string peek() {
        if (isEmpty()) {
            cout << "Stack is empty. Cannot peek.\n";
            return "";
        } else {
            return data[top];
        }
    }

    // Check if the stack is empty
    bool isEmpty() {
        return top == -1;
    }
};

// Function to reverse a string using a stack
string reverseString(string input) {
    BookStack stack;
    for (char ch : input) {
        stack.push(string(1, ch)); // Push each character onto the stack
    }

    string reversed;
    while (!stack.isEmpty()) {
        reversed += stack.pop(); // Pop characters from the stack to form the reversed string
    }
    return reversed;
}

// Function to validate an expression using a stack
bool validateExpression(string expr) {
    BookStack stack;

    for (char ch : expr) {
        if (ch == '(' || ch == '{' || ch == '[') {
            stack.push(string(1, ch)); // Push opening brackets onto the stack
        } else if (ch == ')' || ch == '}' || ch == ']') {
            if (stack.isEmpty()) return false; // No matching opening bracket

            char topChar = stack.pop()[0];
            if ((ch == ')' && topChar != '(') ||
                (ch == '}' && topChar != '{') ||
                (ch == ']' && topChar != '[')) {
                return false; // Mismatched brackets
            }
        }
    }
    return stack.isEmpty(); // If stack is empty, all brackets are matched
}

int main() {
    BookStack myStack;
    int choice;
    string bookName;

    do {
        cout << "\n1. Push book\n2. Pop book\n3. Peek book\n4. Check if stack is empty\n5. Reverse a string\n6. Validate an expression\n0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the name of the book: ";
                cin.ignore();
                getline(cin, bookName);
                myStack.push(bookName);
                break;

            case 2:
                cout << "Popped book: " << myStack.pop() << endl;
                break;

            case 3:
                cout << "Top book: " << myStack.peek() << endl;
                break;

            case 4:
                if (myStack.isEmpty()) {
                    cout << "The stack is empty.\n";
                } else {
                    cout << "The stack is not empty.\n";
                }
                break;

            case 5: {
                string input;
                cout << "Enter a string to reverse: ";
                cin.ignore();
                getline(cin, input);
                cout << "Reversed string: " << reverseString(input) << endl;
                break;
            }

            case 6: {
                string expression;
                cout << "Enter an expression to validate: ";
                cin.ignore();
                getline(cin, expression);
                if (validateExpression(expression)) {
                    cout << "The expression is valid.\n";
                } else {
                    cout << "The expression is invalid.\n";
                }
                break;
            }

            case 0:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}

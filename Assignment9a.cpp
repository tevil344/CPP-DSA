#include <iostream>
using namespace std;

#define MAX 1000 // Maximum size of the queue

class Queue {
    int front, rear;
    string Waitlist[MAX]; // Array to store queue elements

public:
    Queue() {
        front = -1;
        rear = -1;
    }

    // Function to check if the queue is empty
    bool isEmpty() {
        return (front == -1);
    }

    // Function to check if the queue is full
    bool isFull() {
        return (rear == MAX - 1);
    }

    // Function to insert an element in the queue
    void inwaitlist(string value) {
        if (isFull()) {
            cout << "Waitlist is full" << endl;
            return;
        }
        if (front == -1) front = 0; // Initialize front to 0 if the first element is added
        rear++;
        Waitlist[rear] = value;
        cout << "Added: " << value << " in waitlist." << endl;
    }

    // Function to remove an element from the queue
    void done() {
        if (isEmpty()) {
            cout << "Waitlist is empty" << endl;
            return;
        }
        cout << "Table occupied by: " << Waitlist[front] << endl;
        if (front == rear) { // Only one element in the queue
            front = -1;
            rear = -1;
        } else {
            front++;
        }
    }

    // Function to display all elements in the queue
    void display() {
        if (isEmpty()) {
            cout << "Waitlist is empty" << endl;
            return;
        }
        cout << "People in restaurant: ";
        for (int i = front; i <= rear; i++) {
            cout << Waitlist[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    Queue q;
    int choice;
    string name;

    do {
        cout << "\nMenu:\n";
        cout << "1. Add to Waitlist\n";
        cout << "2. Mark Done (Occupy table)\n";
        cout << "3. Display Waitlist\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter name to add to waitlist: ";
                cin >> name;
                q.inwaitlist(name);
                break;

            case 2:
                q.done();
                break;

            case 3:
                q.display();
                break;

            case 4:
                cout << "Exiting program." << endl;
                break;

            default:
                cout << "Invalid choice, please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}

#include <iostream>
#define MAX 5

using namespace std;

class SupermarketQueue {
    int front, rear;
    int queue[MAX];

public:
    SupermarketQueue() {
        front = -1;
        rear = -1;
    }

    bool isFull() {
        return (front == 0 && rear == MAX - 1);
    }

    bool isEmpty() {
        return front == -1;
    }

    void customerArrival(int customerID) {
        if (isFull()) {
            cout << "Queue is full. Cannot add more customers.\n";
            return;
        }

        if (front == -1) {
            front = rear = 0;
        } else if (rear == MAX - 1 && front != 0) {
            rear = 0;
        } else {
            rear++;
        }
        queue[rear] = customerID;
        cout << "Customer " << customerID << " has arrived.\n";
    }

    void customerCheckout() {
        if (isEmpty()) {
            cout << "Queue is empty. No customer to checkout.\n";
            return;
        }

        cout << "Customer " << queue[front] << " has checked out.\n";

        if (front == rear) {
            front = rear = -1; // Queue is empty
        } else if (front == MAX - 1) {
            front = 0;
        } else {
            front++;
        }
    }

    void closeCounter() {
        front = rear = -1;
        cout << "Checkout counter is now closed. All customers are cleared.\n";
    }

    void viewCustomers() {
        if (isEmpty()) {
            cout << "No customers in the queue.\n";
            return;
        }

        cout << "Customers in the queue: ";
        if (rear >= front) {
            for (int i = front; i <= rear; i++) {
                cout << queue[i] << " ";
            }
        } else {
            for (int i = front; i < MAX; i++) {
                cout << queue[i] << " ";
            }
            for (int i = 0; i <= rear; i++) {
                cout << queue[i] << " ";
            }
        }
        cout << "\n";
    }
};

int main() {
    SupermarketQueue sq;
    int choice, customerID;

    do {
        cout << "\n1. Customer Arrival\n2. Customer Checkout\n3. Close Checkout Counter\n4. View Customers\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter customer ID: ";
                cin >> customerID;
                sq.customerArrival(customerID);
                break;
            case 2:
                sq.customerCheckout();
                break;
            case 3:
                sq.closeCounter();
                break;
            case 4:
                sq.viewCustomers();
                break;
            case 5:
                cout << "Exiting the system.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}

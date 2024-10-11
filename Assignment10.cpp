#include <iostream>
#include <string>

using namespace std;

struct Job {
    int job_id;
    int job_priority;
    string job_name;
    Job* next;
    Job* prev;
};

class JobScheduler {
private:
    Job* front;
    Job* rear;

public:
    JobScheduler() {
        front = nullptr;
        rear = nullptr;
    }

    // Add job at the rear of the deque
    void addJob(int id, int priority, const string& name) {
        Job* newJob = new Job{id, priority, name, nullptr, nullptr};

        if (rear == nullptr) {
            front = rear = newJob;
        } else {
            rear->next = newJob;
            newJob->prev = rear;
            rear = newJob;
        }
        cout << "Job added: " << name << " with priority " << priority << endl;
    }

    // Remove job from the front of the deque
    void removeJob() {
        if (front == nullptr) {
            cout << "No jobs to remove." << endl;
            return;
        }

        Job* temp = front;
        cout << "Removing job: " << temp->job_name << endl;

        if (front == rear) {
            front = rear = nullptr;
        } else {
            front = front->next;
            front->prev = nullptr;
        }

        delete temp;
    }

    // Display all jobs in the deque
    void displayJobs() {
        if (front == nullptr) {
            cout << "No jobs in the queue." << endl;
            return;
        }

        Job* current = front;
        cout << "Jobs in the queue:" << endl;
        while (current != nullptr) {
            cout << "ID: " << current->job_id
                 << ", Name: " << current->job_name
                 << ", Priority: " << current->job_priority << endl;
            current = current->next;
        }
    }

    // Search for a job by ID
    void searchJob(int id) {
        Job* current = front;

        while (current != nullptr) {
            if (current->job_id == id) {
                cout << "Job found: " << current->job_name
                     << " with priority " << current->job_priority << endl;
                return;
            }
            current = current->next;
        }
        cout << "Job with ID " << id << " not found." << endl;
    }

    // Destructor to clean up memory
    ~JobScheduler() {
        while (front != nullptr) {
            removeJob();
        }
    }
};

int main() {
    JobScheduler scheduler;

    scheduler.addJob(1, 5, "Cutting");
    scheduler.addJob(2, 3, "Welding");
    scheduler.addJob(3, 4, "Assembling");

    scheduler.displayJobs();

    scheduler.searchJob(2);

    scheduler.removeJob();
    scheduler.displayJobs();

    return 0;
}

#include "../include/Queue.h"

using namespace std;

Queue::Queue() {
    front = nullptr;
    rear = nullptr;
}

Queue::~Queue() {
    while (!isEmpty()) { dequeue(); }
}

bool Queue::isEmpty() const { return front == nullptr; }

void Queue::enqueue(int studentID) {
    StudentNode* temp = new StudentNode();
    temp->studentID = studentID;
    temp->next = nullptr;

    if (rear == nullptr) {
        front = temp;
        rear = temp;
    } 
    else {
        rear->next = temp;
        rear = temp;
    }
    cout << "Student " << studentID << " added to waiting list." << endl;
}

int Queue::dequeue() {
    if (isEmpty()) { return -1; }

    StudentNode* temp = front;
    int removedID = temp->studentID;

    front = front->next;

    if (front == nullptr) { rear = nullptr; }

    delete temp;

    return removedID;
}

int Queue::peek() const {
    if (isEmpty()) { return -1; }
    return front->studentID;
}

void Queue::display() const {
    if (isEmpty()) {
        cout << "Waiting list is empty." << endl;
        return;
    }
    
    StudentNode* current = front;
    cout << "Waiting Queue: ";
    while (current != nullptr) {
        cout << "[" << current->studentID << "] -> ";
        current = current->next;
    }
    cout << "NULL" << endl;
}
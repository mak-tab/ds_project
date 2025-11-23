#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>

struct StudentNode {
    int studentID;
    StudentNode* next;
};

class Queue {
private:
    StudentNode* front;
    StudentNode* rear;

public:
    Queue();

    ~Queue();

    bool isEmpty() const;

    void enqueue(int studentID);

    int dequeue();

    int peek() const;

    void display() const;
};

#endif
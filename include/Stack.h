#ifndef STACK_H
#define STACK_H

#include <iostream>
using namespace std;

struct Action {
    string type;
    int bookID;
    Action* next;
};

class Stack {
private:
    Action* top;

public:
    Stack() { top = nullptr; }
    
    ~Stack() {
        while (!isEmpty()) pop();
    }

    bool isEmpty() { return top == nullptr; }

    void push(string type, int bookID) {
        Action* newNode = new Action{type, bookID, top};
        top = newNode;
    }

    Action pop() {
        if (isEmpty()) return {"", -1, nullptr};
        
        Action* temp = top;
        Action result = *temp;
        top = top->next;
        delete temp;
        return result;
    }
};

#endif
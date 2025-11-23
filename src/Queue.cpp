#include "../include/Queue.h"

using namespace std;

// Конструктор
Queue::Queue() {
    front = nullptr;
    rear = nullptr;
}

// Деструктор - критически важен для предотвращения memory leaks
Queue::~Queue() {
    while (!isEmpty()) {
        dequeue(); // Просто удаляем все элементы один за другим
    }
}

bool Queue::isEmpty() const {
    return front == nullptr;
}

// Алгоритм Enqueue (Добавление в конец)
// См. слайд 1344 "Linked Representation of Queues" 
void Queue::enqueue(int studentID) {
    // 1. Выделяем память под новый узел
    StudentNode* temp = new StudentNode();
    temp->studentID = studentID;
    temp->next = nullptr;

    // 2. Если очередь пуста, новый узел становится и front, и rear
    if (rear == nullptr) {
        front = temp;
        rear = temp;
    } 
    else {
        // 3. Иначе привязываем к текущему rear и сдвигаем rear
        rear->next = temp;
        rear = temp;
    }
    // cout << "Student " << studentID << " added to waiting list." << endl; // Логирование (опционально)
}

// Алгоритм Dequeue (Удаление из начала)
// См. слайд 1345 [cite: 1345]
int Queue::dequeue() {
    // 1. Проверка на опустошение (Underflow)
    if (isEmpty()) {
        // В реальном проекте лучше кидать исключение, но для учебного вернем код ошибки
        // cerr << "Queue Underflow" << endl; 
        return -1; 
    }

    // 2. Запоминаем данные и узел для удаления
    StudentNode* temp = front;
    int removedID = temp->studentID;

    // 3. Сдвигаем front
    front = front->next;

    // 4. Если после удаления очередь стала пустой, rear тоже должен стать nullptr
    if (front == nullptr) {
        rear = nullptr;
    }

    // 5. Освобождаем память! (Важно для C++)
    delete temp;

    return removedID;
}

int Queue::peek() const {
    if (isEmpty()) {
        return -1; 
    }
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
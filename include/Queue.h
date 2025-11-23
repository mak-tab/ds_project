#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>

// Структура узла для очереди студентов.
// В C++ struct по умолчанию имеет public доступ, что удобно для внутренних узлов.
struct StudentNode {
    int studentID;
    StudentNode* next;
};

class Queue {
private:
    StudentNode* front; // Указатель на начало (отсюда удаляем)
    StudentNode* rear;  // Указатель на конец (сюда добавляем)

public:
    // Конструктор: инициализация пустой очереди
    Queue();

    // Деструктор: ОБЯЗАТЕЛЕН для очистки памяти (Academic standard)
    ~Queue();

    // Проверка на пустоту
    bool isEmpty() const;

    // Добавление студента в очередь (Enqueue)
    void enqueue(int studentID);

    // Удаление студента из очереди (Dequeue)
    // Возвращает ID удаленного студента или -1, если очередь пуста
    int dequeue();

    // Посмотреть, кто первый в очереди, без удаления
    int peek() const;

    // Вывод содержимого (для отладки и демонстрации преподавателю)
    void display() const;
};

#endif // QUEUE_H
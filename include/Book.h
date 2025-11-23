#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <iostream>
#include "Queue.h" // Подключаем нашу готовую очередь

using namespace std;

class Book {
public:
    // === Поля данных (согласно заданию) ===
    int id;
    string title;
    string author;
    int totalCopies;
    int availableCopies;

    // === Структурные элементы ===
    
    // 1. Очередь ожидания для ЭТОЙ конкретной книги
    // (Requirement: "manage unavailable book requests using a Queue")
    Queue waitList;

    // 2. Указатель на следующую книгу
    // (Requirement: "Each book must be a node of the list")
    Book* next;

    // === Методы ===

    // Конструктор
    Book(int id, string title, string author, int total);

    // Попытка выдать книгу. Возвращает true, если выдача успешна.
    bool borrowBook();

    // Возврат книги. Увеличивает счетчик.
    void returnBookCopy();

    // Вывод информации о книге
    void displayBookInfo() const;
};

#endif // BOOK_H
#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.h"
#include <iostream>
#include <string>

using namespace std;

class Library {
private:
    Book* head; // Указатель на начало связного списка книг

    // Вспомогательный метод для поиска дубликатов ID
    // (Requirement: "Prevent adding duplicate Book IDs")
    bool isIDUnique(int id);

public:
    Library();
    ~Library();

    // === Управление книгами ===
    // Добавление книги с сохранением сортировки по ID
    void addBook(int id, string title, string author, int total);
    
    // Поиск (возвращает указатель на книгу или nullptr)
    Book* searchBookByID(int id);
    Book* searchBookByTitle(string title);
    Book* searchBookByAuthor(string author);

    // === Бизнес-логика (Выдача и Возврат) ===
    void issueBook(int bookID, int studentID);
    void returnBook(int bookID);

    // === Утилиты ===
    void displayAllBooks();
    
    // Геттер для FileManager (чтобы сохранить список в файл)
    Book* getHead() const { return head; }
};

#endif // LIBRARY_H
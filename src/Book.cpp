#include "../include/Book.h"

// Конструктор
Book::Book(int id, string title, string author, int total) {
    this->id = id;
    this->title = title;
    this->author = author;
    this->totalCopies = total;
    this->availableCopies = total; // Изначально все копии доступны
    
    this->next = nullptr; // Важно обнулять указатели
}

// Логика выдачи книги
bool Book::borrowBook() {
    if (availableCopies > 0) {
        availableCopies--;
        return true;
    }
    return false; // Копий нет
}

// Логика возврата книги
void Book::returnBookCopy() {
    // Защита от ошибок: нельзя вернуть больше, чем всего существует
    if (availableCopies < totalCopies) {
        availableCopies++;
    }
}

// Вывод данных (для удобства отладки и меню)
void Book::displayBookInfo() const {
    cout << "ID: " << id 
         << " | Title: " << title 
         << " | Author: " << author 
         << " | Copies: " << availableCopies << "/" << totalCopies;
    
    // Дополнительно покажем статус очереди, если она есть
    if (!waitList.isEmpty()) {
        cout << " [Waitlist Active]";
    }
    cout << endl;
}
#include "../include/Library.h"

Library::Library() {
    head = nullptr;
}

Library::~Library() {
    Book* current = head;
    while (current != nullptr) {
        Book* nextBook = current->next;
        delete current; // Вызывает деструктор Book -> вызывает деструктор Queue
        current = nextBook;
    }
}

bool Library::isIDUnique(int id) {
    return searchBookByID(id) == nullptr;
}

// === ALGORITHM: Sorted Insert into Linked List ===
// Requirement: "inserted into the linked list in sorted order by Book ID"
void Library::addBook(int id, string title, string author, int total) {
    if (!isIDUnique(id)) {
        cout << "Error: Book with ID " << id << " already exists!" << endl;
        return;
    }

    Book* newBook = new Book(id, title, author, total);

    // Случай 1: Список пуст или новый ID меньше первого элемента
    // Вставка в начало (Head)
    if (head == nullptr || head->id > id) {
        newBook->next = head;
        head = newBook;
    } 
    else {
        // Случай 2: Ищем позицию для вставки в середине или конце
        Book* current = head;
        
        // Идем пока не дойдем до конца ИЛИ пока следующий ID меньше нового
        while (current->next != nullptr && current->next->id < id) {
            current = current->next;
        }
        
        // Вставляем newBook ПОСЛЕ current
        newBook->next = current->next;
        current->next = newBook;
    }
    cout << "Book '" << title << "' added successfully." << endl;
}

// === SEARCH OPERATIONS ===
Book* Library::searchBookByID(int id) {
    Book* current = head;
    while (current != nullptr) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

Book* Library::searchBookByTitle(string title) {
    Book* current = head;
    while (current != nullptr) {
        // Для простоты сравнение чувствительно к регистру.
        // В идеале нужно приводить к lower_case.
        if (current->title == title) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

Book* Library::searchBookByAuthor(string author) {
    Book* current = head;
    while (current != nullptr) {
        if (current->author == author) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

// === ISSUE LOGIC ===
// Requirement: Check availability -> Issue OR Add to Queue
void Library::issueBook(int bookID, int studentID) {
    Book* book = searchBookByID(bookID);
    if (book == nullptr) {
        cout << "Error: Book not found." << endl;
        return;
    }

    // 1. Если есть копии -> выдаем
    if (book->borrowBook()) {
        cout << "Book issued to Student ID: " << studentID << endl;
    } 
    // 2. Если копий нет -> ставим в очередь
    else {
        cout << "No copies available. Adding Student " << studentID << " to waiting list..." << endl;
        book->waitList.enqueue(studentID);
        // Requirement: "Inform the student of their position" - это можно добавить в Queue.h, 
        // но пока просто подтвердим добавление.
    }
}

// === RETURN LOGIC ===
// Requirement: If queue not empty -> give to next student. Else -> increase copies.
void Library::returnBook(int bookID) {
    Book* book = searchBookByID(bookID);
    if (book == nullptr) {
        cout << "Error: Book not found." << endl;
        return;
    }

    // Проверяем очередь ожидания
    if (!book->waitList.isEmpty()) {
        int nextStudent = book->waitList.dequeue();
        cout << "Book returned. Automatically issued to next student in queue: ID " << nextStudent << endl;
        // Важно: availableCopies НЕ увеличивается, так как книга перешла из рук в руки.
        // [Cite source: 52 "Available copies remain unchanged"]
    } 
    else {
        book->returnBookCopy();
        cout << "Book returned successfully. Available copies increased." << endl;
    }
}

void Library::displayAllBooks() {
    if (head == nullptr) {
        cout << "Library is empty." << endl;
        return;
    }
    
    cout << "\n--- Library Catalog ---" << endl;
    Book* current = head;
    while (current != nullptr) {
        current->displayBookInfo(); // Метод из Book.cpp
        current = current->next;
    }
    cout << "-----------------------" << endl;
}
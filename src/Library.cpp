#include "../include/Library.h"
#include "../include/FineManager.h"

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

void Library::issueBook(int bookID, int studentID) {
    Book* book = searchBookByID(bookID);
    if (book == nullptr) {
        cout << "Error: Book not found." << endl;
        return;
    }

    // 1. Если есть копии -> выдаем и назначаем дату
    if (book->borrowBook()) {
        cout << "------------------------------------------------" << endl;
        cout << "SUCCESS: Book issued to Student ID: " << studentID << endl;
        
        // [Feature C: Due-Date]
        // Стандартный срок выдачи - 14 дней
        string dueDate = FineManager::getDueDateString(14);
        cout << "DUE DATE: " << dueDate << " (Please return by this date)" << endl;
        cout << "------------------------------------------------" << endl;
    } 
    // 2. Если копий нет -> очередь
    else {
        cout << "No copies available. Adding Student " << studentID << " to waiting list..." << endl;
        book->waitList.enqueue(studentID);
    }
}

// === RETURN LOGIC (UPDATED) ===
void Library::returnBook(int bookID) {
    Book* book = searchBookByID(bookID);
    if (book == nullptr) {
        cout << "Error: Book not found." << endl;
        return;
    }

    // [Feature C: Fine Calculation]
    // Спрашиваем библиотекаря о просрочке
    int delayedDays = 0;
    cout << "Enter days delayed (0 if returned on time): ";
    // Простая защита от ввода букв
    if (!(cin >> delayedDays)) {
        cin.clear();
        cin.ignore(1000, '\n');
        delayedDays = 0;
    }

    if (delayedDays > 0) {
        int fine = FineManager::calculateFine(delayedDays);
        cout << "\n!!! LATE RETURN DETECTED !!!" << endl;
        cout << "Fine amount: " << fine << " UZS" << endl;
        cout << "Please collect the fine from the student.\n" << endl;
    } else {
        cout << "Returned on time. No fine." << endl;
    }

    // Стандартная логика возврата (очередь или полка)
    if (!book->waitList.isEmpty()) {
        int nextStudent = book->waitList.dequeue();
        cout << "Book passed to next student in queue: ID " << nextStudent << endl;
        
        // Сразу сообщаем новому студенту его дату возврата
        cout << "New Due Date for Student " << nextStudent << ": " << FineManager::getDueDateString(14) << endl;
    } 
    else {
        book->returnBookCopy();
        cout << "Book returned to shelf. Available copies increased." << endl;
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
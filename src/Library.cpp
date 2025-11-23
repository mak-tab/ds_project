#include "../include/Library.h"
#include "../include/FineManager.h"
#include "../include/Utils.h"

Library::Library() { head = nullptr; }

Library::~Library() {
    Book* current = head;
    while (current != nullptr) {
        Book* nextBook = current->next;
        delete current;
        current = nextBook;
    }
}

bool Library::isIDUnique(int id) { return searchBookByID(id) == nullptr; }

void Library::addBook(int id, string title, string author, int total) {
    if (!isIDUnique(id)) {
        cout << "[ERROR]: Book with ID " << id << " already exists!" << endl;
        return;
    }

    Book* newBook = new Book(id, title, author, total);

    if (head == nullptr || head->id > id) {
        newBook->next = head;
        head = newBook;
    } 
    else {
        Book* current = head;
        
        while (current->next != nullptr && current->next->id < id) { current = current->next; }
        
        newBook->next = current->next;
        current->next = newBook;
    }
    cout << "Book '" << title << "' added successfully." << endl;
}

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
    Book* bestMatch = nullptr;
    int minDistance = 100;

    cout << "Searching for  -  " << title << "" << endl;

    while (current != nullptr) {
        if (Utils::toLower(current->title) == Utils::toLower(title)) { return current; }

        int dist = Utils::levenshteinDistance(current->title, title);
        
        if (dist < 3 && dist < minDistance) {
            minDistance = dist;
            bestMatch = current;
        }

        current = current->next;
    }

    if (bestMatch != nullptr) {
        cout << "Exact match not found. You probably meant: \"" << bestMatch->title << "\"" << endl;
        return bestMatch;
    }

    return nullptr;
}

Book* Library::searchBookByAuthor(string author) {
    Book* current = head;
    while (current != nullptr) {
        if (current->author == author) { return current; }
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

    if (book->borrowBook()) {
        cout << "[SUCCESS]: Book issued to Student ID: " << studentID << endl;
        
        string dueDate = FineManager::getDueDateString(14);
        cout << "DUE DATE: " << dueDate << " (Please return by this date)" << endl;
        cout << "------------------------------------------------" << endl;
    } 
    else {
        cout << "No copies available. Adding Student " << studentID << " to waiting list..." << endl;
        book->waitList.enqueue(studentID);
    }
}

void Library::returnBook(int bookID) {
    Book* book = searchBookByID(bookID);
    if (book == nullptr) {
        cout << "Error: Book not found." << endl;
        return;
    }

    int delayedDays = 0;
    cout << "[INFO] Enter days delayed (0 if returned on time): ";
    if (!(cin >> delayedDays)) {
        cin.clear();
        cin.ignore(1000, '\n');
        delayedDays = 0;
    }

    if (delayedDays > 0) {
        int fine = FineManager::calculateFine(delayedDays);
        cout << "[INFO] Fine amount: " << fine << " UZS" << endl;
        cout << "Please collect the fine from the student.\n" << endl;
    } else {
        cout << "[INFO] Returned on time. No fine." << endl;
    }

    if (!book->waitList.isEmpty()) {
        int nextStudent = book->waitList.dequeue();
        cout << "Book passed to next student in queue: ID " << nextStudent << endl;
        
        cout << "[INFO] New Due Date for Student " << nextStudent << ": " << FineManager::getDueDateString(14) << endl;
    } 
    else {
        book->returnBookCopy();
        cout << "[INFO] Book returned to shelf. Available copies increased." << endl;
    }
}

void Library::displayAllBooks() {
    if (head == nullptr) {
        cout << "Library is empty." << endl;
        return;
    }
    
    cout << R"(
    |=============================|
    ||      Library Catalog      ||
    |=============================|
    )";
    Book* current = head;
    while (current != nullptr) {
        current->displayBookInfo();
        current = current->next;
    }
    cout << "|=============================|" << endl;
}
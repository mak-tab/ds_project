#include "../include/Library.h"
#include "../include/FineManager.h"
#include "../include/Utils.h"

Library::Library() {
    head = nullptr;
}

Library::~Library() {
    Book* current = head;
    while (current != nullptr) {
        Book* nextBook = current->next;
        delete current;
        current = nextBook;
    }
}

bool Library::isIDUnique(int id) {
    return searchBookByID(id) == nullptr;
}

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
        while (current->next != nullptr && current->next->id < id) {
            current = current->next;
        }
        newBook->next = current->next;
        current->next = newBook;
    }
    cout << "Book '" << title << "' added successfully." << endl;
    
    // Добавляем действие в стек для Undo
    historyStack.push("ADD_BOOK", id);
}

void Library::deleteBook(int id) {
    if (head == nullptr) return;

    if (head->id == id) {
        Book* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Book* current = head;
    while (current->next != nullptr && current->next->id != id) {
        current = current->next;
    }

    if (current->next != nullptr) {
        Book* temp = current->next;
        current->next = current->next->next;
        delete temp;
    }
}

void Library::undoLastAction() {
    if (historyStack.isEmpty()) {
        cout << "Nothing to undo." << endl;
        return;
    }

    Action lastAction = historyStack.pop();

    if (lastAction.type == "ADD_BOOK") {
        deleteBook(lastAction.bookID);
        cout << "Undo: Removed recently added book (ID: " << lastAction.bookID << ")." << endl;
    }
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

    cout << "Searching for: " << title << "..." << endl;

    while (current != nullptr) {
        if (Utils::toLower(current->title) == Utils::toLower(title)) {
            return current;
        }

        int dist = Utils::levenshteinDistance(current->title, title);
        
        if (dist < 3 && dist < minDistance) {
            minDistance = dist;
            bestMatch = current;
        }

        current = current->next;
    }

    if (bestMatch != nullptr) {
        cout << "Exact match not found. Did you mean: '" << bestMatch->title << "'?" << endl;
        return bestMatch;
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
        cout << "[ERROR] Book not found." << endl;
        return;
    }

    if (book->borrowBook()) {
        // ЗАПИСЫВАЕМ ВРЕМЯ ВЫДАЧИ
        loanManager.addLoan(bookID, studentID);

        cout << "------------------------------------------------" << endl;
        cout << "[SUCCESS] Book issued to Student ID: " << studentID << endl;
        cout << "[INFO] DUE DATE: " << FineManager::getDueDateString(14) << endl;
        cout << "------------------------------------------------" << endl;
    } 
    else {
        cout << "[INFO] No copies available. Adding Student " << studentID << " to queue." << endl;
        book->waitList.enqueue(studentID);
    }
}

// === ЕДИНСТВЕННАЯ ВЕРСИЯ RETURN BOOK (AUTOMATIC) ===
void Library::returnBook(int bookID) {
    Book* book = searchBookByID(bookID);
    if (book == nullptr) {
        cout << "[ERROR] Book not found." << endl;
        return;
    }

    // Автоматический расчет просрочки через LoanManager
    int delay = loanManager.returnLoanAndGetDelay(bookID, -1); 

    if (delay > 0) {
        int fine = FineManager::calculateFine(delay);
        cout << "\n[ALERT] BOOK IS OVERDUE!" << endl;
        cout << "[INFO] Days delayed: " << delay << endl;
        cout << "[INFO] Automatic Fine: " << fine << " UZS" << endl;
    } else {
        cout << "[INFO] Returned on time (or no loan record found). No fine." << endl;
    }

    // Логика очереди
    if (!book->waitList.isEmpty()) {
        int nextStudent = book->waitList.dequeue();
        cout << "[INFO] Book passed to next student: ID " << nextStudent << endl;
        
        // Оформляем выдачу следующему
        loanManager.addLoan(bookID, nextStudent);
        cout << "[INFO] New Due Date for Student " << nextStudent << ": " << FineManager::getDueDateString(14) << endl;
    } 
    else {
        book->returnBookCopy();
        cout << "[INFO] Book returned to shelf." << endl;
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
        current->displayBookInfo();
        current = current->next;
    }
    cout << "-----------------------" << endl;
}
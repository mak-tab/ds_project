#include "../include/Book.h"

Book::Book(int id, string title, string author, int total) {
    this->id = id;
    this->title = title;
    this->author = author;
    this->totalCopies = total;
    this->availableCopies = total;
    this->next = nullptr;
}

bool Book::borrowBook() {
    if (availableCopies > 0) {
        availableCopies--;
        return true;
    }
    return false;
}

void Book::returnBookCopy() {
    if (availableCopies < totalCopies) { availableCopies++; }
}

void Book::displayBookInfo() const {
    cout << R"(
    |================================================================|
    ||                       Book Information                       ||
    |================================================================|
    ||  ID: )" << id << R"(                                         ||
    ||  Title: )" << title << R"(                                   ||
    ||  Author: )" << author << R"(                                 ||
    ||  Copies: )" << availableCopies << "/" << totalCopies << R"(  ||
    |================================================================|
    )";
    
    if (!waitList.isEmpty()) { cout << " [Waitlist Active]"; } // << endl; }
    cout << endl;
}
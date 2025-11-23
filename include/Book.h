#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <iostream>
#include "Queue.h"

using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    int totalCopies;
    int availableCopies;

    Queue waitList;

    Book* next;

    Book(int id, string title, string author, int total);

    bool borrowBook();

    void returnBookCopy();

    void displayBookInfo() const;
};

#endif
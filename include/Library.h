#ifndef LIBRARY_H
#define LIBRARY_H

#include <iostream>
#include <string>
#include "Book.h"

using namespace std;

class Library {
private:
    Book* head;

    bool isIDUnique(int id);

public:
    Library();
    ~Library();

    void addBook(
        int id, 
        string title, 
        string author, 
        int total   
    );
    
    Book* searchBookByID(int id);
    Book* searchBookByTitle(string title);
    Book* searchBookByAuthor(string author);

    void issueBook(int bookID, int studentID);
    void returnBook(int bookID);

    void displayAllBooks();
    
    Book* getHead() const { return head; }
};

#endif

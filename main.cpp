// my_project/
// │
// ├── include/
// │   ├── Book.h
// │   ├── FileManager.h
// │   ├── Library.h
// │   └── Queue.h
// │
// ├── src/
// │   ├── Book.cpp
// │   ├── FileManager.cpp
// │   ├── Library.cpp
// │   └── Queue.cpp
// │
// ├── Extended_Features/
// │   ├── AVL_Tree_for_Fast_Searching
// │   │   └── 
// │   │
// │   ├── User_Login_System/
// │   │   └── 
// │   │
// │   └── Due-Date_and_Fine_Calculation/
// │       └── 
// │   
// ├── library_data.csv
// └── main.cpp

#include <iostream>
#include <limits>
#include "/include/Library.h"
#include "/include/FileManager.h"
#include "/include/AuthManager.h"

using namespace std;

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Меню для Студента
void studentMenu(Library& lib, User* currentUser) {
    int choice = 0;
    while (choice != 4) {
        cout << "\n--- STUDENT MENU (" << currentUser->username << ") ---" << endl;
        cout << "1. Search for a Book" << endl;
        cout << "2. Borrow Book (Issue)" << endl;
        cout << "3. Return Book" << endl;
        cout << "4. Logout" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                // Упрощенный поиск для студента (по названию)
                string title;
                cout << "Enter Book Title: ";
                cin.ignore();
                getline(cin, title);
                Book* b = lib.searchBookByTitle(title);
                if(b) b->displayBookInfo(); else cout << "Not found." << endl;
                break;
            }
            case 2: {
                int bookID;
                cout << "Enter Book ID to borrow: ";
                cin >> bookID;
                // Студент использует свой ID автоматически
                lib.issueBook(bookID, currentUser->id);
                break;
            }
            case 3: {
                int bookID;
                cout << "Enter Book ID to return: ";
                cin >> bookID;
                lib.returnBook(bookID);
                break;
            }
            case 4:
                cout << "Logging out..." << endl;
                break;
            default: cout << "Invalid choice." << endl;
        }
    }
}

// Меню для Админа
void adminMenu(Library& lib, User* currentUser, FileManager& fm) {
    int choice = 0;
    while (choice != 6) {
        cout << "\n--- ADMIN MENU (" << currentUser->username << ") ---" << endl;
        cout << "1. Add New Book" << endl;
        cout << "2. Search for a Book" << endl;
        cout << "3. Display All Books" << endl;
        cout << "4. Save Data" << endl;
        cout << "5. Issue/Return (Manual Override)" << endl;
        cout << "6. Logout" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int id, total;
                string title, author;
                cout << "ID: "; cin >> id;
                cin.ignore();
                cout << "Title: "; getline(cin, title);
                cout << "Author: "; getline(cin, author);
                cout << "Copies: "; cin >> total;
                lib.addBook(id, title, author, total);
                break;
            }
            case 2: {
                int id; cout << "ID: "; cin >> id;
                Book* b = lib.searchBookByID(id);
                if(b) b->displayBookInfo(); else cout << "Not found." << endl;
                break;
            }
            case 3: lib.displayAllBooks(); break;
            case 4: fm.saveBooks(lib); break;
            case 5: cout << "Use student menu for flow test or implement override here." << endl; break;
            case 6: cout << "Logging out..." << endl; break;
            default: cout << "Invalid choice." << endl;
        }
    }
}

int main() {
    Library lib;
    FileManager fileManager("library_data.csv");
    AuthManager authManager; // Система авторизации

    fileManager.loadBooks(lib);

    while (true) {
        cout << "\n=== WELCOME TO INHA LIBRARY SYSTEM ===" << endl;
        cout << "1. Login" << endl;
        cout << "2. Exit" << endl;
        cout << "Choice: ";
        
        int startChoice;
        if (!(cin >> startChoice)) {
            clearInput();
            continue;
        }

        if (startChoice == 2) {
            fileManager.saveBooks(lib);
            break;
        }

        if (startChoice == 1) {
            string user, pass;
            cout << "Username: "; cin >> user;
            cout << "Password: "; cin >> pass;

            User* currentUser = authManager.authenticate(user, pass);

            if (currentUser != nullptr) {
                cout << "Login successful! Role: " << (currentUser->role == ADMIN ? "Admin" : "Student") << endl;
                
                if (currentUser->role == ADMIN) {
                    adminMenu(lib, currentUser, fileManager);
                } else {
                    studentMenu(lib, currentUser);
                }
            } else {
                cout << "Error: Invalid credentials!" << endl;
            }
        }
    }
    return 0;
}
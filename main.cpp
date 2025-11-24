#include <iostream>
#include <limits>
#include "include/Library.h"
#include "include/FileManager.h"
#include "include/AuthManager.h"

using namespace std;

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void studentMenu(Library& lib, User* currentUser) {
    int choice = 0;
    while (choice != 4) {
        cout << R"(
|=========================================================|
||  STUDENT MENU (")" << currentUser->username << R"()   ||
|=========================================================|
|| [1] Search for a Book                                 ||
|| [2] Borrow Book (Issue)                               ||
|| [3] Return Book                                       ||
|| [4] Logout                                            ||
|=========================================================|
)";

        cout << "Enter choice: ";
        
        if (!(cin >> choice)) {
            cout << "[ERROR]Invalid input! Please enter a number." << endl;
            clearInput();
            continue;
        }

        switch (choice) {
            case 1: {
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
                while (!(cin >> bookID)) {
                    cout << "[ERROR]Invalid ID. Enter a number: ";
                    clearInput();
                }
                lib.issueBook(bookID, currentUser->id);
                break;
            }
            case 3: {
                int bookID;
                cout << "Enter Book ID to return: ";
                while (!(cin >> bookID)) {
                    cout << "[ERROR]Invalid ID. Enter a number: ";
                    clearInput();
                }
                lib.returnBook(bookID);
                break;
            }
            case 4:
                cout << "[INFO] Log out" << endl;
                break;
            default: cout << "[ERROR]Invalid choice." << endl;
        }
    }
}

void adminMenu(Library& lib, User* currentUser, FileManager& fm, AuthManager& auth) {
    int choice = 0;
    while (choice != 8) {
        cout << R"(
|=========================================================|
||  ADMIN MENU (")" << currentUser->username << R"()     ||
|=========================================================|
||     [1] Add New Book                                  ||
||     [2] Search for a Book                             ||
||     [3] Display All Books                             ||
||     [4] Save Data                                     ||
||     [5] Issue/Return (Manual Override)                ||
||     [6] Register New User                             ||
||     [7] Undo Last Action (Stack Demo) (It is BETA)    ||
||     [8] Logout                                        ||
|=========================================================|
)";
        cout << "Enter choice: ";
        
        if (!(cin >> choice)) {
            cout << "[ERROR] Invalid input! Please enter a number." << endl;
            clearInput();
            continue;
        }

        switch (choice) {
            case 1: {
                int id, total;
                string title, author;
                cout << "ID: "; 
                while (!(cin >> id)) {
                    cout << "[ERROR] Invalid input. Enter Number: ";
                    clearInput();
                }
                cin.ignore();
                
                cout << "Title: "; getline(cin, title);
                cout << "Author: "; getline(cin, author);
                
                cout << "Copies: "; 
                while (!(cin >> total)) {
                    cout << "[ERROR] Invalid input. Enter Number: ";
                    clearInput();
                }
                
                lib.addBook(id, title, author, total);
                break;
            }
            case 2: {
                int id; 
                cout << "ID: "; 
                while (!(cin >> id)) {
                    cout << "[ERROR] Invalid ID. Enter a number: ";
                    clearInput();
                }
                Book* b = lib.searchBookByID(id);
                if(b) b->displayBookInfo(); else cout << "[INFO] Not found." << endl;
                break;
            }
            case 3: lib.displayAllBooks(); break;
            case 4: fm.saveBooks(lib); break;
            case 5: cout << "Use student menu for flow test or implement override here." << endl; break;
            case 6: { 
                string newU, newP;
                int roleChoice;
                cout << "Enter UserName: "; cin >> newU;
                cout << "Enter Password: "; cin >> newP;
                cout << "Role (0 = Admin, 1 = Student): "; 
                while (!(cin >> roleChoice)) {
                    cout << "[ERROR] Invalid input. Enter 0 or 1: ";
                    clearInput();
                }
                        
                if (auth.registerUser(newU, newP, (UserRole)roleChoice)) {
                    cout << "[INFO] User registered successfully!" << endl;
                } else {
                    cout << "[ERROR] Username already exists." << endl;
                }
                break;
            }
            case 7: lib.undoLastAction(); break;
            case 8: cout << "[INFO] Logging out..." << endl; break;
            default: cout << "[ERROR] Invalid choice." << endl;
        }
    }
}

int main() {
    Library lib;
    FileManager fileManager("library_data.csv");
    AuthManager authManager; 

    fileManager.loadBooks(lib);

    while (true) {
        cout << R"(
|==============================|
||          WELCOME           ||
||            TO              ||
||  SOMEONE's LIBRARY SYSTEM  ||
|==============================|
||     [1] Login              ||
||     [2] Exit               ||
|==============================|
)";
        cout << "Enter choice: ";
        
        int startChoice;
        if (!(cin >> startChoice)) {
            cout << "[ERROR] Invalid input! Please enter a number." << endl;
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
                cout << "[INFO] Login successful! Role: " << (currentUser->role == ADMIN ? "Admin" : "Student") << endl;
                
                if (currentUser->role == ADMIN) { adminMenu(lib, currentUser, fileManager, authManager); } 
                else { studentMenu(lib, currentUser); }
            } else {
                cout << "[ERROR] Invalid credentials!" << endl;
            }
        }
    }
    return 0;
}
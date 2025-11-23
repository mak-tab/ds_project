#include "../include/FileManager.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

using namespace std;

FileManager::FileManager(string file) {
    filename = file;
}

void FileManager::saveBooks(Library& lib) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cerr << "Error: Could not open file for saving!" << endl;
        return;
    }

    outFile << "ID,Title,Author,TotalCopies,AvailableCopies" << endl;

    Book* current = lib.getHead();
    while (current != nullptr) {
        outFile << current->id << ","
                << current->title << ","
                << current->author << ","
                << current->totalCopies << ","
                << current->availableCopies << endl;
        current = current->next;
    }
    outFile.close();
    cout << "Data saved successfully." << endl;
}

void FileManager::loadBooks(Library& lib) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cout << "File not found. Creating new database..." << endl;
        return;
    }

    string line;
    getline(inFile, line); // Пропуск заголовка

    while (getline(inFile, line)) {
        stringstream ss(line);
        string segment;
        vector<string> row;

        while (getline(ss, segment, ',')) {
            row.push_back(segment);
        }

        if (row.size() >= 5) {
            try {
                int id = stoi(row[0]);
                string title = row[1];
                string author = row[2];
                int total = stoi(row[3]);
                int available = stoi(row[4]);

                lib.addBook(id, title, author, total);
                
                // Хак для восстановления availableCopies
                Book* loadedBook = lib.searchBookByID(id);
                if (loadedBook) {
                    loadedBook->availableCopies = available;
                }
            } catch (...) {
                continue;
            }
        }
    }
    inFile.close();
}
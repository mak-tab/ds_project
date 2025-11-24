#include "../include/LoanManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

// const double LOAN_PERIOD_SECONDS = 14 * 24 * 60 * 60; 
const double LOAN_PERIOD_SECONDS = 14 ; // TODO: Для тестов: 14 секунд

LoanManager::LoanManager(string file) : filename(file) {
    loadLoans();
}

void LoanManager::loadLoans() {
    loans.clear();
    ifstream in(filename);
    if (!in.is_open()) return;

    string line, segment;
    while (getline(in, line)) {
        stringstream ss(line);
        vector<string> row;
        while (getline(ss, segment, ',')) row.push_back(segment);

        if (row.size() >= 3) {
            Loan l;
            l.bookID = stoi(row[0]);
            l.studentID = stoi(row[1]);
            l.issueDate = (time_t)stoll(row[2]); // stoll = string to long long
            loans.push_back(l);
        }
    }
    in.close();
}

void LoanManager::saveLoans() {
    ofstream out(filename);
    if (!out.is_open()) return;

    for (const auto& l : loans) {
        out << l.bookID << "," << l.studentID << "," << l.issueDate << endl;
    }
    out.close();
}

void LoanManager::addLoan(int bookID, int studentID) {
    Loan l;
    l.bookID = bookID;
    l.studentID = studentID;
    l.issueDate = time(nullptr); // Записываем ТЕКУЩЕЕ время системы
    loans.push_back(l);
    saveLoans();
}

int LoanManager::returnLoanAndGetDelay(int bookID, int studentID) {
    int delayDays = 0;
    int indexToRemove = -1;

    for (int i = 0; i < loans.size(); ++i) {
        if (loans[i].bookID == bookID) {
            // Если studentID передан как -1, значит возвращает любой (для упрощения),
            // но лучше проверять конкретного студента.
            // В нашем меню пока ID студента при возврате не вводится явно, 
            // поэтому берем первую запись по ID книги.
            
            time_t now = time(nullptr);
            double secondsPassed = difftime(now, loans[i].issueDate);

            if (secondsPassed > LOAN_PERIOD_SECONDS) {
                double diff = secondsPassed - LOAN_PERIOD_SECONDS;
                // Переводим лишние секунды в дни (округляем вверх)
                delayDays = (int)(diff / (24 * 3600)) + 1;
            }
            
            indexToRemove = i;
            break;
        }
    }

    if (indexToRemove != -1) {
        loans.erase(loans.begin() + indexToRemove);
        saveLoans();
    }

    return delayDays;
}

bool LoanManager::isBookBorrowedBy(int bookID, int studentID) {
    for (const auto& l : loans) {
        if (l.bookID == bookID && l.studentID == studentID) return true;
    }
    return false;
}
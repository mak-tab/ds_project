#ifndef LOANMANAGER_H
#define LOANMANAGER_H

#include <string>
#include <vector>
#include <ctime>

using namespace std;

struct Loan {
    int bookID;
    int studentID;
    time_t issueDate;
};

class LoanManager {
private:
    string filename;
    vector<Loan> loans;
    
    void loadLoans();
    void saveLoans();

public:
    LoanManager(string file = "loans.csv");

    void addLoan(int bookID, int studentID);

    int returnLoanAndGetDelay(int bookID, int studentID);
    
    bool isBookBorrowedBy(int bookID, int studentID);
};

#endif
#ifndef FINEMANAGER_H
#define FINEMANAGER_H

#include <string>
#include <ctime>

using namespace std;

class FineManager {
public:
    static const int FINE_PER_DAY = 5000; 
    static string getDueDateString(int daysToAdd);
    static int calculateFine(int daysDelayed);
};

#endif
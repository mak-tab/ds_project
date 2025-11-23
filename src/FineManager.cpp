#include "../include/FineManager.h"
#include <iostream>
#include <sstream>
#include <iomanip>

int FineManager::calculateFine(int daysDelayed) {
    if (daysDelayed <= 0) return 0;
    return daysDelayed * FINE_PER_DAY;
}

string FineManager::getDueDateString(int daysToAdd) {
    time_t now = time(nullptr);
    tm* ltm = localtime(&now);
    ltm->tm_mday += daysToAdd;
    mktime(ltm);

    char buffer[80];
    strftime(buffer, sizeof(buffer), "%d/%m/%Y", ltm);
    return string(buffer);
}
#include "../include/FileManager.h"
#include <iostream>
#include <sstream>
#include <iomanip> // Для put_time

int FineManager::calculateFine(int daysDelayed) {
    if (daysDelayed <= 0) return 0;
    return daysDelayed * FINE_PER_DAY;
}

string FineManager::getDueDateString(int daysToAdd) {
    // Получаем текущее время
    time_t now = time(nullptr);
    
    // Конвертируем в структуру tm (время)
    tm* ltm = localtime(&now);

    // Добавляем дни
    ltm->tm_mday += daysToAdd;
    
    // Нормализуем дату (mktime сам исправит "32 января" на "1 февраля")
    mktime(ltm);

    // Форматируем в строку (DD/MM/YYYY)
    // В C++ (до C++11/20) put_time не всегда доступен, сделаем классически через strftime
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%d/%m/%Y", ltm);
    
    return string(buffer);
}
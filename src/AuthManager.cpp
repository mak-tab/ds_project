#include "../include/AuthManager.h"

AuthManager::AuthManager() {
    // Создаем дефолтных пользователей для проверки
    // В реальной системе это загружалось бы из файла users.csv
    users.push_back(User(1, "admin", "admin123", ADMIN));
    users.push_back(User(2, "student", "1234", STUDENT));
}

User* AuthManager::authenticate(string username, string password) {
    for (auto& user : users) {
        if (user.username == username && user.password == password) {
            return &user;
        }
    }
    return nullptr; // Неверный логин или пароль
}
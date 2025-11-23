#include "../include/AuthManager.h"
#include <fstream>
#include <iostream>

using namespace std;

AuthManager::AuthManager() {
    // При создании класса пытаемся загрузить пользователей
    // Если не выйдет - метод loadUsers сам создаст админа
    loadUsers();
}

// Загрузка из файла users.txt
void AuthManager::loadUsers() {
    users.clear();
    ifstream file("users.txt");
    
    if (!file.is_open()) {
        cout << "[Auth] Users file not found. Creating default admin..." << endl;
        // Если файла нет, создаем дефолтного админа и сохраняем
        registerUser("admin", "admin123", ADMIN); 
        return;
    }

    string u, p;
    int r;
    while (file >> u >> p >> r) {
        users.push_back(User(0, u, p, (UserRole)r));
    }
    file.close();
}

// Сохранение в файл
void AuthManager::saveUsers() {
    ofstream file("users.txt");
    if (!file.is_open()) return;

    for (const auto& user : users) {
        file << user.username << " " << user.password << " " << (int)user.role << endl;
    }
    file.close();
}

User* AuthManager::authenticate(string username, string password) {
    // Можно перезагрузить, чтобы видеть новых юзеров, добавленных другими
    // loadUsers(); 
    
    for (auto& user : users) {
        if (user.username == username && user.password == password) {
            return &user;
        }
    }
    return nullptr;
}

bool AuthManager::registerUser(string username, string password, UserRole role) {
    // Проверка на дубликаты
    for (const auto& user : users) {
        if (user.username == username) return false; // Уже есть такой
    }

    // Добавляем в память
    users.push_back(User(users.size() + 1, username, password, role));
    
    // Сохраняем на диск
    saveUsers();
    return true;
}
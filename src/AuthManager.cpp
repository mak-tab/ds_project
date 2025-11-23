#include "../include/AuthManager.h"
#include <fstream>
#include <iostream>

AuthManager::AuthManager() {
    loadUsers();
}

void AuthManager::loadUsers() {
    users.clear();
    ifstream file("users.txt");
    
    if (!file.is_open()) {
        // Если файла нет, создаем дефолтного админа
        cout << "Users file not found. Creating default admin..." << endl;
        registerUser("admin", "admin123", ADMIN);
        return;
    }

    string u, p;
    int r;
    while (file >> u >> p >> r) {
        users.push_back(User(0, u, p, (UserRole)r)); // ID пока фиктивный (0)
    }
    file.close();
}

void AuthManager::saveUsers() {
    ofstream file("users.txt");
    if (!file.is_open()) return;

    for (const auto& user : users) {
        file << user.username << " " << user.password << " " << user.role << endl;
    }
    file.close();
}

User* AuthManager::authenticate(string username, string password) {
    // Перезагружаем, чтобы видеть новых пользователей без перезапуска
    // (Для оптимизации можно убрать, но для надежности оставим)
    // loadUsers(); 
    
    for (auto& user : users) {
        if (user.username == username && user.password == password) {
            return &user;
        }
    }
    return nullptr;
}

// Метод регистрации (нужно добавить объявление в AuthManager.h!)
bool AuthManager::registerUser(string username, string password, UserRole role) {
    // Проверка на дубликаты
    for (const auto& user : users) {
        if (user.username == username) return false;
    }

    User newUser(users.size() + 1, username, password, role);
    users.push_back(newUser);
    saveUsers(); // Сразу сохраняем в файл
    return true;
}
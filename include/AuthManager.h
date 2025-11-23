#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include "User.h"
#include <vector>
#include <string>

class AuthManager {
private:
    vector<User> users; // Список зарегистрированных пользователей

public:
    AuthManager(); // Здесь создадим пользователей (admin/admin, student/123)

    // Возвращает указатель на найденного пользователя или nullptr, если логин неверен
    User* authenticate(string username, string password);
    bool registerUser(string username, string password, UserRole role);
};

#endif
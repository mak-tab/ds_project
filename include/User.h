#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

enum UserRole {
    ADMIN,
    STUDENT
};

class User {
public:
    int id;
    string username;
    string password;
    UserRole role;

    User(int id, string username, string password, UserRole role) : id(id), username(username), password(password), role(role) {}
};

#endif
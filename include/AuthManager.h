#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include "User.h"
#include <vector>
#include <string>

class AuthManager {
private:
    vector<User> users; 
    
    // ЭТИ ДВА МЕТОДА БЫЛИ ПРОПУЩЕНЫ:
    void loadUsers();
    void saveUsers();

public:
    AuthManager(); 
    User* authenticate(string username, string password);
    bool registerUser(string username, string password, UserRole role);
};

#endif
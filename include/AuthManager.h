#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include <vector>
#include <string>
#include "User.h"

class AuthManager {
private:
    vector<User> users; 
    
    void loadUsers();
    void saveUsers();

public:
    AuthManager(); 
    User* authenticate(
        string username, 
        string password
    );
    bool registerUser(
        string username, 
        string password, 
        UserRole role
    );
};

#endif

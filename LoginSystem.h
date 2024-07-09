#ifndef LOGINSYSTEM_H
#define LOGINSYSTEM_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include "User.h"
#include "Color.h"

using namespace std;

class LoginSystem 
{
private:
    vector<User> users; // Stores all users
    void loadUsers(const string&); // Loads users from file
    string currentUser; // Stores the username of the current user

public:
    LoginSystem();

    bool login(const string&, const string&); // Check if the username and password match
    string Login(); // Prompts user to login
};

#endif

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
    vector<User> users;
    void loadUsers(const string&);

public:
    LoginSystem();
    bool login(const string&, const string&);
    void Login();
};

#endif

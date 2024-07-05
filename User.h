#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

class User 
{
private:
    string username;
    string password;

public:
    User(const string&, const string&);

    string getUsername() const;
    bool checkPassword(const string&) const;
};

#endif
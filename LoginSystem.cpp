#include "LoginSystem.h"

LoginSystem::LoginSystem()
{
    loadUsers("user.csv");
}

void LoginSystem::loadUsers(const string& filename)
{
    ifstream ifs(filename);
    if (!ifs.is_open())
    {
        throw runtime_error("Could not open file for reading: " + filename);
    }

    string line;
    getline(ifs, line); // Skip header line
    while (getline(ifs, line)) 
    {
        stringstream ss(line);
        string username, password;
        getline(ss, username, ',');
        getline(ss, password, ',');
        users.push_back(User(username, password));
    }
}

bool LoginSystem::login(const string& username, const string& password)
{
    for (const auto& user : users)
    {
        if (user.getUsername() == username && user.checkPassword(password)) 
        {
            return true;
        }
    }
    return false;
}

void LoginSystem::Login() 
{
    string username, password;
    bool loggedIn = false;
    while (!loggedIn) 
    {
        cout<<"=== Welcome to the Food Order Login System ==="<<endl;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        
        system("cls");

        if (login(username, password)) 
        {
            loggedIn = true;
            cout << GREEN << "Login successful!" << RESET << endl;
        }
        else {
            cout << "Invalid username or password. Please try again." << endl;
        }
    }
}

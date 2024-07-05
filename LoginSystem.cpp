#include "LoginSystem.h"

LoginSystem::LoginSystem()
{
    loadUsers("user.csv");
}

// Loads users from file
void LoginSystem::loadUsers(const string& filename)
{
    ifstream userData(filename);
    
    if (!userData.is_open())
    {
        // Throw an exception if the file could not be opened
        throw runtime_error("Could not open file for reading: " + filename);
    }

    string line;
    getline(userData, line); // Skip header line
    while (getline(userData, line)) 
    {
        stringstream ss(line);
        string username, password;

        // Extract username and password from the line and push it to the users vector
        getline(ss, username, ',');
        getline(ss, password, ',');
        users.push_back(User(username, password));
    }
}

// Check if the username and password match
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

// Prompts user to login
void LoginSystem::Login() 
{
    string username, password;
    bool loggedIn = false;

    while (!loggedIn) // Keep asking for username and password until the user logs in
    {
        cout << BOLD << BLUE << "=== Welcome to the Food Order Login System ===" << RESET << endl;
       
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
            system("cls");
            cout << RED <<"Invalid username or password. Please try again." << RESET << endl;
            
        }
    }
}

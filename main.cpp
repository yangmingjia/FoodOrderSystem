#include <iostream>
#include "FoodOrderSystem.h"
#include "LoginSystem.h"
#include "Color.h"

using namespace std;

int main()
{
    try {
        LoginSystem login;
        FoodOrderSystem foodOrderSystem;

        int choice;
        // login.Login();
        while (true)
        {
            displayMenu();
            cin >> choice;
            switch (choice)
            {
            case 1:
                foodOrderSystem.newFoodOrder();
                break;
            case 2:
                foodOrderSystem.viewPastOrders();
                break;
            case 3:
                foodOrderSystem.displayRestaurants();
                break;
            case 4:
                foodOrderSystem.reorder();
                break;
            case 5:
                foodOrderSystem.deleteOrder();
                break;
            case 6:
                foodOrderSystem.modifyOrder();
                break;
            case 7:
                cout << GREEN << "Exiting program." << RESET << endl;
                return 0;
            default:
                system("cls");
                cout << RED << "Invalid choice. Please try again!" << RESET << endl;
            }
        }
    }
    catch (const exception& e)
    {
        cerr << "An error occurred: " << e.what() << endl;
        return 1;
    }
    return 0;
}


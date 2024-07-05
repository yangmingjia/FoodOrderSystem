#ifndef FOODORDERSYSTEM_H
#define FOODORDERSYSTEM_H

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <ctime>
#include <stdexcept>
#include "Food.h"
#include "Restaurant.h"
#include "Order.h"
#include "LoginSystem.h"
#include "Delivery.h"
#include "Color.h"

using namespace std;

class FoodOrderSystem
{
private:
    vector<Restaurant> restaurants;
    vector<Order> orders;
    vector<pair<string, string>> riders;

    void loadRestaurants(const string&); // Load restaurants from CSV file
    void loadMenu(const string&); // Load menu from CSV file
    void loadRiders(const string&); // Load riders from CSV file

public:
    FoodOrderSystem();
    void initializeRestaurants(); // Initialize restaurants and their menus from CSV files
    void loadOrders(const string&); // Load past orders from CSV file
    void saveOrders(const string&); // Save all orders to the "orders.csv" file
    void loadMenuPreference(const string& filename); // Load menu preferences from CSV file

    void newFoodOrder(); 
    void viewPastOrders();
    void reorder();
    void deleteOrder();
    void modifyOrder();
    
    void displayRestaurants() const;
};

void displayMenu();

#endif

#ifndef FOODORDERSYSTEM_H
#define FOODORDERSYSTEM_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include "Food.h"
#include "Restaurant.h"
#include "Order.h"
#include "Color.h"
#include "LoginSystem.h"
#include "Delivery.h"

using namespace std;

class FoodOrderSystem
{
private:
    vector<Restaurant> restaurants;
    vector<Order> orders;
    vector<pair<string, string>> riders; // ��������Ա��Ϣ

    void loadRestaurants(const string&);
    void loadMenu(const string&);
    void loadRiders(const string&); // ��������Ա��Ϣ

public:
    FoodOrderSystem();
    void initializeRestaurants();
    void newFoodOrder();
    void viewPastOrders();
    void reorder();
    void deleteOrder();
    void modifyOrder();
    void loadOrders(const string&);
    void saveOrders(const string&);
    void displayRestaurants() const;
};

void displayMenu();

#endif

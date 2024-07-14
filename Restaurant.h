#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Food.h"

using namespace std;

class Restaurant 
{
private:
    string name;
    string type;
    vector<Food*> menu;

public:
    Restaurant(const string&, const string&);

    void addFoodItem(Food*);
    string getName() const;
    string getType() const;
    vector<Food*> getMenu() const;
    static const Restaurant* getRestaurantByName(const string&, const vector<Restaurant>&);
    void displayMenu() const;
    void saveMenu(const string&) const;
};

#endif

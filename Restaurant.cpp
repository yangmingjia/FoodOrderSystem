#include "Restaurant.h"

Restaurant::Restaurant(const string& name, const string& type) : name(name), type(type) {}

string Restaurant::getName() const 
{
    return name;
}

string Restaurant::getType() const
{
    return type;
}

void Restaurant::addFoodItem(Food* food)
{
    menu.push_back(food);
}

vector<Food*> Restaurant::getMenu() const
{
    return menu;
}

const Restaurant* Restaurant::getRestaurantByName(const string& name, const vector<Restaurant>& restaurants)
{
    for (auto& restaurant : restaurants)
    {
        if (restaurant.getName() == name)
        {
            return &restaurant;
        }
    }
    return nullptr;
}

void Restaurant::displayMenu() const
{
    cout << "Menu for " << name << ":" << endl;
    for (const auto& item : menu)
    {
        item->display();
    }
}

void Restaurant::saveMenu(const std::string& filename) const
{
    ofstream ofs(filename);
    if (!ofs.is_open())
    {
        throw runtime_error("Could not open file for writing: " + filename);
    }
    for (const auto& item : menu)
    {
        item->save(ofs);
    }
}

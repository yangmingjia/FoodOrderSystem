#include "Restaurant.h"

Restaurant::Restaurant(const std::string& name, const std::string& type) : name(name), type(type) {}

std::string Restaurant::getName() const {
    return name;
}

std::string Restaurant::getType() const {
    return type; // ·µ»ØÀàĞÍ
}

void Restaurant::addFoodItem(Food* food) {
    menu.push_back(food);
}

std::vector<Food*> Restaurant::getMenu() const {
    return menu;
}

const Restaurant* Restaurant::getRestaurantByName(const string& name, const vector<Restaurant>& restaurants) {
    for (auto& restaurant : restaurants) {
        if (restaurant.getName() == name) {
            return &restaurant;
        }
    }
    return nullptr;
}

void Restaurant::displayMenu() const {
    std::cout << "Menu for " << name << ":" << std::endl;
    for (const auto& item : menu) {
        item->display();
    }
}

void Restaurant::saveMenu(const std::string& filename) const {
    std::ofstream ofs(filename);
    if (!ofs.is_open()) {
        throw std::runtime_error("Could not open file for writing: " + filename);
    }
    for (const auto& item : menu) {
        item->save(ofs);
    }
}

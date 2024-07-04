#include "FoodOrderSystem.h"
#include "Color.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>

using namespace std;

FoodOrderSystem::FoodOrderSystem() {
    initializeRestaurants();
    loadRiders("riders.csv"); // 加载配送员信息
    loadOrders("orders.csv");  // 加载现有订单
}

void FoodOrderSystem::initializeRestaurants() {
    try {
        loadRestaurants("restaurants.csv");
        loadMenu("menu.csv");
    }
    catch (const exception& e) {
        cerr << RED << e.what() << RESET << endl;
    }
}

void FoodOrderSystem::loadRestaurants(const string& filename) {
    ifstream ifs(filename);
    if (!ifs.is_open()) {
        throw runtime_error("Could not open file for reading: " + filename);
    }

    string line;
    getline(ifs, line); // 跳过标题行
    while (getline(ifs, line)) {
        stringstream ss(line);
        string restaurantName, type;
        getline(ss, restaurantName, ',');
        getline(ss, type, ',');

        restaurants.push_back(Restaurant(restaurantName, type));
    }
    ifs.close(); // 确保文件关闭
}

void FoodOrderSystem::loadMenu(const string& filename) {
    ifstream ifs(filename);
    if (!ifs.is_open()) {
        throw runtime_error("Could not open file for reading: " + filename);
    }

    string line;
    getline(ifs, line); // 跳过标题行
    while (getline(ifs, line)) {
        stringstream ss(line);
        string restaurantName, foodName, priceStr, description;
        getline(ss, restaurantName, ',');
        getline(ss, foodName, ',');
        getline(ss, priceStr, ',');
        getline(ss, description, ',');

        double price = stod(priceStr);

        auto it = find_if(restaurants.begin(), restaurants.end(),
            [&restaurantName](const Restaurant& restaurant) {
                return restaurant.getName() == restaurantName;
            });

        if (it != restaurants.end()) {
            Restaurant& restaurant = *it;
            string type = restaurant.getType();
            Food* food = nullptr;

            if (type == "Sichuan") {
                food = new SichuanCuisine(foodName, price, description);
            }
            else if (type == "Cantonese") {
                food = new CantoneseCuisine(foodName, price, description);
            }
            else if (type == "Italian") {
                food = new ItalianCuisine(foodName, price, description);
            }
            else if (type == "French") {
                food = new FrenchCuisine(foodName, price, description);
            }
            else if (type == "Lebanese") {
                food = new LebaneseCuisine(foodName, price, description);
            }
            else if (type == "Moroccan") {
                food = new MoroccanCuisine(foodName, price, description);
            }
            else if (type == "TexMex") {
                food = new TexMexCuisine(foodName, price, description);
            }
            else if (type == "TraditionalMexican") {
                food = new TraditionalMexicanCuisine(foodName, price, description);
            }
            else if (type == "Sushi") {
                food = new SushiCuisine(foodName, price, description);
            }
            else if (type == "Ramen") {
                food = new RamenCuisine(foodName, price, description);
            }
            else {
                throw runtime_error("Unknown cuisine type for restaurant: " + restaurantName);
            }

            restaurant.addFoodItem(food);
        }
        else {
            throw runtime_error("Restaurant not found: " + restaurantName);
        }
    }
    ifs.close(); // 确保文件关闭
}

void FoodOrderSystem::loadOrders(const string& filename) {
    orders = Order::loadOrders(filename, restaurants); // 传递 restaurants 参数
}

void FoodOrderSystem::saveOrders(const string& filename) {
    Order::saveOrders(filename, orders);
}

void FoodOrderSystem::loadRiders(const string& filename) {
    ifstream ifs(filename);
    if (!ifs.is_open()) {
        throw runtime_error("Could not open file for reading: " + filename);
    }

    string line;
    getline(ifs, line); // 跳过标题行
    while (getline(ifs, line)) {
        stringstream ss(line);
        string name, phone;
        getline(ss, name, ',');
        getline(ss, phone, ',');

        riders.push_back(make_pair(name, phone));
    }
    ifs.close(); // 确保文件关闭
}

void FoodOrderSystem::newFoodOrder() {
    try {
        cout << BOLD << BLUE << "Select a restaurant:\n" << RESET;
        displayRestaurants();
        int choice;
        cin >> choice;
        if (choice < 1 || choice > restaurants.size()) {
            throw invalid_argument("Invalid choice. Returning to main menu.\n");
        }

        Restaurant& selectedRestaurant = restaurants[choice - 1];
        Order order;
        order.setRestaurantName(selectedRestaurant.getName()); // 存储餐厅名称
        cout << BOLD << BLUE << "Select food items (enter 0 to finish):\n" << RESET;
        vector<Food*> menu = selectedRestaurant.getMenu();
        for (size_t i = 0; i < menu.size(); ++i) {
            cout << i + 1 << ". " << menu[i]->getName() << " - " << menu[i]->getPrice() << "\n";
            vector<string> preferences = menu[i]->getPreferences();
            if (!preferences.empty()) {
                cout << BOLD << "Available preferences: " << RESET;
                for (const auto& pref : preferences) {
                    cout << pref << " ";
                }
                cout << "\n";
            }
        }

        while (true) {
            cin >> choice;
            if (choice == 0) break;
            if (choice < 1 || choice > menu.size()) {
                throw invalid_argument("Invalid choice. Try again.\n");
            }
            else {
                int quantity;
                string specialInstruction, preference;

                cout << BOLD << BLUE << "Enter quantity: " << RESET;
                cin >> quantity;
                cin.ignore(); // Ignore the newline character left in the input buffer

                cout << BOLD << BLUE << "Enter any special instructions: " << RESET;
                getline(cin, specialInstruction);

                vector<string> preferences = menu[choice - 1]->getPreferences();
                if (!preferences.empty()) {
                    cout << BOLD << BLUE << "Enter your preference: " << RESET;
                    getline(cin, preference);
                    specialInstruction += " Preference: " + preference;
                }

                order.addItem(menu[choice - 1], quantity, specialInstruction);
            }
        }

        // 添加折扣
        double discount;
        cout << BOLD << BLUE << "Enter discount percentage (0-100): " << RESET;
        cin >> discount;
        if (discount < 0 || discount > 100) {
            throw invalid_argument("Invalid discount percentage. Returning to main menu.\n");
        }
        order.applyDiscount(discount);

        vector<Delivery*> deliveryOptions;
        deliveryOptions.push_back(new DirectDelivery("Direct Delivery", 30, 5.0));
        deliveryOptions.push_back(new StandardDelivery("Standard Delivery", 45, 3.0));
        deliveryOptions.push_back(new SaverDelivery("Saver Delivery", 60, 2.0));

        cout << BOLD << BLUE << "Select a delivery option:\n" << RESET;
        for (size_t i = 0; i < deliveryOptions.size(); ++i) {
            cout << i + 1 << ". " << deliveryOptions[i]->getName() << " - " << deliveryOptions[i]->getFee() << "\n";
        }
        cin >> choice;
        if (choice < 1 || choice > deliveryOptions.size()) {
            throw invalid_argument("Invalid choice. Returning to main menu.\n");
        }

        order.setDeliveryOption(deliveryOptions[choice - 1]);

        // 显示订单摘要
        order.displayOrderSummary();

        cout << BOLD << BLUE << "Select payment method (1. Credit Card, 2. E-wallet, 3. Cash on Delivery): " << RESET;
        cin >> choice;
        if (choice == 1) {
            order.setPaymentMethod("Credit Card");
        }
        else if (choice == 2) {
            order.setPaymentMethod("E-wallet");
        }
        else if (choice == 3) {
            order.setPaymentMethod("Cash on Delivery");
        }
        else {
            throw invalid_argument("Invalid payment method selected.\n");
        }

        // 随机分配配送员
        if (riders.empty()) {
            throw runtime_error("No riders available.");
        }
        srand(time(0));
        int riderIndex = rand() % riders.size();
        string riderDetails = "Rider: " + riders[riderIndex].first + ", Phone: " + riders[riderIndex].second;
        order.setRiderDetails(riderDetails);

        // 显示订单确认
        order.displayConfirmation();

        orders.push_back(order);
        saveOrders("orders.csv");  // Save all orders to the "orders.csv" file
    }
    catch (const exception& e) {
        cerr << RED << e.what() << RESET << endl;
    }
}

void FoodOrderSystem::viewPastOrders() {
    try {
        cout << BOLD << BLUE << "Past Orders:\n" << RESET;
        for (const auto& order : orders) {
            order.displayOrderSummary();
            cout << BOLD << BLUE << "--------------------\n" << RESET;
        }
    }
    catch (const exception& e) {
        cerr << RED << e.what() << RESET << endl;
    }
}

void FoodOrderSystem::reorder() {
    try {
        cout << BOLD << BLUE << "Select an order ID to reorder: " << RESET;
        int orderId;
        cin >> orderId;

        auto it = find_if(orders.begin(), orders.end(),
            [orderId](const Order& order) {
                return order.getOrderId() == orderId;
            });

        if (it != orders.end()) {
            Order oldOrder = *it;
            Order newOrder;  // 创建一个新的订单

            // 复制商品内容和特殊指示
            for (size_t i = 0; i < oldOrder.getItems().size(); ++i) {
                newOrder.addItem(oldOrder.getItems()[i].first, oldOrder.getItems()[i].second, oldOrder.getSpecialInstructions()[i]);
            }

            // 用户选择新的配送方式
            vector<Delivery*> deliveryOptions;
            deliveryOptions.push_back(new DirectDelivery("Direct Delivery", 30, 5.0));
            deliveryOptions.push_back(new StandardDelivery("Standard Delivery", 45, 3.0));
            deliveryOptions.push_back(new SaverDelivery("Saver Delivery", 60, 2.0));

            cout << BOLD << BLUE << "Select a delivery option:\n" << RESET;
            for (size_t i = 0; i < deliveryOptions.size(); ++i) {
                cout << i + 1 << ". " << deliveryOptions[i]->getName() << " - " << deliveryOptions[i]->getFee() << "\n";
            }
            int choice;
            cin >> choice;
            if (choice < 1 || choice > deliveryOptions.size()) {
                throw invalid_argument("Invalid choice. Returning to main menu.\n");
            }

            newOrder.setDeliveryOption(deliveryOptions[choice - 1]);

            // 用户选择新的付款方式
            cout << BOLD << BLUE << "Select payment method (1. Credit Card, 2. E-wallet, 3. Cash on Delivery): " << RESET;
            cin >> choice;
            if (choice == 1) {
                newOrder.setPaymentMethod("Credit Card");
            }
            else if (choice == 2) {
                newOrder.setPaymentMethod("E-wallet");
            }
            else if (choice == 3) {
                newOrder.setPaymentMethod("Cash on Delivery");
            }
            else {
                throw invalid_argument("Invalid payment method selected.\n");
            }

            // 随机分配配送员
            if (riders.empty()) {
                throw runtime_error("No riders available.");
            }
            srand(time(0));
            int riderIndex = rand() % riders.size();
            string riderDetails = "Rider: " + riders[riderIndex].first + ", Phone: " + riders[riderIndex].second;
            newOrder.setRiderDetails(riderDetails);

            // 显示订单确认
            newOrder.displayConfirmation();

            orders.push_back(newOrder);
            saveOrders("orders.csv");  // 保存所有订单到 "orders.csv" 文件中
        }
        else {
            throw invalid_argument("Order ID not found.");
        }
    }
    catch (const exception& e) {
        cerr << RED << e.what() << RESET << endl;
    }
}

void FoodOrderSystem::deleteOrder() {
    try {
        cout << BOLD << BLUE << "Select an order ID to delete: " << RESET;
        int orderId;
        cin >> orderId;

        auto it = find_if(orders.begin(), orders.end(),
            [orderId](const Order& order) {
                return order.getOrderId() == orderId;
            });

        if (it != orders.end()) {
            orders.erase(it);
            cout << GREEN << "Order " << orderId << " deleted successfully.\n" << RESET;
            saveOrders("orders.csv");  // Save all orders to the "orders.csv" file
        }
        else {
            throw invalid_argument("Order ID not found.");
        }
    }
    catch (const exception& e) {
        cerr << RED << e.what() << RESET << endl;
    }
}

void FoodOrderSystem::modifyOrder() {
    try {
        cout << BOLD << BLUE << "Select an order ID to modify: " << RESET;
        int orderId;
        cin >> orderId;

        auto it = find_if(orders.begin(), orders.end(),
            [orderId](const Order& order) {
                return order.getOrderId() == orderId;
            });

        if (it != orders.end()) {
            Order& order = *it;
            cout << BOLD << BLUE << "Current order summary:\n" << RESET;
            order.displayOrderSummary();

            cout << BOLD << BLUE << "Modify items (enter 0 to finish):\n" << RESET;
            vector<pair<Food*, int>> items = order.getItems();
            for (size_t i = 0; i < items.size(); ++i) {
                cout << i + 1 << ". " << items[i].first->getName() << " - " << items[i].second << "\n";
            }

            int choice;
            while (true) {
                cin >> choice;
                if (choice == 0) break;
                if (choice < 1 || choice > items.size()) {
                    throw invalid_argument("Invalid choice. Try again.\n");
                }
                else {
                    int quantity;
                    string specialInstruction;

                    cout << BOLD << BLUE << "Enter new quantity: " << RESET;
                    cin >> quantity;
                    cin.ignore(); // Ignore the newline character left in the input buffer

                    cout << BOLD << BLUE << "Enter any new special instructions: " << RESET;
                    getline(cin, specialInstruction);

                    order.modifyItem(choice - 1, quantity, specialInstruction);
                }
            }

            cout << BOLD << BLUE << "Apply discount (enter percentage, or 0 for no discount): " << RESET;
            double discount;
            cin >> discount;
            if (discount > 0) {
                order.applyDiscount(discount);
            }

            // Save modified orders to file
            saveOrders("orders.csv");
        }
        else {
            throw invalid_argument("Order ID not found.");
        }
    }
    catch (const exception& e) {
        cerr << RED << e.what() << RESET << endl;
    }
}

void FoodOrderSystem::displayRestaurants() const {
    cout << BOLD << BLUE << "Restaurants:\n" << RESET;
    for (size_t i = 0; i < restaurants.size(); ++i) {
        cout << i + 1 << ". " << restaurants[i].getName() << "\n";
    }
}

void displayMenu() {
    cout << BOLD << BLUE << "Main Menu:\n" << RESET;
    cout << BOLD << "1. New Food Order" << RESET << "\n";
    cout << BOLD << "2. View Past Orders" << RESET << "\n";
    cout << BOLD << "3. Display Restaurants" << RESET << "\n";
    cout << BOLD << "4. Reorder" << RESET << "\n";
    cout << BOLD << "5. Delete Order" << RESET << "\n";
    cout << BOLD << "6. Modify Order" << RESET << "\n";
    cout << BOLD << "7. Exit" << RESET << "\n";
    cout << BOLD << BLUE << "Enter your choice: " << RESET;
}

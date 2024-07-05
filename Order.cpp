#include "Order.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

int Order::nextOrderId = 1;

Order::Order() : totalPrice(0.0), discountPercentage(0.0), deliveryOption(nullptr), orderId(nextOrderId++) {}

void Order::addItem(Food* item, int quantity, const string& instruction, const string& preference) {
    items.push_back({ item, quantity });
    specialInstructions.push_back(instruction);
    selectedPreferences.push_back(preference); // 添加偏好
    totalPrice += item->getPrice() * quantity;
}

void Order::deleteItem(int itemIndex) {
    if (itemIndex >= 0 && itemIndex < items.size()) {
        totalPrice -= items[itemIndex].first->getPrice() * items[itemIndex].second;
        items.erase(items.begin() + itemIndex);
        specialInstructions.erase(specialInstructions.begin() + itemIndex);
        selectedPreferences.erase(selectedPreferences.begin() + itemIndex); // 删除偏好
    }
    else {
        throw out_of_range("Invalid item index.");
    }
}

void Order::modifyItem(int itemIndex, int quantity, const string& instruction, const string& preference) {
    if (itemIndex >= 0 && itemIndex < items.size()) {
        totalPrice -= items[itemIndex].first->getPrice() * items[itemIndex].second;
        items[itemIndex].second = quantity;
        specialInstructions[itemIndex] = instruction;
        selectedPreferences[itemIndex] = preference; // 修改偏好
        totalPrice += items[itemIndex].first->getPrice() * quantity;
    }
    else {
        throw out_of_range("Invalid item index.");
    }
}

void Order::applyDiscount(double discountPercentage) {
    if (discountPercentage >= 0 && discountPercentage <= 100) {
        this->discountPercentage = discountPercentage;
        totalPrice -= (totalPrice * discountPercentage / 100);
    }
    else {
        throw invalid_argument("Invalid discount percentage.");
    }
}

void Order::cancelOrder() {
    items.clear();
    specialInstructions.clear();
    selectedPreferences.clear(); // 清除偏好
    totalPrice = 0.0;
    deliveryOption = nullptr;
    paymentMethod.clear();
    riderDetails.clear();
}

vector<pair<Food*, int>> Order::getItems() const {
    return items;
}

double Order::getTotalPrice() const {
    return totalPrice;
}

void Order::setDeliveryOption(Delivery* option) {
    deliveryOption = option;
}

Delivery* Order::getDeliveryOption() const {
    return deliveryOption;
}

void Order::setPaymentMethod(const string& method) {
    paymentMethod = method;
}

string Order::getPaymentMethod() const {
    return paymentMethod;
}

int Order::getOrderId() const {
    return orderId;
}

void Order::displayOrderSummary() const {
    cout << "Order Summary (Order ID: " << orderId << "):\n";
    for (size_t i = 0; i < items.size(); ++i) {
        items[i].first->display();
        cout << "Quantity: " << items[i].second << "\n";
        cout << "Special Instruction: " << (specialInstructions[i].empty() ? "None" : specialInstructions[i]) << "\n";
        cout << "Selected Preference: " << (selectedPreferences[i].empty() ? "None" : selectedPreferences[i]) << "\n";
    }
    cout << "Subtotal: $" << totalPrice << "\n";
    if (discountPercentage > 0) {
        cout << "Discount: " << discountPercentage << "%\n";
    }
    else {
        cout << "Discount: None\n";
    }
    if (deliveryOption) {
        deliveryOption->display();
        cout << "Delivery Fee: $" << deliveryOption->getFee() << "\n";
        cout << "Total Price: $" << totalPrice + deliveryOption->getFee() << "\n";
    }
    else {
        cout << "No delivery option selected.\n";
    }
    cout << "Payment Method: " << paymentMethod << "\n";
}

void Order::displayConfirmation() const {
    cout << "Order Confirmation:\n";
    cout << "Order ID: " << orderId << "\n";

    for (size_t i = 0; i < items.size(); ++i) {
        items[i].first->display();
        cout << "Quantity: " << items[i].second << "\n";
        cout << "Special Instruction: " << (specialInstructions[i].empty() ? "None" : specialInstructions[i]) << "\n";
        cout << "Selected Preference: " << (selectedPreferences[i].empty() ? "None" : selectedPreferences[i]) << "\n";
    }
    cout << "Subtotal: $" << totalPrice << "\n";
    if (discountPercentage > 0) {
        cout << "Discount: " << discountPercentage << "%\n";
    }
    else {
        cout << "Discount: None\n";
    }
    if (deliveryOption) {
        deliveryOption->display();
        cout << "Delivery Fee: $" << deliveryOption->getFee() << "\n";
        cout << "Total Price: $" << totalPrice + deliveryOption->getFee() << "\n";
    }
    else {
        cout << "No delivery option selected.\n";
    }
    cout << "Payment Method: " << paymentMethod << "\n";
}

void Order::setRiderDetails(const string& details) {
    riderDetails = details;
}

vector<string> Order::getSpecialInstructions() const {
    return specialInstructions;
}

vector<string> Order::getSelectedPreferences() const {
    return selectedPreferences;
}

void Order::saveOrder(ofstream& ofs) const {
    ofs << orderId << ","
        << paymentMethod << ","
        << totalPrice << ","
        << (deliveryOption ? deliveryOption->getName() : "None") << ","
        << restaurantName << "\n";
    for (size_t i = 0; i < items.size(); ++i) {
        ofs << items[i].first->getName() << ","
            << items[i].first->getPrice() << ","
            << items[i].first->getDescription() << ","
            << items[i].second;
        ofs << "," << (specialInstructions[i].empty() ? "" : specialInstructions[i]);
        ofs << "," << (selectedPreferences[i].empty() ? "" : selectedPreferences[i]);
        ofs << endl;
    }
    ofs << endl; // Use an empty line to separate orders
}

void Order::setRestaurantName(const string& name) {
    restaurantName = name;
}

vector<Order> Order::loadOrders(const string& filename, const vector<Restaurant>& restaurants) {
    vector<Order> orders;
    ifstream ifs(filename);
    if (!ifs.is_open()) {
        return orders;  // If file does not exist, return an empty vector
    }

    string line;
    while (getline(ifs, line)) {
        stringstream ss(line);
        string token;

        Order order;
        // 读取 orderId
        getline(ss, token, ',');
        try {
            order.orderId = stoi(token);
        }
        catch (const invalid_argument& e) {
            cerr << "Invalid orderId in line: " << line << endl;
            continue;  // 跳过此行并继续处理下一行
        }

        if (order.orderId >= nextOrderId) {
            nextOrderId = order.orderId + 1;
        }

        // 读取 paymentMethod
        getline(ss, order.paymentMethod, ',');

        // 读取 totalPrice
        getline(ss, token, ',');
        try {
            order.totalPrice = stod(token);
        }
        catch (const invalid_argument& e) {
            cerr << "Invalid totalPrice in line: " << line << endl;
            continue;  // 跳过此行并继续处理下一行
        }

        // 读取 deliveryOption
        getline(ss, token, ',');
        if (token == "Direct Delivery") {
            order.setDeliveryOption(new DirectDelivery("Direct Delivery", 30, 5.0));
        }
        else if (token == "Standard Delivery") {
            order.setDeliveryOption(new StandardDelivery("Standard Delivery", 45, 3.0));
        }
        else if (token == "Saver Delivery") {
            order.setDeliveryOption(new SaverDelivery("Saver Delivery", 60, 2.0));
        }
        else {
            order.setDeliveryOption(nullptr);
        }

        // 读取 restaurantName
        getline(ss, order.restaurantName, ',');

        // 找到对应的餐厅
        const Restaurant* restaurant = Restaurant::getRestaurantByName(order.restaurantName, restaurants);
        if (!restaurant) {
            cerr << "Restaurant not found in orders: " << order.restaurantName << endl;
            continue;  // 跳过此行并继续处理下一行
        }

        // 读取后续行（食品项）
        while (getline(ifs, line) && !line.empty() && line.find(",") != string::npos) {
            stringstream itemStream(line);
            string name, description, instruction, preference;
            double price;
            int quantity;

            // 读取名称
            getline(itemStream, name, ',');

            // 读取价格
            getline(itemStream, token, ',');
            try {
                price = stod(token);
            }
            catch (const invalid_argument& e) {
                cerr << "Invalid price in line: " << line << endl;
                continue;  // 跳过此行并继续处理下一行
            }

            // 读取描述
            getline(itemStream, description, ',');

            // 读取数量
            getline(itemStream, token, ',');
            try {
                quantity = stoi(token);
            }
            catch (const invalid_argument& e) {
                cerr << "Invalid quantity in line: " << line << endl;
                continue;  // 跳过此行并继续处理下一行
            }

            // 读取特别说明，如果存在
            if (getline(itemStream, instruction, ',')) {
                instruction = instruction;
            }
            else {
                instruction = "";
            }

            // 读取偏好，如果存在
            if (getline(itemStream, preference, ',')) {
                preference = preference;
            }
            else {
                preference = "";
            }

            // 动态确定食品类型
            Food* food = nullptr;
            string type = restaurant->getType();
            if (type == "Sichuan") {
                food = new SichuanCuisine(name, price, description);
            }
            else if (type == "Cantonese") {
                food = new CantoneseCuisine(name, price, description);
            }
            else if (type == "Italian") {
                food = new ItalianCuisine(name, price, description);
            }
            else if (type == "French") {
                food = new FrenchCuisine(name, price, description);
            }
            else if (type == "Lebanese") {
                food = new LebaneseCuisine(name, price, description);
            }
            else if (type == "Moroccan") {
                food = new MoroccanCuisine(name, price, description);
            }
            else if (type == "TexMex") {
                food = new TexMexCuisine(name, price, description);
            }
            else if (type == "TraditionalMexican") {
                food = new TraditionalMexicanCuisine(name, price, description);
            }
            else if (type == "Sushi") {
                food = new SushiCuisine(name, price, description);
            }
            else if (type == "Ramen") {
                food = new RamenCuisine(name, price, description);
            }
            else {
                cerr << "Unknown food type: " << type << endl;
                continue;  // 跳过此行并继续处理下一行
            }

            // 添加食品项到订单中
            order.addItem(food, quantity, instruction, preference);
        }
        orders.push_back(order);
    }

    return orders;
}

void Order::saveOrders(const string& filename, const vector<Order>& orders) {
    ofstream ofs(filename);
    if (!ofs.is_open()) {
        throw runtime_error("Could not open file for writing: " + filename);
    }

    for (const auto& order : orders) {
        order.saveOrder(ofs);
    }
}

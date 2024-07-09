#include "Order.h"

int Order::nextOrderId = 1;

Order::Order() : totalPrice(0.0), discountPercentage(0.0), deliveryOption(nullptr), orderId(nextOrderId++) {}

// Add item to the order
void Order::addItem(Food* item, int quantity, const string& instruction, const string& preference)
{
    items.push_back({ item, quantity });
    specialInstructions.push_back(instruction);
    selectedPreferences.push_back(preference);
    totalPrice += item->getPrice() * quantity;
}

// Delete item from the order
void Order::deleteItem(int itemIndex) 
{
    // Check if the item index is valid
    if (itemIndex >= 0 && itemIndex < items.size()) 
    {
        // Update the total price
        totalPrice -= (double)(100 - discountPercentage) / 100 * (items[itemIndex].first->getPrice() * items[itemIndex].second);
        items.erase(items.begin() + itemIndex);
        specialInstructions.erase(specialInstructions.begin() + itemIndex);
        selectedPreferences.erase(selectedPreferences.begin() + itemIndex);
    }
    else {
        throw out_of_range("Invalid item index.");
    }
}

// Modify order item
void Order::modifyItem(int itemIndex, int quantity, const string& instruction, const string& preference) 
{
    if (itemIndex >= 0 && itemIndex < items.size()) // Check if the item index is valid
    {
        totalPrice -= items[itemIndex].first->getPrice() * items[itemIndex].second;
        items[itemIndex].second = quantity;
        specialInstructions[itemIndex] = instruction;
        selectedPreferences[itemIndex] = preference;
        totalPrice += items[itemIndex].first->getPrice() * quantity;
    }
    else {
        throw out_of_range("Invalid item index.");
    }
}

void Order::applyDiscount(double discountPercentage) 
{
    // Check if the discount percentage is valid
    if (discountPercentage >= 0 && discountPercentage <= 100) 
    {
        // Apply the discount
        this->discountPercentage = discountPercentage;
        totalPrice -= (totalPrice * discountPercentage / 100);
    }
    else {
        throw invalid_argument("Invalid discount percentage.");
    }
}

void Order::setItems(const vector<pair<Food*, int>>& items) 
{
	this->items = items;
}

vector<pair<Food*, int>> Order::getItems() const 
{
    return items;
}

void Order::setTotalPrice(double price) 
{
	totalPrice = price;
}

double Order::getTotalPrice() const 
{
    return totalPrice;
}

void Order::setDeliveryOption(Delivery* option) 
{
    deliveryOption = option;
}

Delivery* Order::getDeliveryOption() const 
{
    return deliveryOption;
}

void Order::setPaymentMethod(const string& method) 
{
    paymentMethod = method;
}

string Order::getPaymentMethod() const 
{
    return paymentMethod;
}

int Order::getOrderId() const 
{
    return orderId;
}

double Order::getDiscountPercentage() const 
{
	return discountPercentage;
}

// Display order summary
void Order::displayOrderSummary(bool inOrder) const 
{
    cout << "Order ID: " << orderId << endl << endl;
    for (int i = 0; i < items.size(); i++) 
    {
        cout << "Item " << i + 1 << ":" << endl;
        items[i].first->display();
        cout << "Quantity: " << items[i].second << endl;
        cout << "Special Instruction: " << (specialInstructions[i].empty() ? "None" : specialInstructions[i]) << endl;
        cout << "Selected Preference: " << (selectedPreferences[i].empty() ? "None" : selectedPreferences[i]) << endl;
        cout << "-----------------------------------" << endl;
    }
    cout << "Subtotal: $" << totalPrice << endl;
    if (discountPercentage > 0) 
    {
        cout << "Discount: " << discountPercentage << "%" << endl;
    }
    else {
        cout << "Discount: None" << endl;
    }
    deliveryOption->display();
    cout << "Delivery Fee: $" << deliveryOption->getFee() << endl;
    cout << "Total Price: $" << totalPrice + deliveryOption->getFee() << endl;

    if(!inOrder)
    {
        // Display payment method only if not in order
        cout << "Payment Method: " << paymentMethod << endl;
    }
}

// Display order confirmation
void Order::displayConfirmation() const 
{
    cout << GREEN << "=== Order Confirmation ===" << RESET << endl;
    cout << "Order ID: " << orderId << endl << endl;

    for (int i = 0; i < items.size(); i++) 
    {
        // Display all items in the order
        cout << "Item " << i + 1 << ":" << endl;
        items[i].first->display();
        cout << "Quantity: " << items[i].second << endl;
        cout << "Special Instruction: " << (specialInstructions[i].empty() ? "None" : specialInstructions[i]) << endl;
        cout << "Selected Preference: " << (selectedPreferences[i].empty() ? "None" : selectedPreferences[i]) << endl;
        cout << "-----------------------------------" << endl;
    }
    cout << "Subtotal: $" << totalPrice << endl;
    if (discountPercentage > 0) 
    {
        cout << "Discount: " << discountPercentage << "%" << endl;
    }
    else {
        cout << "Discount: None" << endl;
    }
    deliveryOption->display();
    cout << "Delivery Fee: $" << deliveryOption->getFee() << endl;
    cout << "Total Price: $" << totalPrice + deliveryOption->getFee() << endl;
    cout << "Payment Method: " << paymentMethod << endl;
    cout<< GREEN << "==========================" << endl << endl;
}

void Order::setRiderDetails(const string& details) 
{
    riderDetails = details;
}

void Order::setCurrentUser(const string& user) 
{
	currentUser = user;
}

vector<string> Order::getSpecialInstructions() const 
{
    return specialInstructions;
}

vector<string> Order::getSelectedPreferences() const 
{
    return selectedPreferences;
}

// Write order details to the file
void Order::saveOrder(ofstream& ofs) const 
{
    ofs << currentUser << ","
        << orderId << ","
        << paymentMethod << ","
        << totalPrice << ","
        << (deliveryOption ? deliveryOption->getName() : "None") << ","
        << restaurantName << "," << discountPercentage << endl;
    for (int i = 0; i < items.size(); i++) 
    {
        ofs << items[i].first->getName() << ","
            << items[i].first->getPrice() << ","
            << items[i].first->getDescription() << ","
            << items[i].second;
        // Write special instructions and selected preferences if they exist
        ofs << "," << (specialInstructions[i].empty() ? "" : specialInstructions[i]);
        ofs << "," << (selectedPreferences[i].empty() ? "" : selectedPreferences[i]);
        ofs << endl;
    }

    ofs << endl; // Use an empty line to separate orders
}

void Order::setRestaurantName(const string& name) 
{
    restaurantName = name;
}

pair<vector<Order>, vector<Order>> Order::loadOrders(const string& filename, const vector<Restaurant>& restaurants, const string& currUser)
{
    vector<Order> orders;
    vector<Order> allOrders;
    ifstream pastOrderData(filename);
    if (!pastOrderData.is_open()) 
    {
        return make_pair(orders, allOrders);  // If file does not exist, return an empty vector pair
    }

    // If file exists, read orders from the file
    string line;
    while (getline(pastOrderData, line)) 
    {
        stringstream ss(line);
        string token;
        Order order;

        // Read currentUser
        getline(ss, order.currentUser, ',');

        // Read orderId
        getline(ss, token, ',');
        try {
            order.orderId = stoi(token); // Convert string to integer
        }
        catch (const invalid_argument& e)
        {
            cerr << RED << "Invalid orderId" << RESET << endl;
            continue;  // Skip this line and continue with the next line
        }

        if (order.orderId >= nextOrderId) 
        {
            nextOrderId = order.orderId + 1;
        }

        // Read paymentMethod
        getline(ss, order.paymentMethod, ',');

        // Read totalPrice
        getline(ss, token, ',');
        try {
            order.totalPrice = stod(token);
        }
        catch (const invalid_argument& e) 
        {
            cerr << RED << "Invalid totalPrice" << RESET << endl;
            continue;  // Skip this line and continue with the next line
        }

        // Read deliveryOption
        getline(ss, token, ',');
        if (token == "Direct Delivery") 
        {
            order.setDeliveryOption(new DirectDelivery("Direct Delivery", 30, 5.0));
        }
        else if (token == "Standard Delivery") 
        {
            order.setDeliveryOption(new StandardDelivery("Standard Delivery", 45, 3.0));
        }
        else if (token == "Saver Delivery") 
        {
            order.setDeliveryOption(new SaverDelivery("Saver Delivery", 60, 2.0));
        }
        else {
            order.setDeliveryOption(nullptr);
        }

        // Read restaurantName
        getline(ss, order.restaurantName, ',');

        // Find the target restaurant
        const Restaurant* restaurant = Restaurant::getRestaurantByName(order.restaurantName, restaurants);
        if (!restaurant) 
        {
            cerr << RED << "Restaurant not found in orders: " << order.restaurantName << RESET << endl;
            continue;  // Skip this order and continue with the next order
        }

        // Read discountPercentage
        getline(ss, token, ',');
        try {
			order.discountPercentage = stod(token);
		}
		catch (const invalid_argument& e) 
		{
			cerr << RED << "Invalid discountPercentage" << RESET << endl;
			continue;  // Skip this order and continue with the next order
		}

        // Read food items
        while (getline(pastOrderData, line) && !line.empty() && line.find(",") != string::npos) 
        {
            stringstream itemStream(line);
            string name, description, instruction, preference;
            double price;
            int quantity;

            // Read item name
            getline(itemStream, name, ',');

            // Read price
            getline(itemStream, token, ',');
            try {
                price = stod(token);
            }
            catch (const invalid_argument& e)
            {
                cerr << "Invalid price" << endl;
                continue;  // Skip this line and continue with the next line
            }

            // Read description
            getline(itemStream, description, ',');

            // Read quantity
            getline(itemStream, token, ',');
            try {
                quantity = stoi(token);
            }
            catch (const invalid_argument& e)
            {
                cerr << "Invalid quantity" << endl;
                continue;  // Skip this line and continue with the next line
            }

            // Read special instruction, if exists
            if (getline(itemStream, instruction, ',')) 
            {
                instruction = instruction;
            }
            else {
                instruction = "";
            }

            // Read preference, if exists
            if (getline(itemStream, preference, ',')) 
            {
                preference = preference;
            }
            else {
                preference = "";
            }
                        
            // Determine the type of food item
            Food* food = nullptr;
            string type = restaurant->getType();
            if (type == "Sichuan") 
            {
                food = new SichuanCuisine(name, price, description);
            }
            else if (type == "Cantonese") 
            {
                food = new CantoneseCuisine(name, price, description);
            }
            else if (type == "Italian") 
            {
                food = new ItalianCuisine(name, price, description);
            }
            else if (type == "French") 
            {
                food = new FrenchCuisine(name, price, description);
            }
            else if (type == "Lebanese") 
            {
                food = new LebaneseCuisine(name, price, description);
            }
            else if (type == "Moroccan") 
            {
                food = new MoroccanCuisine(name, price, description);
            }
            else if (type == "TexMex") 
            {
                food = new TexMexCuisine(name, price, description);
            }
            else if (type == "TraditionalMexican") 
            {
                food = new TraditionalMexicanCuisine(name, price, description);
            }
            else if (type == "Sushi") 
            {
                food = new SushiCuisine(name, price, description);
            }
            else if (type == "Ramen") 
            {
                food = new RamenCuisine(name, price, description);
            }
            else {
                cerr << "Unknown food type: " << type << endl;
                continue;  // Skip this line and continue with the next line
            }

            // Add the item to the order
            order.addItem(food, quantity, instruction, preference);
        }

        // Check if the current user is the same as the user who placed the order
        if (order.currentUser != currUser)
        {
            allOrders.push_back(order);
            continue;
        }
        allOrders.push_back(order);
        orders.push_back(order);
    }

    return make_pair(orders,allOrders);
}

void Order::saveOrders(const string& filename, const vector<Order>& orders) 
{
    ofstream ofs(filename);
    if (!ofs.is_open()) 
    {
        throw runtime_error("Could not open file for writing: " + filename);
    }

    // Write each order to the file
    for (const auto& order : orders) 
    {
        order.saveOrder(ofs);
    }
}

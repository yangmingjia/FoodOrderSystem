#include "FoodOrderSystem.h"

FoodOrderSystem::FoodOrderSystem() 
{
    initializeRestaurants();
    loadRiders("riders.csv"); // Load riders from CSV file
    loadOrders("orders.csv");  // Load past orders from CSV file
}

// Initialize restaurants and their menus from CSV files
void FoodOrderSystem::initializeRestaurants() 
{
    try {
        // Load restaurant and menu data from CSV files
        loadRestaurants("restaurants.csv");
        loadMenu("menu.csv");
        loadMenuPreference("preference.csv");
    }
    catch (const exception& e) // Catch exceptions
    {
        // Print error message in red color
        cerr << RED << e.what() << RESET << endl;
    }
}

void FoodOrderSystem::loadRestaurants(const string& filename) 
{
    ifstream restaurantsData(filename);

    // Check if file is open
    if (!restaurantsData.is_open()) 
    {
        throw runtime_error("Could not open file for reading: " + filename);
    }

    string line;
    getline(restaurantsData, line); // Skip the header line

    while (getline(restaurantsData, line)) // Read each line from the file
    {
        stringstream restaurantData(line);
        string restaurantName, type;

        // Read restaurant name and type from the line and store in the restaurants vector
        getline(restaurantData, restaurantName, ',');
        getline(restaurantData, type, ',');
        restaurants.push_back(Restaurant(restaurantName, type));
    }

    restaurantsData.close(); // Close the file
}

void FoodOrderSystem::loadMenu(const string& filename) 
{
    ifstream menuData(filename);

    // Check if file is open
    if (!menuData.is_open()) 
    {
        throw runtime_error("Could not open file for reading: " + filename);
    }

    string line;
    getline(menuData, line); // Skip the header line

    while (getline(menuData, line)) // Read each line from the file
    {
        stringstream menuData(line);
        string restaurantName, foodName, priceStr, description;

        // Read restaurant details from the line
        getline(menuData, restaurantName, ',');
        getline(menuData, foodName, ',');
        getline(menuData, priceStr, ',');
        getline(menuData, description, ',');

        double price = stod(priceStr);

        Restaurant* restaurantPtr = nullptr;

        // Find the restaurant in the restaurants vector
        for(auto& r: restaurants)
		{
			if(r.getName() == restaurantName)
			{
				restaurantPtr = &r;
				break;
			}
		}

        if (restaurantPtr) // If restaurant is found, add the food item to the menu
        {
            Restaurant& restaurant = *restaurantPtr;
            string type = restaurant.getType();
            Food* food = nullptr;

            // Create a new food item based on the cuisine type
            if (type == "Sichuan") 
            {
                food = new SichuanCuisine(foodName, price, description);
            }
            else if (type == "Cantonese") 
            {
                food = new CantoneseCuisine(foodName, price, description);
            }
            else if (type == "Italian") 
            {
                food = new ItalianCuisine(foodName, price, description);
            }
            else if (type == "French") 
            {
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
                // Throw an exception if the cuisine type is unknown
                throw runtime_error("Unknown cuisine type for restaurant: " + restaurantName);
            }

            restaurant.addFoodItem(food); // Add the food item to the restaurant's menu
        }
        else {
            throw runtime_error("Restaurant not found: " + restaurantName);
        }
    }
    menuData.close(); // Close the file
}

// Load menu preferences from CSV file
void FoodOrderSystem::loadMenuPreference(const string& filename) 
{
    ifstream menuPreferenceData(filename);
    if (!menuPreferenceData.is_open()) 
    {
        throw runtime_error("Could not open file for reading: " + filename);
    }

    string line;
    getline(menuPreferenceData, line); // Skip the header line

    while (getline(menuPreferenceData, line)) // Read each line from the file
    {
        istringstream ss(line);
        string name;
        getline(ss, name, ',');

        string pref;
        vector<string> preferences;
        while (getline(ss, pref, ',')) // Read each preference from the line
        {
            preferences.push_back(pref);
        }
        
        bool foodFound = false; // Flag to check if the food item is found
        
        // Find the food item and set the preferences
        for (Restaurant& restaurant : restaurants)
        {
            for (Food* food : restaurant.getMenu())
            {
                // If the food item is found, set the preferences and break the loop
                if (food->getName() == name)
                {
                    food->setPreferences(preferences);
                    foodFound = true;
                    break;
                }
            }
            if (foodFound) break;
        }

        if (!foodFound)
        {
            // Throw an exception if the food item is not found
            throw runtime_error("Food item \"" + name + "\" not found in the restaurant menu.");
        }
    }

    menuPreferenceData.close(); // Close the file
}
// Load past orders from CSV file
void FoodOrderSystem::loadOrders(const string& filename)
{
    orders = Order::loadOrders(filename, restaurants); // Pass the restaurants vector to loadOrders function
}

// Save all orders to the "orders.csv" file
void FoodOrderSystem::saveOrders(const string& filename)
{
    Order::saveOrders(filename, orders);
}

// Load riders from CSV file
void FoodOrderSystem::loadRiders(const string& filename) 
{
    ifstream ifs(filename);

    // Check if file is open
    if (!ifs.is_open()) 
    {
        throw runtime_error("Could not open file for reading: " + filename);
    }

    string line;
    getline(ifs, line); // Skip the header line

    while (getline(ifs, line)) // Read each line from the file
    {
        stringstream riderData(line);
        string name, phone;

        // Read rider details from the line and store in the riders vector and store in the riders vector
        getline(riderData, name, ',');
        getline(riderData, phone, ',');
        riders.push_back(make_pair(name, phone));
    }
    ifs.close(); // Close the file
}

void FoodOrderSystem::newFoodOrder()
{
    try {
        system("cls");
        cout << BOLD << BLUE << "=== New Food Order ===" << RESET << endl;
        displayRestaurants();

        cout << "Select a restaurant:";
        int choice;
        cin >> choice;
        if (choice < 1 || choice > restaurants.size())
        {
            throw invalid_argument("Invalid choice. Returning to main menu.");
        }

        Restaurant& selectedRestaurant = restaurants[choice - 1];
        Order order;
        order.setRestaurantName(selectedRestaurant.getName());
        
        vector<Food*> menu = selectedRestaurant.getMenu(); // Get the menu of the selected restaurant

        while (true)
        {
            system("cls");

            for (int i = 0; i < menu.size(); i++)
            {
                // Display the food items in the menu
                cout << i + 1 << ". " << menu[i]->getName() << " - $" << menu[i]->getPrice() << endl;

                // Store the preferences for each food item
                vector<string> preferences = menu[i]->getPreferences();
            }

            cout << "Select food items (enter 0 to finish):" << endl;
            cin >> choice;
            if (choice == 0) break;
            if (choice < 1 || choice > menu.size()) 
            {
                cout << RED << "Invalid choice. Try again." << RESET;
                continue;
            }
            else {
                int quantity;
                string specialInstruction, preference;

                cout << "Enter quantity: ";
                cin >> quantity;
                cin.ignore();

                system("cls");

                // Display the preferences for the selected food item
                vector<string> preferences = menu[choice - 1]->getPreferences();
                if (!preferences.empty()) 
                {
                    // Display the preferences for the selected food item
                    cout << "Available preferences: ";
                    for (int i = 0; i < preferences.size(); i++) 
                    {
                        cout << i + 1 << ". " << preferences[i] << " ";
                    }
                    cout << endl;

                    cout << "Enter your preference (enter 0 to skip): ";
                    int prefChoice;
                    cin >> prefChoice;
                    cin.ignore();
                    if (prefChoice > 0 && prefChoice <= preferences.size()) 
                    {
                        preference = preferences[prefChoice - 1]; // Set the preference
                    }
                    else {
                        preference = "";
                    }
                }

                system("cls");

                cout << BOLD << BLUE << "Enter any special instructions: " << RESET;

                // Get the special instructions for the food item and store in the order
                getline(cin, specialInstruction);
                order.addItem(menu[choice - 1], quantity, specialInstruction, preference);
            }
        }
        
        system("cls");

        // Apply discount to the order
        double discount;
        cout<< "Enter discount percentage (0-100): ";
        cin >> discount;
        if (discount < 0 || discount > 100) 
        {
            throw invalid_argument("Invalid discount percentage. Returning to main menu.\n");
        }
        order.applyDiscount(discount);

        // Initialize delivery options
        vector<Delivery*> deliveryOptions;
        deliveryOptions.push_back(new DirectDelivery("Direct Delivery", 30, 5.0));
        deliveryOptions.push_back(new StandardDelivery("Standard Delivery", 45, 3.0));
        deliveryOptions.push_back(new SaverDelivery("Saver Delivery", 60, 2.0));

        // Select delivery option
        cout << endl << "Select a delivery option:" << endl;
        for (int i = 0; i < deliveryOptions.size(); i++) 
        {
            cout << i + 1 << ". " << deliveryOptions[i]->getName() << " - " << deliveryOptions[i]->getFee() << endl;
        }
        cin >> choice;
        if (choice < 1 || choice > deliveryOptions.size()) 
        {
            throw invalid_argument("Invalid choice. Returning to main menu.\n");
        }

        // Set the delivery option for the order
        order.setDeliveryOption(deliveryOptions[choice - 1]);

        while (true) 
        {
            system("cls");

            order.displayOrderSummary();
            cout << "Do you want to delete any item? (enter item number to delete, 0 to proceed): ";
            cin >> choice;
            if (choice == 0) break;
            if (choice < 1 || choice > order.getItems().size()) 
            {
                cout << RED << "Invalid choice. Try again." << RESET <<endl;
                continue;
            }
            else {
                order.deleteItem(choice - 1);
            }
        }

        // Select payment method
        cout << endl <<BOLD << BLUE << "Select payment method (1. Credit Card, 2. E-wallet, 3. Cash on Delivery): " << RESET;
        cin >> choice;
        if (choice == 1) 
        {
            order.setPaymentMethod("Credit Card");
        }
        else if (choice == 2) 
        {
            order.setPaymentMethod("E-wallet");
        }
        else if (choice == 3) 
        {
            order.setPaymentMethod("Cash on Delivery");
        }
        else {
            throw invalid_argument("Invalid payment method selected.\n");
        }

        if (riders.empty()) 
        {
            throw runtime_error("No riders available.");
        }
        srand(time(0));
        int riderIndex = rand() % riders.size();
        string riderDetails = "Rider: " + riders[riderIndex].first + ", Phone: " + riders[riderIndex].second;
        order.setRiderDetails(riderDetails);

        order.displayConfirmation();

        orders.push_back(order);
        saveOrders("orders.csv");
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
            cout << BOLD << BLUE << "--------------------" << RESET;
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
                newOrder.addItem(oldOrder.getItems()[i].first, oldOrder.getItems()[i].second, oldOrder.getSpecialInstructions()[i], oldOrder.getSelectedPreferences()[i]);
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

void FoodOrderSystem::deleteOrder() 
{
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

            cout << BOLD << BLUE << "Modify or delete items (enter 0 to finish):\n" << RESET;
            vector<pair<Food*, int>> items = order.getItems();
            for (size_t i = 0; i < items.size(); ++i) {
                cout << i + 1 << ". " << items[i].first->getName() << " - $ " << items[i].second << "\n";
            }

            int choice;
            while (true) {
                cin >> choice;
                if (choice == 0) break;
                if (choice < 1 || choice > items.size()) {
                    cout << "Invalid choice. Try again.\n";
                }
                else {
                    cout << BOLD << BLUE << "Do you want to delete this item? (1. Yes, 2. No): " << RESET;
                    int deleteChoice;
                    cin >> deleteChoice;
                    if (deleteChoice == 1) {
                        order.deleteItem(choice - 1);
                    }
                    else if (deleteChoice == 2) {
                        int quantity;
                        string specialInstruction, preference;

                        cout << BOLD << BLUE << "Enter new quantity: " << RESET;
                        cin >> quantity;
                        cin.ignore();

                        vector<string> preferences = items[choice - 1].first->getPreferences();
                        if (!preferences.empty()) {
                            cout << BOLD << BLUE << "Available preferences: " << RESET;
                            for (size_t i = 0; i < preferences.size(); ++i) {
                                cout << i + 1 << ". " << preferences[i] << " ";
                            }
                            cout << endl;
                            cout << BOLD << BLUE << "Enter your new preference (enter 0 to skip): " << RESET;
                            int prefChoice;
                            cin >> prefChoice;
                            cin.ignore();
                            if (prefChoice > 0 && prefChoice <= preferences.size()) {
                                preference = preferences[prefChoice - 1];
                            }
                            else {
                                preference = "";
                            }
                        }

                        cout << BOLD << BLUE << "Enter any new special instructions (enter 0 to skip): " << RESET;
                        getline(cin, specialInstruction);
                        if(specialInstruction == "0")
						{
							specialInstruction = "";
						}

                        order.modifyItem(choice - 1, quantity, specialInstruction, preference);
                    }
                    else {
                        cout << "Invalid choice. Returning to modify menu.\n";
                    }
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
            cout << "Order ID not found.\n";
        }
    }
    catch (const exception& e) {
        cerr << RED << e.what() << RESET << endl;
    }
}

void FoodOrderSystem::displayRestaurants() const {
    cout << BOLD << GREEN << "=== Restaurants List ===" << RESET << endl;
    for (size_t i = 0; i < restaurants.size(); ++i) 
    {
        cout << i + 1 << ". " << restaurants[i].getName() << endl;
    }
    cout<< BOLD  << GREEN << "========================" << RESET << endl <<endl;
}

void displayMenu() 
{
    cout << BOLD << BLUE << "=== Food Order System Menu ===" << RESET << endl;
    cout << BOLD << "1. New Food Order" << RESET << endl;
    cout << BOLD << "2. View Past Orders" << RESET << endl;
    cout << BOLD << "3. Display Restaurants" << RESET << endl;
    cout << BOLD << "4. Reorder" << RESET << endl;
    cout << BOLD << "5. Delete Order" << RESET << endl;
    cout << BOLD << "6. Modify Order" << RESET << endl;
    cout << BOLD << "7. Exit" << RESET << endl;
    cout << BOLD << BLUE << "Enter your choice: " << RESET;
}

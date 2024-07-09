#include "FoodOrderSystem.h"

FoodOrderSystem::FoodOrderSystem()
{
    initializeRestaurants();
    loadRiders("riders.csv"); // Load riders from CSV file
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

        // If restaurant is found, add the food item to the menu
        if (restaurantPtr)
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
    pair<vector<Order>, vector<Order>> orderPair  = Order::loadOrders(filename, restaurants, currentUser); // Pass the restaurants vector to loadOrders function
    orders = orderPair.first;
    allOrders = orderPair.second;
}

// Save all orders to the "orders.csv" file
void FoodOrderSystem::saveOrders(const string& filename)
{
    Order::saveOrders(filename, allOrders);
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

void FoodOrderSystem::setLoggedInUser(const string& username) 
{
	currentUser = username;
    loadOrders("orders.csv");  // Load past orders from CSV file
}

string FoodOrderSystem::getLoggedInUser() const 
{
	return currentUser;
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
        order.setCurrentUser(currentUser);
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

            // Get the user's choice for the food item
            cout << "Select food items (enter 0 to finish):" << endl;
            cin >> choice;
            if (choice == 0)
                break;
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

                    // Get the user's preference for the food item
                    cout << "Enter your preference (enter 0 to skip): ";
                    int prefChoice;
                    cin >> prefChoice;
                    cin.ignore(); // Ignore the unwanted newline character
                    if (prefChoice > 0 && prefChoice <= preferences.size()) 
                    {
                        preference = preferences[prefChoice - 1]; // Set the preference
                    }
                    else {
                        preference = "";
                    }
                }

                // Get the special instructions for the food item
                cout << "Enter any special instructions: ";
                getline(cin, specialInstruction);
                order.addItem(menu[choice - 1], quantity, specialInstruction, preference);
            }
        }
        
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
            cout << i + 1 << ". " << deliveryOptions[i]->getName() << " - $" << deliveryOptions[i]->getFee() << endl;
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

            cout<< GREEN << "====== Order Summary ======" << RESET << endl;
            order.displayOrderSummary(true);
            cout << GREEN << "===========================" << RESET << endl;
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
        cout << "Select payment method (1. Credit Card, 2. E-wallet, 3. Cash on Delivery): ";
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

        // Randomly assign a rider
        srand(time(0));
        int riderIndex = rand() % riders.size();
        string riderDetails = "Rider: " + riders[riderIndex].first + ", Phone: " + riders[riderIndex].second;
        order.setRiderDetails(riderDetails);

        system("cls");
        order.displayConfirmation(); // Display the order confirmation

        // Add the order to the orders vector and save the orders to the file
        orders.push_back(order);
        allOrders.push_back(order);
        saveOrders("orders.csv");
    }
    catch (const exception& e) 
    {
        system("cls");
        cerr << RED << e.what() << RESET << endl;
    }
}

void FoodOrderSystem::viewPastOrders()
{
    try {
        system("cls");
        cout << BOLD << BLUE << "===== Past Orders =====" << RESET << endl;
        if(orders.empty())
		{
			throw exception("No past orders found.\n");
		}
        for (const auto& order : orders) 
        {
            cout << endl;
            order.displayOrderSummary(false);
            cout << endl;
            cout << BOLD << BLUE << "-----------------------------------" << RESET <<endl; // Separate each order with a line
        }
    }
    catch (const exception& e) 
    {
        system("cls");
        cerr << RED << e.what() << RESET << endl;
    }
}

void FoodOrderSystem::reorder() 
{
    try {
        viewPastOrders();
        cout << "Select an order ID to reorder: ";
        int orderId;
        cin >> orderId;

        Order* orderPtr = nullptr; // Pointer to the order to be reordered

        // Find the order with the given order ID
        for (auto& o : orders)
        {
            if (o.getOrderId() == orderId)
            {
                orderPtr = &o;
                break;
            }
        }

        // If the order is found, reorder the order
        if (orderPtr) 
        {
            Order oldOrder = *orderPtr;
            Order newOrder;  // Create a new order

            newOrder.setCurrentUser(currentUser);

            for (int i = 0; i < oldOrder.getItems().size(); i++) 
            {
                newOrder.addItem(oldOrder.getItems()[i].first, oldOrder.getItems()[i].second, oldOrder.getSpecialInstructions()[i], oldOrder.getSelectedPreferences()[i]);
            }

            // User selects a discount percentage
            vector<Delivery*> deliveryOptions;
            deliveryOptions.push_back(new DirectDelivery("Direct Delivery", 30, 5.0));
            deliveryOptions.push_back(new StandardDelivery("Standard Delivery", 45, 3.0));
            deliveryOptions.push_back(new SaverDelivery("Saver Delivery", 60, 2.0));

            // User selects a delivery option
            cout << endl << "Select a delivery option:" << endl;
            for (int i = 0; i < deliveryOptions.size(); i++) 
            {
                cout << i + 1 << ". " << deliveryOptions[i]->getName() << " - $" << deliveryOptions[i]->getFee() << endl;
            }
            int choice;
            cin >> choice;
            if (choice < 1 || choice > deliveryOptions.size()) 
            {
                throw invalid_argument("Invalid choice. Returning to main menu.\n");
            }

            newOrder.setDeliveryOption(deliveryOptions[choice - 1]);

            // User selects a payment method
            cout << BOLD << BLUE << "Select payment method (1. Credit Card, 2. E-wallet, 3. Cash on Delivery): " << RESET;
            cin >> choice;
            if (choice == 1) 
            {
                newOrder.setPaymentMethod("Credit Card");
            }
            else if (choice == 2)
            {
                newOrder.setPaymentMethod("E-wallet");
            }
            else if (choice == 3)
            {
                newOrder.setPaymentMethod("Cash on Delivery");
            }
            else {
                throw invalid_argument("Invalid payment method selected.\n");
            }

            // Randomly assign a rider
            if (riders.empty()) 
            {
                throw runtime_error("No riders available.");
            }
            srand(time(0));
            int riderIndex = rand() % riders.size();
            string riderDetails = "Rider: " + riders[riderIndex].first + ", Phone: " + riders[riderIndex].second;
            newOrder.setRiderDetails(riderDetails);

            // Display the order confirmation
            system("cls");
            newOrder.displayConfirmation();

            // Add the new order to the orders vector and save the orders to the file
            orders.push_back(newOrder);
            allOrders.push_back(newOrder);
            saveOrders("orders.csv");
        }
        else {
            throw invalid_argument("Order ID not found.");
        }
    }
    catch (const exception& e)
    {
        system("cls");
        cerr << RED << e.what() << RESET << endl;
    }
}

void FoodOrderSystem::deleteOrder() 
{
    try {
        system("cls");

        viewPastOrders(); // Display all past orders
        cout << BOLD << BLUE << "Select an order ID to delete: " << RESET;
        int orderId;
        cin >> orderId;

        Order* orderPtr = nullptr;

        // Find the order with the given order ID
        for (auto& o : orders)
        {
            if (o.getOrderId() == orderId)
            {
                orderPtr = &o;
                break;
            }
        }

        // If the order is found, delete the order
        if (orderPtr) 
        {
            auto orderIndex = distance(&orders[0], orderPtr); // Get the index of the order
            orders.erase(orders.begin() + orderIndex); // Erase the order from the orders vector
            cout << GREEN << "Order " << orderId << " deleted successfully." << RESET <<endl;

            // Delete the order from the allOrders vector
            for (auto& o : allOrders)
            {
                if (o.getOrderId() == orderId)
                {
                    orderPtr = &o;
                    break;
                }
            }
            orderIndex = distance(&allOrders[0], orderPtr); // Get the index of the order
            allOrders.erase(allOrders.begin() + orderIndex); // Erase the order from the allOrders vector

            saveOrders("orders.csv");  // Save all orders to file
        }
        else {
            throw invalid_argument("Order ID not found.");
        }
    }
    catch (const exception& e)
    {
        system("cls");
        cerr << RED << e.what() << RESET << endl;
    }
}

void FoodOrderSystem::modifyOrder() 
{
    try {
        viewPastOrders(); // Display all past orders
        cout << BOLD << BLUE << "Select an order ID to modify: " << RESET;
        int orderId;
        cin >> orderId;

        Order* orderPtr = nullptr;

        // Find the order with the given order ID
        for (auto& o : orders)
        {
            if (o.getOrderId() == orderId)
            {
                orderPtr = &o;
                break;
            }
        }

        // If the order is found, modify the order
        if (orderPtr)
        {
            Order& order = *orderPtr;
            vector<pair<Food*, int>> items = order.getItems(); // Get the items in the order
            int choice;

            while (true)
            {
                system("cls");
                // Display the current order summary
                cout << GREEN << "====== Current Order Summary ======" << RESET << endl;
                for (int i = 0; i < items.size(); i++)
                {
                    cout << i + 1 << ". " << items[i].first->getName() << " - $" << items[i].second << endl;
                }
                cout << GREEN << "===================================" << RESET << endl;

                cout<< "Select an item to delete or modify (enter 0 to finish): ";
                cin >> choice;
                if (choice == 0) break;
                if (choice < 1 || choice > items.size())
                {
                    cout << "Invalid choice. Try again." << endl;
                    continue;
                }
                else {
                    cout << "Do you want to delete this item? (1. Yes, 2. No): ";
                    int deleteChoice;
                    cin >> deleteChoice;
                    if (deleteChoice == 1) 
                    {
                        order.deleteItem(choice - 1);
                    }
                    else if (deleteChoice == 2) 
                    {
                        int quantity;
                        string specialInstruction, preference;

                        cout << endl;
                        cout << "Enter new quantity: " << RESET;
                        cin >> quantity;
                        cin.ignore();

                        // Display the preferences for the selected food item and get the user's preference
                        vector<string> preferences = items[choice - 1].first->getPreferences();
                        if (!preferences.empty()) 
                        {
                            cout << "Available preferences: ";
                            for (int i = 0; i < preferences.size(); i++) 
                            {
                                cout << i + 1 << ". " << preferences[i] << " ";
                            }
                            cout << endl;
                            cout << "Enter your new preference (enter 0 to skip): ";
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

                        cout << "Enter any new special instructions (enter 0 to skip): ";
                        getline(cin, specialInstruction);

                        if(specialInstruction == "0")
						{
							specialInstruction = order.getSpecialInstructions()[choice - 1];
						}

                        order.modifyItem(choice - 1, quantity, specialInstruction, preference);
                    }
                    else {
                        cout << "Invalid choice. Returning to modify menu.";
                        continue;
                    }
                }
            }


            cout << "Enter discount percentage (0-100): ";
            double discount;
            cin >> discount;
            if (discount > 0) 
            {
                // Reset the total price to the original price
                order.setTotalPrice(order.getTotalPrice() / (100 - order.getDiscountPercentage()) / 100);
                // Apply the new discount
                order.applyDiscount(discount);
            }

            //Modify allOrders vector
            for (auto& o : allOrders)
			{
				if (o.getOrderId() == orderId)
				{
					orderPtr = &o;
					break;
				}
			}
            orderPtr->setItems(order.getItems());

            // Save modified orders to file
            saveOrders("orders.csv");
        }
        else {
            throw invalid_argument("Order ID not found.");
        }
    }
    catch (const exception& e)
    {
        system("cls");
        cerr << RED << e.what() << RESET << endl;
    }
}

void FoodOrderSystem::displayRestaurants() const 
{
    system("cls");
    cout << BOLD << GREEN << "=== Restaurants List ===" << RESET << endl;
    for (int i = 0; i < restaurants.size(); i++) 
    {
        cout << i + 1 << ". " << restaurants[i].getName() << endl;
    }
    cout<< BOLD  << GREEN << "========================" << RESET << endl;
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

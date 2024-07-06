#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Food.h"
#include "Delivery.h"
#include "Restaurant.h"

using namespace std;

class Order 
{
private:
    static int nextOrderId;
    int orderId;
    vector<pair<Food*, int>> items; // pair<Food*, quantity>
    vector<string> specialInstructions;
    vector<string> selectedPreferences;
    double totalPrice;
    double discountPercentage;
    Delivery* deliveryOption;
    string paymentMethod;
    string riderDetails;
    string restaurantName;

public:
    Order();

    void addItem(Food*, int, const string&, const string&); // Add item to the order
    void deleteItem(int itemIndex); // Delete item from order
    void modifyItem(int, int, const string&, const string&); // Modify order item
    void applyDiscount(double);

    vector<pair<Food*, int>> getItems() const; 

    void setTotalPrice(double);
    double getTotalPrice() const;

    void setDeliveryOption(Delivery*);
    Delivery* getDeliveryOption() const;

    void setPaymentMethod(const string&);
    string getPaymentMethod() const;

    int getOrderId() const;

    double getDiscountPercentage() const;

    void displayOrderSummary(bool Inorder) const; // Display order summary
    void displayConfirmation() const; // Display order confirmation

    void setRiderDetails(const string&);

    vector<string> getSpecialInstructions() const;
    vector<string> getSelectedPreferences() const;

    void saveOrder(ofstream&) const;
    void setRestaurantName(const string&);

    static vector<Order> loadOrders(const string&, const vector<Restaurant>&);
    static void saveOrders(const string&, const vector<Order>&);
};

#endif

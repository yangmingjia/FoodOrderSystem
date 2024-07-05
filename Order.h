#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <vector>
#include <string>
#include "Food.h"
#include "Delivery.h"
#include "Restaurant.h"

using namespace std;

class Order {
private:
    static int nextOrderId;
    int orderId;
    vector<pair<Food*, int>> items;
    vector<string> specialInstructions;
    vector<string> selectedPreferences; // 新增：存储用户选择的偏好
    double totalPrice;
    double discountPercentage;
    Delivery* deliveryOption;
    string paymentMethod;
    string riderDetails;
    string restaurantName;

public:
    Order();

    void addItem(Food*, int, const string&, const string&); // 修改方法签名
    void deleteItem(int);
    void modifyItem(int, int, const string&, const string&); // 修改方法签名
    void applyDiscount(double);
    void cancelOrder();

    vector<pair<Food*, int>> getItems() const;
    double getTotalPrice() const;

    void setDeliveryOption(Delivery*);
    Delivery* getDeliveryOption() const;

    void setPaymentMethod(const string&);
    string getPaymentMethod() const;

    int getOrderId() const;

    void displayOrderSummary() const;
    void displayConfirmation() const;

    void setRiderDetails(const string&);

    vector<string> getSpecialInstructions() const;
    vector<string> getSelectedPreferences() const; // 新增：获取选择的偏好

    void saveOrder(ofstream&) const;
    void setRestaurantName(const string&);

    static vector<Order> loadOrders(const string&, const vector<Restaurant>&);
    static void saveOrders(const string&, const vector<Order>&);
};

#endif

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
    vector<string> selectedPreferences; // �������洢�û�ѡ���ƫ��
    double totalPrice;
    double discountPercentage;
    Delivery* deliveryOption;
    string paymentMethod;
    string riderDetails;
    string restaurantName;

public:
    Order();

    void addItem(Food*, int, const string&, const string&); // �޸ķ���ǩ��
    void deleteItem(int);
    void modifyItem(int, int, const string&, const string&); // �޸ķ���ǩ��
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
    vector<string> getSelectedPreferences() const; // ��������ȡѡ���ƫ��

    void saveOrder(ofstream&) const;
    void setRestaurantName(const string&);

    static vector<Order> loadOrders(const string&, const vector<Restaurant>&);
    static void saveOrders(const string&, const vector<Order>&);
};

#endif

#include "Delivery.h"
#include <iostream>

using namespace std;

Delivery::Delivery(const string& name, int deliveryTime, double fee)
    : name(name), deliveryTime(deliveryTime), fee(fee) {}

string Delivery::getName() const 
{
    return name;
}

int Delivery::getDeliveryTime() const 
{
    return deliveryTime;
}

double Delivery::getFee() const 
{
    return fee;
}

DirectDelivery::DirectDelivery(const string& name, int deliveryTime, double fee)
    : Delivery(name, deliveryTime, fee) {}

void DirectDelivery::display() const 
{
    cout << "Direct Delivery: " << name << ", Time: " << deliveryTime << " mins, Fee: $" << fee << endl;
}

StandardDelivery::StandardDelivery(const string& name, int deliveryTime, double fee)
    : Delivery(name, deliveryTime, fee) {}

void StandardDelivery::display() const 
{
    cout << "Standard Delivery: " << name << ", Time: " << deliveryTime << " mins, Fee: $" << fee << endl;
}

SaverDelivery::SaverDelivery(const string& name, int deliveryTime, double fee)
    : Delivery(name, deliveryTime, fee) {}

void SaverDelivery::display() const 
{
    cout << "Saver Delivery: " << name << ", Time: " << deliveryTime << " mins, Fee: $" << fee << endl;
}

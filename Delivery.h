#ifndef DELIVERY_H
#define DELIVERY_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Delivery
{
protected:
    string name;
    int deliveryTime; // 送餐时间（分钟）
    double fee; // 送餐费

public:
    Delivery(const string&, int, double);

    string getName() const;
    int getDeliveryTime() const;
    double getFee() const;

    virtual void display() const = 0;
};

class DirectDelivery : public Delivery
{
public:
    DirectDelivery(const string&, int, double);
    void display() const override;
};

class StandardDelivery : public Delivery
{
public:
    StandardDelivery(const string&, int, double);
    void display() const override;
};

class SaverDelivery : public Delivery
{
public:
    SaverDelivery(const string&, int, double);
    void display() const override;
};

#endif

#ifndef FOOD_H
#define FOOD_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Color.h"

using namespace std;

class Food 
{
protected:
    string name;
    double price;
    string description;
    vector<string> preferences;

public:
    Food(const string&, double, const string&, const vector<string>& = {});

    virtual string getName() const;
    virtual double getPrice() const;
    virtual string getDescription() const;
    virtual vector<string> getPreferences() const;

    void setPreferences(const vector<string>&);
    virtual void display() const = 0;
    virtual void save(ofstream& ofs) const = 0;
};

// Chinese food
class ChineseFood : public Food
{
public:
    ChineseFood(const string&, double, const string&, const vector<string> & = {});
    void display() const override;
    void save(ofstream&) const override;
};

class SichuanCuisine : public ChineseFood
{
public:
    SichuanCuisine(const string&, double, const string&, const vector<string> & = {});
    void display() const override;
    void save(ofstream&) const override;
};

class CantoneseCuisine : public ChineseFood
{
public:
    CantoneseCuisine(const string&, double, const string&, const vector<string> & = {});
    void display() const override;
    void save(ofstream&) const override;
};

// Western food
class WesternFood : public Food
{
public:
    WesternFood(const string&, double, const string&, const vector<string> & = {});
    void display() const override;
    void save(ofstream& ofs) const override;
};

class ItalianCuisine : public WesternFood
{
public:
    ItalianCuisine(const string&, double, const string&, const vector<string> & = {});
    void display() const override;
    void save(ofstream&) const override;
};

class FrenchCuisine : public WesternFood
{
public:
    FrenchCuisine(const string&, double, const string&, const vector<string> & = {});
    void display() const override;
    void save(ofstream&) const override;
};

// Arabic food
class ArabicFood : public Food
{
public:
    ArabicFood(const string&, double, const string&, const vector<string> & = {});
    void display() const override;
    void save(ofstream&) const override;
};

class LebaneseCuisine : public ArabicFood
{
public:
    LebaneseCuisine(const string&, double, const string&, const vector<string> & = {});
    void display() const override;
    void save(ofstream& ofs) const override;
};

class MoroccanCuisine : public ArabicFood
{
public:
    MoroccanCuisine(const string&, double, const string&, const vector<string> & = {});
    void display() const override;
    void save(ofstream&) const override;
};

// Mexican food
class MexicanFood : public Food
{
public:
    MexicanFood(const string&, double, const string&, const vector<string> & = {});
    void display() const override;
    void save(ofstream&) const override;
};

class TexMexCuisine : public MexicanFood 
{
public:
    TexMexCuisine(const string&, double, const string&, const vector<string> & = {});
    void display() const override;
    void save(ofstream&) const override;
};

class TraditionalMexicanCuisine : public MexicanFood {
public:
    TraditionalMexicanCuisine(const string&, double, const string&, const vector<string> & = {});
    void display() const override;
    void save(ofstream&) const override;
};

// Japanese food
class JapaneseFood : public Food {
public:
    JapaneseFood(const string&, double, const string&, const vector<string> & = {});
    void display() const override;
    void save(ofstream&) const override;
};

class SushiCuisine : public JapaneseFood {
public:
    SushiCuisine(const string&, double, const string&, const vector<string> & = {});
    void display() const override;
    void save(ofstream&) const override;
};

class RamenCuisine : public JapaneseFood {
public:
    RamenCuisine(const string&, double, const string&, const vector<string> & = {});
    void display() const override;
    void save(ofstream&) const override;
};

#endif

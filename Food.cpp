#include "Food.h"

Food::Food(const string& name, double price, const string& description, const vector<string>& prefs)
    : name(name), price(price), description(description), preferences(prefs) {}

string Food::getName() const 
{
    return name;
}

double Food::getPrice() const 
{
    return price;
}

string Food::getDescription() const 
{
    return description;
}

vector<string> Food::getPreferences() const
{
    return preferences;
}

void Food::setPreferences(const vector<string>& prefs)
{
    preferences = prefs;
}

// Chinese food
ChineseFood::ChineseFood(const string& name, double price, const string& description, const vector<string>& prefs)
    : Food(name, price, description, prefs) {}

void ChineseFood::display() const 
{
    cout << "Chinese Food: " << name << ", Price: " << price << ", Description: " << description << endl;
    for (const auto& pref : preferences)
    {
        cout << pref << " ";
    }
}

void ChineseFood::save(ofstream& ofs) const
{
    ofs << "Chinese Food," << name << "," << price << "," << description << endl;
}

SichuanCuisine::SichuanCuisine(const string& name, double price, const string& description, const vector<string>& prefs)
    : ChineseFood(name, price, description, prefs) {}

void SichuanCuisine::display() const
{
    cout << "Sichuan Cuisine: " << name << ", Price: " << price << ", Description: " << description << endl;
    for (const auto& pref : preferences)
    {
        cout << pref << " ";
    }
}

void SichuanCuisine::save(ofstream& ofs) const
{
    ofs << "Sichuan Cuisine," << name << "," << price << "," << description << endl;
}

CantoneseCuisine::CantoneseCuisine(const string& name, double price, const string& description, const vector<string>& prefs)
    : ChineseFood(name, price, description, prefs) {}

void CantoneseCuisine::display() const
{
    cout << "Cantonese Cuisine: " << name << ", Price: " << price << ", Description: " << description << endl;
    for (const auto& pref : preferences)
    {
        cout << pref << " ";
    }
}

void CantoneseCuisine::save(ofstream& ofs) const
{
    ofs << "Cantonese Cuisine," << name << "," << price << "," << description << endl;
}

// Western food
WesternFood::WesternFood(const string& name, double price, const string& description, const vector<string>& prefs)
    : Food(name, price, description, prefs) {}

void WesternFood::display() const
{
    cout << "Western Food: " << name << ", Price: " << price << ", Description: " << description << endl;
    for (const auto& pref : preferences) 
    {
        cout << pref << " ";
    }
}

void WesternFood::save(ofstream& ofs) const
{
    ofs << "Western Food," << name << "," << price << "," << description << endl;
}

ItalianCuisine::ItalianCuisine(const string& name, double price, const string& description, const vector<string>& prefs)
    : WesternFood(name, price, description, prefs) {}

void ItalianCuisine::display() const
{
    cout << "Italian Cuisine: " << name << ", Price: " << price << ", Description: " << description << endl;
    for (const auto& pref : preferences)
    {
        cout << pref << " ";
    }
}

void ItalianCuisine::save(ofstream& ofs) const
{
    ofs << "Italian Cuisine," << name << "," << price << "," << description << endl;
}

FrenchCuisine::FrenchCuisine(const string& name, double price, const string& description, const vector<string>& prefs)
    : WesternFood(name, price, description, prefs) {}

void FrenchCuisine::display() const
{
    cout << "French Cuisine: " << name << ", Price: " << price << ", Description: " << description << endl;
    for (const auto& pref : preferences)
    {
        cout << pref << " ";
    }
}

void FrenchCuisine::save(ofstream& ofs) const
{
    ofs << "French Cuisine," << name << "," << price << "," << description << endl;
}

// Arabic food
ArabicFood::ArabicFood(const string& name, double price, const string& description, const vector<string>& prefs)
    : Food(name, price, description, prefs) {}

void ArabicFood::display() const 
{
    cout << "Arabic Food: " << name << ", Price: " << price << ", Description: " << description << endl;
    for (const auto& pref : preferences)
    {
        cout << pref << " ";
    }
}

void ArabicFood::save(ofstream& ofs) const 
{
    ofs << "Arabic Food," << name << "," << price << "," << description << endl;
}

LebaneseCuisine::LebaneseCuisine(const string& name, double price, const string& description, const vector<string>& prefs)
    : ArabicFood(name, price, description, prefs) {}

void LebaneseCuisine::display() const 
{
    cout << "Lebanese Cuisine: " << name << ", Price: " << price << ", Description: " << description << endl;
    for (const auto& pref : preferences)
    {
        cout << pref << " ";
    }
}

void LebaneseCuisine::save(ofstream& ofs) const 
{
    ofs << "Lebanese Cuisine," << name << "," << price << "," << description << endl;
}

MoroccanCuisine::MoroccanCuisine(const string& name, double price, const string& description, const vector<string>& prefs)
    : ArabicFood(name, price, description, prefs) {}

void MoroccanCuisine::display() const 
{
    cout << "Moroccan Cuisine: " << name << ", Price: " << price << ", Description: " << description << endl;
    for (const auto& pref : preferences)
    {
        cout << pref << " ";
    }
}

void MoroccanCuisine::save(ofstream& ofs) const 
{
    ofs << "Moroccan Cuisine," << name << "," << price << "," << description << endl;
}

// Mexican food
MexicanFood::MexicanFood(const string& name, double price, const string& description, const vector<string>& prefs)
    : Food(name, price, description, prefs) {}

void MexicanFood::display() const 
{
    cout << "Mexican Food: " << name << ", Price: " << price << ", Description: " << description << endl;
    for (const auto& pref : preferences)
    {
        cout << pref << " ";
    }
}

void MexicanFood::save(ofstream& ofs) const 
{
    ofs << "Mexican Food," << name << "," << price << "," << description << endl;
}

TexMexCuisine::TexMexCuisine(const string& name, double price, const string& description, const vector<string>& prefs)
    : MexicanFood(name, price, description, prefs) {}

void TexMexCuisine::display() const 
{
    cout << "Tex-Mex Cuisine: " << name << ", Price: " << price << ", Description: " << description << endl;
    for (const auto& pref : preferences)
    {
        cout << pref << " ";
    }
}

void TexMexCuisine::save(ofstream& ofs) const 
{
    ofs << "Tex-Mex Cuisine," << name << "," << price << "," << description << endl;
}

TraditionalMexicanCuisine::TraditionalMexicanCuisine(const string& name, double price, const string& description, const vector<string>& prefs)
    : MexicanFood(name, price, description, prefs) {}

void TraditionalMexicanCuisine::display() const 
{
    cout << "Traditional Mexican Cuisine: " << name << ", Price: " << price << ", Description: " << description << endl;
    for (const auto& pref : preferences)
    {
        cout << pref << " ";
    }
}

void TraditionalMexicanCuisine::save(ofstream& ofs) const 
{
    ofs << "Traditional Mexican Cuisine," << name << "," << price << "," << description << endl;
}

// Japanese food
JapaneseFood::JapaneseFood(const string& name, double price, const string& description, const vector<string>& prefs)
    : Food(name, price, description, prefs) {}

void JapaneseFood::display() const 
{
    cout << "Japanese Food: " << name << ", Price: " << price << ", Description: " << description << endl;
    for (const auto& pref : preferences)
    {
        cout << pref << " ";
    }
}

void JapaneseFood::save(ofstream& ofs) const 
{
    ofs << "Japanese Food," << name << "," << price << "," << description << endl;
}

SushiCuisine::SushiCuisine(const string& name, double price, const string& description, const vector<string>& prefs)
    : JapaneseFood(name, price, description, prefs) {}

void SushiCuisine::display() const 
{
    cout << "Sushi Cuisine: " << name << ", Price: " << price << ", Description: " << description << endl;
    for (const auto& pref : preferences)
    {
        cout << pref << " ";
    }
}

void SushiCuisine::save(ofstream& ofs) const 
{
    ofs << "Sushi Cuisine," << name << "," << price << "," << description << endl;
}

RamenCuisine::RamenCuisine(const string& name, double price, const string& description, const vector<string>& prefs)
    : JapaneseFood(name, price, description, prefs) {}

void RamenCuisine::display() const 
{
    cout << "Ramen Cuisine: " << name << ", Price: " << price << ", Description: " << description << endl;
    for (const auto& pref : preferences)
    {
        cout << pref << " ";
    }
}

void RamenCuisine::save(ofstream& ofs) const 
{
    ofs << "Ramen Cuisine," << name << "," << price << "," << description << endl;
}
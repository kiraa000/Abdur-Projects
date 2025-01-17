#ifndef STOCK_H
#define STOCK_H
#include <string>
#include <vector>

using namespace std;

class Stock {
public:
    void setName(string name);
    string getName() const;
    void setCurrPrice(double price);
    double getCurrPrice() const;
    void setHistory(double price);
    void setRate(double r);
    void newRate();
    double getRate() const;
    vector<double> getHistory() const;
    void setType(string ty);
    string getType() const;
    string getTicker() const;
    Stock(string n, string t, double price, string ty);
private:
    string name;
    string type;
    double currPrice;
    double rate;
    vector<double> history;
    string ticker;
};

#endif

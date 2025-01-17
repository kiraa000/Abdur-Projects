#include "Stock.h"
#include <string>
#include <vector>
#include <random>
using namespace std;

void Stock::setName(string n) {
    name = n;
}

string Stock::getName() const {
    return name;
}
// Update the current price of the stock using the rate of change
void Stock::setCurrPrice(double price) {
    double rate = getRate();
    currPrice = price * (1 + rate / 100.0);
    setHistory(currPrice);
}

double Stock::getCurrPrice() const {
    return currPrice;
}
// Add the current price to the stock's historical price list
void Stock::setHistory(double price) {
    history.push_back(price);
}

vector<double> Stock::getHistory() const {
    return history;
}

void Stock::setRate(double r) {
    rate = r;
}

double Stock::getRate() const {
    return rate;
}

string Stock::getTicker() const {
    return ticker;
}
void Stock::newRate() {
    static random_device rd;  // Will generate a different seed each time the program runs
    static mt19937 gen(rd()); // Mersenne Twister random number generator

    // Uniform distribution for probability (0 to 199)
    uniform_int_distribution<> prob_dist(0, 199);
    int prob = prob_dist(gen);

    uniform_int_distribution<> rate_dist(1, 5);
    int rateChange = rate_dist(gen);

    if (prob == 0) {
        setRate(-15.0);  // Rare large drop
    } else if (prob == 199) {
        setRate(20.0);   // Rare large rise
    } else if (prob < 80) {
        setRate(-rateChange);  // Small negative change
    } else {
        setRate(rateChange);   // Small positive change
    }
}

void Stock::setType(string ty) {
    type = ty;
}

string Stock::getType() const {
    return type;
}

Stock::Stock(string n, string t, double price, string ty) {
    name = n;
    ticker = t;
    currPrice = price;
    type = ty;
    rate = 1.0;
    setHistory(price);
}

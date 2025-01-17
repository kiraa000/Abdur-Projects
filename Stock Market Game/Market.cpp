#include "Market.h"
//Market class for storing stocks and ETFs

Market::Market(string n, string t, double price, string ty, vector<Stock> stocks)
    : Stock(n, t, price, ty), stocks(stocks) {}
// calculate and return the average rate of all stocks in the market
double Market::getRate(vector<Stock>& stocks) {
    double rate = 1.0;
    for (int i = 0; i < stocks.size(); i++) {
        rate += stocks[i].getRate();
    }
    setRate(rate);
    return rate / stocks.size();
}
// Calculate and return the average price of all stocks in the market
double Market::getAveragePrice() const {
    double total = 0.0;
    for (const Stock& stock : stocks) {
        total += stock.getCurrPrice();
    }
    return total / stocks.size();
}

void Market::updateCurrPrice() {
    setCurrPrice(getAveragePrice());
}

vector<Stock>& Market::getStocks()  {
    return stocks;
}


const vector<Stock>& Market::getStocks() const {
    return stocks;
}

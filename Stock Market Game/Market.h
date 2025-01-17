#ifndef MARKET_H
#define MARKET_H

#include "Stock.h"

class Market: public Stock {
public:
    Market(string n, string t, double price, string gr, vector<Stock> stocks);
    double getRate(vector<Stock>& stocks);
    double getAveragePrice() const;
    void updateCurrPrice();
    vector<Stock>& getStocks();
    const vector<Stock>& getStocks() const;

private:
    vector<Stock> stocks;
};

#endif //MARKET_H

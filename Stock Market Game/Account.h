#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>
#include <vector>
#include "Stock.h"
#include "Market.h"

using namespace std;

class Account {
public:
    Account();
    Account(double bal);
    void buyStock(Stock& stock, int quan);
    void sellStock(Stock& stock, int quan);
    double getBalance() const;
    void setBalance(double bal);
    double getPortfolioValue() const;
    void updateBalance();
    void viewCurrentValue() const;
    void refreshPortfolioPrices(const vector<Market>& markets); 
private:
    double balance;
    double portfolioValue;  
    vector<Stock> portfolio;
    vector<int> quantity;
    vector<Stock> buyHistory;
};

#endif // ACCOUNT_H

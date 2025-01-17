//Account class for storing account information and interacting with the market

#include "Account.h"
#include <iostream>

using namespace std;

Account::Account() : balance(0.0), portfolioValue(0.0) {}

Account::Account(double bal) : balance(bal), portfolioValue(0.0) {}
// function to buy the stock
void Account::buyStock(Stock& stock, int quan) {
    if (quan <= 0) {
        cout << "Invalid quantity: " << quan << ". Please enter a positive quantity." << endl;
        return;
    }

    double stockPrice = stock.getCurrPrice();
    double totalCost = stockPrice * quan;
// check if the account has enough balance to buy the stock
    if (getBalance() >= totalCost) {
        balance -= totalCost;
        setBalance(getBalance());
// loop through portfolio to find the stock
        bool found = false;
        for (int i = 0; i < portfolio.size(); i++) {
            if (portfolio[i].getTicker() == stock.getTicker()) {
                quantity[i] += quan;
                found = true;
                buyHistory.push_back(stock);
                cout << "Bought " << quan << " shares of " << stock.getName() << " at $" << stockPrice << " each." << endl;
                break;
            }
        }
        // If stock not found, add new entry to portfolio
        if (!found) {
            portfolio.push_back(stock);
            quantity.push_back(quan);
            buyHistory.push_back(stock);
            cout << "Bought " << quan << " shares of " << stock.getName() << " at $" << stockPrice << " each." << endl;
        }
        updateBalance();
    } else { // if the account does not have enough balance to buy the stock
        cout << "Insufficient balance to buy " << quan << " shares of " << stock.getName() << "." << endl;
    }
}
// function to sell the stock
void Account::sellStock(Stock& stock, int quan) {
    bool found = false;
    int sellIndex = -1;
    // Loop to find stock in portfolio
    for (int i = 0; i < portfolio.size(); i++) {
        if (portfolio[i].getTicker() == stock.getTicker()) {
            if (quantity[i] >= quan) {
                found = true;
                sellIndex = i;
                break;
            }
        }
    }
    // If the stock was not found or there was insufficient shares
    if (!found) {
        cout << "Error: You don't own enough shares (" << quan << ") of " << stock.getTicker() << "." << endl;
        return;
    }

    double revenue = stock.getCurrPrice() * quan; // Calculate revenue
    balance += revenue; // Add revenue to balance
   
    // Update quantity or remove stock from portfolio (we got .erase() from cplusplus.com)
    if (quantity[sellIndex] == quan) {
        portfolio.erase(portfolio.begin() + sellIndex);
        quantity.erase(quantity.begin() + sellIndex);
    } else {
        quantity[sellIndex] -= quan;
    }

    cout << "Sold " << quan << " shares of " << stock.getName() << " at $" << stock.getCurrPrice() << " each." << endl;
    updateBalance();
}

double Account::getBalance() const {
    return balance;
}

void Account::setBalance(double newBalance) {
    balance = newBalance;
}
// Update portfolio value based on current stock prices
void Account::updateBalance() {
    double totalStockValue = 0.0;
    for (int i = 0; i < portfolio.size(); i++) {
        totalStockValue += portfolio[i].getCurrPrice() * quantity[i];
    }
    portfolioValue = totalStockValue;
}

double Account::getPortfolioValue() const {
    return portfolioValue;
}
// Refresh stock prices in portfolio using market data
void Account::refreshPortfolioPrices(const vector<Market>& markets) {
    for (int i = 0; i < portfolio.size(); i++) {
        for (const Market& market : markets) {
            vector<Stock> stocks = market.getStocks();
            for (const Stock& stock : stocks) {
                if (portfolio[i].getTicker() == stock.getTicker()) {
                    portfolio[i].setCurrPrice(stock.getCurrPrice());
                }
            }
        }
    }
    updateBalance();  
}
// Display current account details after the updates
void Account::viewCurrentValue() const {
    cout << "Current Account Details:" << endl;
    cout << "Portfolio Value: $" << portfolioValue << endl;
    cout << "Available Cash Balance: $" << balance << endl;
    cout << "Current Account Value: $" << portfolioValue+balance << endl;
}

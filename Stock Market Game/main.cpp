
#include <iostream>
#include "Stock.h"
#include "Account.h"
#include "Market.h"
#include <string>
#include <cctype>
#include <limits>

using namespace std;


vector<Market> setGame();
void displayStocks(const vector<Market> &markets);
void explainRules();
void nextDay(int days, vector<Market> &markets, Account& account);
void displayMenu();
bool tickerExists(const string &ticker, const vector<Market> &markets);
void buyStock(Account &account, vector<Market> &markets, const string &ticker, int quantity);
void sellStock(Account &account, vector<Market> &markets, const string &ticker, int quantity);
void runGame(); 

int main() {
    runGame();
    return 0;
}
//Initializes all the stocks and ETFs in the game
vector<Market> setGame() {
    //Tech stocks
    Stock Google("Google", "GOOG", 175, "Stock");
    Stock Apple("Apple", "AAPL", 230, "Stock");
    Stock Microsoft("Microsoft", "MSFT", 220, "Stock");
    Stock Nvidia("Nvidia", "NVDA", 140, "Stock");
    Stock Amazon("Amazon", "AMZN", 210, "Stock");
    Stock Tesla("Tesla", "TSLA", 350, "Stock");
    Stock Meta("Meta", "META", 575, "Stock");
    Stock TSMC("TSMC", "TSM", 180, "Stock");
    vector<Stock> tech = {Google, Apple, Microsoft, Nvidia, Amazon, Tesla, Meta, TSMC};
    Market Technology("Technology", "TECH", 980, "ETF", tech);

    //retail stocks
    Stock Walmart("Walmart", "WMT", 140, "Stock");
    Stock Costco("Costco", "COST", 390, "Stock");
    Stock Target("Target", "TGT", 160, "Stock");
    Stock HomeDepot("Home Depot", "HD", 300, "Stock");
    Stock Lowe("Lowe's", "LOW", 190, "Stock");
    Stock TJX("TJX Companies", "TJX", 65, "Stock");
    Stock Walgreens("Walgreens", "WBA", 50, "Stock");
    Stock Kroger("Kroger", "KR", 45, "Stock");
    vector<Stock> retail = {Walmart, Costco, Target, HomeDepot, Lowe, TJX, Walgreens, Kroger};
    Market Retail("Retail", "RTL", 95, "ETF", retail);

    //energy stocks
    Stock ExxonMobil("ExxonMobil", "XOM", 95, "Stock");
    Stock Chevron("Chevron", "CVX", 120, "Stock");
    Stock RoyalDutchShell("Royal Dutch Shell", "RDS.A", 50, "Stock");
    Stock BP("BP", "BP", 25, "Stock");
    Stock Total("Total", "TOT", 55, "Stock");
    Stock ConocoPhillips("ConocoPhillips", "COP", 60, "Stock");
    Stock EOGResources("EOG Resources", "EOG", 75, "Stock");
    Stock MarathonPetroleum("Marathon Petroleum", "MPC", 70, "Stock");
    vector<Stock> energy = {ExxonMobil, Chevron, RoyalDutchShell, BP, Total, ConocoPhillips, EOGResources, MarathonPetroleum};
    Market Energy("Energy", "ERG", 600, "ETF", energy);

    //finance stocks
    Stock JPMorgan("JPMorgan Chase", "JPM", 170, "Stock");
    Stock GoldmanSachs("Goldman Sachs", "GS", 330, "Stock");
    Stock BankOfAmerica("Bank of America", "BAC", 35, "Stock");
    Stock Citigroup("Citigroup", "CITI", 45, "Stock");
    Stock MorganStanley("Morgan Stanley", "MS", 95, "Stock");
    Stock WellsFargo("Wells Fargo", "WFC", 45, "Stock");
    Stock AmericanExpress("American Express", "AXP", 110, "Stock");
    Stock BlackRock("BlackRock", "BLK", 580, "Stock");
    vector<Stock> finance = {JPMorgan, GoldmanSachs, BankOfAmerica, Citigroup, MorganStanley, WellsFargo, AmericanExpress, BlackRock};
    Market Finance("Finance", "FIN", 870, "ETF", finance);

    vector<Market> markets = {Technology, Retail, Energy, Finance};
    return markets;
}
//Display all stocks and ETFs
void displayStocks(const vector<Market> &markets) {
    cout << "Available stocks and ETFs for purchase:" << endl;
    for (const Market &market : markets) {
        vector<Stock> stocks = market.getStocks();
        for (const Stock &stock : stocks) {
            cout << stock.getName() << " (" << stock.getTicker() << ") - $" << stock.getCurrPrice() << endl;
        }
        cout << "ETF: " << market.getName() << " (" << market.getTicker() << ") - $" << market.getCurrPrice() << endl;
    }
    cout << endl;
}
// Explain the game rules
void explainRules() {
    cout << "Welcome to the stock market simulation!" << endl;
    cout << "These are the Rules:" << endl;
    cout << "1. You start with a balance of $500,000." << endl;
    cout << "2. Your goal is to turn this balance into $1,000,000 in 100 days or less." << endl;
    cout << "3. You can buy and sell stocks and ETFs to achieve this goal." << endl;
    cout << "4. Use the menu options to buy, sell, view balance history, and progress through the days." << endl;
    cout << "5. Maximize profits!!!!!" << endl;
    cout << "Good luck!" << endl;
}
// Advance to the next day, update stock prices, etc..
void nextDay(int days, vector<Market>& markets, Account& account) {
    cout << "This is day #: " << days << endl;
    cout << "The prices are: " << endl;
    for (Market& market : markets) {
        vector<Stock>& stocks = market.getStocks();
        for (Stock& stock : stocks) {
            stock.newRate();
            stock.setCurrPrice(stock.getCurrPrice());
            cout << stock.getName() << "(" << stock.getTicker() << "): " << stock.getCurrPrice() << endl;
        }
        market.updateCurrPrice();
        cout << "ETF: " << market.getName() << " (" << market.getTicker() << "): " << market.getCurrPrice() << endl;
        cout << endl;
    }
    account.refreshPortfolioPrices(markets);  //refresh portfolio prices to reflect that day's prices changes
}


// Display main menu options
void displayMenu() {
    cout << "1. Buy Stock or ETF" << endl;
    cout << "2. Sell Stock or ETF" << endl;
    cout << "3. View Portfolio" << endl;
    cout << "4. Next Day" << endl;
    cout << "5. Exit" << endl << endl;
}
//Check if a ticker exists (for validating user input)
bool tickerExists(const string &ticker, const vector<Market> &markets) {
    for (const Market& market : markets) {
        vector<Stock> stocks = market.getStocks();
        for (const Stock& stock : stocks) {
            if (stock.getTicker() == ticker) {
                return true;
            }
        }
        if (market.getTicker() == ticker) {
            return true;
        }
    }
    return false;
}
// Handle buying stocks or ETFs
void buyStock(Account &account, vector<Market> &markets, const string &ticker, int quantity) {
    if (!tickerExists(ticker, markets)) {
        cout << "Error: Ticker symbol not found." << endl;
        return;
    }

    for (Market& market : markets) {
        vector<Stock>& stocks = market.getStocks();
        for (Stock& stock : stocks) {
            if (stock.getTicker() == ticker) {
                account.buyStock(stock, quantity);
                market.updateCurrPrice();
                return;
            }
        }
        if (market.getTicker() == ticker) {
            Stock etf(market.getName(), market.getTicker(), market.getCurrPrice(), "ETF");
            account.buyStock(etf, quantity);
            market.updateCurrPrice();
            return;
        }
    }
}
// Handle selling stocks or ETFs
void sellStock(Account &account, vector<Market> &markets, const string &ticker, int quantity) {
    if (!tickerExists(ticker, markets)) {
        cout << "Error: Ticker symbol not found. Or you do not own the stock." << endl;
        return;
    }

    for (Market& market : markets) {
        vector<Stock>& stocks = market.getStocks();
        for (Stock& stock : stocks) {
            if (stock.getTicker() == ticker) {
                account.sellStock(stock, quantity);
                market.updateCurrPrice();
                return;
            }
        }
        if (market.getTicker() == ticker) {
            Stock etf(market.getName(), market.getTicker(), market.getCurrPrice(), "ETF");
            account.sellStock(etf, quantity);
            market.updateCurrPrice();
                return;
            }
        }
    }


void runGame() {
    vector<Market> markets = setGame();
    Account account(500000.0);

    explainRules();
// Show the initial list of stocks and ETFs available in the markets
    displayStocks(markets);

    int choice = 0;
    int day = 0;
    // Game loop continues until the player chooses to exit or a win/lose condition is met
    while (choice != 5) {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                string ticker;
                int quantity;
                cout << "Enter ticker symbol: ";
                cin >> ticker;
                for (size_t i = 0; i < ticker.length(); i++) {
                    ticker[i] = toupper(ticker[i]); // Convert each character to uppercase
                }
                cout << "Enter quantity: ";
                cin >> quantity;
                // Validate user input & cin.fail() was adapted from the C++ documentation website
                if (cin.fail() || quantity <= 0) {
                    cout << "Error: Invalid quantity. Please enter a positive number." << endl;
                    cin.clear(); // this was from C++ documentation website 
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Code was not working so we had to use ChatGPT for this line
                    break;
                }
                buyStock(account, markets, ticker, quantity);
                break;
            }
            case 2: {
                string ticker;
                int quantity;
                cout << "Enter ticker symbol: ";
                cin >> ticker;
                for (size_t i = 0; i < ticker.length(); i++) {
                    ticker[i] = toupper(ticker[i]); // Convert each character to uppercase
                }
                cout << "Enter quantity: ";
                cin >> quantity;
                if (cin.fail() || quantity <= 0) {
                    cout << "Error: Invalid quantity. Please enter a positive number." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                sellStock(account, markets, ticker, quantity);
                break;
            }
            case 3: {// Option to view portfolio and account details
                account.viewCurrentValue();
                break;
            }
            case 4: {
                nextDay(day++, markets, account);
                break;
            }
            case 5:
                cout << "Exiting the program." << endl;
                break;
            default: // Handle invalid user inputs
                cout << "Invalid choice. Please try again." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
        }
         //win condition: total account value (cash + portfolio) reaches or exceeds $1,000,000
        if (account.getBalance()+account.getPortfolioValue() >= 1000000) {
            cout << "Congratulations! You've reached $1,000,000 in " << day-1 << " days." << endl;
            break;
        }
        //lose condition: player fails to reach $1,000,000 within 100 days
        if (day > 100) {
            cout << "Game over! You didn't reach $1,000,000 within 100 days." << endl;
            break;
        }
    }
}

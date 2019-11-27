
#ifndef ASS5_ACCOUNT_H
#define ASS5_ACCOUNT_H

#include <iostream>
#include <string>
#include <vector>

class Account {

public:
    Account(std::string FirstName, std::string LastName, int AccountNumber);

    ~Account();

    //get the account balance for a given account
    int getAccountBalance(int FundIndex) const;

    //get account number
    const int getAccountNumber();

    //make depost
    //make withdrawl
    //record transaction
    void transaction(std::string InputText, int FundIndex, int TransactionAmount = 0);

    //display transaction history of account
    void displayTransactionHistory() const;

    std::string FirstName;
    std::string LastName;
    int AccountNumber;

private:
    //variables
    int AccontsBalances[10];
    std::vector<std::string> TransactionHistory[10];

    //default names of acocunts
    std::string AccountNames[10] = {"Money Market", "Prime Money Market", "Long Term Bond", 
    "Short term bond", "500 index fund", "Capital Vlaue Fund", "Growth Equity Fund",
    "Growth Index Fund", "Value Fund", "Value Stock Index"};



};
#endif // ASS5_ACCOUNT_H

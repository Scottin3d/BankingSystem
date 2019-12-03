//
// Scott Shilrey 0760484 30 November 2019
// CSS3422 Assignment 5
//

#ifndef ASS5_ACCOUNT_H
#define ASS5_ACCOUNT_H

#include <iostream>
#include <string>
#include <tuple>
#include <vector>

class Account {

public:
    Account(const std::string &FirstName, 
			const std::string &LastName, 
			const int &AccountNumber);

    ~Account();


    //make depost
	void makeDeposit(const int &FundIndex, 
					 const int &DepositAmount);

    //make withdrawl
	std::pair<bool, int> makeWithdraw(const int &FundIndex, 
									  const int &WithdrawAmount);

	//transfer funds self
	std::pair<bool, int> makeTransfer(const int &FROMFundIndex, 
									  const int &TOFundIndex, 
									  const int &TransferAmount);

    //record transaction
    void recordTransaction(const std::string &InputText, 
						   const int &FundIndex);

    //display transaction history of account
    void displayTransactionHistory(bool DisplayHistory) const;

    std::string FirstName;
    std::string LastName;
    int AccountNumber;
	int TfrAccountNumber;

private:
    //variables
	int *AccontsBalances;
    std::vector<std::string> TransactionHistory[10];

    //default names of acocunts
    std::string AccountNames[10] = {"Money Market", "Prime Money Market", "Long Term Bond", 
    "Short term bond", "500 index fund", "Capital Vlaue Fund", "Growth Equity Fund",
    "Growth Index Fund", "Value Fund", "Value Stock Index"};

	//helper functions
	bool withdrawLessThanZero(const int &FundIndex, 
							  const int &WithdrawAmount) const;
};
#endif // ASS5_ACCOUNT_H

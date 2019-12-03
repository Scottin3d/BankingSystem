//
// Scott Shilrey 0760484 30 November 2019
// CSS3422 Assignment 5
//

#include "account.h"

//constructor
Account::Account(const std::string &FirstName, const std::string &LastName, const int &AccountNumber){
    this->FirstName = FirstName;
    this->LastName = LastName;
    this->AccountNumber = AccountNumber;
	this->TfrAccountNumber = 0;
	this->AccontsBalances = new int[10];

	for (int I = 0; I < 10; I++)
	{
		AccontsBalances[I] = 0;
	}
	
}

//destructor
Account::~Account() {
	delete [] AccontsBalances;
}


//depost
void Account::makeDeposit(const int &FundIndex, const int &DepositAmount) {
	AccontsBalances[FundIndex] += DepositAmount;
}

//withdraw
std::pair<bool, int> Account::makeWithdraw(const int &FundIndex, const int &WithdrawAmount) {
	//I used a pair so that I could keep track of which acocunt in linked accounts funds
	//were withdrawn from
	std::pair<bool, int> ReturnValue(false, FundIndex);
	int Balance = AccontsBalances[FundIndex];

	switch (FundIndex) {
		//case 0||1
		case 0 : {
			//hardcode values?
			if (withdrawLessThanZero(0, WithdrawAmount)) {
				if (withdrawLessThanZero(1, WithdrawAmount)) {
					//cant withdraw from either
					return ReturnValue;
				}
				//withdraw from 1
				AccontsBalances[1] -= WithdrawAmount;
				ReturnValue.first = true;
				ReturnValue.second = 1;
				return ReturnValue;
			}
			//withdraw from 0
			AccontsBalances[FundIndex] -= WithdrawAmount;
			ReturnValue.first = true;
			return ReturnValue;
		}
		case 1 : {
			if (withdrawLessThanZero(1, WithdrawAmount)) {
				if (withdrawLessThanZero(0, WithdrawAmount)) {
					//cant withdraw from either
					return ReturnValue;
				}
				//withdraw from 0
				AccontsBalances[0] -= WithdrawAmount;
				ReturnValue.first = true;
				ReturnValue.second = 0;
				return ReturnValue;
			}
			//withdraw from 1
			AccontsBalances[FundIndex] -= WithdrawAmount;
			ReturnValue.first = true;
			return ReturnValue;
		}
		//case 2||3
		case 2 : {
			if (withdrawLessThanZero(2, WithdrawAmount)) {
				if (withdrawLessThanZero(3, WithdrawAmount)) {
					//cant withdraw from either
					return ReturnValue;
				}
				//withdraw from 3
				AccontsBalances[3] -= WithdrawAmount;
				ReturnValue.second = 3;
				ReturnValue.first = true;
				return ReturnValue;
			}
			//withdraw from 2
			AccontsBalances[FundIndex] -= WithdrawAmount;
			ReturnValue.first = true;
			return ReturnValue;
		}
		case 3 : {
			if (withdrawLessThanZero(3, WithdrawAmount)) {
				if (withdrawLessThanZero(2, WithdrawAmount)) {
					//cant withdraw from either
					return ReturnValue;
				}
				//withdraw from 2
				AccontsBalances[2] -= WithdrawAmount;
				ReturnValue.first = true;
				ReturnValue.second = 2;
				return ReturnValue;
			}
			//withdraw from 3
			AccontsBalances[FundIndex] -= WithdrawAmount;
			ReturnValue.first = true;
			return ReturnValue;
		}
		//all other accounts
		default: {
			if (Balance - WithdrawAmount < 0) {
				//cant withdraw
				return ReturnValue;
			}
			//withdraw from FundIndex
			AccontsBalances[FundIndex] -= WithdrawAmount;
			ReturnValue.first = true;
			return ReturnValue;
		}
	}
}

//transfer between self
std::pair<bool, int> Account::makeTransfer(const int &FROMFundIndex, const int &TOFundIndex, const int &TransferAmount) {
	std::pair<bool, int> ReturnValue(false, FROMFundIndex);

	//try to withdraw
	ReturnValue = makeWithdraw(FROMFundIndex, TransferAmount);
	//if withdraw successful, depost into account
	if (ReturnValue.first) {
		makeDeposit(TOFundIndex, TransferAmount);
	}

	return ReturnValue;
}
//record transaction into history
void Account::recordTransaction(const std::string &InputText, const int &FundIndex){
	TransactionHistory[FundIndex].push_back(InputText);
}

//display transaction history
void Account::displayTransactionHistory(bool DisplayHistory) const{
	//account name
    std::cout << "Displaying Transaction History for " << FirstName << " " << LastName << " by fund.\n";
	//loop thru accounts, display balance and history
    for(int I = 0; I < 10; I++){
        std::cout << "\t" << AccountNames[I] << ": $" << AccontsBalances[I] << "\n";
	
		//display history only if call for
		if (DisplayHistory) {
			for (const std::string &Str : TransactionHistory[I]) {
				std::cout << "\t   " << Str << "\n";
			}
		}
    }
}

//helper functions
bool Account::withdrawLessThanZero(const int &FundIndex, const int &WithdrawAmount) const {
	int Balance = AccontsBalances[FundIndex];
	return (Balance - WithdrawAmount < 0);
}


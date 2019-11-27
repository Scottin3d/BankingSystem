#include "account.h"

//constructor
Account::Account(std::string FirstName,std::string LastName, int AccountNumber){
    this->FirstName = FirstName;
    this->LastName = LastName;
    this->AccountNumber = AccountNumber;
}

//destructor
Account::~Account() = default;

//return the balance of the fundindex
int Account::getAccountBalance(int FundIndex) const{
    return AccontsBalances[FundIndex];
}

//get account number
const int Account::getAccountNumber(){
    return AccountNumber;
}

void Account::transaction(std::string InputText, int FundIndex, int TransactionAmount){
	/*
    //deposit
    if(TransactionAmount > 0){
        Account::getAccountBalance[FundIndex] += TransactionAmount;
        TransactionHistory[FundIndex].add(InputText);
        return;
    }
    //withdrawl
    //check overdraw
    if(Account::getAccountBalance[FundIndex] + TransactionAmount < 0){
        //if 0, check 1
        if(FundIndex == 0){
            TransactionHistory[FundIndex].add("Insuffient funds, checking Prime Money Market Account.");
            transaction(InputText, 1, TransactionAmount);
        }
        //if 1, check 0
        if(FundIndex == 1){
            TransactionHistory[FundIndex].add("Insuffient funds, checking Money Market Account.");
            transaction(InputText, 0, TransactionAmount);
        }
    //withdrawl
    }else{

    }

	*/
}

//display transaction history
void Account::displayTransactionHistory() const{
	//account name
    std::cout << "isplaying Transaction History for " << FirstName << " " << LastName << "by fund.\n";
	//loop thru accounts, display balance and history
    for(int i = 0; i < 10; i++){
        std::cout << AccountNames[i] << ": " << AccontsBalances[i] << "\n";
	
        for(std::string  Str : TransactionHistory[i] ){
			std::cout << Str << "\n";
        }
    }
}

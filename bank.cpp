//
// Scott Shilrey 0760484 30 November 2019
// CSS3422 Assignment 5
//

#include "bank.h"

#include <iostream>
#include <iterator>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

//constructor
Bank::Bank() {
	std::queue<std::string> BankProcesses;
	Accounts = new AccountTree();
	Tokens = new std::vector<std::string>;
}

//destructor
Bank::~Bank() {
	Tokens->clear();
	delete Tokens;
	Accounts->clear();
	delete Accounts;
}

//queue all transactions from txt file
void Bank::queueTransactions(const std::string &FileName){
	ifstream InFile;
	InFile.open(FileName);
	if (!InFile) {
		cout << "Unable to open file\n";
		exit(1); // terminate with error
	}
	string Str;
	getline(InFile, Str);
	while (!Str.empty()) {
		BankProcesses.push(Str);
		//std::cout << "Queuing " << Str << "\n";
		getline(InFile, Str);
	}
}

//process transaction
void Bank::processTransactions(const string &FileName) {
    //string split
	tokenizeInput(FileName);\

    //variables
    //case is first token
	char TransCase = FileName.at(0);

	int AccountNumber = 0;
    int FundIndex = 0;
    int TfrTOAccountNumber = 0;
	int TfrTOFundIndex = 0;
    int TransactionAmount =0 ;

		switch (TransCase) {
			// "O" Open a client account with the appropriate funds
			//ex: O Cash Johnny 1001
		case 'O': {
			//checks
			//number of tokens
			if (Tokens->size() == 4) {
				//tokens
				int NewAccountNumber = std::stoi(Tokens->at(3));

				//create new account
				auto *NewAccount = new Account(Tokens->at(2), Tokens->at(1), NewAccountNumber);

				//try to insert new account into tree
				if (!Accounts->insert(NewAccount)) {
					std::cout << "ERROR: Account " << NewAccountNumber << " already open.\n";
					delete NewAccount;
				}

				break;
			}
			//log error
			std::cout << "Error. Invalid account info: " << FileName << "\n";
			break;
		}

		//"D" Deposit assets into a fund
		//D 10016 7576
		case 'D': {
			//tokens
			AccountNumber = std::stoi(Tokens->at(1).substr(0, 4));
			FundIndex = std::stoi(Tokens->at(1).substr(4));
			TransactionAmount = std::stoi(Tokens->back());

			//checks
			if (Tokens->at(1).size() == 5 && Tokens->size() == 3) {
				//retrieve account
				Account *TransactionAccount = Accounts->retrieve(AccountNumber);

				//try to make deposit
				if (Accounts->retrieve(AccountNumber, TransactionAccount)) {
					//these checks are useless with how the number is parsed
					if (AccountNumber > 9999 || AccountNumber < 1000) {
						break;
					}

					//make deposit into account
					TransactionAccount->makeDeposit(FundIndex, TransactionAmount);
					//record transaction
					TransactionAccount->recordTransaction(FileName, FundIndex);

					break;
				}
				std::cout << "ERROR: Could not find account " << AccountNumber << "\n";
				break;
			}
			std::cout << "ERROR: Invalid account number: " << Tokens->at(1) << "\n";

			//log error 

			break;
		}

		//"W" Withdraw assets from a fund
		//W 10017 20000
		case 'W': {
			//tokens
			AccountNumber = std::stoi(Tokens->at(1).substr(0, 4));
			FundIndex = std::stoi(Tokens->at(1).substr(4, 5));
			TransactionAmount = std::stoi(Tokens->back());

			if (Tokens->at(1).size() == 5 && Tokens->size() == 3) {

				//retrieve account to withdraw in
				Account *TransactionAccount = Accounts->retrieve(AccountNumber);

				WithdrawReturn = TransactionAccount->makeWithdraw(FundIndex, TransactionAmount);
				//try to withdraw, if not successful log error
				if (!WithdrawReturn.first) {
					//log error
					std::string Error = FileName;
					Error.erase(Error.length() - 1);
					Error += " (Failed)";
					TransactionAccount->recordTransaction(Error, WithdrawReturn.second);
					break;
				}
				//record the successful transaction
				TransactionAccount->recordTransaction(FileName, WithdrawReturn.second);

				break;
			}
			//log error
			std::cout << "ERROR: Invalid input: " << FileName << "\n";
			break;
		}
				  
		//"T" Transfer assets between funds
		//(can be funds owned by a single client or
		//transfers between clients)
		//T 10017 54 10015
		case 'T': {
			//tokens
			//FROM
			AccountNumber = std::stoi(Tokens->at(1).substr(0, 4));
			FundIndex = std::stoi(Tokens->at(1).substr(4));
			//TO
			TfrTOAccountNumber = std::stoi(Tokens->at(3).substr(0, 4));
			TfrTOFundIndex = std::stoi(Tokens->at(3).substr(4));
			//AMOUNT
			TransactionAmount = std::stoi(Tokens->at(2));

			if (Tokens->at(1).size() == 5 && Tokens->at(3).size() == 5 && Tokens->size() == 4) {

				//retrieve accounts
				Account* TfrFROMAccount = Accounts->retrieve(AccountNumber);
				Account* TfrTOAccount = Accounts->retrieve(TfrTOAccountNumber);
				//verify both accounts are same address
				if (TfrFROMAccount != nullptr && TfrTOAccount != nullptr) {
					//withdraw
					TransferReturn = TfrFROMAccount->makeWithdraw(FundIndex, TransactionAmount);
					if (!TransferReturn.first) {
						std::string Error = FileName + " (Failed)";
						Error.erase(Error.length() - 1);
						Error += " (Transfer Failed)";
						TfrFROMAccount->recordTransaction(Error, TransferReturn.second);
						break;
					}

					//deposit
					//if same account
					if (AccountNumber == TfrTOAccountNumber) {
						TfrFROMAccount->makeDeposit(TfrTOFundIndex, TransactionAmount);
						TfrFROMAccount->recordTransaction("+ " + FileName, TfrTOFundIndex);
					}
					//account to account
					else {
						TfrTOAccount->makeDeposit(TfrTOFundIndex, TransactionAmount);
						TfrTOAccount->recordTransaction("+ " + FileName, TfrTOFundIndex);
					}
					TfrTOAccount->recordTransaction("- " + FileName, FundIndex);
				}
				break;
			}
			//log error
			std::cout << "ERROR: Invalid input: " << FileName << "\n";
			break;
		}
				  
		//H: Display the history of all transactions for a client
		//account or for a single fund
		case 'H': {
			AccountNumber = std::stoi(Tokens->at(1).substr(0, 4));
			//retrieve account
			Account* TransactionAccount = Accounts->retrieve(AccountNumber);
			if (Accounts->retrieve(AccountNumber, TransactionAccount)) {
				TransactionAccount->displayTransactionHistory(true);
			}
			break;
		}
		default :
			break;
				  //Include errors in the output where appropriate.
		}
}

//display all account balances in account tree
void Bank::displayAllBankBalances() const {
	std::cout << "Processing Done. Final Balances.\n";
	Accounts->display();
}


//helper functions
//tokenizes the input string
void Bank::tokenizeInput(const std::string &FileName){
    std::istringstream Buffer(FileName);
    std::istream_iterator<std::string> Beginning(Buffer), End;

	Tokens->assign(Beginning, End);
    //Tokens = new std::vector<std::string>(Beginning, End);
    //return Tokens;
}

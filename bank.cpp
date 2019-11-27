
#include "bank.h"
//#include "accounttree.h"
//#include "account.h"

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <iterator>
#include <queue>


Bank::Bank() = default;

Bank::~Bank() = default;

void Bank::queueTransactions(std::string &FileInput){
	ifstream InFile;
	InFile.open(FileInput);
	if (!InFile) {
		cout << "Unable to open file";
		exit(1); // terminate with error
	}
	string Str;
	getline(InFile, Str);
	while (Str != "") {
		BankProcesses.push(Str);
		std::cout << "Queuing " << Str << "\n";
		getline(InFile, Str);
	}
}

void Bank::processTransactions(const string &FileName) {
    //string split
    Tokens = Bank::tokenizeInput(FileName);  

    //variables
    //case is first token
    int TransactionCase = findTransactionCase(Tokens.front());
    int AccountNumber;
    int TfrAccountNumber;
    int FundIndex;
    int TransactionAmount;

    switch (TransactionCase){
		// "O" Open a client account with the appropriate funds
		//ex: O Cash Johnny 1001
		case 0: {
			std::cout << FileName << "\n";
			std::cout << "Open account selected.\n";

			int NewAccountNumber = std::stoi(Tokens.at(3));
			Account *NewAccount = new Account(Tokens.at(1), Tokens.at(2), NewAccountNumber);
		
			if (Accounts.insert(NewAccount)) {
				//debug code
				std::cout << "Account Created.\n";
				std::cout << "Account Name: " << NewAccount->FirstName << " " << NewAccount->LastName << "\n";
				std::cout << "Account Number: " << NewAccount->AccountNumber << "\n";
			}
		/*
				//checks:
					//valid number pieces of info
			if (Tokens.size() != 4)
				//valid names
				if (Tokens.at(1) != null && Tokens.at(2) != null)
					//valid account ID, int XXXX
					if (typeid(Tokens.back()) == typeid(int()) &&
						Tokens.back() > 999 &&
						Tokens.back() < 10000)

						//create account
						Account AddAccount = new Account(Tokens.at(1),
							Tokens.at(2),
							Tokens.at(3))
						//add account to tree
							//validate if this is koshure
						if (!AccountTree.insert(*AddAccount)) {
							//log error: account already exists
							std::string Error = "Error: ";
							Error += "Cound not find Account ";
							Error += Tokens.back();
							Error += " Account not opened."
								GeneralAccountError.add(Error);
							//delete AddAccount;
						}
		*/
			break;
		}
		//"D" Deposit assets into a fund
		//D 10016 7576
		case 1: {
			std::cout << FileName << "\n";
			std::cout << "Deposit selected.\n";
			AccountNumber = std::stoi(Tokens.at(1).substr(0,4));
			FundIndex = std::stoi(Tokens.at(1).substr(4));
			TransactionAmount = std::stoi(Tokens.back());

			//debug code
			std::cout << "Account Number: " << AccountNumber << "\n";
			std::cout << "Fund Index: " << FundIndex << "\n";
			std::cout << "Deposit Amount: " << TransactionAmount << "\n";

			/*
			//checks
				//valid account
			if (typeid(Tokens.at(1)) == typeid(int()) &&
				Tokens.at(1) > 9999 &&
				Tokens.at(1) < 100000)
				//valid amout
				if (Tokens.back() >= 0)

					//deposit into account
					Account* Account = AccountTree.retrieve(AccountNumber)
					//record transaction
					Account.recordTransactionHistory(FileInput, FundIndex, )
			*/
			break;
		}
		//"W" Withdraw assets from a fund
		//W 10017 20000
		case 2 : {
			std::cout << FileName << "\n";
			std::cout << "Withdraw selected.\n";
			AccountNumber = std::stoi(Tokens.at(1).substr(4));
			FundIndex = std::stoi(Tokens.at(1).substr(4, 5));
			TransactionAmount = std::stoi(Tokens.back());

			//debug code
			std::cout << "Account Number: " << AccountNumber << "\n";
			std::cout << "Fund Index: " << FundIndex << "\n";
			std::cout << "Deposit Amount: " << TransactionAmount << "\n";
			break;
		}
		//"T" Transfer assets between funds
		//(can be funds owned by a single client or
		//transfers between clients)
		case 3 : {
			std::cout << FileName << "\n";
			std::cout << "Transfer selected.\n";
			AccountNumber = std::stoi(Tokens.at(1).substr(4));
			FundIndex = std::stoi(Tokens.at(1).substr(4, 5));
			TransactionAmount = std::stoi(Tokens.back());

			//debug code
			std::cout << "Account Number: " << AccountNumber << "\n";
			std::cout << "Fund Index: " << FundIndex << "\n";
			std::cout << "Deposit Amount: " << TransactionAmount << "\n";
			break;
		}
		//H: Display the history of all transactions for a client
		//account or for a single fund
		case 4: {
			std::cout << FileName << "\n";
			std::cout << "Displaying all cases.\n";
			//call AccountTree.display()
			break;
		}
		//Include errors in the output where appropriate.
    }
}

void Bank::displayAllBankBalances() const {}


//helper functions

//tokenizes the input string
std::vector<std::string> Bank::tokenizeInput(std::string Input){
    std::istringstream buf(Input);
    std::istream_iterator<std::string> beg(buf), end;

    std::vector<std::string> Tokens(beg, end);
    return Tokens;
}

//finds case for transaction processing
int Bank::findTransactionCase(std::string InputCase) {
	for (int I = 0; I < 5 - 1; I++) {
		if (TransactionCases[I] == InputCase) {
			return I;
		}
	}
}

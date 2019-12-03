//
// Scott Shilrey 0760484 30 November 2019
// CSS3422 Assignment 5
//

#include "bank.h"

#include <fstream>
#include <iostream>
#include <string>

int main() {

	std::string FileName = "BankTransIn.txt";
	//inFile.open("BankTransIn.txt");
    Bank Bank;
    //Note that tests were d
	//one in BankTransIn.txt
	Bank.queueTransactions(FileName);

	std::cout << Bank.BankProcesses.size() << " transactions queued from " << FileName << "\n";

	//process transactions in the queue
	while (!Bank.BankProcesses.empty()) {

		Bank.processTransactions(Bank.BankProcesses.front());
		Bank.BankProcesses.pop();
	}

	//display all accoint balances
	Bank.displayAllBankBalances();

	//vs window open
	//std::cin.get();
    return 0;
}
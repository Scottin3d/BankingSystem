
#include "bank.h"
#include <iostream>
#include <string>
#include <fstream>


//using namespace std;

int main(int Argc, char *Argv[]) {

	std::string FileName = "BankTransIn.txt";
	//inFile.open("BankTransIn.txt");
    Bank Bank;
    //Note that tests were d
	//one in BankTransIn.txt
	Bank.queueTransactions(FileName);
	while (!Bank.BankProcesses.empty()) {
		//std::cout << Bank.BankProcesses.front() << "\n";
		Bank.processTransactions(Bank.BankProcesses.front());
		Bank.BankProcesses.pop();
		std::cout << "\n";
	}
	std::cin.get();
    return 0;
}
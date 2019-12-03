//
// Scott Shilrey 0760484 30 November 2019
// CSS3422 Assignment 5
//

#ifndef ASS5_BANK_H
#define ASS5_BANK_H

#include "account.h"
#include "accounttree.h"

#include <fstream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

class Bank {
public:

  Bank();
  ~Bank();
  void queueTransactions(const std::string &FileName);
  //processes transactions
  void processTransactions(const std::string &FileName);
  //displays transactions
  void displayAllBankBalances() const;
  //tokenizes the input string
  void tokenizeInput(const std::string &FileName);

  //variables
  std::queue<std::string> BankProcesses;
  //BST account storage
  AccountTree *Accounts;

private:
//variables
  std::vector<std::string> *Tokens;
  std::pair<bool, int> WithdrawReturn;
  std::pair<bool, int> TransferReturn; 
};
#endif // ASS5_BANK_H

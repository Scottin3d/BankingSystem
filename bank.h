
#ifndef ASS5_BANK_H
#define ASS5_BANK_H

#include "accounttree.h"
#include "account.h"

#include <fstream>
#include <string>
#include <queue>
#include <vector>

using namespace std;

class Bank {
public:

  Bank();
  ~Bank();
  void queueTransactions(std::string &FileName);
  //processes transactions
  void processTransactions(const std::string &FileName);
  //displays transactions
  void displayAllBankBalances() const;
  //tokenizes the input string
  std::vector<std::string> tokenizeInput(std::string Input);

  //variables
  std::queue<std::string> BankProcesses;
  AccountTree Accounts;

private:
//variables
  std::vector<std::string> Tokens;
  std::vector<std::string> GeneralAccountErrors;
  std::string TransactionCases[5] = { "O","D","W","T","H" };

  int findTransactionCase(std::string InputCase);
};
#endif // ASS5_BANK_H

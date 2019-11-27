#include "accounttree.h"

AccountTree::AccountTree() {
	//Q:does root move?  if so then onsided tree?
	//Root = new Node(nullptr);
}

// Delete all nodes in BST
AccountTree::~AccountTree() = default;

// Insert new account
bool AccountTree::insert(Account* Account) { 
	if (Root == nullptr) {
		std::cout << "Tree empty, placing at root.\n";
		Root = new Node(Account);
		return true;
	}
	return insert(Root, Account);
}

bool AccountTree::insert(AccountTree::Node *CurrentNode, Account* Account) {
	
	//if empty
	if (CurrentNode == nullptr) {
		//set leaves
		CurrentNode = new Node(Account);
		return true;
	}
	//if less than
	if (CurrentNode->Account->AccountNumber > Account->AccountNumber) {
		if (CurrentNode->Left == nullptr) {
			//set leaves
			CurrentNode->Left = new Node(Account);
			return true;
		}
		std::cout << "Less than " << CurrentNode->Account->AccountNumber << "Going left.\n";
		return insert(CurrentNode->Left, Account);
	}
	//if greater than
	if (CurrentNode->Account->AccountNumber < Account->AccountNumber) {
		if (CurrentNode->Right == nullptr) {
			//set leaves
			CurrentNode->Right = new Node(Account);
			return true;
		}
		std::cout << "Greater than " << CurrentNode->Account->AccountNumber << ". Going right.\n";
		return insert(CurrentNode->Right, Account);
	}
	std::cout << "Account already exists.\n";
	//log in general errors
	return false;
}

// Retrieve account
// returns true if successful AND *Account points to account
bool AccountTree::retrieve(const int &AccountNumber, Account *&Account) const {
  return true;
}

// Display information on all accounts
void AccountTree::display() const {
	//display(*Root);
}

/*
void AccountTree::display(Account* Account) const{
    //if node is null, return
    if(!Account){
      return;
    }

    //if node is leaf node, print data
    if(!Account->Left && !Account->Right){
      std::cout << Account.displayTransactionHistory();
      return;
    }

    //if left child exists, check for leaf recursively
    if(Account->Left){
      display(Account->Left);
    }

    //if right child exists, check for leaf recursively
    if(Account->Right){
      display(Account->Right);
    }
}
*/

// delete all information in AccountTree
void AccountTree::clear() {
  
}


// check if tree is empty
bool AccountTree::isEmpty() const {
  return true;
}
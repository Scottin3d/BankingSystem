//
// Scott Shilrey 0760484 30 November 2019
// CSS3422 Assignment 5
//

#include "accounttree.h"

AccountTree::AccountTree() = default;

// Delete all nodes in BST
AccountTree::~AccountTree() {
	clear();
	delete Root;
}

// Insert new account
bool AccountTree::insert(Account *Account) { 
	if (Root == nullptr) {
		Root = new Node(Account);
		return true;
	}

	return insert(Root, Account);
}

//insert account into tree
bool AccountTree::insert(AccountTree::Node *CurrentNode, Account *Account) {	
	//if empty

	if (CurrentNode == nullptr) {

		//set leaves
		CurrentNode = new Node(Account);
		return true;
	}

	//if less than
	if (CurrentNode->NodeAccount->AccountNumber > Account->AccountNumber) {
		if (CurrentNode->Left == nullptr) {
			//set leaves
			CurrentNode->Left = new Node(Account);
			return true;
		}

		return insert(CurrentNode->Left, Account);
	}
	//if greater than
	if (CurrentNode->NodeAccount->AccountNumber < Account->AccountNumber) {
		if (CurrentNode->Right == nullptr) {
			//set leaves
			CurrentNode->Right = new Node(Account);
			return true;
		}

		return insert(CurrentNode->Right, Account);
	}
	return false;
}

// Retrieve account
// returns true if successful AND *Account points to account
bool AccountTree::retrieve(const int &AccountNumber, Account *&CheckAccount) const {
	if (CheckAccount == nullptr) {
		return false;
	}
	Account* Retrieved = retrieve(Root, AccountNumber);
	return (Retrieved == CheckAccount);
}

//retrieve helper -init recursive retrieve with account number
Account* AccountTree::retrieve(const int &AccountNumber) const {
	return retrieve(Root, AccountNumber);
}

//retrieve helper -recursive retrieve with account number
Account* AccountTree::retrieve(AccountTree::Node *CurrentNode, const int &AccountNumber) const {
	if (CurrentNode == nullptr) {
		return nullptr;
	}
	int CheckAccountNumber = CurrentNode->NodeAccount->AccountNumber;
	//check currentnode
	if (CheckAccountNumber == AccountNumber) {
		return CurrentNode->NodeAccount;
	}

	//if less, go left
	if (CheckAccountNumber > AccountNumber) {
		return retrieve(CurrentNode->Left, AccountNumber);
	}
	//if greater, go right
	if (CheckAccountNumber < AccountNumber) {
		return retrieve(CurrentNode->Right, AccountNumber);
	}

	return nullptr;
}

// Display information on all accounts
void AccountTree::display() const {
	display(Root);
}

//display helper
void AccountTree::display(AccountTree::Node *CurrentNode) const{
    //if node is leaf node, print data
	
	CurrentNode->NodeAccount->displayTransactionHistory(false);

    //if left child exists, check for leaf recursively
    if(CurrentNode->Left != nullptr){
		display(CurrentNode->Left);
    }

    //if right child exists, check for leaf recursively
    if(CurrentNode->Right != nullptr){
      display(CurrentNode->Right);
    }
}


// delete all information in AccountTree
void AccountTree::clear() {
	if (Root != nullptr) {
		clear(Root);
	}
}

//clear helper
void AccountTree::clear(AccountTree::Node *CurrentNode) {
	if (
		CurrentNode == nullptr) {
		return;
	}
	clear(CurrentNode->Left);
	clear(CurrentNode->Right);
}

// check if tree is empty
bool AccountTree::isEmpty() const {
	return(Root == nullptr);
}
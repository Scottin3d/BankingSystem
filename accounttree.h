//
// Scott Shilrey 0760484 30 November 2019
// CSS3422 Assignment 5
//

#ifndef ASS5_ACCOUNTTREE_H
#define ASS5_ACCOUNTTREE_H

#include "account.h"

#include <iostream>

class AccountTree {
private:
	class Node {
	public:
		Node() = delete;
		explicit Node(Account *AddAccount)  {
			NodeAccount = AddAccount;
			Right = nullptr;
			Left = nullptr;
		}
		Account *NodeAccount = nullptr;
		Node *Right = nullptr;
		Node *Left = nullptr;
	};

	Node *Root = nullptr;

public:
  // Create BST
  AccountTree();

  // Delete all nodes in BST
  ~AccountTree();

  // Insert new account
  bool insert(Account *Account);

  //insert helper
  bool insert(Node *CurrentNode, Account* Account);

  // Retrieve account
  // returns true if successful AND *Account points to account
  bool retrieve(const int &AccountNumber, 
				Account *&Account) const;

  //retrieve helper
  Account* retrieve(Node *CurrentNode, 
					const int &AccountNumber) const;

  //retrieve helper
  Account* retrieve(const int &AccountNumber) const;

  // Display information on all accounts
  void display() const;

  //display helper
  void display(Node *CurrentNode) const;

  // delete all information in AccountTree
  void clear();

  //clear helper
  void clear(Node *CurrentNode);

  // check if tree is empty
  bool isEmpty() const;

};
#endif // ASS5_ACCOUNTTREE_H

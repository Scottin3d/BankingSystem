READ.ME
Author: Scott Shirley 0760484
Designers: Erica Ferguson, Jace Yoon, Joseph Cho
CSS342 Assignment 5 - Banking System and Data Structure

## Assumptions
-input is in correct format
	(can handle bad inputs)
	
## Compile and Run
```
date
echo "compile"
scl enable llvm-toolset-7.0 bash
clang++ -std=c++14 -Wall -Wextra -Wno-sign-compare *.cpp -g -o program
clang-tidy *.cpp -- -std=c++14
./program > BankTransOut.txt
rm program 
```
	
## Overview
A bank driver will queue "transactions" from a txt file, then process the 
the transactions in the order they were queued.  The data structure for this
assignment is the Accout.  Accounts are stored in a basic binary search tree.

##Bank 
The processing of the transactions was handled with a switch statment that used 
the cue char at the beginning of the read line.  We decided to store each line in 
the queue as a single string.  It wasn't until we processed the transaction that
the string was broken down into token based on white space.  This was done after the 
switch case was determined because the number of tokens would depend on the case.
This made inout checking easy, because we know how many tokens each case should expect.
If there were not enough tokens, it would fail and move on.

Retrieving the accounts was probably the hardest part for me to figure out due to the
given code.  I ultimately ended up writing two helper functions and using the given
function as a check to make sure that the account retrieved match the same memory
address.  This probably is not the most efficient route, but it works.  If I go back
and optimize this assignment later, this will be on the priority list.

## Account
Some interesting approaches: Because of the way we were allowed to 
make withdraws from accounts (certain accounts balances were linked) I thought
it was important to know which account funds were actually withdrawn from.

In order to track whether or not the action was successful AND which acount,
I made the return type a pair<bool, int>.  This way, using pair.first to check
if the action was successful, then pair.second for the fund index to record the
transaction in the transaction history.

I used the same data type for transfers, and handled transfers as a withdraw ? deposit.

## AccountTree
A basic binary search tree (not balanced) used to store accounts.  The first account 
created is the root, and all other accounts are places accordingly (Left < && Right >).
Several helper functions were written to make them recursive (insert(), retrieve(), 
display(), clear()).  Empty() returns is Root == nullptr.
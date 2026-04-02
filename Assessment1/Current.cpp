#include "Current.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

Current::Current() // default constructor - if no initial deposit is provided that is greater than 0
{
	balance = 0.00f; //sets the current accounts' balance to 0
	Transaction newAmount = Transaction("initial deposit", balance, currentDateAndTime(), false); 
	history.push_back(newAmount); // writes new transaction to the accounts history
	cout << "Current account created!" << endl;
}

Current::Current(float openingBalance) // constructor override 
{
	balance = openingBalance;
	Transaction newAmount = Transaction("initial deposit", balance, currentDateAndTime(), false);
	history.push_back(newAmount); // writes new transaction to the accounts history
	cout << "Current account created!" << endl;
}

Current::~Current() {}

void Current::deposit(float Amount) { // method to add money to the account - similar design to the withdraw member
	Transaction newAmount = Transaction("deposit", Amount, currentDateAndTime(), false); // "false" implies the transaction will be created and be a positive representation of the amount - i.e. £100 and not -£100
	history.push_back(newAmount); // add the new transaction to the current accounts' history
	balance += Amount; // update the current accounts' private member balance - inherited by Account
}

void Current::toString() { // outputs the string representation of the object
	if (getBalance() < 0) { cout << getTypeOfAccount() << " | Balance: -" << char(156) << (getBalance() * -1) << endl; } // outputs if balance is negative
	else { cout << getTypeOfAccount() << " | Balance: " << char(156) << getBalance() << endl; } // else outputs balance as positive
	for (Transaction t : getHistory()) { t.toString(); } // outputs every transaction in history vector<transaction>
}

void Current::withdraw(float Amount) { // method called to take money out of the accout
	Transaction newAmount = Transaction("withdraw", Amount, currentDateAndTime(), true); // creates a new transaction, with the "true" boolean representing it will be a negative transaction - since money out of an account will be e.g. -£100
	history.push_back(newAmount); // add the new transaction to the current accounts' history
	balance -= Amount; // update the current accounts' private member balance - inherited by Account
}
float Current::getBalance() { return balance; } // accessor method - returns float balance, since balance is a protected member that only can be accessed within this class or a friend

vector<Transaction> Current::getHistory() { return history; } // accessor method - returns vector<Transaction> hisory, since history is a protected member that only can be accessed within this class or a friend

string Current::getTypeOfAccount() { return "Current account"; } // returns string of account type

void Current::transferIn(float transferAmount, int AccountFrom, char* dateAndTime) { // method called in transfer command. parameters include the amount to be transferred, the number of the account transferring from to write into the accounts history, and the transaction date and time
	balance = balance + transferAmount; // update the current accounts' private member balance - inherited by Account
	string historyTemp = "transfer from account " + to_string(AccountFrom); // create a new string to write to the new transaction, stating a transaction was made and from which account
	Transaction newAmount = Transaction(historyTemp, transferAmount, dateAndTime, false);
	history.push_back(newAmount);
}
bool Current::transferOut(float transferAmount, int AccountTo, char* dateAndTime) {
	if ((balance - transferAmount) < getOverdraft()) { // a check to see if the transfer would cause the account to exceed the accounts' overdraft
		cout << "Transfer unsuccessful - insufficient funds to transfer";
		return false; // return to main, stating there was not enough funds in the first account to be moved into the second account
	}
	else {
		cout << "Transfer successful!\n";
		balance = balance - transferAmount; // update the current accounts' private member balance - inherited by Account
		string historyTemp = "transfer to account " + to_string(AccountTo); // create a new string to write to the new transaction, stating a transaction was made and to which account
		Transaction newAmount = Transaction(historyTemp, transferAmount, dateAndTime, true);
		history.push_back(newAmount);
		return true; // return to main, stating there was enough funds on the account, and was about to transfer the amount. Which in turn would call the second accounts' transferIn method
	}
}
float Current::getOverdraft() { return overdraft; } // accessor method - returns float overdraft, since overdraft is a private member that only can be accessed within this class
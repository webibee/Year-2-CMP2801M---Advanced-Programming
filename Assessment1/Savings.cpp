#include "Savings.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

Savings::Savings() // default constructor - if no initial deposit is provided that is greater than 0
{
	balance = 0.00f; //sets the savings accounts' balance to 0
	Transaction newAmount = Transaction("initial deposit", balance, currentDateAndTime(), false);
	history.push_back(newAmount); // writes new transaction to the accounts history
	cout << "Savings account created!" << endl;
}

Savings::Savings(float openingBalance) // constructor override 
{
	balance = openingBalance;
	Transaction newAmount = Transaction("initial deposit", balance, currentDateAndTime(), false);
	history.push_back(newAmount);
	cout << "Savings account created!" << endl;
}

Savings::Savings(bool ISA, float openingBalance) // constructor override - specifies the savings account created is an ISA
{
	balance = openingBalance;
	IsTypeISA = ISA; // Sets private variable to true, stating this type of savings account is an ISA
	Transaction newAmount = Transaction("initial deposit", balance, currentDateAndTime(), false);
	history.push_back(newAmount);
	cout << "ISA account created!" << endl;
}

Savings::~Savings() {}

void Savings::deposit(float Amount) { // method to add money to the account - similar design to the withdraw member
	Transaction newAmount = Transaction("deposit", Amount, currentDateAndTime(), false); // "false" implies the transaction will be created and be a positive representation of the amount - i.e. £100 and not -£100
	history.push_back(newAmount); // add the new transaction to the savings accounts' history
	balance += Amount; // update the savings accounts' private member balance - inherited by Account
}

void Savings::toString(void) { // outputs the string representation of the object
	if (getBalance() < 0) { cout << getTypeOfAccount() << " | Balance: -" << char(156) << (getBalance() * -1) << endl; } // outputs if balance is negative
	else { cout << getTypeOfAccount() << " | Balance: " << char(156) << getBalance() << endl; } // else outputs balance as positive
	for (Transaction t : getHistory()) { t.toString(); } // outputs every transaction in history vector<transaction>
}

void Savings::withdraw(float Amount) { // method called to take money out of the accout
	Transaction newAmount = Transaction("withdraw", Amount, currentDateAndTime(), true); // creates a new transaction, with the "true" boolean representing it will be a negative transaction - since money out of an account will be e.g. -£100
	history.push_back(newAmount); // add the new transaction to the savings accounts' history
	balance -= Amount; // update the savings accounts' private member balance - inherited by Account
}

float Savings::getBalance(void) { return balance; } // accessor method - returns float balance, since balance is a protected member that only can be accessed within this class or a friend

vector<Transaction> Savings::getHistory(void) { return history; } // accessor method - returns vector<Transaction> hisory, since history is a protected member that only can be accessed within this class or a friend

string Savings::getTypeOfAccount(void) { // returns string of account type
	if (IsTypeISA == false) { return "Savings account"; }
	else { return "ISA account"; }
}

void Savings::transferIn(float transferAmount, int AccountFrom, char* dateAndTime) { // method called in transfer command. parameters include the amount to be transferred, the number of the account transferring from to write into the accounts history, and the transaction date and time
	balance = balance + transferAmount; // update the savings accounts' private member balance - inherited by Account
	string historyTemp = "transfer from account " + to_string(AccountFrom); // create a new string to write to the new transaction, stating a transaction was made and from which account
	Transaction newAmount = Transaction(historyTemp, transferAmount, dateAndTime, false);
	history.push_back(newAmount);
}

bool Savings::transferOut(float transferAmount, int AccountTo, char* dateAndTime) {
	if ((balance - transferAmount) < 0) { // a check to see if the transfer would cause the account to exceed £0.00
		cout << "Transfer unsuccessful - insufficient funds to transfer";
		return false; // return to main, stating there was not enough funds in the first account to be moved into the second account
	}
	else {
		cout << "Transfer successful!\n";
		balance = balance - transferAmount; // update the savings accounts' private member balance - inherited by Account
		string historyTemp = "transfer to account " + to_string(AccountTo); // create a new string to write to the new transaction, stating a transaction was made and to which account
		Transaction newAmount = Transaction(historyTemp, transferAmount, dateAndTime, true);
		history.push_back(newAmount);
		return true; // return to main, stating there was enough funds on the account, and was about to transfer the amount. Which in turn would call the second accounts' transferIn method
	}
}

double Savings::computeInterest(int yearsIntoFuture) {
	double interestRate;
	if (IsTypeISA == true) { interestRate = ISAIR; }
	else { interestRate = SavingsIR; }
	return (getBalance() * (pow((1 + (interestRate / 12)), (12 * yearsIntoFuture))));
}
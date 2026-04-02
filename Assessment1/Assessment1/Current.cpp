#include "Account.h"
#include "Current.h"
#include "Transaction.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

Current::Current()
{
	balance = 0.00f;
	Transaction newAmount = Transaction("initial deposit", balance, currentDateAndTime(), false);
	history.push_back(newAmount);
	cout << "Current account created!" << endl;
}
Current::Current(float openingBalance)
{
	balance = openingBalance;
	Transaction newAmount = Transaction("initial deposit", balance, currentDateAndTime(), false);
	history.push_back(newAmount);
	cout << "Current account created!" << endl;
}
Current::~Current() {}
void Current::toString() {
	cout << "Account toString..." << endl; /////// CHANGE
}
void Current::withdraw(float Amount) {
	Transaction newAmount = Transaction("withdraw", Amount, currentDateAndTime(), true);
	history.push_back(newAmount);
	balance -= Amount;
}
string Current::getTypeOfAccount() { return "Current account"; }
float Current::getBalance() { return balance; }
vector<Transaction> Current::getHistory() { return history; }
void Current::deposit(float Amount) {
	Transaction newAmount = Transaction("deposit", Amount, currentDateAndTime(), false);
	history.push_back(newAmount);
	balance += Amount;
}
void Current::transferIn(float transferAmount, int AccountFrom, char* dateAndTime) {
	balance = balance + transferAmount;
	string historyTemp = "transfer from account " + to_string(AccountFrom);
	Transaction newAmount = Transaction(historyTemp, transferAmount, dateAndTime, false);
	history.push_back(newAmount);
}
bool Current::transferOut(float transferAmount, int AccountTo, char* dateAndTime) {
	if ((balance - transferAmount) < -500) {
		cout << "Transfer unsuccessful - insufficient funds to transfer";
		return false;
	}
	else {
		cout << "Transfer successful!\n";
		balance = balance - transferAmount;
		string historyTemp = "transfer to account " + to_string(AccountTo);
		Transaction newAmount = Transaction(historyTemp, transferAmount, dateAndTime, true);
		history.push_back(newAmount);
		return true;
	}
}
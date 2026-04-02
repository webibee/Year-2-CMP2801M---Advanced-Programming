// class Savings : public Account, public InterestEarning                                     once InterestEarning is made
#include "Account.h"
#include "Savings.h"
#include "Transaction.h"
#include "InterestEarning.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

Savings::Savings()
{
	balance = 0.00f;
	Transaction newAmount = Transaction("initial deposit", balance, currentDateAndTime(), false);
	history.push_back(newAmount);
	cout << "Savings account created!" << endl;
}
Savings::Savings(float openingBalance)
{
	balance = openingBalance;
	Transaction newAmount = Transaction("initial deposit", balance, currentDateAndTime(), false);
	history.push_back(newAmount);
	cout << "Savings account created!" << endl;
}
Savings::Savings(bool ISA, float openingBalance)
{
	balance = openingBalance;
	IsTypeISA = ISA;
	Transaction newAmount = Transaction("initial deposit", balance, currentDateAndTime(), false);
	history.push_back(newAmount);
	cout << "ISA account created!" << endl;
}
Savings::~Savings() {}
void Savings::toString(void) {
	cout << "Account toString..." << endl; /////// CHANGE
}
void Savings::withdraw(float Amount) {
	Transaction newAmount = Transaction("withdraw", Amount, currentDateAndTime(), true);
	history.push_back(newAmount);
	balance -= Amount;
}
string Savings::getTypeOfAccount(void) {
	if (IsTypeISA == false) { return "Savings account"; }
	else { return "ISA account"; }
}
float Savings::getBalance(void) { return balance; }
vector<Transaction> Savings::getHistory(void) { return history; }
void Savings::deposit(float Amount) {
	Transaction newAmount = Transaction("deposit", Amount, currentDateAndTime(), false);
	history.push_back(newAmount);
	balance += Amount;
}
double Savings::computeInterest(int yearsIntoFuture) {
	double interestRate;
	if (IsTypeISA == true) { interestRate = ISAIR; }
	else { interestRate = SavingsIR; }
	return (getBalance() * (pow((1 + (interestRate / 12)), (12 * yearsIntoFuture))));
}
void Savings::transferIn(float transferAmount, int AccountFrom, char* dateAndTime) {
	balance = balance + transferAmount;
	string historyTemp = "transfer from account " + to_string(AccountFrom);
	Transaction newAmount = Transaction(historyTemp, transferAmount, dateAndTime, false);
	history.push_back(newAmount);
}
bool Savings::transferOut(float transferAmount, int AccountTo, char* dateAndTime) {
	if ((balance - transferAmount) < 0) {
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

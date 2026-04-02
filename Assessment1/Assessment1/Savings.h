#pragma once
#include "Account.h"
#include "InterestEarning.h"

using namespace std;

class Savings : public Account, public InterestEarning
{
public:
	Savings();
	Savings(float);
	Savings(bool, float);
	~Savings();
	void toString(void);
	void withdraw(float);
	string getTypeOfAccount(void);
	float getBalance(void);
	vector<Transaction> getHistory(void);
	void deposit(float);
	double computeInterest(int);
	void transferIn(float, int, char*);
	bool transferOut(float, int, char*);
private:
	bool IsTypeISA = false;
	double SavingsIR = 0.00085; // Regular Savings Interest Rate
	double ISAIR = 0.0115; //ISA Savings Interest Rate
};
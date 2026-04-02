#pragma once
#include "Transaction.h"
#include <string>
#include <vector>


using namespace std;

class Account // is this how to do abstract class?	
{
public:
	virtual ~Account() {}; //destructor called
	virtual void deposit(float) = 0;
	virtual void toString() = 0;
	virtual void withdraw(float) = 0;
	virtual float getBalance() = 0;
	virtual vector<Transaction> getHistory() = 0;
	virtual string getTypeOfAccount() = 0;
	virtual void transferIn(float, int, char*) = 0;
	virtual bool transferOut(float, int, char*) = 0;

protected:
	float balance;
	vector<Transaction> history;
};
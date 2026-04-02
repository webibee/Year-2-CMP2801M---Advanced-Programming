#pragma once
#include "Transaction.h"
#include <string>
#include <vector>
#include <iostream>


using namespace std;

class Account // Abstract class	- expecting everything to be overriden by child classes with inheritance
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

char* currentDateAndTime(); // function to get the systems current date and time of when this function is run
#pragma once
#include "Account.h"
using namespace std;

class Current : public Account
{
public:
	Current();
	Current(float);
	~Current();
	void withdraw(float);
	string getTypeOfAccount();
	float getBalance();
	vector<Transaction> getHistory();
	void deposit(float);
	void transferIn(float, int, char*);
	bool transferOut(float, int, char*);
private:
	float overdraft = -500;
};
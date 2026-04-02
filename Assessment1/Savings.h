#pragma once
#include "Account.h"
#include "InterestEarning.h"

class Savings : public Account, public InterestEarning // child class wiht multiple inheritance - from the parent and all it's public and protected members, along with InterestEarning and its members
{
public:
	Savings(); // Default constructor
	Savings(float); // Override Constructor
	Savings(bool, float); // Override Constructor
	~Savings(); // Destructor 
	void deposit(float); //Polymorphism - function overloading from abstract parent Account
	void toString(void); //Polymorphism - function overloading from abstract parent Account
	void withdraw(float); //Polymorphism - function overloading from abstract parent Account
	float getBalance(void); //Polymorphism - function overloading from abstract parent Account
	vector<Transaction> getHistory(void); //Polymorphism - function overloading from abstract parent Account
	string getTypeOfAccount(void); //Polymorphism - function overloading from abstract parent Account
	void transferIn(float, int, char*); //Polymorphism - function overloading from abstract parent Account
	bool transferOut(float, int, char*); //Polymorphism - function overloading from abstract parent Account
	double computeInterest(int); // New method exclusive to this class
private:
	bool IsTypeISA = false;
	double SavingsIR = 0.00085; // Regular Savings Interest Rate
	double ISAIR = 0.0115; //ISA Savings Interest Rate
};
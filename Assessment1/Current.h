#pragma once
#include "Account.h"

class Current : public Account // child class inheriting from the parent and all it's public and protected members
{
public:
	Current(); // Default constructor
	Current(float); // Override Constructor
	~Current(); // Destructor
	void deposit(float); //Polymorphism - function overloading from abstract parent Account
	void toString(); //Polymorphism - function overloading from abstract parent Account
	void withdraw(float); //Polymorphism - function overloading from abstract parent Account
	float getBalance(); //Polymorphism - function overloading from abstract parent Account
	vector<Transaction> getHistory(); //Polymorphism - function overloading from abstract parent Account
	string getTypeOfAccount(); //Polymorphism - function overloading from abstract parent Account
	void transferIn(float, int, char*); //Polymorphism - function overloading from abstract parent Account
	bool transferOut(float, int, char*); //Polymorphism - function overloading from abstract parent Account
	float getOverdraft(); // New method, exclusive to Current Accounts
private:
	float overdraft = -500; // Private overdraft variable - can only be accessed within this Class
};
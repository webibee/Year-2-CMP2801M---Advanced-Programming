#pragma once
#include <string>

using namespace std;

class Transaction {
public:
	string desc;
	float value;
	string timestamp;
	bool outgoing; // bool variable representing if the transaction is positive or negatiev
	Transaction(string, float, string, bool); // Class constructor
	void toString();
	friend ostream& operator<<(ostream&, const Transaction&); // classing the operator overloader as a friend, so that is can access the class properties
};

ostream& operator<<(ostream& os, const Transaction& transac); // Operator Overloading - the function of the "<<" symbols when using a cout command
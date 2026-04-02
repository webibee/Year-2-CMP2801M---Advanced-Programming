#include "Transaction.h"
#include <iostream>
#include <string>

Transaction::Transaction(string descPar, float valuePar, string timestampPar, bool NegativeTransaction) { desc = descPar, value = valuePar, timestamp = timestampPar; outgoing = NegativeTransaction; } // Setter constructor; assigning argument values to the class member properties

void Transaction::toString() { // string representation of the class - to output the transactions to console
	cout << *this; // calling the operator overloader on the class itself
}

ostream& operator<<(ostream& os, const Transaction& transac) { // operator overloader - to print each transaction which each of its properties 
	if (transac.outgoing == false) { os << "-- " << transac.desc << ": " << char(156) << transac.value << " on " << transac.timestamp; }
	else { os << "-- " << transac.desc << ": -" << char(156) << transac.value << " on " << transac.timestamp; }
	return os;
}
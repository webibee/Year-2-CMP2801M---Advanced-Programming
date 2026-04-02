#include "Transaction.h"
#include <iostream>
#include <string>

using namespace std;

Transaction::Transaction(string descPar, float valuePar, string timestampPar, bool NegativeTransaction) { desc = descPar, value = valuePar, timestamp = timestampPar; outgoing = NegativeTransaction; }
void Transaction::toString() {
	if (outgoing == false) { cout << "-- " << desc << ": " << char(156) << value << " on " << timestamp; }
	else { cout << "-- " << desc << ": -" << char(156) << value << " on " << timestamp; }
}
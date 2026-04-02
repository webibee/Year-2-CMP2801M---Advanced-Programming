#pragma once

using namespace std;

class Transaction {
public:
	string desc;
	float value;
	string timestamp;
	bool outgoing;
	Transaction(string, float, string, bool);
	void toString();
};
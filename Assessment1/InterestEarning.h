#pragma once

class InterestEarning // Interface class
{
protected:
	virtual double computeInterest(int) = 0; // one pure virtual function - expected to be overriden within the savings class 
};
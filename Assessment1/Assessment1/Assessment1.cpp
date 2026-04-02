#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <vector>
#include <ctime>
#include <string>
#include <cmath>
#include "Account.h"
#include "Current.h"
#include "Savings.h"
#include "Transaction.h"
#include "InterestEarning.h"

using namespace std;

//     HEADER FILES
//		e.g. Account.cpp, Account.hd (whatever the header extension is)

// find how to get type of class - for checking overdraft with "with" command, and for anywhere need to check type of account
// project calculation is wrong
//  e.g. for OPEN command - there is an error if "open 2" is entered
//  doesnt allow just "view " command -- "view" + " "
// e.g. when doing withdraw command - make the if statements compare to the current account class private member 'overdraft' rather than just comparing to int 500
// do i need #include <typeinfo>?

char* currentDateAndTime() {
	time_t now = time(0);
	char* currDateTime = ctime(&now);
	return currDateTime;
}

void OutputBankLog(Account* a) {
	if (a->getBalance() < 0) { cout << a->getTypeOfAccount() << " | Balance: -" << char(156) << (a->getBalance() * -1) << endl; }
	else { cout << a->getTypeOfAccount() << " | Balance: " << char(156) << a->getBalance() << endl; }
	for (Transaction t : a->getHistory()) { t.toString(); }
}

void Withdraw(Account* a, vector<string> para) {
	float arg1AsFloat = stof(para[1]);
	try {
		if (arg1AsFloat >= 0.00) {
			a->withdraw(arg1AsFloat);
			OutputBankLog(a);
		}
		else { cout << "Inavlid amount to withdraw"; }
	}
	catch (...) { cout << "Inavlid Input for withdraw command"; }
}

void ViewAllAccounts(vector<Account*> accs) {
	int accsIndex = 1;
	for (Account* a : accs) {
		cout << "\n---------------  Account " << accsIndex << "  ---------------\n";
		OutputBankLog(a);
		accsIndex += 1;
	}
}

bool CheckValidBankAccount(vector<string> para) {
	string arg1 = para[1];
	string arg2 = para[2];
	try {
		int arg1AsInt = stoi(arg1);
		int arg2AsInt = stoi(arg2);
		if ((para.size() == 3) && (1 <= arg1AsInt) && (arg1AsInt <= 3)) { return true; }
		else { return false; }
	}
	catch (...) { return false; }
}

int main()
{
	vector<string> parameters;
	vector<Account*> accounts; // A collection of opened accounts 
	string userCommand;
	int NumberOfCurrentAccounts = 0;
	cout << "~~~ Welcome to LincBank! ~~~\nopen type initial_deposit: open a current (1), savings (2) or ISA (3) account \nview [index]: view balance and recent transactions\nwithdraw sum: withdraw funds from most recently viewed account\ndeposit sum: deposit funds into most recently viewed account\ntransfer src dest sum: transfer funds between accounts\nproject years: project balance forward in time\nexit: close this application \noptions: view these options again" << endl;
	Account* CurrAcc = 0; // most recent account being made or accessed to
	while (userCommand != "exit")
	{
		parameters.clear(); // clear ready for next command
		cout << endl << ">>> ";

		getline(cin, userCommand);
		char* cstr = new char[userCommand.length() + 1];
		strcpy(cstr, userCommand.c_str());

		char* token;
		token = strtok(cstr, " ");

		while (token != NULL)
		{
			parameters.push_back(token);
			token = strtok(NULL, " ");
		}

		// Define all commands as per the brief
		string command = parameters[0];
		string argument1;
		string argument2;
		int arg1AsInt;
		int arg2AsInt;
		float arg1AsFloat = 0;
		int accountIndex;
		if (command.compare("options") == 0) { cout << "\nopen type initial_deposit: open a current (1), savings (2) or ISA (3) account \nview [index]: view balance and recent transactions\nwithdraw sum: withdraw funds from most recently viewed account\ndeposit sum: deposit funds into most recently viewed account\ntransfer src dest sum: transfer funds between accounts\nproject years: project balance forward in time\nexit: close this application \noptions: view these options again" << endl; }
		else if (command.compare("open") == 0)
		{
			try{
				if (CheckValidBankAccount(parameters) == true) {
					argument1 = parameters[1];
					argument2 = parameters[2];
					arg1AsInt = stoi(argument1);
					arg2AsInt = stoi(argument2);
					if (arg1AsInt == 1) { //Checking type of account that it wanted to be opened
						//Create Current Account
						if (NumberOfCurrentAccounts >= 1) { cout << "Maximum number of current accounts has already been reached (Max Limit: 1)"; }
						else {
							try {
								if (arg2AsInt > 0) { CurrAcc = new Current(stof(argument2)); }
								else if (arg2AsInt == 0) { CurrAcc = new Current(); }
								else {
									cout << "Inavlid amount to deposit for account type (>= 0.00)";
									throw argument2;
								};
								accounts.push_back(CurrAcc);
								NumberOfCurrentAccounts += 1;
							}
							catch (...) { cout << "Inavlid amount input to open a savings account"; }
						}
					}
					else if (arg1AsInt == 2) {
						//Create Savings
						try {
							if (arg2AsInt > 0) { CurrAcc = new Savings(stof(argument2)); }
							else if (arg2AsInt = 0) { CurrAcc = new Savings(); }
							else { throw argument2; };
							accounts.push_back(CurrAcc);
						}
						catch (...) { cout << "Inavlid amount input to open a savings account"; }
					}
					else if (arg1AsInt == 3) {
						//Create ISA
						if (arg2AsInt >= 1000) {
							CurrAcc = new Savings(true, stof(argument2));
							accounts.push_back(CurrAcc);
						}
						else { cout << "Inavlid amount to deposit for account type (>= 1,000.00)"; }
					}
				}
				else { throw (stoi(argument1)); }
			}
			catch (...) { cout << "Inavlid Input for Bank Type or amount to deposit"; }
		}
		else if (command.compare("view") == 0)
		{
			// display an account according to an index (starting from 1)
			// alternatively, display all accounts if no index is provided
			if (userCommand == "view") { // If only the command view is entered
				ViewAllAccounts(accounts);
			}
			else {
				try {
					argument1 = parameters[1];
					arg1AsInt = stoi(argument1) - 1;
					if ((arg1AsInt < 0) || (arg1AsInt + 1 > accounts.size())) { cout << "Invalid integer entered for account index"; }
					else {
						try {
							CurrAcc = accounts[arg1AsInt];
							OutputBankLog(CurrAcc);
						}
						catch (...) { cout << "Invalid input parameter for view command"; }
					}
				}
				catch (...) { cout << "Inavlid Input for view command"; }
			}
		}
		else if (command.compare("withdraw") == 0)
		{
			// allow user to withdraw funds from an account
			try {
				arg1AsFloat = stof(parameters[1]);
				if ((CurrAcc->getTypeOfAccount() == "Current account")) {
					if ((CurrAcc->getBalance() - arg1AsFloat) >= -500) { Withdraw(CurrAcc, parameters); }//////////////////////////////////////////////////////////////////////////////////////
					else { cout << "Inavlid withdrawal - amount exceeds " << char(156) << "500 overdraft limit on Current accounts"; }
				}
				else {
					if ((CurrAcc->getBalance() - arg1AsFloat) < 0) { cout << "Invalid amount to withdraw - not enough funds"; }
					else { Withdraw(CurrAcc, parameters); }
				}
			}
			catch (...) { cout << "Invalid withdraw command"; }
		}
		else if (command.compare("deposit") == 0)
		{
			// allow user to deposit funds into an account
			try {
				arg1AsFloat = stof(parameters[1]);
				if (arg1AsFloat >= 0.00) {
					CurrAcc->deposit(arg1AsFloat);
					OutputBankLog(CurrAcc);
				}
				else { cout << "Inavlid amount to deposit"; }
			}
			catch (...) { cout << "Inavlid Input for deposit command"; }
		}
		else if (command.compare("transfer") == 0)
		{
			// allow user to transfer funds between accounts
			// i.e., a withdrawal followed by a deposit!
			

			// use a temp variable for amount to transfer
			// use pointer to account1balance + accountbalance2
			try {
				arg1AsInt = (stoi(parameters[1]) - 1);
				arg2AsInt = (stoi(parameters[2]) - 1);
				float tempAmount = stof(parameters[3]);
				char* currDateAndTime = currentDateAndTime(); // This is so that the transfer has the same timestamp on both accounts
				if ((accounts[arg1AsInt]->transferOut(tempAmount, arg2AsInt + 1, currDateAndTime)) == true) { 
					accounts[arg2AsInt]->transferIn(tempAmount, arg1AsInt + 1, currDateAndTime); 
					OutputBankLog(accounts[arg1AsInt]);
					OutputBankLog(accounts[arg2AsInt]);
				}
			}
			catch (...) { cout << "Invalid input for transfer command"; }
		}
		else if (command.compare("project") == 0)
		{
			// compute compound interest t years into the future
			int accountChosenIndex;
			// create loop that projects all savings accounts
			if (userCommand == "project") {
				cout << ">>> Enter integer to represent account to project: " << endl;
				accountIndex = 1;
				for (Account* a : accounts) {
					cout << "\n-------  Account " << accountIndex << ":  " << a->getTypeOfAccount() << " | Balance: " << char(156)  << a->getBalance() << "\n";
					accountIndex += 1;
				}
				try {
					cout << endl << ">>> ";
					string accountChosen;
					getline(cin, accountChosen);
					accountChosenIndex = stoi(accountChosen) - 1;
					if ((accountChosenIndex < 0) || (accountChosenIndex + 1 > accountIndex)) { throw accountChosenIndex; }
				}
				catch (...) { cout << "Invalid input for integer account" << endl; }
			}
			else {
				try { 
					arg1AsInt = stoi(parameters[1]); 
					accountChosenIndex = arg1AsInt - 1;
				}
				catch (...) { cout << "Invalid input for account"; }
			}
			string accTypeTemp = accounts[accountChosenIndex]->getTypeOfAccount();
			if ((accTypeTemp == "Savings account") || (accTypeTemp == "ISA account")) {
				try {
					cout << ">>> Enter integer to represent number of years to project: ";
					cout << endl << ">>> ";
					string years;
					getline(cin, years);
					int yearsInt = stoi(years);
					//Savings currSavings = *accounts[accountChosenIndex];

					//if (!(dynamic_cast<Savings*>(accounts[accountChosenIndex]) == nullptr))
					Savings* savingTemp = dynamic_cast<Savings*>(accounts.at(accountChosenIndex));
					cout << "Projected balance: " << char(156) << savingTemp->computeInterest(yearsInt);
				}
				catch (...) { cout << "Invalid input for integer years to project" << endl; }
			}
			else { cout << "Invalid type of account to project"; }
		}
		else if (command.compare("search"))
		{
		//	allow users to search their account history for a transaction
		//  (this is a stretch task)
		}
	}
	for (int i = 0; i < accounts.size(); i++) { delete accounts[i]; }
	cout << "Press any key to quit...";
	getchar();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
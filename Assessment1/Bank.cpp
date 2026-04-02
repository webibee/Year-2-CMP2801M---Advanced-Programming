#define _CRT_SECURE_NO_WARNINGS
#include "Current.h"
#include "Savings.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

void Withdraw(Account* a, vector<string> para) { // function to withdraw the amount entered by the user
	float arg1AsFloat = stof(para[1]); // Main program already checks to make sure the 2nd argument entered by the user is a number data type
	try {
		if (arg1AsFloat >= 0.00) { // will only withdraw if the amount entered is positive or greater than 0.
			a->withdraw(arg1AsFloat); // will call the class-specific override-withdraw method
			a->toString(); // will print to the console the accounts type, current balance and history of transactions
		}
		else { cout << "Inavlid amount to withdraw"; } // will print if the user tries to enter a negative amount to withdraw
	}
	catch (...) { cout << "Inavlid input for withdraw command"; }
}

void ViewAllAccounts(vector<Account*> accs) { // For loop that iterates through every account in the accounts vector, printing which account it is (its index in the vector + 1) along with all the accounts specific details (type, balance, transactions)
	int accsIndex = 1;
	for (Account* a : accs) {
		cout << "\n---------------  Account " << accsIndex << "  ---------------\n";
		a->toString();
		accsIndex += 1;
	}
}

bool CheckValidBankAccount(vector<string> para) { // Function used when opening an account
	string arg1 = para[1];
	try { // Checks to see if string user entered to represent type of bank is a number data type, else it would throw an error trying to convert it to an int type
		int arg1AsInt = stoi(arg1);
		if ((1 <= arg1AsInt) && (arg1AsInt <= 3)) { return true; }
		else { return false; }
	}
	catch (...) { return false; } // catches errors if the data entered by the user was unable to be converted to an int - meaning the data entered was not a number and therefore could not represent a type of account
}

void ProjectSavingsAccount(string getType, Account* acc) {
	string accTypeTemp = getType;
	if ((accTypeTemp == "Savings account") || (accTypeTemp == "ISA account")) { // Only continue with project command if the account chosen to project is of type savings or ISA
		try {
			cout << ">>> Enter integer to represent number of years to project: ";
			cout << endl << ">>> ";
			string years;
			getline(cin, years);
			int yearsInt = stoi(years); // Get the integer value to project n number of years, as entered by the user
			Savings* savingTemp = dynamic_cast<Savings*>(acc); // Dynamic cast the currAcc from main to make sure it is a savings account, and therefore would be able to access the savings-exclusive-computeInterest() method
			cout << "Projected balance: " << char(156) << savingTemp->computeInterest(yearsInt); 
			/*
			- char(156) == £ symbol
			- computeInterest() member computes using the formula provided by the brief, returning the result as type double	*/
		}
		catch (...) { cout << "Invalid input for integer years to project" << endl; } // Catch errors if the user enters anything other than an integer for the years variable to project 
	}
	else { cout << "Invalid type of account to project"; } // won't project if the account selected is type Current - since there is no interest rate to be included into the computeInterest() formula
}

int main()
{
	vector<string> parameters;
	vector<Account*> accounts; // A collection of opened accounts 
	string userCommand;
	int NumberOfCurrentAccounts = 0; // A tracker since only 1 current account is allowed to be opened 
	cout << "~~~ Welcome to LincBank! ~~~\nopen type initial_deposit: open a current (1), savings (2) or ISA (3) account \nview [index]: view balance and recent transactions\nwithdraw sum: withdraw funds from most recently viewed account\ndeposit sum: deposit funds into most recently viewed account\ntransfer src dest sum: transfer funds between accounts\nproject [years]: project balance forward in time\nsearch: search for transactions by their value\nexit: close this application \noptions: view these options again" << endl;
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
		while (userCommand.back() == ' ') {
			userCommand.pop_back(); // if an accidental space(s) is entered at the end of the command input, it is removed. This previous raised errors
		}
		string command = parameters[0];
		string argument1;
		string argument2;
		int arg1AsInt;
		int arg2AsInt;
		float arg1AsFloat = 0;
		int accountIndex;
		string accTypeTemp;
		if (command.compare("options") == 0) { cout << "\nopen type initial_deposit: open a current (1), savings (2) or ISA (3) account \nview [index]: view balance and recent transactions\nwithdraw sum: withdraw funds from most recently viewed account\ndeposit sum: deposit funds into most recently viewed account\ntransfer src dest sum: transfer funds between accounts\nproject [years]: project balance forward in time\nsearch: search for transactions by their value\nexit: close this application \noptions: view these options again" << endl; }
		else if (command.compare("open") == 0)
		{
			if (parameters.size() != 3) { cout << "Inavlid input to open a Bank - requires::: open {type} {initial_deposit}"; } // Only runs the open command if the same parameter inputs are made as designed in the brief
			else {
				try {
					if (CheckValidBankAccount(parameters) == true) {
						argument1 = parameters[1];
						arg1AsInt = stoi(argument1);
						if (arg1AsInt == 1) { //Checking type of account that it wanted to be opened
							//Create Current Account
							if (NumberOfCurrentAccounts >= 1) { cout << "Maximum number of current accounts has already been reached (Max Limit: 1)"; }
							else {
								try {
									argument2 = parameters[2];
									arg2AsInt = stoi(argument2);
									if (arg2AsInt > 0) { CurrAcc = new Current(stof(argument2)); } // Create a current account if balance entered is greater than 0 (overload constructor)
									else if (arg2AsInt == 0) { CurrAcc = new Current(); } // Create a current account if balance entered is equal to 0 (default constructor)
									else { throw argument2; }; // if the user enters data invalid to be converted to an integer
									accounts.push_back(CurrAcc); // Add the created current account into the vector storing all bank accounts
									NumberOfCurrentAccounts += 1; // increment to keep track and only allow 1 current account to be made
								}
								catch (...) { cout << "Inavlid amount input to open a current account"; }
							}
						}
						else if (arg1AsInt == 2) {
							//Create Savings
							try {
								argument2 = parameters[2];
								arg2AsInt = stoi(argument2);
								if (arg2AsInt > 0) { CurrAcc = new Savings(stof(argument2)); } // Create a savings account if balance entered is greater than 0 (overload constructor)
								else if (arg2AsInt == 0) { CurrAcc = new Savings(); } // Create a savings account if balance entered is equal to 0 (default constructor)
								else { throw argument2; };
								accounts.push_back(CurrAcc); // Add the created Savings account into the vector storing all bank accounts
							}
							catch (...) { cout << "Inavlid amount input to open a savings account"; } // catches anything entered for amount other than a positive int/float
						}
						else if (arg1AsInt == 3) {
							//Create ISA
							try {
								argument2 = parameters[2];
								arg2AsInt = stoi(argument2);
								if (arg2AsInt >= 1000) { CurrAcc = new Savings(true, stof(argument2)); } // Create an ISA account if initial deposit entered is greater than 1,000 (overload constructor)
								else { throw argument2; }
								accounts.push_back(CurrAcc); // Add the created ISA account into the vector storing all bank accounts
							}
							catch (...) { cout << "Inavlid amount input to open an ISA account (>= 1000.00)"; } // catches anything entered for amount other than a positive int/float greater or equal to 1000
						}
						else { throw (stoi(argument1)); }
					}
					else { throw (stoi(argument1)); }
				}
				catch (...) { cout << "Inavlid input for Bank Type or amount to deposit"; }
			}
		}
		else if (command.compare("view") == 0)
		{
			// display an account according to an index (starting from 1)
			// alternatively, display all accounts if no index is provided
			if (accounts.size() == 0) { cout << "Inavlid input to view - there are no accounts currently open to view"; } // If there are no accounts made - then there will be no accounts to view, so output message to console
			else {
				if (!(parameters.size() <= 2)) { cout << "Inavlid input to view - requires::: view {index}"; } // will only run the view command if the word "view" is present at the start and there may be 1 more parameter entered 
				else {
					if (userCommand == "view") { // If only the command view is entered, display all accounts with their details, since no index was specified
						ViewAllAccounts(accounts);
					}
					else { // Else if the view command is entered with another parameter 
						try {
							argument1 = parameters[1];
							arg1AsInt = stoi(argument1) - 1; //check to see if the parameter entered can be converted to an integer type and subtract 1 to store as a reference to the accounts index within the "accounts" vector
							if ((arg1AsInt < 0) || (arg1AsInt + 1 > accounts.size())) { cout << "Invalid integer entered for account index"; } // If the index entered by the user is not valid as an index without throwing a error; i.e. below index 0 or greater than the number or accounts there are
							else {
								try {
									CurrAcc = accounts[arg1AsInt]; // make the current account variable update to the account specified by the view command parameter 
									CurrAcc->toString(); // Output all details about the account
								}
								catch (...) { cout << "Invalid input parameter for view command"; }
							}
						}
						catch (...) { cout << "Inavlid input for view command"; }
					}
				}
			}
		}
		else if (command.compare("withdraw") == 0)
		{
			// allow user to withdraw funds from an account
			if (accounts.size() == 0) { cout << "Inavlid input to withdraw - there are no accounts currently open to withdraw from"; } // won't run withdraw command unless there is at least 1 account opened to withdraw from
			else {
				if (parameters.size() != 2) { cout << "Inavlid input to withdraw - requires::: withdraw {sum}"; } // Will only run the wihdraw command with 2 parameters as specified by the brief "withdraw" followed by a number data type (float/integer)
				else {
					try {
						arg1AsFloat = stof(parameters[1]);
						if ((CurrAcc->getTypeOfAccount() == "Current account")) {
							accTypeTemp = CurrAcc->getTypeOfAccount();
							if (accTypeTemp == "Current account") {
								Current* currentTemp = dynamic_cast<Current*>(CurrAcc); // Casting from currAcc pointer to a Current account, to access private member Overdraft
								if ((CurrAcc->getBalance() - arg1AsFloat) >= currentTemp->getOverdraft()) { Withdraw(CurrAcc, parameters); } // If the amount to withdraw doesn't exceed the Current accounts' overdraft, then withdraw he amount
								else { cout << "Inavlid withdrawal - amount exceeds " << char(156) << "500 overdraft limit on Current accounts"; }
							}
						}
						else {
							if ((CurrAcc->getBalance() - arg1AsFloat) < 0) { cout << "Invalid amount to withdraw - not enough funds"; } // Since Savings and ISA don't have an overdraft, check if the amount to withdraw causes the accounts balance to become negative
							else { Withdraw(CurrAcc, parameters); } // If the account has enough credit, withdraw the specified amount 
						}
					}
					catch (...) { cout << "Invalid withdraw command"; } // Catch errors if the user parameter entered is anything other than a number data type, since "arg1AsFloat = stof(parameters[1]);" would raise an error if it cannot convert to type float
				}
			}
		}
		else if (command.compare("deposit") == 0)
		{
			// allow user to deposit funds into an account
			if (accounts.size() == 0) { cout << "Inavlid input to deposit - there are no accounts currently open to deposit into"; } // won't run deposit command unless there is at least 1 account opened to deposit to
			else {
				if (parameters.size() != 2) { cout << "Inavlid input to deposit - requires::: deposit {sum}"; } // Only runs if deposit command has 2 parameters as specified in the brief "deposit" followed by a number data type (float/integer)
				else {
					try {
						arg1AsFloat = stof(parameters[1]);
						if (arg1AsFloat >= 0.00) {
							CurrAcc->deposit(arg1AsFloat); // deposit float into account, and update balance private member
							CurrAcc->toString(); // Output type of account, balance, as well as transactions - as provided as an example by the Sample Execution file
						}
						else { cout << "Inavlid amount to deposit"; } // Will not allow a deposit of negative numbers
					}
					catch (...) { cout << "Inavlid input for deposit command"; } //  will only allow number data types to be entered for the deposit command 2nd parameter
				}
			}
		}
		else if (command.compare("transfer") == 0)
		{
			// allow user to transfer funds between accounts
			if (accounts.size() <= 1) { cout << "Inavlid input to transfer - there are not enough accounts currently open to transfer between"; } // won't run transfer command unless there is at least two accounts to transfer between
			else {
				if (parameters.size() != 4) { cout << "Inavlid input to transfer - requires::: transfer {src} {dest} {sum}"; } // Will only run if 4 parameters are entered as stated in the brief
				else {
					try {
						arg1AsInt = (stoi(parameters[1]) - 1); // fetches accounts vector index of the account the user wishes to transfer from
						arg2AsInt = (stoi(parameters[2]) - 1); // fetches accounts vector index of the account the user wishes to transfer to
						/*
						 The following if statement checks for:
						 - whether the user input account to transfer from - has an index in the accounts vector greater than its size - i.e. if they enter to transfer from account 4 but there are only 3 accounts
						 - whether the user input account to transfer to - has an index in the accounts vector greater than its size - i.e. if they enter to transfer to account 4 but there are only 3 accounts
						 - whether the user input account to transfer from - has an index in the accounts vector less than 0
									- i.e. if they enter to transfer from account 0 but accounts would start at 1 and only increment positively - therefore trying to access an account which doesn't exist
						 - whether the user input account to transfer to - has an index in the accounts vector less than 0
									- i.e. if they enter to transfer to account 0 but accounts would start at 1 and only increment positively - therefore trying to access an account which doesn't exist

						Therefore if any of the previous are true, then this would be raised as an invalid command, since none of these situations should be allowed to happen
						*/
						if ((arg1AsInt + 1 > accounts.size()) || (arg2AsInt + 1 > accounts.size()) || (arg1AsInt + 1 <= 0) || (arg2AsInt + 1 <= 0)) { cout << "Invalid account(s) entered to transfer between"; }
						// Otherwise if both account parameters entered are valid and have an account created at that index, the program will attempt to transfer - by doing so, in checking both accounts balances' and amount wished to transfer
						else {
							float tempAmount = stof(parameters[3]); // temp variable to hold amount to transfer between accounts
							char* currDateAndTime = currentDateAndTime(); // This is so that the transfer has the same timestamp on both accounts
							/*
							- if there is enough money in the first account available to be removed by the specified transfer amount, then continue with the transfer
							- if the transfer amount exceeds the accounts overdraft / £0.00 limit, then the "->transferOut()" method would return false and print "Transfer unsuccessful - insufficient funds to transfer"
							*/
							if ((accounts[arg1AsInt]->transferOut(tempAmount, arg2AsInt + 1, currDateAndTime)) == true) {
								accounts[arg2AsInt]->transferIn(tempAmount, arg1AsInt + 1, currDateAndTime); // Carry out the transfer
								accounts[arg1AsInt]->toString();
								accounts[arg2AsInt]->toString(); // print to console both accounts and transactions
							}
						}
					}
					catch (...) { cout << "Invalid input for transfer command"; } // if anything other than a number data type is entered for the account or amount parameters of the transfer command, this error will be caught
				}
			}
		}
		else if (command.compare("project") == 0)
		{
			if (accounts.size() == 0) { cout << "Inavlid input to project - there are no accounts currently open to project"; } // will only run project command if there is at least one account to project
			else {
				// compute compound interest t years into the future
				int accountChosenIndex;
				if (userCommand == "project") { // if the command entered by the user only says "project" and no other arguments given
					cout << ">>> Enter integer to represent account to project: " << endl; // User is asked which account they would like to project
					accountIndex = 1;
					for (Account* a : accounts) { // all accounts that have been created are listed onto the console, stating their indexes within the accounts vector as their account numbers - i.e. account[0] is Account 1....
						cout << "\n-------  Account " << accountIndex << ":  " << a->getTypeOfAccount() << " | Balance: " << char(156) << a->getBalance() << "\n";
						accountIndex += 1;
					}
					try {
						cout << endl << ">>> ";
						string accountChosen;
						getline(cin, accountChosen); // accept a user input to represent which account they would like to project
						accountChosenIndex = stoi(accountChosen) - 1;
						if ((accountChosenIndex < 0) || (accountChosenIndex + 1 >= accountIndex)) { throw accountChosenIndex; } 
						// if the number the user entered is out of range from the number of accounts stored in the "accounts" vector, throw an error since there is no account at the user specified index
						else { ProjectSavingsAccount(accounts[accountChosenIndex]->getTypeOfAccount(), accounts.at(accountChosenIndex)); } // if the user entered a valid integer to represent an existing account, run the ProjectSavingsAccount function
					}
					catch (...) { cout << "Invalid input for integer account" << endl; } // if anything is entered by the user to represent the number of years to project, which isnt a number data type such as int or float
				}
				else { // else if the user entered the command "project" along with another parameter 
					try {
						arg1AsInt = stoi(parameters[1]); // try converting user parameter entered into an integer to represent which account they would like to project
						accountChosenIndex = arg1AsInt - 1;
						if ((accountChosenIndex < 0) || (accountChosenIndex + 1 > accounts.size())) { throw accountChosenIndex; }
						// if the number the user entered is out of range from the number of accounts stored in the "accounts" vector, throw an error since there is no account at the user specified index
						else { ProjectSavingsAccount(accounts[accountChosenIndex]->getTypeOfAccount(), accounts.at(accountChosenIndex)); }
					}
					catch (...) { cout << "Invalid input for account"; } // if the parameter entered by the user is not accepted when trying to convert to an integer data type
				}
			}
		}
		else if (command.compare("search") == 0)
		{
			if (accounts.size() == 0) { cout << "Inavlid input to search - there are no accounts currently open to search"; } // won't run the search command unless there is at least 1 account opened to search
			else {
				//	allow users to search their account history for a transaction
				cout << ">>> Here are the available accounts to search: \n";
				ViewAllAccounts(accounts); // Displays all accounts along with all of their information 
				cout << "\n>>> Enter account number you wish to search: ";
				cout << endl << ">>> ";
				string accInt;
				try {
					getline(cin, accInt);
					int searchAcc = stoi(accInt); // if user enters anything other than a number data type to represent which account to search - an error is raised
					if ((searchAcc < 1) || (searchAcc > accounts.size())) { cout << "Invalid Account number entered"; } // if the user tries to enter an invalid account
					else {
						cout << "\n>>> Enter transaction amount/number you wish to search for: ";
						cout << endl << ">>> ";
						string userTransactionAmount;
						getline(cin, userTransactionAmount);
						int searchTransac = stoi(userTransactionAmount); // if anything other than a number data type is entered, an error is raised, so the catch line is run
						vector<Transaction> tempSearchOfTrans; // create a temporary vector to store data of type Transaction to store all transaactions with the same value as the user input amount
						for (Transaction t : accounts[searchAcc - 1]->getHistory()) { if (t.value == stof(userTransactionAmount)) { tempSearchOfTrans.push_back(t); } } // loop iterating through all transactions, and adding the transaction to the temporary vector if their "value" values match
						if (tempSearchOfTrans.empty() == true) { cout << "No transactions of the value entered where found in this account"; } // if no transations were found with the same value as the amount entered by the user; it'll print that no transactions were found
						else { // Otherwise if transactions were found matching the same value with the amount entered by the user, then all of those transactions would be output 
							cout << "\n>>> Results of transaction search in Account " << searchAcc << ": \n";
							for (Transaction t : tempSearchOfTrans) { t.toString(); }
						}
					}
				}
				catch (...) { cout << "Invalid input for account to search"; } // error is caught for entering a data type other than a number for which account the user would wish to search in
			}
		}
	}
	for (int i = 0; i < accounts.size(); i++) { delete accounts[i]; } // memory management - releasing all the class memory by calling all accounts' destructors through iterating through the accounts vector 
	cout << "Press any key to quit...";
	getchar();
}
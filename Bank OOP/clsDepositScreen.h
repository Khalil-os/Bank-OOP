#pragma once
#include <iomanip>
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsDepositScreen : protected clsScreen
{
private:

	static void _Print(clsBankClient Client) {
		cout << setw(37) << left << "" << "\t\tClient Card\n";
		cout << setw(37) << left << "" << "---------------------------------------\n";
		cout << setw(37) << left << "" << "\tFirstName  : " << Client.FirstName << endl;
		cout << setw(37) << left << "" << "\tLastName   : " << Client.LastName << endl;
		cout << setw(37) << left << "" << "\tFullName   : " << Client.FullName << endl;
		cout << setw(37) << left << "" << "\tEmail      : " << Client.Email << endl;
		cout << setw(37) << left << "" << "\tPhone      : " << Client.Phone << endl;
		cout << setw(37) << left << "" << "\tAcc.Number : " << Client.AccountNumber << endl;
		cout << setw(37) << left << "" << "\tPassword   : " << Client.PinCode << endl;
		cout << setw(37) << left << "" << "\tBalance    : " << Client.AccountBalance << endl;
		cout << setw(37) << left << "" << "---------------------------------------\n";
	}

public:

	static void ShowDepositScreen()
	{
		_DrawScreenHeader("    Deposit Screen");
		string AccountNumber = "";
		cout << setw(37) << left << "" << "Enter Please Your Account Number : ";
		AccountNumber = clsInputValidate::ReadString();
		cout << endl;
		while (!(clsBankClient::IsClientExist(AccountNumber))) {
			cout << setw(37) << left << "" << "Your Account Number is NOT Found , Please enter another one : ";
			AccountNumber = clsInputValidate::ReadString();
			cout << endl;
		}
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		cout << endl;
		_Print(Client);
		cout << endl;
		float Amount;
		cout << "\n\n" << setw(37) << left << "" << "Please enter deposit amount : ";
		cin >> Amount;
		cout << endl << endl;
		char Acces;
		cout << setw(37) << left << "" << "Are you sure you want perfrom this transaction ? ( Y / N ) : ";
		cin >> Acces;
		cout << endl;
		if (Acces == 'Y' || Acces == 'y') {
			Client.Deposit(Amount);
			cout << endl << setw(37) << left << "" << "Amount Deposited Successfully.\n\n";
			cout << setw(37) << left << "" << "New Balance Is: " << Client.AccountBalance;
		}
		else
		{
			cout << "\nOperation was cancelled.\n";
		}
	}
};


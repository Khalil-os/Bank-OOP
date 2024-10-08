#pragma once
#include <iomanip>
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "Global.h"
#include "clsInputValidate.h"

using namespace std;

class clsTransferScreen : protected clsScreen
{
private:

	static void _Print(clsBankClient Client) {
		cout << setw(37) << left << "" << "\t\tClient Card\n";
		cout << setw(37) << left << "" << "---------------------------------------\n";		
		cout << setw(37) << left << "" << "\tFullName   : " << Client.FullName << endl;		
		cout << setw(37) << left << "" << "\tAcc.Number : " << Client.AccountNumber << endl;
		cout << setw(37) << left << "" << "\tBalance    : " << Client.AccountBalance << endl;
		cout << setw(37) << left << "" << "---------------------------------------\n";
	}

	static string _ConvertTransferObjToLine(clsUser User, clsBankClient ClientFrom, clsBankClient ClientTo, float Amount, string seperatore = "#//#") {
		time_t now;
		struct tm* Date;
		time(&now);
		Date = localtime(&now);

		return  (clsDate::DateToString(clsDate()) + " - " + to_string(Date->tm_hour) + ":" + to_string(Date->tm_min) + ":" + to_string(Date->tm_sec) + seperatore + ClientFrom.AccountNumber + seperatore + ClientTo.AccountNumber + seperatore + to_string(Amount) + seperatore + to_string(ClientFrom.AccountBalance) + seperatore + to_string(ClientTo.AccountBalance) + seperatore + User.UserName);
	}

	static void AddLineInFile(string TransferLogLine) {
		fstream MyFile;
		MyFile.open("TransferLogs.txt", ios::out | ios::app);
		if (MyFile.is_open()) {
			MyFile << TransferLogLine << endl;
			MyFile.close();
		}
	}

public:

	static void ShowWithdrawScreen()
	{
		_DrawScreenHeader("    Transfer Screen");
		string AccountNumberFrom = "";
		string AccountNumberTo = "";
		cout << setw(37) << left << "" << "Enter Please Account Number To Transfer From : ";
		AccountNumberFrom = clsInputValidate::ReadString();
		cout << endl;
		while (!(clsBankClient::IsClientExist(AccountNumberFrom))) {
			cout << setw(37) << left << "" << "Your Account Number is NOT Found , Please enter another one : ";
			AccountNumberFrom = clsInputValidate::ReadString();
			cout << endl;
		}
		clsBankClient ClientFrom = clsBankClient::Find(AccountNumberFrom);
		cout << endl;
		_Print(ClientFrom);
		cout << endl;

		cout << setw(37) << left << "" << "Enter Please Account Number To Transfer To : ";
		AccountNumberTo = clsInputValidate::ReadString();
		cout << endl;
		while (!(clsBankClient::IsClientExist(AccountNumberTo))) {
			cout << setw(37) << left << "" << "Your Account Number is NOT Found , Please enter another one : ";
			AccountNumberTo = clsInputValidate::ReadString();
			cout << endl;
		}
		clsBankClient ClientTo = clsBankClient::Find(AccountNumberTo);
		cout << endl;
		_Print(ClientTo);
		cout << endl;

		float Amount;
		cout << "\n\n" << setw(37) << left << "" << "Please enter Transfer amount : ";
		cin >> Amount;
		cout << endl;
		while (Amount > ClientFrom.AccountBalance) {
			cout << endl << setw(37) << left << "" << "Amount Exceeds the balance, you can withdraw up to : " << ClientFrom.AccountBalance << endl;
			cout << setw(37) << left << "" << "Please enter another amount : ";
			cin >> Amount;
		}
		cout << endl << endl;
		char Acces;
		cout << setw(37) << left << "" << "Are you sure you want perfrom this Transfer ? ( Y / N ) : ";
		cin >> Acces;
		cout << endl;
		if (Acces == 'Y' || Acces == 'y') {
			ClientFrom.Withdraw(Amount);
			ClientTo.Deposit(Amount);
			cout << endl << setw(37) << left << "" << "Transfer Done Successfully.\n\n";
			_Print(ClientFrom);
			cout << endl;
			_Print(ClientTo);
			AddLineInFile(_ConvertTransferObjToLine(CurrentUser , ClientFrom , ClientTo , Amount));
		}
	}

};
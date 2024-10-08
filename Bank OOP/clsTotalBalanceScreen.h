#pragma once
#include <iomanip>
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsUtil.h"

using namespace std;

class clsTotalBalanceScreen : protected clsScreen
{
private:

	static void _PrintClientRecordBanlanceLine(clsBankClient Client, int& Number) {
		cout << "| " << setw(15) << left << Client.AccountNumber;
		cout << "| " << setw(40) << left << Client.FullName;
		cout << "| " << setw(12) << left << Client.AccountBalance;
		Number += Client.AccountBalance;
	}

public:

	static void ShowTotalBalancesScreen()
	{
		vector <clsBankClient> _vClients;
		_vClients = clsBankClient::GetClientsList();

		int Total = 0;
		cout << "\n\t\t\t\t\tBalances List (" << _vClients.size() << ") Client(s).";
		cout << "\n_______________________________________________________";
		cout << "_________________________________________\n" << endl;
		cout << "| " << left << setw(15) << "Accout Number";
		cout << "| " << left << setw(40) << "Client Name";
		cout << "| " << left << setw(12) << "Balance";
		cout << "\n_______________________________________________________";
		cout << "_________________________________________\n" << endl;
		if (_vClients.size() == 0)
			cout << "\t\t\t\tNo Clients Available In the System!";
		else{
			for (clsBankClient Client : _vClients) {
				_PrintClientRecordBanlanceLine(Client, Total);
				cout << endl;
			}
		}
		cout << "\n_______________________________________________________";
		cout << "_________________________________________\n" << endl;
		cout << "\t\t\t\t\tTotal Balances = " << Total << endl;
		cout << "\t\t\t\t( " << clsUtil::NumberToText(Total) << " )\n";
	}

};


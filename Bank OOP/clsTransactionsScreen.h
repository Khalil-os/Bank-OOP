#pragma once
#include <iomanip>
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalanceScreen.h"
#include "clsUser.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"

using namespace std;

class clsTransactionsScreen : protected clsScreen
{
private:

	static short _ReadTransactionsMenueOption() {
		cout << setw(37) << left << "" << "\tChoose what do you want to do ? [1 ato 6] : ";
		short Choose = clsInputValidate::ReadShortNumberBetween(1, 6, "\t\t\t\t\t\tEnter Number between 1 to 6 : ");
		return Choose;
	}

	enum enTransactionsMenueOptions{ 
		eDeposit = 1,
		eWithraw = 2,
		eTotalBalances = 3,
		eTransfer = 4,
		eTransferLog = 5,
		eMainMenue = 6
	};

	static void _ShowDepositScreen()
	{
		clsDepositScreen::ShowDepositScreen();
	}

	static void _ShowWithdrawScreen()
	{
		clsWithdrawScreen::ShowWithdrawScreen();
	}

	static void _ShowTotalBalancesScreen() {
		clsTotalBalanceScreen::ShowTotalBalancesScreen();
	}

	static void _ShowTransferScreen() {
		clsTransferScreen::ShowWithdrawScreen();
	}

	static void _ShowTransferLogScreen() {
		clsTransferLogScreen::ShowTransferLogScreen();
	}

	static void _GoBackToTransactionsMenue() {
		cout << endl << setw(37) << left << "" << "\tPress anu key To return to Transactions Menue ...";
		system("pause>0");
		ShowTransactionsMenue();
	}

	static void _PerfromTransactionsMenueOption(enTransactionsMenueOptions TransactionsMenueOptions) {
		switch (TransactionsMenueOptions)
		{
		case clsTransactionsScreen::eDeposit:
			system("cls");
			_ShowDepositScreen();
			_GoBackToTransactionsMenue();
			break;
		case clsTransactionsScreen::eWithraw:
			system("cls");
			_ShowWithdrawScreen();
			_GoBackToTransactionsMenue();
			break;
		case clsTransactionsScreen::eTotalBalances:
			system("cls");
			_ShowTotalBalancesScreen();
			_GoBackToTransactionsMenue();
			break;
		case clsTransactionsScreen::eTransfer:
			system("cls");
			_ShowTransferScreen();
			_GoBackToTransactionsMenue();
			break;
		case clsTransactionsScreen::eTransferLog:
			system("cls");
			_ShowTransferLogScreen();
			_GoBackToTransactionsMenue();
			break;
		case clsTransactionsScreen::eMainMenue:
			break;
		}
	}

public:

	static void ShowTransactionsMenue() {

		system("cls");
		if (!CheckAccessRights(clsUser::enPermessions::pTransactions))
		{
			return;
		}
		_DrawScreenHeader("    Transactions Screen");
		cout << setw(37) << left << "" << "====================================================\n";
		cout << setw(37) << left << "" << "\t\t" << "Transactions Menue Screen" << endl;
		cout << setw(37) << left << "" << "====================================================\n";
		cout << setw(37) << left << "" << "\t" << "[1] Deposit" << endl;
		cout << setw(37) << left << "" << "\t" << "[2] Withraw" << endl;
		cout << setw(37) << left << "" << "\t" << "[3] Total Balances" << endl;
		cout << setw(37) << left << "" << "\t" << "[4] Transfer" << endl;
		cout << setw(37) << left << "" << "\t" << "[5] Transfer Log" << endl;
		cout << setw(37) << left << "" << "\t" << "[6] Main Menue" << endl;
		cout << setw(37) << left << "" << "====================================================\n";
		_PerfromTransactionsMenueOption((enTransactionsMenueOptions)_ReadTransactionsMenueOption());
	}

};


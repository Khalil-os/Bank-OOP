#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdareRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"

using namespace std;

class clsCurrencyExchangeScreen : protected clsScreen
{
private:

	enum enCurrencyExChangeOptions {
		eCurrenciesList = 1,
		eFindCurrency = 2,
		eUpdateRate = 3,
		eCurrencyCalculator = 4,
		eMainMenue = 5
	};

	static short _ReadCurrencyExChangeOption() {
		cout << setw(37) << left << "" << "\tChoose what do you want to do ? [1 ato 5] : ";
		short Choose = clsInputValidate::ReadShortNumberBetween(1, 5, "\t\t\t\t\t\tEnter Number between 1 to 5 : ");
		return Choose;
	}

	static void _GoBackToCurrencyExchangeScreen() {
		cout << endl << setw(37) << left << "" << "Press anu key To return to Currency Exchage Menue ...";
		system("pause>0");
		ShowCurrencyExchangeMenue();
	}

	static void _ShowCurrenciesListScreen() {
		clsCurrenciesListScreen::ShowCurrenciesList();
	}

	static void _ShowFindCurrencyScreen() {
		clsFindCurrencyScreen::ShowFindClientScreen();
	}

	static void _ShowUpdateCurrencyScreen() {
		clsUpdareRateScreen::ShowUpdateRateScreen();
	}

	static void _ShowCurrencyCalcullator() {
		clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
	}

	static void _PerfromCurrencyExchangeMenueOption(enCurrencyExChangeOptions CurrencyExChangeOptions) {
		switch (CurrencyExChangeOptions)
		{
		case clsCurrencyExchangeScreen::eCurrenciesList:
			system("cls");
			_ShowCurrenciesListScreen();
			_GoBackToCurrencyExchangeScreen();
			break;
		case clsCurrencyExchangeScreen::eFindCurrency:
			system("cls");
			_ShowFindCurrencyScreen();
			_GoBackToCurrencyExchangeScreen();
			break;
		case clsCurrencyExchangeScreen::eUpdateRate:
			system("cls");
			_ShowUpdateCurrencyScreen();
			_GoBackToCurrencyExchangeScreen();
			break;
		case clsCurrencyExchangeScreen::eCurrencyCalculator:
			system("cls");
			_ShowCurrencyCalcullator();
			_GoBackToCurrencyExchangeScreen();
			break;
		case clsCurrencyExchangeScreen::eMainMenue:			
			break;
		}
	}

public:

	static void ShowCurrencyExchangeMenue() {

		system("cls");
		_DrawScreenHeader("Currency Exchange Main Screen");
		cout << setw(37) << left << "" << "====================================================\n";
		cout << setw(37) << left << "" << "\t\t" << "Currency Exchange Menue Screen" << endl;
		cout << setw(37) << left << "" << "====================================================\n";
		cout << setw(37) << left << "" << "\t" << "[1] List Currencies" << endl;
		cout << setw(37) << left << "" << "\t" << "[2] Find Currency" << endl;
		cout << setw(37) << left << "" << "\t" << "[3] Update Rate" << endl;
		cout << setw(37) << left << "" << "\t" << "[4] Currency Calculator" << endl;
		cout << setw(37) << left << "" << "\t" << "[5] Main Menue" << endl;
		cout << setw(37) << left << "" << "====================================================\n";
		_PerfromCurrencyExchangeMenueOption((enCurrencyExChangeOptions)_ReadCurrencyExChangeOption());
	}

};


#pragma once
#include <iostream>
#include <iomanip>
#include "clsCurrency.h"
#include "clsScreen.h"
#include <string>

using namespace std;

class clsCurrenciesListScreen : protected clsScreen
{
private:

    static void PrintCurrencyRecordLine(clsCurrency Currency) {
        cout << "| " << setw(40) << left << Currency.Country;
        cout << "| " << setw(5) << left << Currency.CurrencyCode;
        cout << "| " << setw(50) << left << Currency.CurrencyName;
        cout << "| " << setw(15) << left << Currency.Rate;
    }

public:

    static void ShowCurrenciesList() {
        vector <clsCurrency> _vCurrencies = clsCurrency::GetAllUSDRates();
        string Title = "     Currencies List Screen";
        string SubTitle = "       (" + to_string(_vCurrencies.size()) + ") Currency.";

        _DrawScreenHeader(Title, SubTitle);


        cout << "\n__________________________________________________________";
        cout << "____________________________________________________________\n" << endl;

        cout << "| " << left << setw(40) << "Country";
        cout << "| " << left << setw(5) << "Code";
        cout << "| " << left << setw(50) << "Name";
        cout << "| " << left << setw(15) << "Rate/(1$)";
        cout << "\n__________________________________________________________";
        cout << "____________________________________________________________\n" << endl;

        if (_vCurrencies.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else

            for (clsCurrency Currency : _vCurrencies)
            {

                PrintCurrencyRecordLine(Currency);
                cout << endl;
            }

        cout << "\n__________________________________________________________";
        cout << "____________________________________________________________\n" << endl;
    }

};


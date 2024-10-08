#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsCurrency.h"

using namespace std;

class clsUpdareRateScreen : protected clsScreen
{
private:

    static void _Print(clsCurrency Currency) {
        cout << setw(37) << left << "" << "\t\tCurrency Card\n";
        cout << setw(37) << left << "" << "---------------------------------------\n";
        cout << setw(37) << left << "" << "\tCountry     : " << Currency.Country << endl;
        cout << setw(37) << left << "" << "\tCode        : " << Currency.CurrencyCode << endl;
        cout << setw(37) << left << "" << "\tName        : " << Currency.CurrencyName << endl;
        cout << setw(37) << left << "" << "\tRate(1$) =  : " << Currency.Rate << endl;
        cout << setw(37) << left << "" << "---------------------------------------\n";
    }

public:

    static void ShowUpdateRateScreen() {
        _DrawScreenHeader("    Update Currency Screen");
        float NewRate;
        string CurrencyName = "";
        char Up;
        cout << setw(37) << left << "" << "Please Enter Currnecy Code : ";
        cin >> CurrencyName;
        cout << endl;
        clsCurrency Currency = clsCurrency::FindByCode(CurrencyName);
        cout << endl;
        while (!Currency.IsCurrencyExist()) {
            cout << setw(37) << left << "" << "This Currency is NOT Found :(\n";
            return;
        }
        _Print(Currency);
        cout << endl;
        cout << setw(37) << left << "" << "Are You want to Update the Rate of this Currency ( y / n ) : ";
        cin >> Up;
        cout << endl;
        if (Up == 'y' || Up == 'Y') {
            cout << setw(37) << left << "" << "Update Currency Rate:\n";
            cout << setw(37) << left << "" << "---------------------\n\n";
            cout << setw(37) << left << "" << "Enter New Rate : ";
            cin >> NewRate;
            cout << endl;
            Currency.UpdateRate(NewRate);
            cout << "\nCurrency Rate Update Successfully :)\n";
        }
    }

};


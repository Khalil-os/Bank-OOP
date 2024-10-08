#pragma once
#include <iomanip>
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"

using namespace std;

class clsFindCurrencyScreen : protected clsScreen
{
private:

    enum enFindByCodeOrByCountry {
        eFindByCode = 1,
        eFindByCountry = 2
    };

    static void _Print(clsCurrency Currency) {
        cout << setw(37) << left << "" << "\t\tCurrency Card\n";
        cout << setw(37) << left << "" << "---------------------------------------\n";
        cout << setw(37) << left << "" << "\tCountry     : " << Currency.Country << endl;
        cout << setw(37) << left << "" << "\tCode        : " << Currency.CurrencyCode << endl;
        cout << setw(37) << left << "" << "\tName        : " << Currency.CurrencyName << endl;
        cout << setw(37) << left << "" << "\tRate(1$) =  : " << Currency.Rate << endl;
        cout << setw(37) << left << "" << "---------------------------------------\n";
    }

    static short ReadFindByCodeOrByCountry() {
        short Choose;
        cout << setw(37) << left << "" << "Find By : [1] Code or [2] Country : ";
        Choose = clsInputValidate::ReadDblNumberBetween(1 , 2 , "\n\t\t\t\tEnter Please Number Between 1 and 2 : ");
        cout << endl;
        return Choose;
    }

    static clsCurrency Find(enFindByCodeOrByCountry FindCurrency) {

        string CurrencyName = "";
        switch (FindCurrency)
        {
        case clsFindCurrencyScreen::eFindByCode:
            cout << setw(37) << left << "" << "Please Enter Code Name : ";
            CurrencyName = clsInputValidate::ReadString();
            cout << endl;
            return clsCurrency::FindByCode(CurrencyName);
            break;
        case clsFindCurrencyScreen::eFindByCountry:
            cout << setw(37) << left << "" << "Please Enter Country Name : ";
            CurrencyName = clsInputValidate::ReadString();
            cout << endl;
            return clsCurrency::FindByCountry(CurrencyName);
            break;
        }
    }

public:

    static void ShowFindClientScreen() {

        _DrawScreenHeader("    Find Currency Screen");
        short CodeORCountry = ReadFindByCodeOrByCountry();
        cout << endl;
        clsCurrency Currency = Find((enFindByCodeOrByCountry)CodeORCountry);
        while (!Currency.IsCurrencyExist() ) {
            cout << setw(37) << left << "" << "This Currency is NOT Found :(\n";
            return;
        }
        cout << endl;
        _Print(Currency);
        cout << endl;
    }


};


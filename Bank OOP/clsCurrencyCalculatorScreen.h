#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsCurrency.h"

using namespace std;

class clsCurrencyCalculatorScreen : protected clsScreen
{
private:

    static void _Print(clsCurrency Currency , string Sentence) {
        cout << setw(37) << left << "" << "\t\t" << Sentence << "\n";
        cout << setw(37) << left << "" << "---------------------------------------\n";
        cout << setw(37) << left << "" << "\tCountry     : " << Currency.Country << endl;
        cout << setw(37) << left << "" << "\tCode        : " << Currency.CurrencyCode << endl;
        cout << setw(37) << left << "" << "\tName        : " << Currency.CurrencyName << endl;
        cout << setw(37) << left << "" << "\tRate(1$) =  : " << Currency.Rate << endl;
        cout << setw(37) << left << "" << "---------------------------------------\n";
    }

    static float ConverAmountToUSD(clsCurrency Currency, float Amount) {
        return Amount = Amount / Currency.Rate;
    }

    static void CouverAmountFromUSD(clsCurrency Currency, float& Amount) {
        Amount = Amount * Currency.Rate;
    }

public:

    static void ShowCurrencyCalculatorScreen() {
        string CurrencyCodeFrom = "";
        string CurrencyCodeTo = "";
        float Amount;
        float AmountAfterExchange;
        char Repete = 'n';

        cout << setw(37) << left << "" << "Please Enter Currency1 Code : ";
        cin >> CurrencyCodeFrom;
        cout << endl;
        clsCurrency CurrencyFrom = clsCurrency::FindByCode(CurrencyCodeFrom);
        while (!CurrencyFrom.IsCurrencyExist()) {
            cout << setw(37) << left << "" << "This Currency is NOT Found :(\n";
            return;
        }
        cout << setw(37) << left << "" << "Please Enter Currency2 Code : ";
        cin >> CurrencyCodeTo;
        cout << endl;
        clsCurrency CurrencyTo = clsCurrency::FindByCode(CurrencyCodeTo);
        while (!CurrencyTo.IsCurrencyExist()) {
            cout << setw(37) << left << "" << "This Currency is NOT Found :(\n";
            return;
        }
        cout << setw(37) << left << "" << "Enter Amount To Exchange : ";
        cin >> Amount;
        cout << endl;

        AmountAfterExchange = ConverAmountToUSD(CurrencyFrom, Amount);

        cout << endl;
        _Print(CurrencyFrom , "Convert From :");
        cout << endl;
        cout << setw(37) << left << "" << Amount << " " << CurrencyFrom.CurrencyCode << " = " << AmountAfterExchange << " " << "USD" << endl;
        cout << endl;
        if (CurrencyTo.CurrencyCode != "USD") {
            _Print(CurrencyTo,"To :");
            CouverAmountFromUSD(CurrencyTo,AmountAfterExchange);
            cout << endl;
            cout << setw(37) << left << "" << Amount << " " << CurrencyFrom.CurrencyCode << " = " << AmountAfterExchange << " " << CurrencyTo.CurrencyCode << endl;
            cout << endl;
        }
        cout << setw(37) << left << "" << "Do You Want to perform another Calculation ? ( y / n ) : ";
        cin >> Repete;
        cout << endl;
        if (Repete == 'y' || Repete == 'Y') {
            system("cls");
            ShowCurrencyCalculatorScreen();
        }
    }

};


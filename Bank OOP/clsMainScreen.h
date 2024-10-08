#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsShowClientsList.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsers.h"
#include "Global.h"
#include "clsLoginRegister.h"
#include "clsCurrencyExchangeScreen.h"

using namespace std;

class clsMainScreen : protected clsScreen
{
private:

    enum enMainMenueOptions {
        eShowClientList = 1,
        eAddNewClient = 2,
        eDeleteClient = 3,
        eUpdateClinetInfo = 4,
        eFindClient = 5,
        eTransactions = 6,
        eManageUsers = 7,
        eLoginRegister = 8,
        eCurrencyExchange = 9,
        eLogout = 10, 
        eExit = 11
    };

    static short _ReadMainMenueOption() {
        cout << setw(37) << left << "" << "\tChoose what do you want to do ? [1 ato 11] : ";
        short Choose = clsInputValidate::ReadShortNumberBetween(1, 11, "\t\t\t\t\t\tEnter Number between 1 to 11 : ");
        return Choose;
    }

    static void _GoBackToMainMenue() {
        cout << endl << setw(37) << left << "" << "\tPress anu key To return to Main Menue ...";
        system("pause>0");
        ShowMainMenue();
    }

    static void _ShowAllClientsScreen()
    {
        clsShowClientsList::ShowClientsList();
    }

    static void _ShowAddNewClientsScreen()
    {
        clsAddNewClientScreen::ShowAddNewClientScreen();
    }

    static void _ShowDeleteClientScreen()
    {
        clsDeleteClientScreen::ShowDeleteClientScreen();
    }

    static void _ShowUpdateClientScreen()
    {
        clsUpdateClientScreen::UpdateClient();
    }

    static void _ShowFindClientScreen()
    {
        clsFindClientScreen::ShowFindClientScreen();
    }

    static void _ShowTransactionsMenue()
    {
        clsTransactionsScreen::ShowTransactionsMenue();
    }

    static void _ShowManageUsersMenue()
    {
        clsManageUsers::ShowManageUsersMenue();
    }

    static void _ShowLoginRegisterScreen() {
        clsLoginRegister::ShowLoginRegisterScreen();
    }

    static void _ShowCurrencyExchangeScreen() {
        clsCurrencyExchangeScreen::ShowCurrencyExchangeMenue();
    }

    static void _LogOut()
    {
        CurrentUser = clsUser::Find("", "");
    }

    static void _PerfromMainMenueOption(enMainMenueOptions MainMenueOption) {
        switch (MainMenueOption)
        {
        case clsMainScreen::eShowClientList:
            system("cls");
            _ShowAllClientsScreen();
            _GoBackToMainMenue();
            break;
        case clsMainScreen::eAddNewClient:
            system("cls");
            _ShowAddNewClientsScreen();
            _GoBackToMainMenue();
            break;
        case clsMainScreen::eDeleteClient:
            system("cls");
            _ShowDeleteClientScreen();
            _GoBackToMainMenue();
            break;
        case clsMainScreen::eUpdateClinetInfo:
            system("cls");
            _ShowUpdateClientScreen();
            _GoBackToMainMenue();
            break;
        case clsMainScreen::eFindClient:
            system("cls");
            _ShowFindClientScreen();
            _GoBackToMainMenue();
            break;
        case clsMainScreen::eTransactions:
            system("cls");
            _ShowTransactionsMenue();
            _GoBackToMainMenue();
            break;
        case clsMainScreen::eManageUsers:
            system("cls");
            _ShowManageUsersMenue();
            _GoBackToMainMenue();
            break;
        case clsMainScreen::eLoginRegister:
            system("cls");
            _ShowLoginRegisterScreen();
            _GoBackToMainMenue();
            break;
        case clsMainScreen::eCurrencyExchange:
            system("cls");
            _ShowCurrencyExchangeScreen();
            _GoBackToMainMenue();
            break;
        case clsMainScreen::eLogout:
            system("cls");
            _LogOut();
            break;
        case clsMainScreen::eExit:
            ON = false;
            break;
        default:
            break;
        }
    }

public:

	static void ShowMainMenue() {

        system("cls");
        _DrawScreenHeader("\tMain Screen");
        cout << setw(37) << left << "" << "====================================================\n";
        cout << setw(37) << left << "" << "\t\t\t" << "Main Menue Screen" << endl;
        cout << setw(37) << left << "" << "====================================================\n";
        cout << setw(37) << left << "" << "\t" << "[1] Show Client List" << endl;
        cout << setw(37) << left << "" << "\t" << "[2] Add New Client" << endl;
        cout << setw(37) << left << "" << "\t" << "[3] Delete Client" << endl;
        cout << setw(37) << left << "" << "\t" << "[4] Update Client Info" << endl;
        cout << setw(37) << left << "" << "\t" << "[5] Find Client" << endl;
        cout << setw(37) << left << "" << "\t" << "[6] Transactions" << endl;
        cout << setw(37) << left << "" << "\t" << "[7] Manage Users" << endl;
        cout << setw(37) << left << "" << "\t" << "[8] Login Register" << endl;
        cout << setw(37) << left << "" << "\t" << "[9] Currency Exchange" << endl;
        cout << setw(37) << left << "" << "\t" << "[10] Logout" << endl;
        cout << setw(37) << left << "" << "\t" << "[11] Exit" << endl;
        cout << setw(37) << left << "" << "====================================================\n";
        _PerfromMainMenueOption((enMainMenueOptions)_ReadMainMenueOption());
	}

};
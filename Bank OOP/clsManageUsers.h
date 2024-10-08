#pragma once
#include <iomanip>
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUsersListScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsFindUserScreen.h"
#include "clsUser.h"

using namespace std;

class clsManageUsers : protected clsScreen
{
private:

    enum enManageUsersMenueOptions {
        eListUsers = 1,
        eAddNewUser = 2,
        eDeleteUser = 3,
        eUpdateUser = 4,
        eFindUser = 5,
        eMainMenue = 6
    };

    static short _ReadManageUsersMenueOption() {
        cout << setw(37) << left << "" << "\tChoose what do you want to do ? [1 ato 6] : ";
        short Choose = clsInputValidate::ReadShortNumberBetween(1, 6, "\t\t\t\t\t\tEnter Number between 1 to 6 : ");
        return Choose;
    }

    static void _GoBackToManageUsersMenue() {
        cout << endl << setw(37) << left << "" << "\tPress anu key To return to Main Menue ...";
        system("pause>0");
        ShowManageUsersMenue();
    }

    static void _ShowAllUsersScreen()
    {
        clsUsersListScreen::ShowClientsList();
    }

    static void _ShowAddNewUserScreen()
    {
        clsAddNewUserScreen::ShowAddNewUserScreen();
    }

    static void _ShowDeleteUserScreen()
    {
        clsDeleteUserScreen::ShowDeleteUserScreen();
    }

    static void _ShowUpdateUserScreen()
    {
        clsUpdateUserScreen::UpdateUser();
    }

    static void _ShowFindUserScreen()
    {
        clsFindUserScreen::ShowFindUserScreen();
    }

    static void _PerfromManageUsersMenueOption(enManageUsersMenueOptions ManageUsersMenueOption) {
        switch (ManageUsersMenueOption)
        {
        case clsManageUsers::eListUsers:
            system("cls");
            _ShowAllUsersScreen();
            _GoBackToManageUsersMenue();
            break;
        case clsManageUsers::eAddNewUser:
            system("cls");
            _ShowAddNewUserScreen();
            _GoBackToManageUsersMenue();
            break;
        case clsManageUsers::eDeleteUser:
            system("cls");
            _ShowDeleteUserScreen();
            _GoBackToManageUsersMenue();
            break;
        case clsManageUsers::eUpdateUser:
            system("cls");
            _ShowUpdateUserScreen();
            _GoBackToManageUsersMenue();
            break;
        case clsManageUsers::eFindUser:
            system("cls");
            _ShowFindUserScreen();
            _GoBackToManageUsersMenue();
            break;
        case clsManageUsers::eMainMenue:
            break;
        default:
            break;
        }
    }

public:

    static void ShowManageUsersMenue() {

        system("cls");
        if (!CheckAccessRights(clsUser::enPermessions::pManageUsers))
        {
            return;
        }
        _DrawScreenHeader("     Manage Users Screen");
        cout << setw(37) << left << "" << "====================================================\n";
        cout << setw(37) << left << "" << "\t\t   " << "Manage Users Menue Screen" << endl;
        cout << setw(37) << left << "" << "====================================================\n";
        cout << setw(37) << left << "" << "\t" << "[1] Show Users List" << endl;
        cout << setw(37) << left << "" << "\t" << "[2] Add New User" << endl;
        cout << setw(37) << left << "" << "\t" << "[3] Delete User" << endl;
        cout << setw(37) << left << "" << "\t" << "[4] Update User Info" << endl;
        cout << setw(37) << left << "" << "\t" << "[5] Find User" << endl;
        cout << setw(37) << left << "" << "\t" << "[6] Main Menue" << endl;
        cout << setw(37) << left << "" << "====================================================\n";
        _PerfromManageUsersMenueOption((enManageUsersMenueOptions)_ReadManageUsersMenueOption());
    }

};


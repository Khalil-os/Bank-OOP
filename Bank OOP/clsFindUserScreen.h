#pragma once
#include <iomanip>
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

using namespace std;

class clsFindUserScreen : protected clsScreen
{
private:

    static void _Print(clsUser User) {
        cout << setw(37) << left << "" << "\t\tClient Card\n";
        cout << setw(37) << left << "" << "------------------------------------------\n";
        cout << setw(37) << left << "" << "\tFirstName  : " << User.FirstName << endl;
        cout << setw(37) << left << "" << "\tLastName   : " << User.LastName << endl;
        cout << setw(37) << left << "" << "\tFullName   : " << User.FullName << endl;
        cout << setw(37) << left << "" << "\tEmail      : " << User.Email << endl;
        cout << setw(37) << left << "" << "\tPhone      : " << User.Phone << endl;
        cout << setw(37) << left << "" << "\tAcc.Number : " << User.UserName << endl;
        cout << setw(37) << left << "" << "\tPassword   : " << User.Password << endl;
        cout << setw(37) << left << "" << "\tBalance    : " << User.Pertmissions << endl;
        cout << setw(37) << left << "" << "------------------------------------------\n";
    }

public:

    static void ShowFindUserScreen() {
        _DrawScreenHeader("    Find User Screen");
        string AccountNumber = "";
        cout << setw(37) << left << "" << "Enter Please Your UserName : ";
        AccountNumber = clsInputValidate::ReadString();
        cout << endl;
        while (!(clsUser::IsUserExist(AccountNumber))) {
            cout << setw(37) << left << "" << "Your Account Number is NOT Found , Please enter another one : ";
            AccountNumber = clsInputValidate::ReadString();
            cout << endl;
        }
        clsUser User = clsUser::Find(AccountNumber);
        cout << endl;
        _Print(User);
        cout << endl;
    }
};
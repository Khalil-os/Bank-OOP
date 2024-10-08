#pragma once
#include <iomanip>
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

using namespace std;

class clsDeleteUserScreen : protected clsScreen
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

    static void ShowDeleteUserScreen() {
        _DrawScreenHeader("    Delete User Screen");
        string AccountNumber = "";
        cout << setw(37) << left << "" << "Enter Please Your UserName : ";
        AccountNumber = clsInputValidate::ReadString();
        cout << endl;
        while (!clsUser::IsUserExist(AccountNumber)) {
            cout << setw(37) << left << "" << "Your Account Number is NOT Found , Please enter another one : ";
            AccountNumber = clsInputValidate::ReadString();
            cout << endl;
        }
        clsUser User = clsUser::Find(AccountNumber);
        cout << endl;
        _Print(User);
        cout << endl;
        char Acces;
        cout << setw(37) << left << "" << "Do you want realy to Delete Your Account ( Y / N ) ; ";
        cin >> Acces;
        cout << endl;
        if (Acces == 'Y' || Acces == 'y')
        {
            if (User.Delete()) {
                cout << setw(37) << left << "" << "User Deleted Successfully :)\n\n";
                _Print(User);
            }
        }
    }

};
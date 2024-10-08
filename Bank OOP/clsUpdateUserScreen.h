#pragma once
#include <iomanip>
#include <iostream>
#include "clsUser.h"
#include "clsScreen.h"
#include "clsInputValidate.h"


class clsUpdateUserScreen : protected clsScreen
{
private:

    static void ReadUserInfo(clsUser& User) {
        cout << setw(37) << left << "" << "Enter FirstName : ";
        User.FirstName = clsInputValidate::ReadString();
        cout << endl;
        cout << setw(37) << left << "" << "Enter LastName : ";
        User.LastName = clsInputValidate::ReadString();
        cout << endl;
        cout << setw(37) << left << "" << "Enter Email : ";
        User.Email = clsInputValidate::ReadString();
        cout << endl;
        cout << setw(37) << left << "" << "Enter Phone : ";
        User.Phone = clsInputValidate::ReadString();
        cout << endl;
        cout << setw(37) << left << "" << "Enter Password : ";
        User.Password = clsInputValidate::ReadString();
        cout << endl;
        User.Pertmissions = _ReadPermissionsToSet();
        cout << endl;
    }

    static int _ReadPermissionsToSet() {
        int Permissions = 0;
        char Answer = 'n';
        cout << setw(37) << left << "" << "Do you want to give full access ( y / n ) : ";
        cin >> Answer;
        cout << endl;
        if (Answer == 'y' || Answer == 'Y')
            return -1;
        cout << setw(37) << left << "" << "Do you want to give access to : " << endl << endl;
        cout << setw(37) << left << "" << "Show Client List ( y / n ) : ";
        cin >> Answer;
        cout << endl;
        if (Answer == 'y' || Answer == 'Y')
            Permissions += clsUser::enPermessions::pShowClientList;
        cout << setw(37) << left << "" << "Add New Client ( y / n ) : ";
        cin >> Answer;
        cout << endl;
        if (Answer == 'y' || Answer == 'Y')
            Permissions += clsUser::enPermessions::pAddNewClient;
        cout << setw(37) << left << "" << "Delete Client ( y / n ) : ";
        cin >> Answer;
        cout << endl;
        if (Answer == 'y' || Answer == 'Y')
            Permissions += clsUser::enPermessions::pDeleteClient;
        cout << setw(37) << left << "" << "Update Client ( y / n ) : ";
        cin >> Answer;
        cout << endl;
        if (Answer == 'y' || Answer == 'Y')
            Permissions += clsUser::enPermessions::pUpdateClinetInfo;
        cout << setw(37) << left << "" << "Find Client ( y / n ) : ";
        cin >> Answer;
        cout << endl;
        if (Answer == 'y' || Answer == 'Y')
            Permissions += clsUser::enPermessions::pFindClient;
        cout << setw(37) << left << "" << "Transactions ( y / n ) : ";
        cin >> Answer;
        cout << endl;
        if (Answer == 'y' || Answer == 'Y')
            Permissions += clsUser::enPermessions::pTransactions;
        cout << setw(37) << left << "" << "Maneger Users ( y / n ) : ";
        cin >> Answer;
        cout << endl;
        if (Answer == 'y' || Answer == 'Y')
            Permissions += clsUser::enPermessions::pManageUsers;
        cout << setw(37) << left << "" << "Login Register ( y / n ) : ";
        cin >> Answer;
        cout << endl;
        if (Answer == 'y' || Answer == 'Y')
            Permissions += clsUser::enPermessions::pLoginRegister;
        return Permissions;
    }

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

    static void UpdateUser() {
        _DrawScreenHeader("    Update User Screen");
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
        char Acces;
        cout << setw(37) << left << "" << "Do you want realy to Update Your Account ( Y / N ) ; ";
        cin >> Acces;
        cout << endl;
        if (Acces == 'Y' || Acces == 'y')
        {
            ReadUserInfo(User);

            clsUser::enSaveResults SaveResult;
            SaveResult = User.Save();
            switch (SaveResult)
            {
            case clsUser::svFaildEmptyObject:
                cout << setw(37) << left << "" << "Error Account NOT Updated because is Empty !\n";
                break;
            case clsUser::svSucceded:
                cout << setw(37) << left << "" << "Account Updated Successfuly :)\n\n";
                _Print(User);
                break;
            }
        }
    }
};
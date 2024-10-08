#pragma once
#include <iomanip>
#include <iostream>
#include "clsUser.h"
#include "clsInputValidate.h"
#include "clsScreen.h"

using namespace std;

class clsAddNewUserScreen : protected clsScreen
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
        {
            Permissions += clsUser::enPermessions::pShowClientList;
        }
        cout << setw(37) << left << "" << "Add New Client ( y / n ) : ";
        cin >> Answer;
        cout << endl;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermessions::pAddNewClient;
        }
        cout << setw(37) << left << "" << "Delete Client ( y / n ) : ";
        cin >> Answer;
        cout << endl;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermessions::pDeleteClient;
        }
        cout << setw(37) << left << "" << "Update Client ( y / n ) : ";
        cin >> Answer;
        cout << endl;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermessions::pUpdateClinetInfo;
        }
        cout << setw(37) << left << "" << "Find Client ( y / n ) : ";
        cin >> Answer;
        cout << endl;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermessions::pFindClient;
        }
        cout << setw(37) << left << "" << "Transactions ( y / n ) : ";
        cin >> Answer;
        cout << endl;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermessions::pTransactions;
        }
        cout << setw(37) << left << "" << "Maneger Users ( y / n ) : ";
        cin >> Answer;
        cout << endl;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermessions::pManageUsers;
        }
        cout << setw(37) << left << "" << "Login Register ( y / n ) : ";
        cin >> Answer;
        cout << endl;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermessions::pLoginRegister;
        }
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

    static void ShowAddNewUserScreen() {
        _DrawScreenHeader("    Add New User Screen");
        string UserName = "";
        cout << setw(37) << left << "" << "Enter Please Your UserName : ";
        UserName = clsInputValidate::ReadString();
        cout << endl;
        while (clsUser::IsUserExist(UserName)) {
            cout << setw(37) << left << "" << "Your UserName is Aready Used , Please enter another one : ";
            UserName = clsInputValidate::ReadString();
            cout << endl;
        }
        clsUser User = clsUser::GetAddNewClientObject(UserName);
        cout << endl;
        char Acces;
        cout << setw(37) << left << "" << "Do you want realy to Add Your Account ( Y / N ) ; ";
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
                cout << setw(37) << left << "" << "Error Account NOT Added because is Empty !\n";
                break;
            case clsUser::svSucceded:
                cout << setw(37) << left << "" << "Account Added Successfuly :)\n\n";
                _Print(User);
                break;
            case clsUser::svFaildAccountNumberExists:
                cout << setw(37) << left << "" << "Error account was not saved because UserName is used!\n";
                break;
            }
        }
    }
};
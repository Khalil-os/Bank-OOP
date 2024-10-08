#pragma once
#include <iomanip>
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"


class clsUpdateClientScreen : protected clsScreen
{
private:

    static void ReadClientInfo(clsBankClient& Client) {
        cout << setw(37) << left << "" << "Enter FirstName : ";
        Client.FirstName = clsInputValidate::ReadString();
        cout << endl;
        cout << setw(37) << left << "" << "Enter LastName : ";
        Client.LastName = clsInputValidate::ReadString();
        cout << endl;
        cout << setw(37) << left << "" << "Enter Email : ";
        Client.Email = clsInputValidate::ReadString();
        cout << endl;
        cout << setw(37) << left << "" << "Enter Phone : ";
        Client.Phone = clsInputValidate::ReadString();
        cout << endl;
        cout << setw(37) << left << "" << "Enter PinCode : ";
        Client.PinCode = clsInputValidate::ReadString();
        cout << endl;
        cout << setw(37) << left << "" << "Enter Account Balance : ";
        Client.AccountBalance = clsInputValidate::ReadFloatNumber();
        cout << endl;
    }

    static void _Print(clsBankClient Client) {
        cout << setw(37) << left << "" << "\t\tClient Card\n";
        cout << setw(37) << left << "" << "---------------------------------------\n";
        cout << setw(37) << left << "" << "\tFirstName  : " << Client.FirstName << endl;
        cout << setw(37) << left << "" << "\tLastName   : " << Client.LastName << endl;
        cout << setw(37) << left << "" << "\tFullName   : " << Client.FullName << endl;
        cout << setw(37) << left << "" << "\tEmail      : " << Client.Email << endl;
        cout << setw(37) << left << "" << "\tPhone      : " << Client.Phone << endl;
        cout << setw(37) << left << "" << "\tAcc.Number : " << Client.AccountNumber << endl;
        cout << setw(37) << left << "" << "\tPassword   : " << Client.PinCode << endl;
        cout << setw(37) << left << "" << "\tBalance    : " << Client.AccountBalance << endl;
        cout << setw(37) << left << "" << "---------------------------------------\n";
    }

public:

    static void UpdateClient() {
        if (!CheckAccessRights(clsUser::enPermessions::pUpdateClinetInfo))
        {
            return;
        }
        _DrawScreenHeader("    Update Client Screen");
        string AccountNumber = "";
        cout << setw(37) << left << "" << "Enter Please Your Account Number : ";
        AccountNumber = clsInputValidate::ReadString();
        cout << endl;
        while (!(clsBankClient::IsClientExist(AccountNumber))) {
            cout << setw(37) << left << "" << "Your Account Number is NOT Found , Please enter another one : ";
            AccountNumber = clsInputValidate::ReadString();
            cout << endl;
        }
        clsBankClient Client = clsBankClient::Find(AccountNumber);
        cout << endl;
        _Print(Client);
        cout << endl;
        char Acces;
        cout << setw(37) << left << "" << "Do you want realy to Update Your Account ( Y / N ) ; ";
        cin >> Acces;
        cout << endl;
        if (Acces == 'Y' || Acces == 'y')
        {
            ReadClientInfo(Client);

            clsBankClient::enSaveResults SaveResult;
            SaveResult = Client.Save();
            switch (SaveResult)
            {
            case clsBankClient::svFaildEmptyObject:
                cout << setw(37) << left << "" << "Error Account NOT Updated because is Empty !\n";
                break;
            case clsBankClient::svSucceded:
                cout << setw(37) << left << "" << "Account Updated Successfuly :)\n\n";
                _Print(Client);
                break;
            }
        }
    }

};


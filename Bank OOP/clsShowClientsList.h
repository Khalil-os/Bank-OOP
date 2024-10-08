#pragma once
#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsScreen.h"
#include <string>

using namespace std;

class clsShowClientsList : protected clsScreen
{
private:

    static void PrintClientRecordLine(clsBankClient Client) {
        cout << "| " << setw(15) << left << Client.AccountNumber;
        cout << "| " << setw(20) << left << Client.FullName;
        cout << "| " << setw(15) << left << Client.Phone;
        cout << "| " << setw(25) << left << Client.Email;
        cout << "| " << setw(15) << left << Client.PinCode;
        cout << "| " << setw(15) << left << Client.AccountBalance;
    }

public:

    static void ShowClientsList() {
        if (!CheckAccessRights(clsUser::enPermessions::pShowClientList))
        {
            return;
        }
        vector <clsBankClient> vClients = clsBankClient::GetClientsList();
        string Title = "     Client List Screen";
        string SubTitle = "       (" + to_string(vClients.size()) + ") Client(s).";

        _DrawScreenHeader(Title, SubTitle);


        cout << "\n_______________________________________________________";
        cout << "_________________________________________________________\n" << endl;

        cout << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(20) << "Client Name";
        cout << "| " << left << setw(15) << "Phone";
        cout << "| " << left << setw(25) << "Email";
        cout << "| " << left << setw(15) << "Pin Code";
        cout << "| " << left << setw(15) << "Balance";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________________________\n" << endl;

        if (vClients.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else

            for (clsBankClient Client : vClients)
            {

                PrintClientRecordLine(Client);
                cout << endl;
            }

        cout << "\n_______________________________________________________";
        cout << "_________________________________________________________\n" << endl;
    }

};


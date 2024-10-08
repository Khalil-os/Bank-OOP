#pragma once
#include <iostream>
#include <iomanip>
#include "clsUser.h"
#include "clsScreen.h"
#include <string>

using namespace std;

class clsUsersListScreen : protected clsScreen
{
private:
    static void PrintUserRecordLine(clsUser User) {
        cout << "| " << setw(15) << left << User.UserName;
        cout << "| " << setw(20) << left << User.FullName;
        cout << "| " << setw(15) << left << User.Phone;
        cout << "| " << setw(25) << left << User.Email;
        cout << "| " << setw(15) << left << User.Password;
        cout << "| " << setw(15) << left << User.Pertmissions;
    }
public:
    static void ShowClientsList() {
        vector <clsUser> _vUsers = clsUser::GetClientsList();
        string Title = "     Users List Screen";
        string SubTitle = "       (" + to_string(_vUsers.size()) + ") User(s).";

        _DrawScreenHeader(Title, SubTitle);


        cout << "\n__________________________________________________________";
        cout << "____________________________________________________________\n" << endl;

        cout << "| " << left << setw(15) << "UserName";
        cout << "| " << left << setw(20) << "Full Name";
        cout << "| " << left << setw(15) << "Phone";
        cout << "| " << left << setw(25) << "Email";
        cout << "| " << left << setw(15) << "Password";
        cout << "| " << left << setw(15) << "Permissions";
        cout << "\n__________________________________________________________";
        cout << "____________________________________________________________\n" << endl;

        if (_vUsers.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else

            for (clsUser User : _vUsers)
            {

                PrintUserRecordLine(User);
                cout << endl;
            }

        cout << "\n__________________________________________________________";
        cout << "____________________________________________________________\n" << endl;
    }
};


#pragma once
#include <iomanip>
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"
#include "clsMainScreen.h"
#include "Global.h"
#include "clsLoginRegister.h"

using namespace std;

class clsLoginScreen : protected clsScreen
{
public:

	static bool ShowLoginScreen() {
		bool LoginFaild = false;
		short NumberOfLoginFaild = 0;
		system("cls");
		_DrawScreenHeader("      Login Screen");
		string UserName;
		string Password;
		do {

			if (LoginFaild) {
				NumberOfLoginFaild++;
				cout << setw(37) << left << "" << "Invalaid UserName/Password !\n";
				cout << setw(37) << left << "" << "You Have " << 3 - NumberOfLoginFaild << " Trials to Login.\n\n";
			}
			if (NumberOfLoginFaild == 3) {
				cout << setw(37) << left << "" << "Your are Locked after 3 faild trails \n\n";
				return false;
			}
			cout << setw(37) << left << "" << "Enter UserName : ";
			UserName = clsInputValidate::ReadString();
			cout << endl;
			cout << setw(37) << left << "" << "Enter Password : ";
			Password = clsInputValidate::ReadString();
			cout << endl;
			CurrentUser = clsUser::Find(UserName, Password);
			LoginFaild = CurrentUser.IsEmpty();
			
		}while (LoginFaild);
		clsLoginRegister::RegisterLogin();
		clsMainScreen::ShowMainMenue();
	}
};


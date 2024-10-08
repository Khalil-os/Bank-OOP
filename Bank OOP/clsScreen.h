#pragma once
#include <iostream>
#include <iomanip>
#include "clsUser.h"
#include "Global.h"
#include "clsDate.h"

using namespace std;

class clsScreen
{
protected:
	static void _DrawScreenHeader(string Title, string SubTitle = "") {
		cout << "\t\t\t\t\t   ______________________________________" << endl;
		cout << "\n\t\t\t\t\t\t" << Title << endl;
		if (SubTitle != "")
			cout << "\t\t\t\t\t\t" << SubTitle << endl;
		cout << "\n\t\t\t\t\t   ______________________________________" << endl << endl;
		cout << "\t\t\t\t\t   User: " << CurrentUser.UserName << endl;
		cout << "\t\t\t\t\t   Date: " << clsDate::DateToString(clsDate());
		cout << endl << endl;
	}
	static bool CheckAccessRights(clsUser::enPermessions Permission) {
		if(!CurrentUser.CheckAccessPermission(Permission))
		{
			system("cls");
			cout << setw(37) << left << "" << "----------------------------------------------------\n";
			cout << setw(37) << left << "" << "\t\tAccess Denied," << endl;
			cout << setw(37) << left << "" << "\t\tYou don't have Permission to do this," << endl;
			cout << setw(37) << left << "" << "\t\tPlease Contact Your Admin" << endl;
			cout << setw(37) << left << "" << "----------------------------------------------------\n";
			return false;
		}
		else {
			return true;
		}
	}
};


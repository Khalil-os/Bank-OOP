#pragma once
#include <iostream>
#include <fstream>
#include "clsBankClient.h"
#include "clsUser.h"
#include "clsDate.h"
#include <string>
#include "Global.h"
#include "clsScreen.h"

using namespace std;

class clsTransferRegister : protected clsScreen
{
private:

	string _Date;

	string _UserName;

	string _Password;

	int _Permissions;

	static string _ConvertTransferObjToLine(clsUser User,clsBankClient ClientFrom,clsBankClient ClientTo,float Amount,string seperatore="#//#") {
		time_t now;
		struct tm* Date;
		time(&now);
		Date = localtime(&now);

		return  (clsDate::DateToString(clsDate()) + " - " + to_string(Date->tm_hour) + ":" + to_string(Date->tm_min) + ":" + to_string(Date->tm_sec) + seperatore + ClientFrom.AccountNumber + seperatore + ClientTo.AccountNumber + seperatore + to_string(Amount) + seperatore + to_string(ClientFrom.AccountBalance) + seperatore + to_string(ClientTo.AccountBalance) + seperatore + User.UserName);
	}

	static void AddLineInFile(string LoginRegisterLine) {
		fstream MyFile;
		MyFile.open("TransferRegister.txt", ios::out | ios::app);
		if (MyFile.is_open()) {
			MyFile << LoginRegisterLine << endl;
			MyFile.close();
		}
	}

	static void PrintloginRecordLine(clsTransferRegister LoginRegister) {
		cout << "| " << setw(35) << left << LoginRegister.GetDate();
		cout << "| " << setw(30) << left << LoginRegister.GetUserName();
		cout << "| " << setw(25) << left << LoginRegister.GetPassword();
		cout << "| " << setw(20) << left << LoginRegister.GetPermissions();
	}

	static clsTransferRegister _ConvertLineToLoginObj(string sentence, string seperatore = "#//#") {
		vector <string> vSentence;
		vSentence = clsString::Split(sentence, seperatore);

		clsLoginRegister LoginRegister(vSentence.at(0), vSentence.at(1), vSentence.at(2), stoi(vSentence.at(3)));
		return LoginRegister;
	}

	static vector <clsTransferRegister> _LoadLoginRegisterDateFromFile() {
		fstream MyFile;
		vector <clsLoginRegister> _vLoginRegisters;
		MyFile.open("LoginRegister.txt", ios::in);
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				if (!Line.empty()) {

					clsLoginRegister User = _ConvertLineToLoginObj(Line);
					_vLoginRegisters.push_back(User);

				}
			}
			MyFile.close();
		}
		return _vLoginRegisters;
	}

public:

	clsTransferRegister(string Date, string UserName, string Password, int Permissions) {
		_Date = Date;
		_UserName = UserName;
		_Password = Password;
		_Permissions = Permissions;
	}

	static void RegisterLogin() {

		AddLineInFile(_ConvertLoginUserObjToLine(CurrentUser));

	}

	string GetDate() {
		return _Date;
	}
	string GetUserName() {
		return _UserName;
	}
	string GetPassword() {
		return _Password;
	}
	int GetPermissions() {
		return _Permissions;
	}

	static void ShowLoginRegisterScreen() {

		if (!CheckAccessRights(clsUser::enPermessions::pLoginRegister)) {
			return;
		}
		vector <clsLoginRegister> _vLoginRegisters = _LoadLoginRegisterDateFromFile();
		string Title = "     Login Register List Screen";
		string SubTitle = "       (" + to_string(_vLoginRegisters.size()) + ") Record(s).";

		_DrawScreenHeader(Title, SubTitle);


		cout << "\n__________________________________________________________";
		cout << "____________________________________________________________\n" << endl;

		cout << "| " << left << setw(35) << "Date/Time";
		cout << "| " << left << setw(30) << "UserName";
		cout << "| " << left << setw(25) << "Password";
		cout << "| " << left << setw(20) << "Permissions";
		cout << "\n__________________________________________________________";
		cout << "____________________________________________________________\n" << endl;

		if (_vLoginRegisters.size() == 0)
			cout << "\t\t\t\tNo Record Available In the System!";
		else

			for (clsLoginRegister LoginRegister : _vLoginRegisters)
			{

				PrintloginRecordLine(LoginRegister);
				cout << endl;
			}

		cout << "\n__________________________________________________________";
		cout << "____________________________________________________________\n" << endl;
	}

};
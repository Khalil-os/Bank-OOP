#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include "clsString.h"
#include "clsPerson.h"
#include <string>
#include "clsUtil.h"

using namespace std;

class clsUser : public clsPerson
{
private:

	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;

	string _UserName;
	string _Password;
	int _Permissions;
	bool _MarkedForDelete = false;
	 
	static clsUser _ConvertLineToUserObj(string sentence, string seperatore = "#//#") {
		vector <string> vSentence;
		vSentence = clsString::Split(sentence, seperatore);

		clsUser User(enMode::UpdateMode, vSentence.at(0), vSentence.at(1), vSentence.at(2), vSentence.at(3), vSentence.at(4), 
			clsUtil::DecryptText(vSentence.at(5)), stof(vSentence.at(6)));
		return User;
	}
	static string _ConvertUserObjToLine(clsUser User, string seperatore = "#//#") {
		return  (User.FirstName + seperatore + User.LastName + seperatore + User.Email + seperatore + User.Phone + seperatore + User.UserName + seperatore + clsUtil::EncryptText(User.Password) + seperatore + to_string(User.Pertmissions));
	}
	static clsUser _GetEmptyUserObj() {
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}
	static vector <clsUser> _LoadUsersDateFromFile() {
		fstream MyFile;
		vector <clsUser> _vUsers;
		MyFile.open("Users.txt", ios::in);
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				if (!Line.empty()) {

					clsUser User = _ConvertLineToUserObj(Line);
					_vUsers.push_back(User);

				}
			}
			MyFile.close();
		}
		return _vUsers;
	}
	static void _SaveUsersDataToFile(vector <clsUser> _vUsers) {
		fstream MyFile;
		string DataLine;
		MyFile.open("Users.txt", ios::out);
		if (MyFile.is_open()) {
			for (clsUser& C : _vUsers) {
				if (C.MarkedForDeleted() == false)
				{
					DataLine = _ConvertUserObjToLine(C);
					if (DataLine != "") {
						MyFile << DataLine << endl;
					}
				}
			}
			MyFile.close();
		}
	}
	void _Update() {
		vector <clsUser> _vUsers;
		_vUsers = _LoadUsersDateFromFile();

		for (clsUser& C : _vUsers) {
			if (C.UserName == GetUserName()) {
				C = *this;
				break;
			}
		}

		_SaveUsersDataToFile(_vUsers);
	}
	void _AddClient() {
		_AddDataLineToFile(_ConvertUserObjToLine(*this));
	}
	void _AddDataLineToFile(string stDataLine) {
		fstream MyFile;
		MyFile.open("Users.txt", ios::app | ios::out);
		if (MyFile.is_open()) {
			MyFile << stDataLine << endl;
			MyFile.close();
		}
	}

public:

	clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone, string UserName, string Password, int Pertmissions) : clsPerson(FirstName, LastName, Email, Phone) {
		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permissions = Pertmissions;
	}
	bool IsEmpty() {
		return (_Mode == enMode::EmptyMode);
	}

	enum enPermessions {
		eAll = -1,
		pShowClientList = 1,
		pAddNewClient = 2,
		pDeleteClient = 4,
		pUpdateClinetInfo = 8,
		pFindClient = 16,
		pTransactions = 32,
		pManageUsers = 64,
		pLoginRegister = 128,
	};

	//    Password
	void SetPassword(string Password) {
		_Password = Password;
	}
	string GetPassword() {
		return _Password;
	}
	__declspec(property(get = GetPassword, put = SetPassword)) string Password;

	//    UserName
	string GetUserName() {
		return _UserName;
	}
	__declspec(property(get = GetUserName)) string UserName;

	//    Pertmissions
	void SetPertmissions(int Pertmissions) {
		_Permissions = Pertmissions;
	}
	int GetPertmissions() {
		return _Permissions;
	}
	__declspec(property(get = GetPertmissions, put = SetPertmissions)) int Pertmissions;

	bool MarkedForDeleted() {
		return _MarkedForDelete;
	}

	static clsUser Find(string UserName) {

		fstream MyFile;
		MyFile.open("Users.txt", ios::in);
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				if (!Line.empty()) {

					clsUser User = _ConvertLineToUserObj(Line);
					if (User.UserName == UserName) {
						MyFile.close();
						return User;
					}
				}
			}
			MyFile.close();
		}
		return _GetEmptyUserObj();
	}
	static clsUser Find(string UserName, string Password) {

		fstream MyFile;
		MyFile.open("Users.txt", ios::in);
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				if (!Line.empty()) {

					clsUser User = _ConvertLineToUserObj(Line);
					if (User.UserName == UserName && User.Password == Password) {
						MyFile.close();
						return User;
					}
				}
			}
			MyFile.close();
		}
		return _GetEmptyUserObj();
	}
	static bool IsUserExist(string AccountNumber) {
		clsUser User = clsUser::Find(AccountNumber);
		if (!User.IsEmpty())
			return true;
		return false;
	}
	static bool IsUserExist(string AccountNumber , string Password) {
		clsUser User = clsUser::Find(AccountNumber , Password);
		if (!User.IsEmpty())
			return true;
		return false;
	}

	bool IsUserExist() {
		if (!(*this).IsEmpty())
			return true;
		return false;
	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceded = 1, svFaildAccountNumberExists = 2 };
	enSaveResults Save() {
		switch (_Mode)
		{
		case clsUser::EmptyMode:
			return enSaveResults::svFaildEmptyObject;
			break;
		case clsUser::UpdateMode:
			_Update();
			return enSaveResults::svSucceded;
			break;
		case clsUser::AddNewMode:

			if (clsUser::IsUserExist(_UserName))
				return enSaveResults::svFaildAccountNumberExists;
			else {
				_AddClient();
				return enSaveResults::svSucceded;
			}
		}
	}
	static clsUser GetAddNewClientObject(string UserName) {
		return clsUser(clsUser::enMode::AddNewMode, "", "", "", "", UserName, "", 0);
	}
	bool Delete() {
		vector <clsUser> _vUsers;
		_vUsers = _LoadUsersDateFromFile();
		for (clsUser& C : _vUsers) {
			if (C.UserName == _UserName) {
				C._MarkedForDelete = true;
				break;
			}
		}
		_SaveUsersDataToFile(_vUsers);
		*this = _GetEmptyUserObj();
		return true;
	}
	static vector <clsUser> GetClientsList() {
		return _LoadUsersDateFromFile();
	}
	bool CheckAccessPermission(enPermessions Permission)
	{
		if (this->_Permissions == enPermessions::eAll)
			return true;

		if ((Permission & this->_Permissions) == Permission)
			return true;
		else
			return false;

	}
};


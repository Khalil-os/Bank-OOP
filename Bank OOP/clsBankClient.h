#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include "clsString.h"
#include "clsPerson.h"
#include <string>

using namespace std;

class clsBankClient : public clsPerson
{
private:

	enum enMode{EmptyMode = 0 , UpdateMode = 1 , AddNewMode = 2 };
	enMode _Mode;

	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkedForDelete = false;

	static clsBankClient _ConvertLineToClientObj(string sentence , string seperatore = "#//#") {
		vector <string> vSentence;
		vSentence = clsString::Split(sentence , seperatore);
		
		clsBankClient Client(enMode::UpdateMode, vSentence.at(0), vSentence.at(1), vSentence.at(2), vSentence.at(3), vSentence.at(4), vSentence.at(5), stof(vSentence.at(6)));
		return Client;
	}
	static string _ConvertClientObjToLine(clsBankClient Client , string seperatore = "#//#") {
		return  (Client.FirstName + seperatore + Client.LastName + seperatore + Client.Email + seperatore + Client.Phone + seperatore + Client.AccountNumber + seperatore + Client.PinCode + seperatore + to_string(Client.AccountBalance));
	}
	static clsBankClient _GetEmptyClientObj() {
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}
	static vector <clsBankClient> _LoadClientDateFromFile() {
		fstream MyFile;
		vector <clsBankClient> vInformation;
		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				if (!Line.empty()) {

					clsBankClient Client = _ConvertLineToClientObj(Line);
					vInformation.push_back(Client);

				}
			}
			MyFile.close();
		}
		return vInformation;
	}
	static void _SaveClientDataToFile(vector <clsBankClient> _vClients) {
		fstream MyFile;
		string DataLine;
		MyFile.open("Clients.txt", ios::out);
		if (MyFile.is_open()) {
			for (clsBankClient& C : _vClients) {
				if(C.MarkedForDeleted() == false)
				{
					DataLine = _ConvertClientObjToLine(C);
					if (DataLine!= "") {
						MyFile << DataLine << endl;
					}
				}
			}
			MyFile.close();
		}
	}
	void _Update() {
		vector <clsBankClient> _vClients;
		_vClients = _LoadClientDateFromFile();

		for (clsBankClient& C : _vClients) {
			if (C.AccountNumber == GetAccountNumber()) {
				C = *this;
				break;
			}
		}

		_SaveClientDataToFile(_vClients);
	}
	void _AddClient() {
		_AddDataLineToFile(_ConvertClientObjToLine(*this));
	}
	void _AddDataLineToFile(string stDataLine) {
		fstream MyFile;
		MyFile.open("Clients.txt", ios::app | ios::out);
		if (MyFile.is_open()) {
			MyFile << stDataLine << endl;
			MyFile.close();
		}
	}

public:

	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PinCode, float AccountBalance) : clsPerson(FirstName, LastName, Email, Phone) {
		_Mode = Mode;
		_PinCode = PinCode; 
		_AccountBalance = AccountBalance;
		_AccountNumber = AccountNumber;
	}
	bool IsEmpty() {
		return (_Mode == enMode::EmptyMode);
	}

	//    PinCode
	void SetPinCode(string PinCode) {
		_PinCode = PinCode;
	}
	string GetPinCode() {
		return _PinCode;
	}
	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	//    AccountNumber
	string GetAccountNumber() {
		return _AccountNumber;
	}
	__declspec(property(get = GetAccountNumber)) string AccountNumber;

	//    AccountBalance
	void SetAccountBalance(float AccountBalance) {
		_AccountBalance = AccountBalance;
	}
	float GetAccountBalance() {
		return _AccountBalance;
	}
	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;
	
	bool MarkedForDeleted() {
		return _MarkedForDelete;
	}

	static clsBankClient Find(string Acc_Number) {

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				if (!Line.empty()) {

					clsBankClient Client = _ConvertLineToClientObj(Line);
					if (Client.GetAccountNumber() == Acc_Number) {
						MyFile.close();
						return Client;
					}
				}
			}
			MyFile.close();
		}
		return _GetEmptyClientObj();
	}
	static clsBankClient Find(string Acc_Number , string Pass) {

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				if (!Line.empty()) {

					clsBankClient Client = _ConvertLineToClientObj(Line);
					if (Client.AccountNumber == Acc_Number && Client.PinCode == Pass) {
						MyFile.close();
						return Client;
					}
				}
			}
			MyFile.close();
		}
		return _GetEmptyClientObj();
	}
	static bool IsClientExist(string AccountNumber) {
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		if (!Client.IsEmpty())
			return true;
		return false;
	}
	bool IsClientExist() {
		if (!(*this).IsEmpty())
			return true;
		return false;
	}

	enum enSaveResults {svFaildEmptyObject = 0 , svSucceded = 1 , svFaildAccountNumberExists = 2};
	enSaveResults Save() {
		switch (_Mode)
		{
		case clsBankClient::EmptyMode:
			return enSaveResults::svFaildEmptyObject;
			break;
		case clsBankClient::UpdateMode:
			_Update();
			return enSaveResults::svSucceded;
			break;
		case clsBankClient::AddNewMode:

			if (clsBankClient::IsClientExist(_AccountNumber))
				return enSaveResults::svFaildAccountNumberExists;
			else {
				_AddClient();
				return enSaveResults::svSucceded;
			}
		}
	}
	static clsBankClient GetAddNewClientObject(string AccountNumber) {
		return clsBankClient(clsBankClient::enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}
	bool Delete() {
		vector <clsBankClient> _vClients;
		_vClients = _LoadClientDateFromFile();
		for (clsBankClient& C : _vClients) {
			if (C.AccountNumber == _AccountNumber) {
				C._MarkedForDelete = true;
				break;
			}
		}
		_SaveClientDataToFile(_vClients);
		*this = _GetEmptyClientObj();
		return true;
	}
	static vector <clsBankClient> GetClientsList() {
		return _LoadClientDateFromFile();
	}
	void Deposit(float Amount)
	{
		_AccountBalance += Amount;
		Save();
	}
	void Withdraw(float Amount)
	{
		_AccountBalance -= Amount;
		Save();
	}
};


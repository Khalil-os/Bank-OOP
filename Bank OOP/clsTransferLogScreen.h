#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsUser.h"
#include "clsScreen.h"
#include "Global.h"

using namespace std;

class clsTransferLogScreen : protected clsScreen
{
private:

	string _Date;
	string _ClientFrom_AccountNumber;
	string _ClientTo_AccountNumber;
	float _Amount;
	float _ClientFrom_AccountBalance;
	float _ClientTo_AccountBalance;
	string _UserName;

	static void PrintloginRecordLine(clsTransferLogScreen TransferLog) {

		cout << "| " << setw(25) << left << TransferLog.GetDate();
		cout << "| " << setw(10) << left << TransferLog.GetClientFromAccountNumber();
		cout << "| " << setw(10) << left << TransferLog.GetClientToAccountNumber();
		cout << "| " << setw(15) << left << TransferLog.GetAmount();
		cout << "| " << setw(15) << left << TransferLog.GetClientFromAccountBalance();
		cout << "| " << setw(15) << left << TransferLog.GetClientToAccountBalance();
		cout << "| " << setw(10) << left << TransferLog.GetUserName();

	}

	static clsTransferLogScreen _ConvertLineToLoginObj(string sentence, string seperatore = "#//#") {
		vector <string> vSentence;
		vSentence = clsString::Split(sentence, seperatore);

		clsTransferLogScreen TransferLog(vSentence.at(0), vSentence.at(1), vSentence.at(2), stof(vSentence.at(3)), stof(vSentence.at(4)), stof(vSentence.at(5)) , vSentence.at(6));
		return TransferLog;
	}

	static vector <clsTransferLogScreen> _LoadTransferLogDateFromFile() {

		fstream MyFile;
		vector <clsTransferLogScreen> _vTransferLogs;
		MyFile.open("TransferLogs.txt", ios::in);
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				if (!Line.empty()) {

					clsTransferLogScreen TransferLog = _ConvertLineToLoginObj(Line);
					_vTransferLogs.push_back(TransferLog);

				}
			}
			MyFile.close();
		}
		return _vTransferLogs;
	}

public:

	clsTransferLogScreen(string Date, string ClientFrom_AccountNumber, string ClientTo_AccountNumber, float Amount, float ClientFrom_AccountBalance, float ClientTo_AccountBalance, string UserName) {
		_Date = Date;
		_ClientFrom_AccountNumber = ClientFrom_AccountNumber;
		_ClientTo_AccountNumber = ClientTo_AccountNumber;
		_Amount = Amount;
		_ClientFrom_AccountBalance = ClientFrom_AccountBalance;
		_ClientTo_AccountBalance = ClientTo_AccountBalance;
		_UserName = UserName;
	}

	string GetDate() {
		return _Date;
	}
	string GetClientFromAccountNumber() {
		return _ClientFrom_AccountNumber;
	}
	string GetClientToAccountNumber() {
		return _ClientTo_AccountNumber;
	}
	float GetClientFromAccountBalance() {
		return _ClientFrom_AccountBalance;
	}
	float GetClientToAccountBalance() {
		return _ClientTo_AccountBalance;
	}
	string GetUserName() {
		return _UserName;
	}
	float GetAmount() {
		return _Amount;
	}

	static void ShowTransferLogScreen() {

		vector <clsTransferLogScreen> _vtransferLogs = _LoadTransferLogDateFromFile();
		string Title = "     Transfer Log List Screen";
		string SubTitle = "       (" + to_string(_vtransferLogs.size()) + ") Record(s).";

		_DrawScreenHeader(Title, SubTitle);


		cout << "\n__________________________________________________________";
		cout << "____________________________________________________________\n" << endl;

		cout << "| " << left << setw(25) << "Date/Time";
		cout << "| " << left << setw(10) << "s.Acct";
		cout << "| " << left << setw(10) << "d.Acct";
		cout << "| " << left << setw(15) << "Amount";
		cout << "| " << left << setw(15) << "s.Balance";
		cout << "| " << left << setw(15) << "d.Balance";
		cout << "| " << left << setw(10) << "User";
		cout << "\n__________________________________________________________";
		cout << "____________________________________________________________\n" << endl;

		if (_vtransferLogs.size() == 0)
			cout << "\t\t\t\tNo Record Available In the System!";
		else

			for (clsTransferLogScreen TransferLog : _vtransferLogs)
			{

				PrintloginRecordLine(TransferLog);
				cout << endl;
			}

		cout << "\n__________________________________________________________";
		cout << "____________________________________________________________\n" << endl;
	}

};


#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "clsString.h"
#include <string>

using namespace std;

class clsCurrency
{
private:

	enum enMode { EmptyMode = 0, UpdateMode = 1 };
	enMode _Mode;
	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;

	static clsCurrency _ConvertLineToCurrencyObject(string sentence, string seperatore = "#//#") {
		vector <string> vSentence;
		vSentence = clsString::Split(sentence, seperatore);

		clsCurrency Client(enMode::UpdateMode, vSentence.at(0), vSentence.at(1), vSentence.at(2), stof(vSentence.at(3)));
		return Client;
	}

	static string _ConvertCurrencyObjectToLine(clsCurrency Currency, string seperatore = "#//#") {
		return (Currency.Country+seperatore+Currency.CurrencyCode+seperatore+Currency.CurrencyName+seperatore+to_string(Currency.Rate));
	}

	static vector <clsCurrency> _LoadCurrencysDataFromFile() {

		fstream MyFile;
		vector <clsCurrency> _vCurrencys;
		MyFile.open("Currencies.txt", ios::in);
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				if (!Line.empty()) {

					clsCurrency Client = _ConvertLineToCurrencyObject(Line);
					_vCurrencys.push_back(Client);

				}
			}
			MyFile.close();
		}
		return _vCurrencys;
	}

	static void _SaveCurrencyDataToFile(vector <clsCurrency> _vClerrencys) {
		fstream MyFile;
		string DataLine;
		MyFile.open("Currencies.txt", ios::out);
		if (MyFile.is_open()) {
			for (clsCurrency& C : _vClerrencys) {				
				DataLine = _ConvertCurrencyObjectToLine(C);
				if (DataLine != "") {
					MyFile << DataLine << endl;
				}
			}
			MyFile.close();
		}
	}

	void _Update() {
		vector <clsCurrency> _vClerrencys;
		_vClerrencys = _LoadCurrencysDataFromFile();

		for (clsCurrency& C : _vClerrencys) {
			if (C.CurrencyCode == GetCurrencyCode()) {
				C = *this;
				break;
			}
		}

		_SaveCurrencyDataToFile(_vClerrencys);
	}

	static clsCurrency _GetEmptyCurrencyObject() {
		return clsCurrency(enMode::EmptyMode, "", "", "", 0);
	}

public:

	clsCurrency(enMode Mode, string Country, string CurrencyCode , string CurrencyName, float Rate) {
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}

	string GetCountry() {
		return _Country;
	}
	__declspec(property(get = GetCountry)) string Country;
	string GetCurrencyCode() {
		return _CurrencyCode;
	}
	__declspec(property(get = GetCurrencyCode)) string CurrencyCode;
	string GetCurrencyName() {
		return _CurrencyName;
	}
	__declspec(property(get = GetCurrencyName)) string CurrencyName;
	float GetRate() {
		return _Rate;
	}
	__declspec(property(get = GetRate)) float Rate;

	static vector <clsCurrency> GetAllUSDRates()
	{
		return _LoadCurrencysDataFromFile(); 
	}

	bool IsEmpty() {
		return (_Mode == enMode::EmptyMode);
	}

	void UpdateRate(float NewRate)
	{
		_Rate = NewRate;
		_Update();
	}

	static clsCurrency FindByCode(string CurrencyCode){

		CurrencyCode = clsString::UpperAllString(CurrencyCode);
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				if (!Line.empty()) {

					clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
					if (Currency.CurrencyCode == CurrencyCode) {
						MyFile.close();
						return Currency;
					}
				}
			}
			MyFile.close();
		}
		return _GetEmptyCurrencyObject();
	}

	static clsCurrency FindByCountry(string Country){

		Country = clsString::UpperAllString(Country);
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				if (!Line.empty()) {

					clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
					if (clsString::UpperAllString(Currency.Country) == Country) {
						MyFile.close();
						return Currency;
					}
				}
			}
			MyFile.close();
		}
		return _GetEmptyCurrencyObject();
	}

	bool IsCurrencyExist() {
		if (!(*this).IsEmpty())
			return true;
		return false;
	}
	
	static vector <clsCurrency> GetCurrenciesList()
	{
		return _LoadCurrencysDataFromFile();
	}

};


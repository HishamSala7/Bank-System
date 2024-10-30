#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "clsString.h"
 
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

	static clsCurrency _ConvertLineToCurrencyObject(string Line, string Separator = "#//#") {
		vector <string> vCurrencyData = clsString::Split(Line, Separator);
		return clsCurrency(enMode::UpdateMode, vCurrencyData[0], vCurrencyData[1], vCurrencyData[2], stof(vCurrencyData[3]));
	}

	static string _ConvertCurrencyObjectToLine(clsCurrency Currency, string Separator = "#//#") {
		string stCurrencyRecord = "";
		stCurrencyRecord += Currency.Country() + Separator;
		stCurrencyRecord += Currency.CurrencyCode() + Separator;
		stCurrencyRecord += Currency.CurrencyName() + Separator;
		stCurrencyRecord += to_string(Currency.Rate());
		
		return stCurrencyRecord;
	}

	static clsCurrency _GetEmptyCurrencyObject() {
		return clsCurrency(enMode::EmptyMode, "", "", "", 0);
	}

	static vector<clsCurrency> _LoadCurrencyDataFromFile() {
		vector<clsCurrency>vCurrency;
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);
		if (MyFile.is_open()) {
			string Line = "";
			while (getline(MyFile,Line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				vCurrency.push_back(Currency);
			}
			MyFile.close();
		}
		return vCurrency;
	}

	static void _SaveCurrencyDataToFile(vector<clsCurrency> vCurrency) {
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::out);
		string DataLine;
		if (MyFile.is_open()) {
			for (clsCurrency C : vCurrency) {
				DataLine = _ConvertCurrencyObjectToLine(C);
				MyFile << DataLine << endl;
			}
			MyFile.close();
		}
	}

	void _Update() {
		vector<clsCurrency> vCurrency = _LoadCurrencyDataFromFile();
		for (clsCurrency& C : vCurrency) {
			if (C.CurrencyCode() == CurrencyCode()) {
				C = *this;
				break;
			}
		}
		_SaveCurrencyDataToFile(vCurrency);
	}


public:

	clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate) {
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}

	bool IsEmpty() {
		return (_Mode == enMode::EmptyMode);
	}

	string Country() {
		return _Country;
	}

	string CurrencyCode() {
		return _CurrencyCode;
	}

	string CurrencyName() {
		return _CurrencyName;
	}

	void UpdateRate(float NewRate) {
		_Rate = NewRate;
		_Update();
	}

	float Rate() {
		return _Rate;
	}

	static clsCurrency FindByCountry(string Country) {
		Country = clsString::UpperAllString(Country);
		fstream	MyFile;
		MyFile.open("Currencies.txt", ios::in);
		if (MyFile.is_open()) {
			string Line = "";
			while (getline(MyFile,Line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				if (clsString::UpperAllString(Currency.Country()) == Country) {
					MyFile.close();
					return Currency;
				}
			}
			MyFile.close();
		}
		return _GetEmptyCurrencyObject();
	}

	static clsCurrency FindByCode(string CurrencyCode) {
		CurrencyCode = clsString::UpperAllString(CurrencyCode);

		fstream	MyFile;
		MyFile.open("Currencies.txt", ios::in);
		
		if (MyFile.is_open()) {
			string Line = "";
			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				if (Currency.CurrencyCode() == CurrencyCode) {
					MyFile.close();
					return Currency;
				}
			}
			MyFile.close();
		}
		return _GetEmptyCurrencyObject();
	}

	static vector<clsCurrency> _GetCurrenciesList() {
		return _LoadCurrencyDataFromFile();
	}

	static bool IsCurrencyExist(string CurrencyCode) {
		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		return (!Currency.IsEmpty());
	}

	float ConvertToUSD(float Amount) {
		return (float) (Amount / Rate());
	}

	float ConvertToOtherCurrency(float Amount, clsCurrency Currency2) {
		float AmountInUSD = ConvertToUSD(Amount);
		if (Currency2.CurrencyCode() == "USD")
			return AmountInUSD;
		return (float)(AmountInUSD * Currency2.Rate());
	}

};


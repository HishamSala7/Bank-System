#pragma once

#include <iostream>
#include "clsDate.h"


using namespace std;

class clsInputValidate
{

public:

	static bool IsNumberBetween(short Number, short From, short To) {
		return (Number >= From && Number <= To);
	}

	static bool IsNumberBetween(int Number, int From, int To) {
		return (Number >= From && Number <= To);
	}
	
	static bool IsNumberBetween(float Number, float From, float To) {
		return (Number >= From && Number <= To);
	}

	static bool IsNumberBetween(double Number, double From, double To) {
		return (Number >= From && Number <= To);
	}

	static bool IsDateBetween(clsDate Date, clsDate DateFrom, clsDate DateTo) {
		if ((clsDate::IsDate1AfterDate2(Date, DateFrom) || clsDate::IsDate1EqualDate2(Date, DateFrom)) &&
			(clsDate::IsDate1BeforeDate2(Date, DateTo) || clsDate::IsDate1EqualDate2(Date, DateTo)))
			return true;
		if ((clsDate::IsDate1AfterDate2(Date, DateTo) || clsDate::IsDate1EqualDate2(Date, DateTo)) &&
			(clsDate::IsDate1BeforeDate2(Date, DateFrom) || clsDate::IsDate1EqualDate2(Date, DateFrom)))
			return true;
		
		return false;
	}

	static int ReadIntNumber(string ErrorMessage = "Invalid Number, Enter again:\n") {
		int Number;
		while (!(cin>>Number))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}

	static double ReadDblNumber(string ErrorMessage = "Invalid Number, Enter again:\n") {
		double Number;
		while (!(cin >> Number))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}

	static float ReadFloatNumber(string ErrorMessage = "Invalid Number, Enter again:\n") {
		float Number;
		while (!(cin >> Number))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}

	static int ReadIntNumberBetween(int From, int To, string ErrorMessage = "Number is not within range, Enter again:\n") {
		int Number = ReadIntNumber();
		while (!IsNumberBetween(Number, From, To)) {
			cout << ErrorMessage;
			Number = ReadIntNumber();
		}
		return Number;
	}

	static short ReadShortNumberBetween(short From, short To, string ErrorMessage = "Number is not within range, Enter again:\n") {
		short Number = ReadIntNumber();
		while (!IsNumberBetween(Number, From, To)) {
			cout << ErrorMessage;
			Number = ReadIntNumber();
		}
		return Number;
	}

	static double ReadDblNumberBetween(double From, double To, string ErrorMessage = "Number is not within range, Enter again:\n") {
		double Number = ReadDblNumber();
		while (!IsNumberBetween(Number, From, To)) {
			cout << ErrorMessage;
			Number = ReadDblNumber();
		}
		return Number;
	}

	static float ReadFloatNumberBetween(float From, float To, string ErrorMessage = "Number is not within range, Enter again:\n") {
		float Number = ReadDblNumber();
		while (!IsNumberBetween(Number, From, To)) {
			cout << ErrorMessage;
			Number = ReadDblNumber();
		}
		return Number;
	}

	static bool IsValidDate(clsDate Date) {
		return clsDate::IsValidDate(Date);
	}

	static string ReadString() {
		string s = "";
		getline(cin >> ws, s);
		return s;
	}
	
};

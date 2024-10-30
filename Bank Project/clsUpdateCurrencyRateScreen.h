#pragma once

#include <iostream>
#include "clsInputValidate.h"
#include "clsCurrency.h"
#include "clsScreen.h"

using namespace std;

class clsUpdateCurrencyRateScreen : protected clsScreen
{
private:

	static void _PrintCurrency(clsCurrency Currency) {
		cout << "\nCurrency Card:";
		cout << "\n____________________________\n";
		cout << "\nCountry    : " << Currency.Country();
		cout << "\nCode       : " << Currency.CurrencyCode();
		cout << "\nName       : " << Currency.CurrencyName();
		cout << "\nRate(1$) = : " << Currency.Rate();
		cout << "\n____________________________\n\n";
	}

	static float _ReadRate() {
		cout << "\nEnter New Rate: ";
		float NewRate = clsInputValidate::ReadFloatNumber();
		return NewRate;
	}

public:

	static void ShowUpdateCurrencyRateScreen() {
		_DrawScreenHeader("\tUpdate Currency Screen");
		
		cout << "\nPlease Enter Currency Code: ";
		string CurrencyCode = clsInputValidate::ReadString();

		while (!clsCurrency::IsCurrencyExist(CurrencyCode))
		{
			cout << "\nCurrency is not found, choose another one: ";
			CurrencyCode = clsInputValidate::ReadString();
		}

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		_PrintCurrency(Currency);

		cout << "Are You Sure you want to update the rate of this currency? y/n? ";
		char Answer = 'n';
		cin >> Answer;
		
		if (Answer == 'Y' || Answer == 'y') {
			cout << "\n\nUpdate Currency Rate:";
			cout << "\n____________________________\n";

			Currency.UpdateRate(_ReadRate());
			cout << "\nCurrency Rate Updated successfuly :-)\n";
			_PrintCurrency(Currency);
		}

	}

};


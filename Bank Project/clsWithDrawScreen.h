#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsWithDrawScreen : clsScreen
{
private:

	static void _PrintClient(clsBankClient Client) {
		cout << "\nClient Card:";
		cout << "\n--------------------";
		cout << "\nFirstName   : " << Client.FirstName;
		cout << "\nLastName    : " << Client.LastName;
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nEmail       : " << Client.Email;
		cout << "\nPhone       : " << Client.Phone;
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nPassword    : " << Client.PinCode;
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n--------------------\n";
	}

	static string _ReadAccountNumber() {
		string AccountNumber;
		cout << "\nPlease Enter Account Number? ";
		cin >> AccountNumber;
		return AccountNumber;
	}

public:

	static void ShowWithDrawScreen() {
		_DrawScreenHeader("\t  WithDraw Screen");

		string AccountNumber = _ReadAccountNumber();
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nClient With [" << AccountNumber << "] does not exist.\n";
			AccountNumber = _ReadAccountNumber();
		}
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);

		double Amount = 0;
		cout << "\nPlease enter withdraaw amount: ";
		Amount = clsInputValidate::ReadDblNumber();

		cout << "\nAre you sure you want to perform this transaction? y/n? ";
		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y') {
			if (Client.WithDraw(Amount)) {
				cout << "\nAmount withdrew Successfully.\n";
				cout << "\nNew Balance Is: " << Client.AccountBalance;
			}
			else {
				cout << "\nCannot withdraw, Insuffecient Balance!\n";
				cout << "\nAmout to withdraw is: " << Amount;
				cout << "\nYour Balance is: " << Client.AccountBalance;
			}
				
		}
		else
			cout << "\nOperation was cancelled.\n";


	}
	

};


#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"


using namespace std;

class clsTransferScreen : protected clsScreen
{

private:

	static void _PrintClientCard(clsBankClient Client) {
		cout << "\nClient Card:";
		cout << "\n__________________\n";
		cout << "\nFull Name  : " << Client.FullName();
		cout << "\nAcc. Number: " << Client.AccountNumber();
		cout << "\nBalance    : " << Client.AccountBalance;
		cout << "\n__________________\n";

	}

	static double _ReadAmount(clsBankClient SourceClient) {
		double Amount;
		cout << "\nEnter Transfer Amount? ";
		Amount = clsInputValidate::ReadDblNumber();
		
		while (Amount > SourceClient.AccountBalance)
		{
			cout << "\nAmount Exceeds The available Balance, Enter another amount? ";
			Amount = clsInputValidate::ReadDblNumber();
		}
		return Amount;
	}

	static string _ReadAccountNumber() {
		cout << "\nPlease Enter Account Number to Transfer From: ";
		string AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number Not Found, Please Choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}
		return AccountNumber;
	}


public:

	static void ShowTransferScreen() {
		_DrawScreenHeader("\t\tTransfer Screen");

		clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber());
		_PrintClientCard(SourceClient);

		clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber());
		_PrintClientCard(DestinationClient);

		double Amount = _ReadAmount(SourceClient);
		
		char Answer = 'n';
		cout << "\nAre you sure you want to perform this operation? y/n? ";
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y') {
			
			if (SourceClient.Transfer(Amount, DestinationClient, CurrentUser.UserName)) 
				cout << "\nTransfer done successully.\n";

			else
				cout << "\nTransfer Failed \n";
		}

		_PrintClientCard(SourceClient);
		_PrintClientCard(DestinationClient);
	}


};


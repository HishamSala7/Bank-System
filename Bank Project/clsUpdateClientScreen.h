#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"

using namespace std;

class clsUpdateClientScreen : protected clsScreen
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

	static void _ReadClientInfo(clsBankClient& Client) {
		cout << "\nEnter FirstName: ";
		Client.FirstName = clsInputValidate::ReadString();

		cout << "\nEnter LastName: ";
		Client.LastName = clsInputValidate::ReadString();

		cout << "\nEnter Email: ";
		Client.Email = clsInputValidate::ReadString();

		cout << "\nEnter Phone:";
		Client.Phone = clsInputValidate::ReadString();

		cout << "\nEnter PinCode: ";
		Client.PinCode = clsInputValidate::ReadString();

		cout << "\nEnter Account Balance:";
		Client.AccountBalance = clsInputValidate::ReadDblNumber();

	}

public:

	static void ShowUpdateClientScreen() {

		if (!CheckAccessRights(clsUser::enPermissions::pUpdateClient))
			return;

		_DrawScreenHeader("\tUpdate Client Screen");


		string AccountNumber = "";
		cout << "\nplease Enter Client Account Number: ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number is Not found, choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);

		char Answer = 'n';
		cout << "\nAre you sure you want to update this client y/n? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y') {

			cout << "\n\nUpdate Client Info:";
			cout << "\n---------------------\n";

			_ReadClientInfo(Client);

			clsBankClient::enSaveResults SaveResult;

			SaveResult = Client.Save();

			switch (SaveResult)
			{
			case  clsBankClient::enSaveResults::svSucceeded:
				cout << "\nAccount Updated Successfully :-)\n";
				_PrintClient(Client);
				break;
			case clsBankClient::enSaveResults::svFailedEmptyObject:
				cout << "\nError account was not saved because it's Empty";
				break;
			}
		}
	}


};


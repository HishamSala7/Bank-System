#pragma once

#include <iostream>
#include <iomanip>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"

using namespace std;

class clsDeleteClientScreen : protected clsScreen
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


public:

	static void ShowDeleteClientScreen() {

		if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient))
			return;

		_DrawScreenHeader("\tDelete Client Screen");

		string AccountNumber = "";
		char Answer = 'n';
		cout << "\nEnter Account Number you want to delete: ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber)) {
			cout << "\nAccount Number is not found, choose anothe one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);

		cout << "\nAre you sure you want to delete this client? y/n? ";
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y') {
			if (Client.Delete())
			{
				cout << "\nClient Deleted successfully :-)\n";
				_PrintClient(Client);
			}
			else
				cout << "\nerror Client was not deleted\n";
		}
	}

};


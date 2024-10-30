#pragma once

#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"

class clsFindClientScreen : protected clsScreen
{

private:

	static void _PrintClient(clsBankClient Client) {
		cout << "\nClient Card:";
		//cout << "\n--------------------";
		cout << "\n____________________";
		cout << "\nFirstName   : " << Client.FirstName;
		cout << "\nLastName    : " << Client.LastName;
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nEmail       : " << Client.Email;
		cout << "\nPhone       : " << Client.Phone;
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nPassword    : " << Client.PinCode;
		cout << "\nBalance     : " << Client.AccountBalance;
		//cout << "\n--------------------\n";
		cout << "\n____________________\n";
	}

public:
	
	static void ShowFindClientScreen() {

		if (!CheckAccessRights(clsUser::enPermissions::pFindClient))
			return;

		_DrawScreenHeader("\tFind Client Screen");

		string AccountNumber = "";
		cout << "\nplease Enter Client Account Number: ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number is Not found, choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);

		if (!Client.IsEmpty())
			cout << "\nClient Found :-)\n";
		else
			cout << "\nClient was not found :-(\n";

		_PrintClient(Client);
	}


};


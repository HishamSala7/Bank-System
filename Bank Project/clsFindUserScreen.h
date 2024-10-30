#pragma once

#include <iostream>
#include "clsInputValidate.h"
#include "clsUser.h"
#include "clsScreen.h"

using namespace std;

class clsFindUserScreen : protected clsScreen
{
private:
	
	static void _PrintUser(clsUser User) {
		cout << "\nUser Card:";
		cout << "\n--------------------";
		cout << "\nFirstName   : " << User.FirstName;
		cout << "\nLastName    : " << User.LastName;
		cout << "\nFull Name   : " << User.FullName();
		cout << "\nEmail       : " << User.Email;
		cout << "\nPhone       : " << User.Phone;
		cout << "\nAcc. Number : " << User.UserName;
		cout << "\nPassword    : " << User.Password;
		cout << "\nBalance     : " << User.Permissions;
		cout << "\n--------------------\n";
	}

public:

	static void ShowFindUserScreen() {

		_DrawScreenHeader("\tFind User Screen");

		string UserName = "";
		cout << "\nplease Enter UserName: ";
		UserName = clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(UserName))
		{
			cout << "\nUserName is Not found, choose another one: ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::Find(UserName);

		if (!User.IsEmpty())
			cout << "\nUser Found :-)\n";
		else
			cout << "\nUser was not found :-(\n";

		_PrintUser(User);


	}
};


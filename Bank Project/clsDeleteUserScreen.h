#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h" 

using namespace std;

class clsDeleteUserScreen : protected clsScreen
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
		cout << "\nPermissions : " << User.Permissions;
		cout << "\n--------------------\n";
	}

public:

	static void ShowDeleteUserScreen() {
		_DrawScreenHeader("\tDelete User Screen");

		string UserName = "";
		char Answer = 'n';
		cout << "\nEnter User Name you want to delete: ";
		UserName = clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(UserName)) {
			cout << "\nUserName is not found, choose anothe one: ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::Find(UserName);
		_PrintUser(User);

		cout << "\nAre you sure you want to delete this User? y/n? ";
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y') {
			if (User.Delete())
			{
				cout << "\nUser Deleted successfully :-)\n";
				_PrintUser(User);
			}
			else
				cout << "\nerror User was not deleted\n";
		}
	}

};


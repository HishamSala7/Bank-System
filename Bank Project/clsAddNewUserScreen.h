#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsString.h"
#include "clsInputValidate.h"

using namespace std;

class clsAddNewUserScreen : protected clsScreen
{

private:

	static void _ReadUserInfo(clsUser& User) {
		cout << "\nEnter FirstName: ";
		User.FirstName = clsInputValidate::ReadString();

		cout << "\nEnter LastName: ";
		User.LastName = clsInputValidate::ReadString();

		cout << "\nEnter Email: ";
		User.Email = clsInputValidate::ReadString();

		cout << "\nEnter Phone:";
		User.Phone = clsInputValidate::ReadString();

		cout << "\nEnter Password: ";
		User.Password = clsInputValidate::ReadString();
		
		cout << "\nEnter Permissions:";
		User.Permissions = _ReadPermissionsToSet();
	}

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

	static int _ReadPermissionsToSet() {
		
		int Permissions = 0;
		char Answer = 'n';

		cout << "\nDo You want to give full access? y/n? ";
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y')
			return -1;
		
		cout << "\nDo you want to give access to: \n";

		cout << "\nShow Client List? y/n? ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
			Permissions += clsUser::enPermissions::pListClients;

		cout << "\nShow Add New Client? y/n? ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
			Permissions += clsUser::enPermissions::pAddNewClient;


		cout << "\nShow Delete Client? y/n? ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
			Permissions += clsUser::enPermissions::pDeleteClient;


		cout << "\nShow Update Client? y/n? ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
			Permissions += clsUser::enPermissions::pUpdateClient;


		cout << "\nShow Find Client? y/n? ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
			Permissions += clsUser::enPermissions::pFindClient;


		cout << "\nTransaction ? y/n? ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
			Permissions += clsUser::enPermissions::pTransactions;


		cout << "\nManage Users ? y/n? ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
			Permissions += clsUser::enPermissions::pManageUsers;

		cout << "\nShow Login Register ? y/n? ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
			Permissions += clsUser::enPermissions::pShowLoginRegister;

		return Permissions;
	}

public:

	static void ShowAddNewUserScreen() {

		_DrawScreenHeader("\t  Add New User Screen");

		cout << "\nPlease enter UserName: ";
		string UserName = clsInputValidate::ReadString();

		while (clsUser::IsUserExist(UserName))
		{
			cout << "\nUserName Is Already Used, Choose another one: ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser NewUser = clsUser::GetAddNewUserObject(UserName);
		_ReadUserInfo(NewUser);

		clsUser::enSaveResults	SaveResults;
		SaveResults = NewUser.Save();

		switch (SaveResults)
		{
		case clsUser::enSaveResults::svFailedEmptyObject:
			cout << "\nError User Was not saved because it's empty";
			break;
		case clsUser::enSaveResults::svSucceeded:
			cout << "\nUser Added Successfully :-)\n";
			_PrintUser(NewUser);
			break;
		case clsUser::enSaveResults::svFailedUserExists:
			cout << "\nError User was not saved because UserName is used!\n";
			break;
		}
	}

};


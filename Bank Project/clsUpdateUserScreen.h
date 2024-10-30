#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"

using namespace std;

class clsUpdateUserScreen : protected clsScreen
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

		cout << "\nShow User List? y/n? ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
			Permissions += clsUser::enPermissions::pListClients;

		cout << "\nShow Add New User? y/n? ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
			Permissions += clsUser::enPermissions::pAddNewClient;


		cout << "\nShow Delete User? y/n? ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
			Permissions += clsUser::enPermissions::pDeleteClient;


		cout << "\nShow Update User? y/n? ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
			Permissions += clsUser::enPermissions::pUpdateClient;


		cout << "\nShow Find User? y/n? ";
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

	static void ShowUpdateUserScreen() {

		_DrawScreenHeader("\tUpdate User Screen");

		string UserName = "";
		cout << "\nplease Enter UserName: ";
		UserName = clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(UserName))
		{
			cout << "\nUserName is Not found, choose another one: ";
			UserName = clsInputValidate::ReadString();
		}
		clsUser User = clsUser::Find(UserName);
		_PrintUser(User);

		char Answer = 'n';
		cout << "\nAre you sure you want to update this User y/n? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y') {

			cout << "\n\nUpdate User Info:";
			cout << "\n---------------------\n";

			_ReadUserInfo(User);

			clsUser::enSaveResults SaveResult;

			SaveResult = User.Save();

			switch (SaveResult)
			{
			case  clsUser::enSaveResults::svSucceeded:
				cout << "\nUser Updated Successfully :-)\n";
				_PrintUser(User);
				break;
			case clsUser::enSaveResults::svFailedEmptyObject:
				cout << "\nError user was not saved because it's Empty";
				break;
			}
		}


	}

};


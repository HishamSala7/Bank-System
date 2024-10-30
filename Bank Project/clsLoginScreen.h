#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include "clsMainScreen.h"
#include "Global.h"

using namespace std;

class clsLoginScreen : protected clsScreen
{
private:

	static bool _Login() {

		string UserName, Password;
		bool LoginFailed = false;
		short FailedLoginCount = 0;

		do
		{
			if (LoginFailed) {
				FailedLoginCount++;
				cout << "\nInvalid Username/Password!\n";
				cout << "You have " << (3-FailedLoginCount) << " Trial(s) to login.\n"; 
			}

			if (FailedLoginCount == 3)
			{
				cout << "\n\nYou are Locked after 3 failed trials \n\n";
				return false;
			}

			cout << "\nEnter Username? ";
			cin >> UserName;

			cout << "Enter Password? ";
			cin >> Password;

			CurrentUser = clsUser::Find(UserName, Password);

			LoginFailed = CurrentUser.IsEmpty();

		} while (LoginFailed);

		CurrentUser.RegisterLogin();
		clsMainScreen::ShowMainMenue();
		return true;
	}


public:

	static bool ShowLoginScreen()  {
		system("cls");
		_DrawScreenHeader("\t     Login Screen");
		return _Login();
	}

};


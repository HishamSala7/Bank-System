#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsString.h"
#include "clsPerson.h"
#include "clsDate.h"
#include "clsUtil.h"

using namespace std;

class clsUser : public clsPerson
{

private:
	
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };

	enMode _Mode;
	string _UserName;
	string _Password;
	int _Permissions = 0;
	bool MarkForDeleted = false;
	struct stLoginRegisterRecord;

	static clsUser _ConvertLineToUserObject(string Line, string Separator = "#//#") {
		vector <string> vUserData = clsString::Split(Line, Separator);
		return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2],
			vUserData[3], vUserData[4], clsUtil::DecryptText(vUserData[5],2), stoi(vUserData[6]));
	}

	static string _ConvertUserObjectToLine(clsUser User, string Separator = "#//#") {
		
		string UserRecord = "";
		UserRecord += User.FirstName + Separator;
		UserRecord += User.LastName + Separator;
		UserRecord += User.Email + Separator;
		UserRecord += User.Phone + Separator;
		UserRecord += User.UserName + Separator;
		//UserRecord += User.Password + Separator;
		UserRecord += clsUtil::EncryptText(User.Password, 2) + Separator;
		UserRecord += to_string(User.Permissions);

		return UserRecord;
	}
	 
	static vector<clsUser> _LoadUsersDataFromFile() {
		vector <clsUser> vUsers;
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);
		
		if (MyFile.is_open()) {
			string Line = "";
			while (getline(MyFile,Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);
				vUsers.push_back(User);
			}
			MyFile.close();
		}
		return vUsers;
	}

	static void _SaveUsersDataToFile(vector <clsUser> vUsers) {
		fstream MyFile;
		MyFile.open("Users.txt", ios::out);
		string Line = "";

		if (MyFile.is_open()) {
			for (clsUser U : vUsers) {
				if (!U.MarkedForDeleted()) {
					Line = _ConvertUserObjectToLine(U);
					MyFile << Line << endl;
				}
			}

			MyFile.close();
		}
	}

	static void _AddDataLineToFile(string sDataLine) {
		fstream MyFile;
		MyFile.open("Users.txt", ios::out | ios::app);
		if (MyFile.is_open()) {
			MyFile << sDataLine << endl;
			MyFile.close();
		}
	}

	static clsUser _GetEmptyUserObject() {
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	void _Update() {
		vector <clsUser> vUsers = _LoadUsersDataFromFile();
		for (clsUser& U : vUsers) {
			if (U.UserName == _UserName) {
				U = *this;
				break;
			}
		}
		_SaveUsersDataToFile(vUsers);
	}

	void _AddNew() {
		_AddDataLineToFile(_ConvertUserObjectToLine(*this));
	}

	string _PrepareLoginRecord(string Separator = "#//#") {
		string LoginRecord = clsDate::GetSystemDateTimeString() + Separator;
		LoginRecord += UserName + Separator;
		LoginRecord += clsUtil::EncryptText(Password ,2) + Separator;
		LoginRecord += to_string(Permissions);
		return LoginRecord;
	}

	static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string Line, string Separator = "#//#") {
		
		vector<string>vLoginData = clsString::Split(Line, Separator);
		stLoginRegisterRecord LoginRegisterRecord;
		
		LoginRegisterRecord.DateTime = vLoginData[0];
		LoginRegisterRecord.UserName = vLoginData[1];
		LoginRegisterRecord.Password = clsUtil::DecryptText(vLoginData[2], 2);
		LoginRegisterRecord.Permissions = stoi(vLoginData[3]);
		
		return LoginRegisterRecord;
	}

public:

	enum enPermissions {
		eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
		pUpdateClient = 8, pFindClient = 16, pTransactions = 32, pManageUsers = 64, pShowLoginRegister = 128
	};

	struct stLoginRegisterRecord
	{
		string DateTime;
		string UserName;
		string Password;
		int Permissions;
	};

	clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone, string UserName, string Password, int Permissions)
		:clsPerson(FirstName, LastName, Email, Phone) {
		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permissions = Permissions;
	}

	bool IsEmpty() {
		return (_Mode == enMode::EmptyMode);
	}

	bool MarkedForDeleted() {
		return MarkForDeleted;
	}

	void SetUsername(string UserName) {
		_UserName = UserName;
	}

	string GetUsername() {
		return _UserName;
	}

	__declspec(property(get = GetUsername, put = SetUsername)) string UserName;

	void SetPassword(string Password) {
		_Password = Password;
	}

	string GetPassword() {
		return _Password;
	}

	__declspec(property(get = GetPassword, put = SetPassword)) string Password;

	void SetPermissions(int Permissions) {
		_Permissions = Permissions;
	}

	int GetPermissions() {
		return _Permissions;
	}
	 
	__declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

	static clsUser Find(string UserName) {
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open()) {
			string Line = "";
			while (getline(MyFile,Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);
				if (User.UserName == UserName) {
					MyFile.close();
					return User;
				}
			}
			MyFile.close();
		}
		return _GetEmptyUserObject();
	}

	static clsUser Find(string UserName, string Password) {
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open()) {
			string Line = "";
			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);
				if (User.UserName == UserName && User.Password == Password) {
					MyFile.close();
					return User;
				}
			}
			MyFile.close();
		}
		return _GetEmptyUserObject();
	}

	enum enSaveResults{svFailedEmptyObject = 0 , svSucceeded = 1 , svFailedUserExists = 2};

	static bool IsUserExist(string UserName) {
		clsUser User = clsUser::Find(UserName);
		return (!User.IsEmpty());
	}

	enSaveResults Save() {
		switch (_Mode)
		{
		case enMode::EmptyMode:
			if (IsEmpty())
				return enSaveResults::svFailedEmptyObject;
			break;
		case enMode::UpdateMode:
			_Update();
			return enSaveResults::svSucceeded;
			break;
		case enMode::AddNewMode:
			if (clsUser::IsUserExist(_UserName))
				return enSaveResults::svFailedUserExists;
			else
			{
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}
			break;
		}
	}

	static clsUser GetAddNewUserObject(string UserName) {
		return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
	}

	bool Delete() {
		vector <clsUser> vUsers = _LoadUsersDataFromFile();
		for (clsUser& U : vUsers) {
			if (U.UserName == _UserName) {
				U.MarkForDeleted = true;
				break;
			}
		}
		_SaveUsersDataToFile(vUsers);
		*this = _GetEmptyUserObject();
		return true;
	}

	static vector<clsUser> GetUsersList() {
		return _LoadUsersDataFromFile();
	}

	bool CheckAccessPermissions(enPermissions Permission) {
		
		if (this->Permissions == enPermissions::eAll)
			return true;
		
		if ((Permission & this->Permissions) == Permission)
			return true;

		else
			return false;
	}

	void RegisterLogin() {

		string stDataLine = _PrepareLoginRecord();
		fstream MyFile;
		MyFile.open("LoginRegister.txt", ios::out | ios::app);
		
		if (MyFile.is_open()) {

			MyFile << stDataLine << endl;
			MyFile.close();
		}
	}

	static vector<stLoginRegisterRecord> GetLoginRegisterList() {
		vector<stLoginRegisterRecord> vLoginRegisterRecord;
		fstream MyFile;
		MyFile.open("LoginRegister.txt", ios::in);
		if (MyFile.is_open()) {
			string Line;
			stLoginRegisterRecord LoginRegisterRecord;
			
			while (getline(MyFile,Line))
			{
				LoginRegisterRecord = _ConvertLoginRegisterLineToRecord(Line);
				vLoginRegisterRecord.push_back(LoginRegisterRecord);
			}
			MyFile.close();
		}
		return vLoginRegisterRecord;
	}

};


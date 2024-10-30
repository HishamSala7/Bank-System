#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"


using namespace std;

class clsBankClient : public clsPerson
{
private:

	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;

	string _AccountNumber;
	string _PinCode;
	bool _MarkForDelete = false;
	float _AccountBalance;
	struct stTransferLogRecord;

	static clsBankClient _ConvertLineToClientObject(string Line, string Separate = "#//#") {
		vector <string> vClientData = clsString::Split(Line, Separate);
		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3], vClientData[4],
			vClientData[5], stod(vClientData[6]));
	}

	static clsBankClient _GetEmptyClientObject() {
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static string _ConvertClientObjectToLine(clsBankClient Client , string Separator = "#//#") {
		string sClientRecord = "";
		sClientRecord += Client.FirstName + Separator;
		sClientRecord += Client.LastName + Separator;
		sClientRecord += Client.Email + Separator;
		sClientRecord += Client.Phone + Separator;
		sClientRecord += Client.AccountNumber() + Separator;
		sClientRecord += Client.PinCode + Separator;
		sClientRecord += to_string( Client.AccountBalance);
		
		return sClientRecord;
	}

	static vector<clsBankClient> _LoadClientDataFromFile() {
		vector<clsBankClient> vClients;
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile,Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				vClients.push_back(Client);
			}
			MyFile.close();
		}
		return vClients;
	}

	static void _SaveClientsDataToFile(vector<clsBankClient>vClients) {
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out);
		string Line = "";

		if (MyFile.is_open()) {	
			for (clsBankClient C : vClients) {
				if (C.MarkForDeleted() == false) {
					Line = _ConvertClientObjectToLine(C);
					MyFile << Line << endl;
				}
			}
			MyFile.close();
		}
	}

	void _Update() {
		vector<clsBankClient>vClients = _LoadClientDataFromFile();
		for (clsBankClient& C : vClients) {
			if (C.AccountNumber() == AccountNumber()) {
				C = *this;
				break;
			}
		}
		_SaveClientsDataToFile(vClients);
	}

	void _AddDataLineToFile(string sDataLine) {
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out | ios::app);
		if (MyFile.is_open()) {
			MyFile << sDataLine << endl;
			MyFile.close();
		}
	}

	void _AddNew() {
		_AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}

	string _PrepareTransferLogRecord( double Amount, clsBankClient DestinationClient, string UserName, string Separator = "#//#") {
		
		string TransferLogRecord = "";
		
		TransferLogRecord += clsDate::GetSystemDateTimeString() + Separator;
		TransferLogRecord += AccountNumber() + Separator;
		TransferLogRecord += DestinationClient.AccountNumber() + Separator;
		TransferLogRecord += to_string(Amount) + Separator;
		TransferLogRecord += to_string(AccountBalance) + Separator;
		TransferLogRecord += to_string(DestinationClient.AccountBalance) + Separator;
		TransferLogRecord += UserName;
		
		return TransferLogRecord;
	}

	void _RegisterTransferLog(double Amount, clsBankClient DestinationClient, string UserName) {
		
		string sDataLine = _PrepareTransferLogRecord(Amount, DestinationClient, UserName);
		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::out | ios::app);
		
		if (MyFile.is_open()) {
			MyFile << sDataLine << endl;
			MyFile.close();
		}
	}

	static stTransferLogRecord _ConvertTransferLogLineToRecord(string Line, string Separator = "#//#") {
		vector<string>vTansferLogRecordLine = clsString::Split(Line, Separator);
		stTransferLogRecord TransferLogRecord;
		
		TransferLogRecord.DateTime = vTansferLogRecordLine[0];
		TransferLogRecord.SourceAccountNumber = vTansferLogRecordLine[1];
		TransferLogRecord.DestinationAccountNumber = vTansferLogRecordLine[2];
		TransferLogRecord.Amount = stod(vTansferLogRecordLine[3]);
		TransferLogRecord.srcBalanceAfter = stof(vTansferLogRecordLine[4]);
		TransferLogRecord.destBalanceAfter = stof(vTansferLogRecordLine[5]);
		TransferLogRecord.UserName = vTansferLogRecordLine[6];
		
		return TransferLogRecord;
	}

	

public:

	struct stTransferLogRecord
	{
		string DateTime;
		string SourceAccountNumber;
		string DestinationAccountNumber;
		double Amount;
		float srcBalanceAfter;
		float destBalanceAfter;
		string UserName;
	};
	
	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone,
		string AccountNumber, string PinCode, float AccountBalance)
		:clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}

	bool IsEmpty() {
		return (_Mode == enMode::EmptyMode);
	}

	string AccountNumber() {
		return _AccountNumber;
	}

	void SetPinCode(string PinCode) {
		_PinCode = PinCode;
	}

	string GetPinCode() {
		return _PinCode;
	}

	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	void SetAccountBalance(float AccountBalance) {
		_AccountBalance = AccountBalance;
	}

	float GetAccountBalance() {
		return _AccountBalance;
	}

	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

	bool MarkForDeleted() {
		return _MarkForDelete;
	}

	/*void Print() {

		cout << "\nClient Card:";
		cout << "\n--------------------";
		cout << "\nFirstName   : " << FirstName;
		cout << "\nLastName    : " << LastName;
		cout << "\nFull Name   : " << FullName();
		cout << "\nEmail       : " << Email;
		cout << "\nPhone       : " << Phone;
		cout << "\nAcc. Number : " << _AccountNumber;
		cout << "\nPassword    : " << _PinCode;
		cout << "\nBalance     : " << _AccountBalance;
		cout << "\n--------------------\n";
	}*/

	static clsBankClient Find(string AccountNumber) {
		vector <clsBankClient> vClients;
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in); //read mode
		
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber() == AccountNumber) {
					MyFile.close();
					return Client;
				}
				vClients.push_back(Client);
			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber , string PinCode) {
		vector <clsBankClient> vClients;
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in); //read mode

		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode) {
					MyFile.close();
					return Client;
				}
				vClients.push_back(Client);
			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}

	static bool IsClientExist(string AccountNumber) {
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		return (!Client.IsEmpty());
	}

	enum enSaveResults { svFailedEmptyObject = 0, svSucceeded = 1, svFailedAccountNumberExists = 2 };

	enSaveResults Save() {
		switch (_Mode)
		{
		case enMode::EmptyMode:
		{
			if (IsEmpty())
				return enSaveResults::svFailedEmptyObject;
			break;
		}
		case enMode::UpdateMode:
		{
			_Update();
			return enSaveResults::svSucceeded;
			break;
		}
		case enMode::AddNewMode:
		{
			if (clsBankClient::IsClientExist(_AccountNumber))
				return enSaveResults::svFailedAccountNumberExists;
			else {
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}
			break;
		}

		}

	}

	static clsBankClient GetAddNewClientObject(string AccountNumber) {
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	bool Delete() {
		vector<clsBankClient>vClients = _LoadClientDataFromFile();
		for (clsBankClient& C : vClients) {
			if (C.AccountNumber() == _AccountNumber) {
				C._MarkForDelete = true;
				break;
			}
		}
		_SaveClientsDataToFile(vClients);
		*this = _GetEmptyClientObject();
		return true; 

	}

	static vector<clsBankClient> GetClientsList() {
		return  _LoadClientDataFromFile();
	}

	static double GetTotalBalances() {
		vector<clsBankClient>vClients = clsBankClient::GetClientsList();
		int TotalBalances = 0;
		for (clsBankClient C : vClients) {
			TotalBalances += C.AccountBalance;
		}
		return TotalBalances;	
	}

	void Deposit(double Amount) {
		_AccountBalance += Amount;
		Save();
	}

	bool WithDraw(double Amount) {
		if (Amount > _AccountBalance)
			return false;

		_AccountBalance -= Amount;
		Save();
		return true;
	}

	bool Transfer(double Amount, clsBankClient& DestinationClient, string UserName ) {
		if (Amount > AccountBalance)
			return false;

		WithDraw(Amount);
		DestinationClient.Deposit(Amount);
		_RegisterTransferLog(Amount, DestinationClient, UserName);
		return true;
	}

	static vector<stTransferLogRecord> GetTransferLogList() {
		vector<stTransferLogRecord> vTransferLog;
		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::in);
		

		if (MyFile.is_open()) {
			
			string Line = "";
			stTransferLogRecord TransferLogRecord;

			while (getline(MyFile, Line))
			{
				TransferLogRecord = _ConvertTransferLogLineToRecord(Line);
				vTransferLog.push_back(TransferLogRecord);
			}
			MyFile.close();
		}
		return vTransferLog;
	}


};


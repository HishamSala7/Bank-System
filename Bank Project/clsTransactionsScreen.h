#pragma once

#include <iostream>
#include <iomanip>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsDepositScreen.h"
#include "clsWithDrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"

using namespace std;

class clsTransactionsScreen : clsScreen
{

private:

	enum enTransactionsMenueOptions {
		eDeposit = 1, eWithDraw = 2, eShowTotalBalances = 3,
		eTransfer = 4, eTransferLog = 5, eShowMainMenue = 6
	};

	static void _GoBackToTransactionMenue() {
		cout << "\n\nPress any key to go back to Transactions menue...\n";
		system("pause>0");
		ShowTransactionsMenue();
	}

	static short _ReadTransactionsMenueOption() {
		short Choice;
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
		Choice = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter number between 1 to 6? ");
		return Choice;
	}

	static void _ShowDepositScreen() {
		clsDepositScreen::ShowDepositScreen();
	}

	static void _ShowWithDrawScreen() {
		clsWithDrawScreen::ShowWithDrawScreen();
	}

	static void _ShowTotalBalancesScreen() {
		clsTotalBalancesScreen::ShowTotalBalances();
	}

	static void _ShowTransferSceen() {
		clsTransferScreen::ShowTransferScreen();
	}

	static void _ShowTransferLogScreen() {
		clsTransferLogScreen::ShowTransferLogScreen();
	}

	static void _PerformTransactionsMenueOption(enTransactionsMenueOptions TransactionMenueOption) {
		switch (TransactionMenueOption)
		{
		case enTransactionsMenueOptions::eDeposit:
			system("cls");
			_ShowDepositScreen();
			_GoBackToTransactionMenue();
			break;
		case enTransactionsMenueOptions::eWithDraw:
			system("cls");
			_ShowWithDrawScreen();
			_GoBackToTransactionMenue();
			break;
		case enTransactionsMenueOptions::eShowTotalBalances:
			system("cls");
			_ShowTotalBalancesScreen();
			_GoBackToTransactionMenue();
			break;
		case enTransactionsMenueOptions::eTransfer:
			system("cls");
			_ShowTransferSceen();
			_GoBackToTransactionMenue();
			break;
		case enTransactionsMenueOptions::eTransferLog:
			system("cls");
			_ShowTransferLogScreen();
			_GoBackToTransactionMenue();
		case enTransactionsMenueOptions::eShowMainMenue:
			break;
		
		}
	}

public:

	static void ShowTransactionsMenue() {

		if (!CheckAccessRights(clsUser::enPermissions::pTransactions))
			return;

		system("cls");
		_DrawScreenHeader("\t  Transactions Screen");


		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t  Transactions Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] Deposit.\n";
		cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
		cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
		cout << setw(37) << left << "" << "\t[4] Transfer.\n";
		cout << setw(37) << left << "" << "\t[5] Transfer Log.\n";
		cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
		cout << setw(37) << left << "" << "===========================================\n";

		_PerformTransactionsMenueOption((enTransactionsMenueOptions)_ReadTransactionsMenueOption());

	}

};


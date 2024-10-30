#pragma once

#include <iostream>
#include <string>
#include <time.h>
#include "clsDate.h"

using namespace std;

class clsUtil
{
public:

	enum enCharType { SmallLetter = 1, CapitalLetter = 2, SpecialCharacter = 3, OneDigit = 4, MixChars = 5 };

	static string EncryptText(string Text, short EncryptionKey = 2) {
		for (int i = 0; i < Text.length(); i++) {
			Text[i] = char((int)Text[i] + EncryptionKey);
		}
		return Text;
	}

	static string DecryptText(string Text, short EncryptionKey = 2) {
		for (int i = 0; i < Text.length(); i++) {
			Text[i] = char((int)Text[i] - EncryptionKey);
		}
		return Text;
	}

	static int RandomNumber(int From, int To) {
		int RandomNum = rand() % (To - From + 1) + From;
		return RandomNum;
	}

	static char GetRandomCharacter(enCharType CharType) {
		
		if (CharType == enCharType::MixChars)
			CharType = (enCharType)RandomNumber(1, 4);

		switch (CharType)
		{
		case SmallLetter:
			return char(RandomNumber(97, 122));
		case CapitalLetter:
			return char(RandomNumber(65, 90));
		case SpecialCharacter:
			return char(RandomNumber(33, 47));
		case OneDigit:
			return char(RandomNumber(48, 57));
		default:
			return char(RandomNumber(65, 90));
		}
	}

	static void Srand() {
		srand((unsigned)time(NULL));
	}

	static string GenerateWord(enCharType CharType, short Length) {
		string word = "";
		for (int i = 0; i < Length; i++) {
			word += GetRandomCharacter(CharType);
		}
		return word;
	}

	static string GenerateKey(enCharType CharType = CapitalLetter) {
		string Key = "";
		Key = GenerateWord(CharType, 4) + "-";
		Key = Key + GenerateWord(CharType, 4) + "-";
		Key = Key + GenerateWord(CharType, 4) + "-";
		Key = Key + GenerateWord(CharType, 4);
		return Key;
	}

	static void GenerateKeys(short NumberOfKeys, enCharType CharType) {
		cout << endl;
		for (int i = 1; i <= NumberOfKeys; i++) {
			cout << "Key[" << i << "]: " << GenerateKey(CharType) << endl;
		}
	}

	static void Swap(int& Number1, int& Number2) {
		int Temp = Number1;
		Number1 = Number2;
		Number2 = Temp;
	}

	static void Swap(double& Number1, double& Number2) {
		double Temp = Number1;
		Number1 = Number2;
		Number2 = Temp;
	}

	static void Swap(bool& A, bool& B) {
		bool Temp = A;
		A = B;
		B = Temp;
	}

	static void Swap(char& A, char& B) {
		char Temp = A;
		A = B;
		B = Temp;
	}

	static void Swap(string& s1, string& s2) {
		string sTemp = s1;
		s1 = s2;
		s2 = sTemp;
	}

	static void Swap(clsDate& Date1, clsDate& Date2) {
		clsDate::SwapDates(Date1, Date2);
	}

	static void ShuffleArray(int arr[100], int arrLength) {
		for (int i = 0; i < arrLength; i++) {
			int index1 = RandomNumber(1, arrLength) - 1;
			int index2 = RandomNumber(1, arrLength) - 1;
			Swap(arr[index1], arr[index2]);
		}
	}

	static void ShuffleArray(string arr[100], int arrLength) {
		for (int i = 0; i < arrLength; i++) {
			int index1 = RandomNumber(1, arrLength) - 1;
			int index2 = RandomNumber(1, arrLength) - 1;
			Swap(arr[index1], arr[index2]);
		}
	}

	static void FillArrayWithRandomNumbers(int arr[100], int arrLength, int From, int To) {
		for (int i = 0; i < arrLength; i++) {
			arr[i] = RandomNumber(From, To);
		}
	}

	static void FillArrayWithRandomWords(string arr[100], int arrLength, enCharType CharType, int WordLength) {
		for (int i = 0; i < arrLength; i++) {
			arr[i] = GenerateWord(CharType, WordLength);
		}
	}

	static void FillArrayWithRandomKeys(string arr[100], int arrLength, enCharType CharType) {
		for (int i = 0; i < arrLength; i++) {
			arr[i] = GenerateKey(CharType);
		}
	}

	static string Tabs(short NumberOfTabs) {
		string t = "";
		for (short i = 0; i < NumberOfTabs; i++) {
			t += "\t";
			cout << "\t";
		}
		return t;
	}

	static string NumberToText(int Number) {
		if (Number == 0)
			return "";
		
		if (Number >= 1 && Number <= 19)
		{
			string arr[] = { "","One","Two","Three","Four","Five","Six","Seven","Eight","Nine","Ten",
			"Eleven","Twelve","Thirteen","Fourteen","Fifteen","Sixteen","Seventeen","Eighteen","Nineteen" };
			return arr[Number] + " ";
		}
		
		if (Number >= 20 && Number <= 99) {
			string arr[] = { "","","Twenty","Thirty","Fourty","Fifty","Sixty","Seventy","Eighty","Ninety" };
			return arr[Number / 10] + " " + NumberToText(Number % 10);
		}

		if (Number >= 100 && Number <= 199) {
			return "One Hundred " + NumberToText(Number % 100);
		}

		if (Number >= 200 && Number <= 999) {
			return NumberToText(Number / 100) + "Hundreds " + NumberToText(Number % 100);
		}

		if (Number >= 1000 && Number <= 1999) {
			return "One Thousand " + NumberToText(Number % 1000);
		}

		if (Number >= 2000 && Number <= 999999){
			return NumberToText(Number / 1000) + "Thousands " + NumberToText(Number % 1000);
		}

		if (Number >= 1000000 && Number <= 1999999) {
			return "One Million " + NumberToText(Number % 1000000);
		}

		if (Number >= 2000000 && Number <= 999999999) {
			return NumberToText(Number / 1000000) + "Millions " + NumberToText(Number % 1000000);

		}

		if (Number >= 1000000000 && Number <= 1999999999) {
			return "One Billion " + NumberToText(Number % 1000000000);
		}
		else
		{
			return NumberToText(Number / 1000000000) + "Billions " + NumberToText(Number % 1000000000);
		}

	}

};


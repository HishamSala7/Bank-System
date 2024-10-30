

#pragma once

#include <iostream>
#include <cctype>
#include <vector>
using namespace std;

class clsString
{

private:
    string _Value;

public:

    clsString()
    {
        _Value = "";
    }

    clsString(string Value)
    {
        _Value = Value;
    }

    void SetValue(string Value) {
        _Value = Value;
    }

    string GetValue() {
        return _Value;
    }

    __declspec(property(get = GetValue, put = SetValue)) string Value;

    static short CountWords(string S1)
    {

        string delim = " "; // delimiter  
        short Counter = 0;
        short pos = 0;
        string sWord; // define a string variable  

        // use find() function to get the position of the delimiters  
        while ((pos = S1.find(delim)) != std::string::npos)
        {
            sWord = S1.substr(0, pos); // store the word   
            if (sWord != "")
            {
                Counter++;
            }

            //erase() until positon and move to next word.
            S1.erase(0, pos + delim.length());
        }

        if (S1 != "")
        {
            Counter++; // it counts the last word of the string.
        }

        return Counter;

    }

    short CountWords()
    {
        return CountWords(_Value);
    };

    static short Length(string s) {
        /*
        int Counter = 0;
        int i = 0;
        while (s[i] != '\0')
        {
            Counter++;
            i++;
        }
        return Counter;*/
        return s.length();
    }

    short Length() {
        return _Value.length();
    }

    char At(short Index) {
        return _Value[Index];
    }

    void Append(string s) {
        _Value = _Value + s;
    }

    static void PrintFirstLetterOfEachWord(string s) {
        bool IsFirstLetter = true;
        cout << "\nFirst Letter of this string: \n";
        for (short i = 0; i < s.length(); i++) {
            if (s[i] != ' ' && IsFirstLetter)
                cout << s[i] << endl;

            IsFirstLetter = (s[i] == ' ' ? true : false);
        }
    }

    void PrintFirstLetterOfEachWord() {
        PrintFirstLetterOfEachWord(_Value);
    }

    static string UpperFirstLetterOfEachWord(string s) {
        bool IsFirstLetter = true;
        for (short i = 0; i < s.length(); i++) {
            if (s[i] != ' ' && IsFirstLetter)
                s[i] = toupper(s[i]);

            IsFirstLetter = (s[i] == ' ' ? true : false);
        }
        return s;
    }

    void UpperFirstLetterOfEachWord() {
        _Value = UpperFirstLetterOfEachWord(_Value);
    }

    static string LowerFirstLetterOfEachWord(string s) {
        bool IsFirstLetter = true;
        for (short i = 0; i < s.length(); i++) {
            if (s[i] != ' ' && IsFirstLetter)
                s[i] = tolower(s[i]);

            IsFirstLetter = (s[i] == ' ' ? true : false);
        }
        return s;
    }

    void LowerFirstLetterOfEachWord() {
        _Value = LowerFirstLetterOfEachWord(_Value);
    }

    static string UpperAllString(string s) {
        for (short i = 0; i < s.length(); i++) {
            s[i] = toupper(s[i]);
        }
        return s;
    }

    void UpperAllString() {
        _Value = UpperAllString(_Value);
    }

    static string LowerAllString(string s) {
        for (short i = 0; i < s.length(); i++) {
            s[i] = tolower(s[i]);
        }
        return s;
    }

    void LowerAllString() {
        _Value = LowerAllString(_Value);
    }

    static char InvertLetterCase(char ch) {
        return isupper(ch) ? tolower(ch) : toupper(ch);
    }

    static string InvertAllLettersCase(string s) {
        for (short i = 0; i < s.length(); i++) {
            s[i] = InvertLetterCase(s[i]);
        }
        return s;
    }

    void InvertAllLettersCase() {
        _Value = InvertAllLettersCase(_Value);
    }

    enum enWhatToCount { SmallLetters = 0, CapitalLetters = 1, All = 3 };

    static short CountLetters(string s, enWhatToCount WhatToCount = enWhatToCount::All) {
        if (WhatToCount == enWhatToCount::All)
            return s.length();
        short Counter = 0;
        for (short i = 0; i < s.length(); i++) {
            if (isupper(s[i]) && WhatToCount == enWhatToCount::CapitalLetters)
                Counter++;
            if (islower(s[i]) && WhatToCount == enWhatToCount::SmallLetters)
                Counter++;
        }
        return Counter;
    }

    static int CountCapitalLetters(string s) {
        int Counter = 0;
        for (short i = 0; i < s.length(); i++) {
            if (isupper(s[i]))
                Counter++;
        }
        return Counter;
    }

    int CountCapitalLetters() {
        return CountCapitalLetters(_Value);
    }

    static int CountSmallLetters(string s) {
        int Counter = 0;
        for (short i = 0; i < s.length(); i++) {
            if (islower(s[i]))
                Counter++;
        }
        return Counter;
    }

    int CountSmallLetters() {
        return CountSmallLetters(_Value);
    }

    static short CountSpecificLetter(string s, char ch, bool IsMatchCase = true) {
        short Counter = 0;
        for (short i = 0; i < s.length(); i++) {
            if (IsMatchCase) {
                if (s[i] == ch)
                    Counter++;
            }
            else {
                if (tolower(s[i]) == tolower(ch))
                    Counter++;
            }
        }
        return Counter;
    }

    short CountSpecificLetter(char ch, bool IsMatchCase = true) {
        return CountSpecificLetter(_Value, ch, IsMatchCase);
    }

    static bool IsVowel(char ch) {
        ch = tolower(ch);
        return (ch == 'a' || ch == 'o' || ch == 'e' || ch == 'u' || ch == 'i');
    }

    static short CountVowels(string s) {
        short Counter = 0;
        for (short i = 0; i < s.length(); i++) {
            if (IsVowel(s[i]))
                Counter++;
        }
        return Counter;
    }

    short CountVowels() {
        return CountVowels(_Value);
    }

    static void PrintAllVowels(string s) {
        cout << "\nVowels in string are: ";
        for (short i = 0; i < s.length(); i++) {
            if (IsVowel(s[i]))
                cout << s[i] << " ";
        }
        cout << endl;
    }

    void PrintAllVowels() {
        PrintAllVowels(_Value);
    }

    static void PrintEachWordInString(string s) {
        string sWord = "";
        string Delim = " ";
        short pos = 0;
        cout << "\nyour string words are: \n\n";
        while ((pos = s.find(Delim)) != std::string::npos)
        {
            sWord = s.substr(0, pos);
            if (sWord != "")
                cout << sWord << endl;
            s.erase(0, pos + Delim.length());
        }

        if (s != "")
            cout << s << endl;
    }

    void PrintEachWordInString() {
        PrintEachWordInString(_Value);
    }

    static vector<string> Split(string s, string Delim) {
        vector<string> vString;
        short pos = 0;
        string sWord = "";
        while ((pos = s.find(Delim)) != s.npos)
        {
            sWord = s.substr(0, pos);
            //if (sWord != "")
                vString.push_back(sWord);
            s.erase(0, pos + Delim.length());
        }
        if (s != "")
            vString.push_back(s);

        return vString;
    }

    vector<string> Split(string Delim) {
        return Split(_Value,Delim);
    }

    static string TrimLeft(string s) {
        /*if (s[0] != ' ')
            return s;
        return TrimLeft(s.substr(1, s.length() - 1));*/

        for (short i = 0; i < s.length(); i++) {
            if (s[i] != ' ')
                return s.substr(i, s.length() - i);
        }
        return "";

    }

    void TrimLeft() {
        _Value = TrimLeft(_Value);
    }

    static string TrimRight(string s) {
        /*if (s[s.length() - 1] != ' ')
            return s;
        return TrimRight(s.substr(0, s.length() - 2));*/

        for (short i = s.length() - 1; i >= 0; i--) {
            if (s[i] != ' ')
                return s.substr(0, i + 1);
        }
        return "";
    }

    void TrimRight() {
        _Value = TrimRight(_Value);
    }

    static string Trim(string s) {
        return TrimLeft(TrimRight(s));
    }

    void Trim() {
        _Value = Trim(_Value);
    }

    static string JoinString(vector<string> vString, string Delim = " ") {
        string s = "";
        for (string Word : vString) {
            s = s + Word + Delim;
        }
        return s.substr(0, s.length() - Delim.length());
    }

    static string JoinString(string arrString[], short Length, string Delim = " ") {
        string s = "";
        for (short i = 0; i < Length; i++) {
            s = s + arrString[i] + Delim;
        }
        return s.substr(0, s.length() - Delim.length());
    }

    static string ReverseWordsInString(string s) {
        string ReversedString = "";
        string sWord;
        for (short i = s.length() - 1; i >= 0; i--) {
            if (s[i] == ' ') {
                sWord = s.substr(i + 1, s.length() - 1);
                if (sWord != "")
                    ReversedString += sWord + ' ';
                s.erase(i, s.length() - 1);
            }
        }

        if (s != "")
            ReversedString += s;

        return ReversedString;
    }

    void ReverseWordsInString() {
        _Value = ReverseWordsInString(_Value);
    }

    static string ReverseWordsInString2(string s) {
        vector<string>vString = Split(s," ");
        vector<string>::iterator iter = vString.end();
        string ReversedString = "";
        while (iter != vString.begin())
        {
            --iter;
            ReversedString += *iter + " ";
        }

        return ReversedString.substr(0, ReversedString.length() - 1);
    }

    void ReverseWordsInString2() {
        _Value = ReverseWordsInString2(_Value);
    }

    /*static string ReplaceWordsInString(string s, string StringToReplace, string ReplaceTo) {
        short pos = s.find(StringToReplace);
        short Length = StringToReplace.length();
        string NewString = "";
        while (pos != s.npos)
        {
            NewString = s.substr(0, pos);
            NewString += ReplaceTo + " ";
            NewString += s.substr(pos + Length, s.length() - 1);
            s = NewString;
            pos = s.find(StringToReplace);
        }
        return NewString;
    }

    static string ReplaceWordsInString2(string s, string StringToReplace, string ReplaceTo) {
        short pos = 0;
        while ((pos = s.find(StringToReplace)) != s.npos)
        {
            s.erase(pos, StringToReplace.length());
            s.insert(pos, ReplaceTo);
        }
        return s;
    }

    static string ReplaceWordInStringUsingBuiltInFunction(string s, string StringToReplace, string ReplaceTo) {
        short pos = s.find(StringToReplace);

        while (pos != s.npos)
        {
            s.replace(pos, StringToReplace.length(), ReplaceTo);
            pos = s.find(StringToReplace);
        }
        return s;
    }*/

    static string ReplaceWords(string s, string  StringToReplace, string ReplaceTo, bool IsMatchCase = true) {
        vector<string> vString = Split(s, " ");
        for (string& Word : vString) {
            if (IsMatchCase) {
                if (Word == StringToReplace)
                    Word = ReplaceTo;
            }
            else
            {
                if (LowerAllString(Word) == LowerAllString(StringToReplace))
                    Word = ReplaceTo;   
            }
        }
        return JoinString(vString, " ");
    }

    string ReplaceWords(string StringToReplace, string ReplaceTo, bool IsMatchCase = true) {
        return ReplaceWords(_Value, StringToReplace, ReplaceTo, IsMatchCase);
    }

    /*static string RemovePunctuation(string s) {
        for (short i = 0; i < s.length(); i++) {
            if (ispunct(s[i])) {
                s.erase(i, 1);
                --i;
            }
        }
        return s;
    }*/

    static string RemovePunctuations2(string s) {
        string s1 = "";
        for (short i = 0; i < s.length(); i++) {
            if (!ispunct(s[i])) {
                s1 += s[i];
            }
        }
        return s1;
    }

    void RemovePunctuations() {
        _Value = RemovePunctuations2(_Value);
    }

};

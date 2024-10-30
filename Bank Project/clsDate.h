#pragma once
#pragma warning (disable:4996)

#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include <iomanip>
#include "clsString.h"

using namespace std;

class clsDate
{
private:
	short _Day;
	short _Month;
	short _Year;

public:
	
	clsDate() {
		time_t t = time(0);
		tm* now = localtime(&t);
		_Day = now->tm_mday;
		_Month = now->tm_mon + 1;
		_Year = now->tm_year + 1900;
	}

	clsDate(string Date) {
		vector<string> vDate = clsString::Split(Date, "/");
		_Day = stoi(vDate[0]);
		_Month = stoi(vDate[1]);
		_Year = stoi(vDate[2]);
	}

	clsDate(short Day, short Month, short Year) {
		_Day = Day;
		_Month = Month;
		_Year = Year;
	}

	clsDate(short DayOrderInYear, short Year) {
		clsDate Date = GetDateFromDayOrderInYear(DayOrderInYear,Year);
		_Day = Date._Day;
		_Month = Date._Month;
		_Year = Date._Year;
	}

	void SetDay(short Day) {
		_Day = Day;
	}

	short GetDay() {
		return _Day;
	}

	__declspec(property(get = GetDay, put = SetDay)) short Day;

	void SetMonth(short Month) {
		_Month = Month;
	}

	short GetMonth() {
		return _Month;
	}

	__declspec(property(get = GetMonth, put = SetMonth)) short Month;

	void SetYear(short Year) {
		_Year = Year;
	}

	short GetYear() {
		return _Year;
	}

	__declspec(property(get = GetYear, put = SetYear)) short Year;

	static clsDate GetSystemDate() {
		short Day, Month, Year;
		time_t t = time(0);
		tm* now = localtime(&t);
		Day = now->tm_mday;
		Month = now->tm_mon + 1;
		Year = now->tm_year + 1900;
		return clsDate(Day, Month, Year);
	}

	static string GetSystemDateTimeString() {
		time_t t = time(0);
		tm* now = localtime(&t);
		short Day, Month, Year, Hour, Minute, Second;

		Day = now->tm_mday;
		Month = now->tm_mon + 1;
		Year = now->tm_year + 1900;
		Hour = now->tm_hour;
		Minute = now->tm_min;
		Second = now->tm_sec;

		return (to_string(Day) + "/" + to_string(Month) + "/" + to_string(Year) + " - " +
			to_string(Hour) + ":" + to_string(Minute) + ":" + to_string(Second));
		
	}

	void Print() {
		cout << DateToString() << endl;
	}

	static string DateToString(clsDate Date) {
		return to_string(Date._Day) + '/' + to_string(Date._Month) + '/' + to_string(Date._Year);
	}

	string DateToString() {
		return DateToString(*this);
	}

	static bool IsLeapYear(short Year) {
		return ((Year % 400 == 0) || (Year % 4 == 0 && Year % 100 != 0));
	}

	bool IsLeapYear() {
		return IsLeapYear(_Year);
	}

	static short NumberOfDaysInMonth(short Month, short Year) {
		if (Month < 1 || Month >12)
			return 0;

		int Days[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
		return Month == 2 ? (IsLeapYear(Year) ? 29 : 28) : Days[Month];
	}

	short NumberOfDaysInMonth() {
		return NumberOfDaysInMonth(_Month, _Year);
	}

	static clsDate GetDateFromDayOrderInYear(short DayOrderInYear, short Year) {
		clsDate Date ;
		short RemainingDays = DayOrderInYear;
		Date._Month = 1;
		Date._Year = Year;
		short DaysInMonth = NumberOfDaysInMonth(Date._Month, Date._Year);

		while (true)
		{
			DaysInMonth = NumberOfDaysInMonth(Date._Month, Date._Year);
			if (RemainingDays > DaysInMonth) {
				Date._Month++;
				RemainingDays -= DaysInMonth;
			}
			else
			{
				Date._Day = RemainingDays;
				break;
			}
		}
		return Date;

		/*string Date;
		short RemainingDays = DayOrderInYear;
		short MonthDays = 0;
		short Month = 1;
		while (true)
		{
			MonthDays = NumberOfDaysInMonth(Month, Year);
			if (RemainingDays > MonthDays) {
				Month++;
				RemainingDays -= MonthDays;
			}
			else
			{
				Date = to_string(RemainingDays) + '/' + to_string(Month) + '/' + to_string(Year);
				break;
			}
		}
		return Date;*/
	}

	static bool IsValidDate(clsDate Date) {

		if (Date._Year < 1)
			return false;
		if (Date._Month < 1 || Date._Month >12)
			return false;
		if (Date._Month == 2) {
			if (IsLeapYear(Date._Year)) {
				if (Date._Day > 29)
					return false;
			}
			else
			{
				if (Date._Day > 28)
					return false;
			}
		}
		short DaysInMonth = NumberOfDaysInMonth(Date._Month, Date._Year);
		if (Date._Day > DaysInMonth || Date._Day < 1)
			return false;
		return true;
	}

	bool IsValid() {
		return IsValidDate(*this);
	}

	static short DaysInYear(short Year) {
		return IsLeapYear(Year) ? 366 : 365;
	}

	short DaysInYear() {
		return DaysInYear(_Year);
	}

	static int HoursInYear(int Year) {
		return DaysInYear(Year) * 24;
	}

	int HoursInYear() {
		return HoursInYear(_Year);
	}

	static int MinutesInYear(int Year) {
		return HoursInYear(Year) * 60;
	}

	int MinutesInYear() {
		return MinutesInYear(_Year);
	}

	static int SecondsInYear(int Year) {
		return MinutesInYear(Year) * 60;
	}

	int SecondsInYear() {
		return SecondsInYear(_Year);
	}

	static void DaysHoursMinutesSecondsInYear(int Year) {

		cout << "\nNumber of Days    in Year [" << Year << "] is " << DaysInYear(Year) << endl;
		cout << "Number of Hours   in Year [" << Year << "] is " << HoursInYear(Year )<< endl;
		cout << "Number of Minutes in Year [" << Year << "] is " << MinutesInYear(Year) << endl;
		cout << "Number of Seconds in Year [" << Year << "] is " << SecondsInYear(Year) << endl;

	}

	void DaysHoursMinutesSecondsInYear() {
		DaysHoursMinutesSecondsInYear(_Year);
	}

	static int HoursInMonth(short Year, short Month) {
		return NumberOfDaysInMonth(Month,Year) * 24;
	}

	int HoursInMonth() {
		return HoursInMonth(_Year, _Month);
	}

	static int MinutesInMonth(int Year, int Month) {
		return HoursInMonth(Year, Month) * 60;
	}

	int MinutesInMonth() {
		return MinutesInMonth(_Year, _Month);
	}

	static int SecondsInMonth(int Year, int Month) {
		return MinutesInMonth(Year,Month) * 60;
	}

	int SecondsInMonth() {
		return SecondsInMonth(_Year, _Month);
	}

	void DaysHoursMinutesSecondsInMonth(int Year, int Month) {

		cout << "\nNumber of Days    in Month [" << Month << "] is " << NumberOfDaysInMonth(Month,Year) << endl;
		cout << "Number of Hours   in Month [" << Month << "] is " << HoursInMonth(Year,Month) << endl;
		cout << "Number of Minutes in Month [" << Month << "] is " << MinutesInMonth(Year,Month) << endl;
		cout << "Number of Seconds in Month [" << Month << "] is " << SecondsInMonth(Year,Month) << endl;

	}

	static short DayOfWeekOrder(int Year, int Month, int Day) {
		short a = floor((14 - Month) / 12);
		short y = Year - a;
		short m = Month + (12 * a) - 2;

		return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
	}

	short DayOfWeekOrder() {
		return DayOfWeekOrder(_Year, _Month, _Day);
	}

	static string DayShortName(int Year, int Month, int Day) {
		short DayOrder = DayOfWeekOrder(Year, Month, Day);
		string Week[] = { "Sun", "Mon","Tue","Wed","Thu","Fri","Sat" };
		return Week[DayOrder];
	}

	static string DayShortName(short DayOfWeekOrder) {
		string Week[] = { "Sun", "Mon","Tue","Wed","Thu","Fri","Sat" };
		return Week[DayOfWeekOrder];
	}
	
	string DayShortName() {
		return DayShortName(_Year, _Month, _Day);
	}

	static string MonthShortName(short Month) {
		string MonthArr[] = { "","Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec" };
		return MonthArr[Month];
	}

	string MonthShortName() {
		return MonthShortName(_Month);
	}

	static void PrintMonthCalendar(short Year, short Month) {
		//cout << "\n  ______________" << MonthShortName(Month) << "________________\n\n";
		printf("\n  _______________%s_______________\n\n", MonthShortName(Month).c_str());
		cout << "  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n";
		short Current = DayOfWeekOrder(Year, Month, 1);
		short NumberOfDays = NumberOfDaysInMonth(Month, Year);
		int i;
		for ( i = 0; i < Current; i++)
			cout << "     ";
		for (short j = 1; j <= NumberOfDays; j++) {
			printf("%5d", j);
			if (++i == 7) {
				i = 0;
				printf("\n");
			}
		}
		cout << "\n  _________________________________\n";
		
	}

	void PrintMonthCalendar() {
		PrintMonthCalendar(_Year, _Month);
	}

	static void PrintYearCalendar(short Year) {
		cout << "\n\n  _________________________________\n";
		cout << "\n         Calendar - " << Year << endl;
		cout << "  _________________________________\n\n";

		for (short i = 1; i <= 12; i++) 
			PrintMonthCalendar(Year, i);
	}

	void PrintYearCalendar() {
		PrintYearCalendar(_Year);
	}

	static short DaysFromTheBeginingOfTheYear(short Day, short Month, short Year) {
		short TotalDays = 0;
		for (short i = 1; i < Month; i++)
			TotalDays += NumberOfDaysInMonth(i, Year);
		return TotalDays + Day;
	}

	short DaysFromTheBeginingOfTheYear() {
		return DaysFromTheBeginingOfTheYear(_Day, _Month, _Year);
	}

	void AddDays(short Days) {
		short RemainingDays = Days + DaysFromTheBeginingOfTheYear(_Day, _Month, _Year);
		_Month = 1;
		short MonthDays = 0;
		while (true)
		{
			MonthDays = NumberOfDaysInMonth(_Month, _Year);
			if (RemainingDays > MonthDays) {
				_Month++;
				RemainingDays -= MonthDays;
				if (_Month > 12) {
					_Month = 1;
					_Year++;
				}
			}
			else
			{
				_Day = RemainingDays;
				break;
			}
		}
	}

	static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2) {
		return (Date1._Year < Date2._Year) ? true : ((Date1._Year == Date2._Year) ? (Date1._Month < Date2._Month ? true :
			(Date1._Month == Date2._Month) ? (Date1._Day < Date2._Day) : false) : false);
	}

	bool IsDateBeforeDate2(clsDate Date2) {
		return IsDate1BeforeDate2(*this, Date2);
	}

	static bool IsDate1EqualDate2(clsDate Date1, clsDate Date2) {
		return (Date1._Year == Date2._Year) ? ((Date1._Month == Date2._Month) ? (Date1._Day == Date2._Day) : false) : false;
	}
	
	static bool IsLastDayInMonth(clsDate Date) {
		return Date._Day == NumberOfDaysInMonth(Date._Month, Date._Year);
	}

	bool IsLastDayInMonth() {
		return IsLastDayInMonth(*this);
	}

	static bool IsLastMonthInYear(short Month) {
		return Month == 12;
	}

	static clsDate AddOneDay(clsDate Date) {
		if (IsLastDayInMonth(Date)) {
			if (IsLastMonthInYear(Date._Month)) {
				Date._Month = 1;
				Date._Day = 1;
				Date._Year++;
			}
			else {
				Date._Month++;
				Date._Day = 1;
			}
		}
		else
			Date._Day++;

		return Date;
	}

	clsDate AddOneDay() {
		return AddOneDay(*this);
	}

	static void SwapDates(clsDate& Date1, clsDate& Date2) {
		clsDate TempDate;
		TempDate = Date1;
		Date1 = Date2;
		Date2 = TempDate;
	}

	static int GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false) {
		
		if (IsDate1EqualDate2(Date1, Date2))
			return 0;

		int DiffDays = 0;
		short SwapFlagValue = 1;
		clsDate Temp = Date1;

		if (!IsDate1BeforeDate2(Date1, Date2)) {
			SwapDates(Date1, Date2);
			SwapFlagValue = -1;
		}
		
		while (IsDate1BeforeDate2(Temp,Date2))
		{
			DiffDays++;
			Temp = AddOneDay(Temp);
		}
		
		if (SwapFlagValue == -1)
			SwapDates(Date1, Date2);

		return IncludeEndDay ? ++DiffDays * SwapFlagValue : DiffDays * SwapFlagValue;
	}

	int GetDifferenceInDays(clsDate Date2, bool IncludeEndDay = false) {
		return GetDifferenceInDays(*this, Date2, IncludeEndDay);
	}

	static int CalculateMyAgeInDays(clsDate DateOfBirth) {
		return GetDifferenceInDays(DateOfBirth, clsDate::GetSystemDate(), true);
	}

	static clsDate IncreaseDateByXDays(clsDate& Date, int Days) {
		for (int i = 0; i < Days; i++) {
			Date = AddOneDay(Date);
		}
		return Date;
	}

	void IncreaseDateByXDays(int Days) {
		 IncreaseDateByXDays(*this, Days);
	}

	static clsDate IncreaseDateByOneWeek(clsDate& Date) {
		for (short i = 0; i < 7; i++)
			Date = AddOneDay(Date);
		return Date;
	}

	void IncreaseDateByOneWeek() {
		IncreaseDateByOneWeek(*this);
	}

	static clsDate IncreaseDateByXWeeks(clsDate& Date, short Weeks) {
		for (short i = 0; i < Weeks; i++)
			Date = IncreaseDateByOneWeek(Date);
		return Date;
	}

	void IncreaseDateByXWeeks(short Weeks) {
		IncreaseDateByXWeeks(*this, Weeks);
	}

	static clsDate IncreaseDateByOneMonth(clsDate& Date) {

		if (IsLastMonthInYear(Date._Month))
		{
			Date._Month = 1;
			Date._Year++;
		}
		else
			Date._Month++;
		
		short NumberOfDaysInCurrentMonth = NumberOfDaysInMonth(Date._Month , Date._Year);
		if (Date._Day > NumberOfDaysInCurrentMonth) {
			Date._Day = NumberOfDaysInCurrentMonth;
		}

		return Date;
	}

	void IncreaseDateByOneMonth() {
		IncreaseDateByOneMonth(*this);
	}

	static clsDate IncreaseDateByXMonths(clsDate& Date, short Months) {
		for (short i = 0; i < Months; i++)
			Date = IncreaseDateByOneMonth(Date);
		return Date;
	}

	void IncreaseDateByXMonths(short Months) {
		IncreaseDateByXMonths(*this, Months);
	}

	static clsDate IncreaseDateByOneYear(clsDate& Date) {
		if (IsLeapYear(Date._Year) && Date._Month == 2 && Date._Day == 29)
			Date._Day = 28;
		Date._Year++;
		return Date;
	}

	void IncreaseDateByOneYear() {
		IncreaseDateByOneYear(*this);
	}

	static clsDate IncreaseDateByXYears(clsDate& Date, short Years) {
		for (short i = 0; i < Years; i++)
			Date = IncreaseDateByOneYear(Date);
		return Date;
	}

	void IncreaseDateByXYears(short Years) {
		IncreaseDateByXYears(*this, Years);
	}

	static clsDate IncreaseDateByOneDecade(clsDate& Date) {
		Date._Year += 10;
		return Date;
	}

	void IncreaseDateByOneDecade() {
		IncreaseDateByOneDecade(*this);
	}

	static clsDate IncreaseDateByXDecade(clsDate& Date, short Decades) {
		Date._Year += 10 * Decades;
		return Date;
	}

	void IncreaseDateByXDecade(short Decades) {
		IncreaseDateByXDecade(*this, Decades);
	}

	static clsDate IncreaseDateByOneCentury(clsDate& Date) {
		Date._Year += 100;
		return Date;
	}

	void IncreaseDateByOneCentury() {
		IncreaseDateByOneCentury(*this);
	}

	static clsDate IncreaseDateByOneMillennium(clsDate& Date) {
		Date._Year += 1000;
		return Date;
	}

	void IncreaseDateByOneMillennium() {
		IncreaseDateByOneMillennium(*this);
	}

	static clsDate DecreseDateByOneDay(clsDate& Date) {
		if (Date._Day == 1) {
			if (Date._Month == 1) {
				Date._Month = 12;
				Date._Year--;
				Date._Day = NumberOfDaysInMonth(Date._Month, Date._Year);
			}
			else
			{
				Date._Month--;
				Date._Day = NumberOfDaysInMonth(Date._Month, Date._Year);
			}
		}
		else
			Date._Day--;
		return Date;
	}

	void DecreseDateByOneDay() {
		DecreseDateByOneDay(*this);
	}

	static clsDate DecreseDateByXDays(clsDate& Date, short Days) {
		for (short i = 0; i < Days; i++)
			Date = DecreseDateByOneDay(Date);
		return Date;
	}

	void DecreseDateByXDays(short Days) {
		DecreseDateByXDays(*this, Days);
	}

	static clsDate DecreseDateByOneWeek(clsDate& Date) {
		return DecreseDateByXDays(Date, 7);
	}

	void DecreseDateByOneWeek() {
		DecreseDateByOneWeek(*this);
	}

	static clsDate DecreseDateByXWeeks(clsDate& Date, short Weeks) {
		for (short i = 0; i < Weeks; i++)
			Date = DecreseDateByOneWeek(Date);
		return Date;
	}

	void DecreseDateByXWeeks(short Weeks) {
		DecreseDateByXWeeks(*this, Weeks);
	}

	static clsDate DecreaseDateByOneMonth(clsDate& Date) {
		if (Date._Month == 1) {
			Date._Month = 12;
			Date._Year--;
		}
		else
		{
			Date._Month--;
			short NumberOfDaysInCurrentMonth = NumberOfDaysInMonth(Date._Month, Date._Year);
			
			if (Date._Day > NumberOfDaysInCurrentMonth)
				Date._Day = NumberOfDaysInCurrentMonth;
		}
		return Date;
	}

	void DecreaseDateByOneMonth() {
		DecreaseDateByOneMonth(*this);
	}

	static clsDate DecreaseDateByXMonths(clsDate& Date, short Months) {
		for (short i = 0; i < Months; i++)
			Date = DecreaseDateByOneMonth(Date);
		return Date;
	}

	void DecreaseDateByXMonths(short Months) {
		DecreaseDateByXMonths(*this, Months);
	}

	static clsDate DecreaseDateByOneYear(clsDate& Date) {
		if (Date._Month == 2 && Date._Day == 29)
			Date._Day = 28;
		Date._Year--;
		return Date;
	}

	void DecreaseDateByOneYear() {
		DecreaseDateByOneYear(*this);
	}

	static clsDate DecreaseDateByXYears(clsDate& Date, short Years) {
		for (short i = 0; i < Years; i++)
			Date = DecreaseDateByOneYear(Date);
		return Date;
	}

	void DecreaseDateByXYears(short Years) {
		DecreaseDateByXYears(*this, Years);
	}

	static clsDate DecreaseDateByOneDecade(clsDate& Date) {
		Date._Year -= 10;
		return Date;
	}

	void DecreaseDateByOneDecade() {
		DecreaseDateByOneDecade(*this);
	}

	static clsDate DecreaseDateByXDecades(clsDate& Date, short Decades) {
		Date._Year -= 10 * Decades;
		return Date;
	}

	void DecreaseDateByXDecades(short Decades) {
		DecreaseDateByXDecades(*this, Decades);
	}

	static clsDate DecreaseDateByOneCentury(clsDate& Date) {
		Date._Year -= 100;
		return Date;
	}

	void DecreaseDateByOneCentury() {
		DecreaseDateByOneCentury(*this);
	}

	static clsDate DecreaseDateByOneMillennium(clsDate& Date) {
		Date._Year -= 1000;
		return Date;
	}

	void DecreaseDateByOneMillennium() {
		DecreaseDateByOneMillennium(*this);
	}

	static bool IsEndOfWeek(clsDate Date) {
		return DayOfWeekOrder(Date._Year, Date._Month, Date._Day) == 6;
	}

	bool IsEndOfWeek() {
		return IsEndOfWeek(*this);
	}

	static bool IsWeekEnd(clsDate Date) {
		short DayIndex = DayOfWeekOrder(Date._Year, Date._Month, Date._Day);
		return (DayIndex == 5 || DayIndex == 6);
	}

	bool IsWeekEnd() {
		return IsWeekEnd(*this);
	}

	static bool IsBusinessDay(clsDate Date) {
		return !IsWeekEnd(Date);
	}

	bool IsBusinessDay() {
		return IsBusinessDay(*this);
	}

	static short DaysUntillTheEndOfWeek(clsDate Date) {
		return 6 - DayOfWeekOrder(Date._Year, Date._Month, Date._Day);
	}

	short DaysUntillTheEndOfWeek() {
		return DaysUntillTheEndOfWeek(*this);
	}

	static short DaysUntillTheEndOfMonth(clsDate Date) {
		clsDate EndOfMonth;
		EndOfMonth._Day = NumberOfDaysInMonth(Date._Month, Date._Year);
		EndOfMonth._Month = Date._Month;
		EndOfMonth._Year = Date._Year;

		return GetDifferenceInDays(Date, EndOfMonth, true);
	}

	short DaysUntillTheEndOfMonth() {
		return DaysUntillTheEndOfMonth(*this);
	}

	static short DaysUntillTheEndOfYear(clsDate Date) {
		clsDate EndOfTheYear(31, 12, Date._Year);
		return GetDifferenceInDays(Date, EndOfTheYear, true);
	}

	short DaysUntillTheEndOfYear() {
		return DaysUntillTheEndOfYear(*this);
	}

	static short CalculateVacationDays(clsDate DateFrom, clsDate DateTo) {
		short Days = 0;
		while (IsDate1BeforeDate2(DateFrom,DateTo))
		{
			if (IsBusinessDay(DateFrom))
				Days++;
			DateFrom = AddOneDay(DateFrom);
		}
		return Days;
	}

	static clsDate CalculateVacationReturnDate(clsDate DateFrom, short VacationDays) {
		/*clsDate	ReturnDate;
		ReturnDate = DateFrom;
		while (VacationDays > 0)
		{
			if (IsWeekEnd(ReturnDate)) 
				VacationDays++;
			AddOneDay(ReturnDate);
			VacationDays--;
		}
		return ReturnDate;*/

		short WeekEndCounter = 0;

		while (IsWeekEnd(DateFrom))
		{
			DateFrom = AddOneDay(DateFrom);
		}

		for (short i = 0; i < VacationDays + WeekEndCounter; i++) {
			if (IsWeekEnd(DateFrom))
				WeekEndCounter++;
			DateFrom = AddOneDay(DateFrom);
		}

		while (IsWeekEnd(DateFrom))
		{
			DateFrom = AddOneDay(DateFrom);
		}
		return DateFrom;
	}

	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2) {
		return (Date1._Year > Date2._Year) ? true : (Date1._Year == Date2._Year ? (Date1._Month > Date2._Month ? true :
			(Date1._Month == Date2._Month) ? (Date1._Day > Date2._Day) : false) : false);
	}

	enum enDateCompare { Before = -1, Equal = 0, After = 1 };

	static enDateCompare CompareDates(clsDate Date1, clsDate Date2) {
		if (IsDate1EqualDate2(Date1, Date2))
			return enDateCompare::Equal;
		if (IsDate1BeforeDate2(Date1, Date2))
			return enDateCompare::Before;
		return enDateCompare::After;
	}


};


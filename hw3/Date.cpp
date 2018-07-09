#include <iostream>
#include "Date.h"

const int Date::days[] = 
{ 0, 31, 28, 31, 30, 31, 30,
31, 31, 30, 31, 30, 31 };

//建構日期
Date::Date(int m, int d, int y)
{
	setDate(m, d, y); 
}
//傳到setData設定日期
void Date::setDate(int m1, int d1, int y1)
{
	//檢查月份
	if (m1 >= 1 && m1 <= 12)
		month = m1;
	else
		month = 1;
	//檢查年份
	if (y1 >= 1900 && y1 <= 2100)
		year = y1;
	else
		year = 1900;
	//檢查日期
	if (month == 2 && leapyear(year)) //閏年的情況
	{
		if (d1 >= 1 && d1 <= 29)
			day = d1;
		else
			day = 1;
	}
	else //非閏年的情況
	{
		if (d1 >= 1 && d1 <= days[month])
			day = d1;
		else
			day = 1;
	}
}
//檢查閏年函式
bool Date::leapyear(int check)
{
	if (check % 400 == 0 || (check % 100 != 0
		&& check % 4 == 0))
		return true; //是閏年
	else
		return false; //不是閏年
}

/////////////////////////////////
//多載前置運算子
Date &Date::operator++()
{
	helpIncrement();
	return *this;
}
//多載後置運算子
Date Date::operator++(int)
{
	Date init = *this;
	helpIncrement();
	return init;
}
//多載+=運算子
const Date &Date::operator+=(int add)
{
	for (int i = 0; i < add; i++)
		helpIncrement();
	return *this;
}
////////////////////////////////////
//加日期
void Date::helpIncrement()
{
	//如果不是這個月最後一天就加一天日期
	if (!endofMonth(day))
		day++;
	else
		if (month < 12) //若是當月最後一天且非12月就到下個月
		{
			month++;
			day = 1;
		}
		else //若是12月最後一天就換到下個年份
		{
			year++;
			month = 1;
			day = 1;
		}
}
//檢查當月最後一天
bool Date::endofMonth(int check) const
{
	//閏年的最後一天
	if (month == 2 && leapyear(year) == true)
		return check == 29;
	else
		return check == days[month];
}
////////////////////////////////////
ostream &operator<<(ostream &output, const Date &d)
{
	static char *monthN[13]=
	{ "", "January", "February", "March", 
	"April", "May", "June", "July", 
	"August", "September", "October", 
	"November", "December" };
	output << monthN[d.month] << " "<< d.day<< ", "<< d.year;
	return output;
}
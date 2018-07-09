#include <iostream>
#include "Date.h"

const int Date::days[] = 
{ 0, 31, 28, 31, 30, 31, 30,
31, 31, 30, 31, 30, 31 };

//�غc���
Date::Date(int m, int d, int y)
{
	setDate(m, d, y); 
}
//�Ǩ�setData�]�w���
void Date::setDate(int m1, int d1, int y1)
{
	//�ˬd���
	if (m1 >= 1 && m1 <= 12)
		month = m1;
	else
		month = 1;
	//�ˬd�~��
	if (y1 >= 1900 && y1 <= 2100)
		year = y1;
	else
		year = 1900;
	//�ˬd���
	if (month == 2 && leapyear(year)) //�|�~�����p
	{
		if (d1 >= 1 && d1 <= 29)
			day = d1;
		else
			day = 1;
	}
	else //�D�|�~�����p
	{
		if (d1 >= 1 && d1 <= days[month])
			day = d1;
		else
			day = 1;
	}
}
//�ˬd�|�~�禡
bool Date::leapyear(int check)
{
	if (check % 400 == 0 || (check % 100 != 0
		&& check % 4 == 0))
		return true; //�O�|�~
	else
		return false; //���O�|�~
}

/////////////////////////////////
//�h���e�m�B��l
Date &Date::operator++()
{
	helpIncrement();
	return *this;
}
//�h����m�B��l
Date Date::operator++(int)
{
	Date init = *this;
	helpIncrement();
	return init;
}
//�h��+=�B��l
const Date &Date::operator+=(int add)
{
	for (int i = 0; i < add; i++)
		helpIncrement();
	return *this;
}
////////////////////////////////////
//�[���
void Date::helpIncrement()
{
	//�p�G���O�o�Ӥ�̫�@�ѴN�[�@�Ѥ��
	if (!endofMonth(day))
		day++;
	else
		if (month < 12) //�Y�O���̫�@�ѥB�D12��N��U�Ӥ�
		{
			month++;
			day = 1;
		}
		else //�Y�O12��̫�@�ѴN����U�Ӧ~��
		{
			year++;
			month = 1;
			day = 1;
		}
}
//�ˬd���̫�@��
bool Date::endofMonth(int check) const
{
	//�|�~���̫�@��
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
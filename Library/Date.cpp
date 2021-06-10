#include "Date.h"

Date::Date()
{
	this->day = 0;
	this->month = 0;
	this->year = 0;
}

Date::Date(int& day, int& month, int& year)
{
	this->day = day;
	this->month = month;
	this->year = year;
}

Date::Date(const Date& other)
{
	this->day = other.day;
	this->month = other.month;
	this->year = other.year;
}

bool Date::operator>(const Date& other)
{
	if (this->year < other.year)
		return true;
	if (this->year == other.year && this->month < other.month)
		return true;
	if (this->year == other.year && this->month == other.month &&
		this->day < other.day)
		return true;

	return false;
}

bool Date::operator<(const Date& other)
{
	if (this->year > other.year)
		return true;
	if (this->year == other.year && this->month > other.month)
		return true;
	if (this->year == other.year && this->month == other.month &&
		this->day > other.day)
		return true;

	return false;
}

std::ostream& operator<<(std::ostream& out, const Date& date)
{
	out << date.day << ' ' << date.month << ' ' << date.year;
	return out;
}

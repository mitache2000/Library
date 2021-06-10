#pragma once
#include <iostream>
class Date
{
public:
	int day;
	int month;
	int year;

	Date();
	Date(int& day, int& month, int& year);
	Date(const Date& other);

	friend std::ostream& operator<<(std::ostream& out, const Date& date);
	bool operator> (const Date& other);
	bool operator< (const Date& other);
};


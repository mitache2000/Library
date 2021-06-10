#pragma once
#include <iostream>
#include "String.h"
#include "Date.h"

class Book
{
public:
	size_t id;
	String title;
	String author;
	String genre;
	String description;
	Date year;
	String keyWords;
	float rating;

	Book();
	Book(const Book& other);
	void PrintBookInformation();





};


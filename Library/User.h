#pragma once
#include <iostream>
#include "String.h"

class User
{
private:
	String name;
	String password;

public:
	User();
	User(String name, String password);
	User(const User& other);

	String getName();
	String getPassword();
	bool isAdmin();

	User& operator= (const User& other);

	friend std::istream& operator>>(std::istream& in, User& user);
};


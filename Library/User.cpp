#include "User.h"

User::User()
{
	this->name.setString("default");
	this->password.setString("default");
}

User::User(String name, String password)
{
	this->name = name;
	this->password = password;
}

User::User(const User& other)
{
	this->name = other.name;
	this->password = other.password;
}

String User::getName()
{
	return this->name;
}

String User::getPassword()
{
	return this->password;
}

bool User::isAdmin()
{
	if (name == "admin")
	{
		return true;
	}
	else return false;
}

User& User::operator=(const User& other)
{
	if (this != &other)
	{
		this->name = other.name;
		this->password = other.password;
	}
	return *this;
}

std::istream& operator>>(std::istream& in, User& user)
{
	in >> user.name >> user.password;
	return in;
}

#include "Checker.h"

bool Checker::doesUserExist(String& name, Vector<User>& allUsers)
{
	for (int i = 0; i < allUsers.getSize(); i++)
	{
		if (allUsers[i].getName() == name)
		{
			return true;
		}
	}
	return false;
}

bool Checker::doesUserLoginExist(String& name, String& password, Vector<User>& allUsers)
{
	for (int i = 0; i < allUsers.getSize(); i++)
	{
		if (allUsers[i].getName() == name && allUsers[i].getPassword() == password)
		{
			return true;
		}
	}
	return false;
}

bool Checker::DoesBookExist(String& name, Vector<Book>& allBooks)
{
	for (int i = 0; i < allBooks.getSize(); i++)
	{
		if (allBooks[i].title == name)
		{
			return true;

		}
	}
	return false;
}

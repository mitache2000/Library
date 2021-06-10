#pragma once
#include <iostream>
#include "String.h"
#include "Vector.h"
#include "User.h"
#include "Book.h"
class Checker
{
public:

	bool doesUserExist(String& name, Vector<User>& allUsers);
	bool doesUserLoginExist(String& name, String& password, Vector<User>& allUsers);
	bool DoesBookExist(String& name, Vector<Book>& allBooks);


};


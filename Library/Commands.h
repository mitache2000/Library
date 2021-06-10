#pragma once
#include <iostream>
#include <fstream>
#include "User.h"
#include "Vector.h"
#include "String.h"
#include "Book.h"
#include "Checker.h"

class Commands
{
private:
	void AddUser();
	void RemoveUser();

public:
	Vector<User> allUsers;
	Vector<Book> allBooks;
	User user;
	String filePath;

	Commands(String& path);

	Checker checker;

	bool isUserLoggedIn;

	void LogInUser();
	void LogoutUser();
	void AdminActions(String& path);

	void BookSplit();


	void SaveBooks(String& path);

	Vector<User>& allUsersFromData(Vector<User>& allUsers);
	Vector<Book>& allBooksFromData(Vector<Book>& allBooksFromFile, String& path);

	String enterUsername(String& username);
	String enterPassword(String& password);

	bool isLeap(int year);
	Date enterYear(Date& date);

	void PrintBooks(Vector<Book>& allBooksFromFile);

	void AddUserToFile(String& username, String& password);
	void RemoveUserFromFile(String& usernameToRemove, Vector<User>& allUsers);

};


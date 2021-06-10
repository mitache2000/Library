#include "Commands.h"

void Commands::AddUser()
{
	String username;
	String password;
	username = enterUsername(username);
	password = enterPassword(password);

	User newUser = User(username, password);
	this->allUsers.push_back(User(username, password));
	AddUserToFile(username, password);
}

void Commands::RemoveUser()
{
	String usernameToRemove;

	std::cout << "Enter username to remove: ";
	std::cin >> usernameToRemove;
	if (!this->checker.doesUserExist(usernameToRemove, this->allUsers))
	{
		std::cout << "The user you are trying to remove does not exists!" << std::endl;
		return;
	}
	if (usernameToRemove == "admin")
	{
		std::cout << "You can't remove yourself!" << std::endl;
		return;
	}

	RemoveUserFromFile(usernameToRemove, this->allUsers);
}

Commands::Commands(String& path)
{
	this->allUsers = allUsersFromData(this->allUsers);
	this->allBooks = allBooksFromData(this->allBooks, path);
	this->isUserLoggedIn = false;
	this->filePath = path;
}

void Commands::LogInUser()
{
	if (this->isUserLoggedIn)
	{
		std::cout << "You are already logged in." << std::endl;
		return;
	}

	String name;
	name.setString("");
	String password;
	password.setString("");

	name = enterUsername(name);
	password = enterPassword(password);


	if (this->checker.doesUserLoginExist(name, password, this->allUsers))
	{
		this->user = User(name, password);
		std::cout << "Welcome, " << this->user.getName() << '!' << std::endl;
		this->isUserLoggedIn = true;
		return;
	}
	std::cout << "Invalid username or password!" << std::endl;
}

void Commands::LogoutUser()
{
	if (this->isUserLoggedIn == false)
	{
		std::cout << "You are not logged in to logout!" << std::endl;
		return;
	}
	this->user = User();
	this->isUserLoggedIn = false;
	std::cout << "Succesfully logout!" << std::endl;
}

void Commands::AdminActions(String& path)
{
	String command;
	std::cin >> command;
	if (this->isUserLoggedIn == false)
	{
		std::cout << "You are not logged in to make these actions!" << std::endl;
		return;
	}
	if (!this->user.isAdmin())
	{
		std::cout << "You dont have permission to make these actions!" << std::endl;
		return;
	}
	if (command == "add")
	{
		this->AddUser();
	}
	else if (command == "remove")
	{
		this->RemoveUser();
	}
	else
	{
		std::cout << "The action you are trying to make does't exists!" << std::endl;
	}
}

void Commands::BookSplit()
{
	String command;
	std::cin >> command;
	if (this->isUserLoggedIn == false)
	{
		std::cout << "You must be logged in to make operations with the books." << std::endl;
		return;
	}

	if (!this->user.isAdmin() && (command == "add" || command == "remove"))
	{
		std::cout << "You don't have permission to do this command!" << std::endl;
		return;
	}

	if (command == "add")
	{
		size_t id;
		String author;
		String title;
		String description;
		String keyWords;
		String genre;
		float rating = 0.0;

		Book bookToAdd;

		std::cout << "Enter id: ";
		std::cin >> id;
		while (id < 1)
		{
			id = 0;
			std::cout << "Id must be different from 0" << std::endl;
			std::cout << "Enter id: ";
			std::cin >> id;
		}
		bookToAdd.id = id;

		std::cout << "Enter author name: ";
		std::cin >> author;
		while (author == "")
		{
			std::cout << "Name must be 1 character or longer!" << std::endl;
			std::cout << "Enter author name: ";
			std::cin >> author;
		}
		bookToAdd.author = author;

		std::cout << "Enter title: ";
		std::cin >> title;
		while (title == "")
		{
			std::cout << "Title must be 1 character or longer!" << std::endl;
			std::cout << "Enter title: ";
			std::cin >> title;
		}
		bookToAdd.title = title;

		std::cout << "Enter genre: ";
		std::cin >> genre;
		while (genre == "")
		{
			std::cout << "Genre must be 1 character or longer!!" << std::endl;
			std::cout << "Enter genre: ";
			std::cin >> genre;
		}
		bookToAdd.genre = genre;

		std::cout << "Enter description: ";
		std::cin >> description;
		while (description == "" || description.getLength() > 500)
		{
			std::cout << "Description must be between 1 and 500 characters!" << std::endl;
			std::cout << "Enter description: ";
			std::cin >> description;
		}
		bookToAdd.description = description;

		std::cout << "Enter release Date: ";
		Date date;
		bookToAdd.year = enterYear(date);
		std::cin.ignore();

		std::cout << "Enter key words: ";
		std::cin >> keyWords;
		while (keyWords == "")
		{
			std::cout << "You must input at least one key word!" << std::endl;
			std::cout << "Enter key words: ";
			std::cin >> keyWords;
		}
		bookToAdd.keyWords = keyWords;

		std::cout << "Enter rating: ";
		std::cin >> rating;
		while (rating < 1.0 || rating > 10.0)
		{
			rating = 0.0;
			std::cout << "Rating must be between 1.0 and 10.0!" << std::endl;
			std::cout << "Enter rating: ";
			std::cin >> rating;
		}
		bookToAdd.rating = rating;

		this->allBooks.push_back(bookToAdd);
		std::cout << "Book \"" << bookToAdd.title << "\" added to the waiting list. If you want to keep it, you have to save it in the file." << std::endl;
		std::cin.ignore();
		return;
	}

	else if (command == "info")
	{
		size_t id;
		std::cout << "Enter id: ";
		std::cin >> id;
		Book bookToFind;
		for (int i = 0; i < this->allBooks.getSize(); i++)
		{
			if (this->allBooks[i].id == id)
			{
				bookToFind = this->allBooks[i];
			}
		}

		if (bookToFind.id == 0)
		{
			std::cout << "The book with this id does not exist" << std::endl;
			std::cin.ignore();
			return;
		}

		bookToFind.PrintBookInformation();
		std::cin.ignore();
		return;
	}

	else if (command == "find")
	{
		String criteria;
		std::cout << "Enter criteria(author/title/tag): ";
		std::cin >> criteria;
		String search;
		std::cout << "Enter " << criteria << " to search for: ";
		std::cin >> search;

		if (!(criteria == "author" || criteria == "title" || criteria == "tag"))
		{
			std::cout << "Invalid criteria, please try again." << std::endl;
			return;
		}
		if (this->allBooks.getSize() == 0)
		{
			std::cout << "There are no books for searching." << std::endl;
			return;
		}

		Vector<Book> booksToPrint;
		if (search == "")
		{
			std::cout << "Please enter any information and try again" << std::endl;
			return;
		}
		if (criteria == "author")
		{
			for (int i = 0; i < this->allBooks.getSize(); i++)
			{
				if (this->allBooks[i].author == search)
				{
					booksToPrint.push_back(this->allBooks[i]);
				}
			}
		}
		else if (criteria == "title")
		{
			for (int i = 0; i < this->allBooks.getSize(); i++)
			{
				if (this->allBooks[i].title == search)
				{
					booksToPrint.push_back(this->allBooks[i]);
				}
			}
		}
		else
		{
			for (int i = 0; i < this->allBooks.getSize(); i++)
			{
				if (this->allBooks[i].keyWords.Contains(search))
				{
					booksToPrint.push_back(this->allBooks[i]);
				}
			}
		}
		PrintBooks(booksToPrint);

	}

	else if (command == "all")
	{
		PrintBooks(this->allBooks);
	}

	else if (command == "remove")
	{
		String titleToRemove;
		std::cout << "Enter title of the book, which you want to remove: ";
		std::cin >> titleToRemove;
		if (!this->checker.DoesBookExist(titleToRemove, this->allBooks))
		{
			std::cout << "There is no book with this title" << std::endl;
			return;
		}
		Vector<Book> result;
		for (int i = 0; i < this->allBooks.getSize(); i++)
		{
			if (this->allBooks[i].title == titleToRemove)
			{
				continue;
			}
			result.push_back(this->allBooks[i]);
		}
		this->allBooks = result;
		std::cout << "The book was successfully removed! If you want to delete it from file, save the file." << std::endl;
	}

	else if (command == "sort")
	{

		String option;
		String way;
		std::cout << "Type the option for the sort(title/author/year/rating): ";
		std::cin >> option;
		std::cout << "Type the way you want to sort the books(ascending/descending): ";
		std::cin >> way;
		if (this->allBooks.getSize() == 0)
		{
			std::cout << "There are no books to sort" << std::endl;
			return;
		}
		if (!(option == "title" || option == "author" || option == "year" || option == "rating"))
		{
			std::cout << "Invalid way to sort! Try again" << std::endl;
			return;
		}

		if (way == "ascending")
		{
			if (option == "title")
			{
				for (int i = 0; i < this->allBooks.getSize() - 1; i++)
				{
					for (int j = 0; j < this->allBooks.getSize() - i - 1; j++)
						if (this->allBooks[j].title > this->allBooks[j + 1].title) {
							Book temp = this->allBooks[j];
							this->allBooks[j] = this->allBooks[j + 1];
							this->allBooks[j + 1] = temp;
						}
				}
			}
			else if (option == "author")
			{
				for (int i = 0; i < this->allBooks.getSize() - 1; i++)
				{
					for (int j = 0; j < this->allBooks.getSize() - i - 1; j++)
						if (this->allBooks[j].author > this->allBooks[j + 1].author) {
							Book temp = this->allBooks[j];
							this->allBooks[j] = this->allBooks[j + 1];
							this->allBooks[j + 1] = temp;
						}
				}
			}
			else if (option == "rating")
			{
				for (int i = 0; i < this->allBooks.getSize() - 1; i++)
				{
					for (int j = 0; j < this->allBooks.getSize() - i - 1; j++)
						if (this->allBooks[j].rating > this->allBooks[j + 1].rating) {
							Book temp = this->allBooks[j];
							this->allBooks[j] = this->allBooks[j + 1];
							this->allBooks[j + 1] = temp;
						}
				}
			}
			else if (option == "year")
			{
				for (int i = 0; i < this->allBooks.getSize() - 1; i++)
				{
					for (int j = 0; j < this->allBooks.getSize() - i - 1; j++)
						if (this->allBooks[j].year > this->allBooks[j + 1].year) {
							Book temp = this->allBooks[j];
							this->allBooks[j] = this->allBooks[j + 1];
							this->allBooks[j + 1] = temp;
						}
				}
			}
		}
		else if (way == "descending")
		{
			if (option == "title")
			{
				for (int i = 0; i < this->allBooks.getSize() - 1; i++)
				{
					for (int j = 0; j < this->allBooks.getSize() - i - 1; j++)
						if (this->allBooks[j].title < this->allBooks[j + 1].title) {
							Book temp = this->allBooks[j];
							this->allBooks[j] = this->allBooks[j + 1];
							this->allBooks[j + 1] = temp;
						}
				}
			}
			else if (option == "author")
			{
				for (int i = 0; i < this->allBooks.getSize() - 1; i++)
				{
					for (int j = 0; j < this->allBooks.getSize() - i - 1; j++)
						if (this->allBooks[j].author < this->allBooks[j + 1].author) {
							Book temp = this->allBooks[j];
							this->allBooks[j] = this->allBooks[j + 1];
							this->allBooks[j + 1] = temp;
						}
				}
			}
			else if (option == "rating")
			{
				for (int i = 0; i < this->allBooks.getSize() - 1; i++)
				{
					for (int j = 0; j < this->allBooks.getSize() - i - 1; j++)
						if (this->allBooks[j].rating < this->allBooks[j + 1].rating) {
							Book temp = this->allBooks[j];
							this->allBooks[j] = this->allBooks[j + 1];
							this->allBooks[j + 1] = temp;
						}
				}
			}
			else if (option == "year")
			{
				for (int i = 0; i < this->allBooks.getSize() - 1; i++)
				{
					for (int j = 0; j < this->allBooks.getSize() - i - 1; j++)
						if (this->allBooks[j].year < this->allBooks[j + 1].year) {
							Book temp = this->allBooks[j];
							this->allBooks[j] = this->allBooks[j + 1];
							this->allBooks[j + 1] = temp;
						}
				}
			}
		}
		else
		{
			std::cout << "Invalid way of ordering. Please try again!" << std::endl;
			return;
		}

		PrintBooks(this->allBooks);
	}

	else
	{
		std::cout << "Invalid command for books!" << std::endl;
		return;
	}


}

void Commands::SaveBooks(String& path)
{
	if (this->allBooks.getSize() == 0)
	{
		return;
	}
	else {
		std::ofstream out;
		out.open(path.string, std::ios::in | std::ios::trunc);

		for (int i = 0; i < this->allBooks.getSize(); i++)
		{
			
			out << this->allBooks[i].id << '\n' << this->allBooks[i].title << '\n' << this->allBooks[i].author << '\n' << this->allBooks[i].description << '\n' << this->allBooks[i].genre << '\n' << this->allBooks[i].year <<
				'\n' << this->allBooks[i].keyWords << '\n' << this->allBooks[i].rating << '\n';
			
		}
		out.close();
	}
	std::cout << "Unsaved books successfully saved" << std::endl;
}

Vector<User>& Commands::allUsersFromData(Vector<User>& allUsers)
{
	Vector<User> result;
	std::ifstream in;
	in.open("users.txt", std::ios::in);
	if (!in)
	{
		std::cout << "There are no users in the file" << std::endl;
		return result;
	}
	User temp;
	in >> temp;
	while (!(temp.getName() == "" && temp.getPassword() == ""))
	{
		result.push_back(temp);
		temp = User();
		in >> temp;
	}
	in.close();
	allUsers = result;
	return allUsers;
}

Vector<Book>& Commands::allBooksFromData(Vector<Book>& allBooksFromFile, String& path)
{
	std::ifstream in;
	in.open(path.string, std::ios::in);
	Vector<Book> result;

	in.ignore();
	while (!in.eof() || in.get() != -1)
	{
		Book book;
		in >> book.id;
		in.ignore();
		in >> book.title;
		in >> book.author;
		in >> book.description;
		in >> book.genre;
		in >> book.year.day; in >> book.year.month, in >> book.year.year;
		in.ignore();
		in >> book.keyWords;
		in >> book.rating;
		result.push_back(book);
	}
	in.close();
	allBooksFromFile = result;
	return allBooksFromFile;
}

String Commands::enterUsername(String& username)
{
	username.setString("");
	while (username.getLength() == 0)
	{
		std::cout << "Enter username: ";
		std::cin >> username;
		if (username.getLength() == 0)
		{
			std::cout << "Invalid username! Username must be 1 character or longer!" << std::endl;
			continue;
		}
	}
	return username;
}

String Commands::enterPassword(String& password)
{
	password.setString("");
	while (password.getLength() == 0)
	{
		std::cout << "Enter password: ";
		std::cin >> password;
		if (password.getLength() == 0)
		{
			std::cout << "Invalid password! Password must be 1 character or longer!" << std::endl;
			continue;
		}
	}
	return password;
}

bool Commands::isLeap(int year)
{
	return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
}

Date Commands::enterYear(Date& date)
{
	int day;
	int month;
	int year;
	std::cout << '\n';
	std::cout << "Enter day: ";
	std::cin >> day;
	std::cout << "Enter month: ";
	std::cin >> month;
	std::cout << "Enter year: ";
	std::cin >> year;

	bool isValidDate = false;
	while (!isValidDate)
	{
		if (month < 1 || month > 12 || day < 1 || day > 31 || (day == 31 && (month == 4 || month == 6 || month == 9 || month == 11)) || (!isLeap(year) && day == 29 && month == 2))
		{
			std::cout << "Invalid date!";
			std::cout << '\n';
			std::cout << "Enter day: ";
			std::cin >> day;
			std::cout << "Enter month: ";
			std::cout << '\n';
			std::cin >> month;
			std::cout << "Enter year: ";
			std::cout << '\n';
			std::cin >> year;
		}
		else
		{
			isValidDate = true;
		}
	}

	date.day = day;
	date.month = month;
	date.year = year;

	return date;
}

void Commands::PrintBooks(Vector<Book>& allBooksFromFile)
{
	std::cout << "-----" << std::endl;
	if (allBooks.getSize() == 0)
	{
		std::cout << "There are no books registered." << std::endl;
		return;
	}

	int counter = 1;
	for (int i = 0; i < allBooks.getSize(); i++)
	{
		std::cout << counter << ". " << allBooks[i].title << ", " << allBooks[i].author << ", " << allBooks[i].genre << ", personal number: " << allBooks[i].id << std::endl;
		counter++;
	}
}

void Commands::AddUserToFile(String& username, String& password)
{
	std::ofstream outfile;

	outfile.open("users.txt", std::ios_base::app);
	outfile << username << "\n" << password << "\n";
	outfile.close();
	std::cout << username << " successfully registered." << std::endl;
}

void Commands::RemoveUserFromFile(String& usernameToRemove, Vector<User>& allUsers)
{
	std::ofstream out;
	out.open("users.txt", std::ios::out);
	Vector<User> result;

	for (int i = 0; i < allUsers.getSize(); i++)
	{
		if (!(allUsers[i].getName() == usernameToRemove))
		{
			result.push_back(allUsers[i]);
		}
	}
	allUsers = result;

	for (int i = 0; i < allUsers.getSize(); i++)
	{
		out << allUsers[i].getName() << "\n" << allUsers[i].getPassword() << "\n";
	}
	out.close();
	std::cout << usernameToRemove << " succesfully removed." << std::endl;
}

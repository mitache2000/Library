#include "Book.h"


Book::Book()
{
	this->id = 0;
	this->title.setString("default");
	this->author.setString("default");
	this->genre.setString("default");
	this->description.setString("default");
	this->year = Date();
	this->keyWords.setString("default");
	this->rating = 0;
}

Book::Book(const Book& other)
{
	this->id = other.id;
	this->title = other.title;
	this->author = other.author;
	this->genre = other.genre;
	this->description = other.description;
	this->year = other.year;
	this->keyWords = other.keyWords;
	this->rating = other.rating;

}

void Book::PrintBookInformation()
{
	std::cout << "Book title: " << this->title << std::endl;
	std::cout << "Book author: " << this->author << std::endl;
	std::cout << "Book genre: " << this->genre << std::endl;
	std::cout << "Book description: " << this->description << std::endl;
	std::cout << "Publication date: " << this->year.day << "/" << this->year.month << "/" << this->year.year << std::endl;
	std::cout << "Book key words: " << this->keyWords << std::endl;
	std::cout << "Book rating: " << this->rating << std::endl;
}


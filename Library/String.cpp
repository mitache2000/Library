#include "String.h"

void String::copy(const String& other)
{
	this->string = new char[strlen(other.string) + 1];
	strcpy_s(this->string, strlen(other.string) + 1, other.string);
	this->size = other.size;
	this->capacity = other.capacity;
}

void String::erase()
{
	delete[] this->string;
}

void String::resize()
{
	capacity *= 2;
	char* newString = new char[capacity];

	for (size_t i = 0; i < size; i++)
	{
		newString[i] = string[i];
	}
	delete[] this->string;
	this->string = newString;
}

String::String()
{
	this->size = 16;
	this->capacity = 16;
	this->string = new char[8];
	strcpy_s(this->string, 8, "default");
}

String::String(const String& other)
{
	this->copy(other);
}

String& String::operator=(const String& other)
{
	if (this != &other)
	{
		this->erase();
		this->copy(other);
	}
	return *this;
}

String::~String()
{
	this->erase();
}

void String::print() const
{
	std::cout << this->string << std::endl;
	std::cout << this->size << std::endl;
	std::cout << this->capacity << std::endl;
}

void String::setString(const char* newString)
{
	if (newString != nullptr)
	{
		delete[] this->string;
		this->string = new char[strlen(newString) + 1];
		strcpy_s(this->string, strlen(newString) + 1, newString);
	}
}

const char* String::getString() const
{
	return this->string;
}

void String::setSize(size_t newSize)
{
	this->size = newSize;
}

size_t String::getSize() const
{
	return this->size;
}

void String::setCapacity(size_t newCapacity)
{
	this->capacity = newCapacity;
}

size_t String::getCapacity() const
{
	return this->capacity;
}

void String::add(const char symbol)
{
	if (size >= capacity)
	{
		resize();
	}
	string[size++] = symbol;
}

size_t String::getLength() const
{
	return strlen(string);
}

void String::insertAt(size_t index, char symbol)
{
	if (index <= size)
	{
		if (size >= capacity)
		{
			resize();
		}

		size++;

		for (int i = size; i > index; i--)
		{
			string[i] = string[i - 1];
		}
		string[index] = symbol;
	}
}

void String::removeAt(size_t index)
{
	if (index <= size)
	{
		for (size_t i = index; i < size; i++)
		{
			string[i] = string[i + 1];
		}
		size--;
	}
}

void String::trimStart()
{
	if (size > 0)
	{
		for (size_t i = 0; i < size; i++)
		{
			string[i] = string[i + 1];
		}
		size--;
	}
}

void String::trimEnd()
{
	if (size > 0)
	{
		size--;
	}
}

void String::trimStart(size_t n)
{
	size_t m = n;
	if (n < size)
	{
		size_t i = 0;
		while (n < size)
		{
			string[i] = string[n];
			n++;
			i++;
		}
		size -= m;
	}
}

void String::trimEnd(size_t n)
{
	if (n <= size)
	{
		size -= n;
	}
}

bool String::Contains(String& newString)
{
	if (!(strstr(this->string, newString.string) == NULL))
	{
		return true;
	}
	return false;
}

bool String::operator>(String& other)
{

	if (this->getSize() > other.getSize())
	{
		return true;
	}
	else if (this->getSize() < other.getSize())
	{
		return false;
	}
	else
	{
		bool flag = false;
		for (int i = 0; i < this->getSize(); i++)
		{
			if (this->string[i] > other.string[i])
			{
				flag = true;
				return flag;
			}
			else if (this->string[i] < other.string[i])
			{
				return flag;
			}
		}
		return false;
	}

}

bool String::operator<(String& other)
{
	if (this->getSize() < other.getSize())
	{
		return true;
	}
	else if (this->getSize() > other.getSize())
	{
		return false;
	}
	else
	{
		bool flag = false;
		for (int i = 0; i < this->getSize(); i++)
		{
			if (this->string[i] < other.string[i])
			{
				flag = true;
				return flag;
			}
			else if (this->string[i] > other.string[i])
			{
				return flag;
			}
		}
		return false;
	}
}

String& String::operator+(const String& other)
{
	String temp = *this;
	temp += other;

	return temp;
}

String& String::operator+=(const String& other)
{
	for (size_t i = 0; i < other.size; i++)
	{
		this->push(other.string[i]);
	}

	return *this;
}

bool String::operator==(String& other)
{
	return strcmp(string, other.string) == 0;
}


bool String::operator==(const char* other)
{
	return strcmp(this->string, other) ? false : true;
}

bool String::operator==(const char other)
{
	if (this->getLength() == 1 && this->string[0] == other)
	{
		return true;
	}
	return false;
}


void String::push(char element)
{
	if (size == capacity - 1)
	{
		resize();
	}
	this->string[size] = element;
	size++;
	this->string[size] = '\0';
}

std::istream& operator>>(std::istream& in, String& data)
{
	char str[100];
	in.getline(str, 64);
	data.setString(str);
	return in;

}

std::ostream& operator<<(std::ostream& out, const String& data)
{
	out << data.string;
	return out;
}

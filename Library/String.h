#pragma once
#include <iostream>

class String
{
public:
	char* string;
	size_t size;
	size_t capacity;

	void copy(const String& other);
	void erase();
	void resize();


	String();
	String(const String& other);
	String& operator=(const String& other);
	~String();

	void print() const;

	void setString(const char* newString);
	const char* getString() const;
	void setSize(size_t newSize);
	size_t getSize() const;
	void setCapacity(size_t newCapacity);
	size_t getCapacity() const;

	void add(const char symbol);
	size_t getLength() const;
	void insertAt(size_t index, char symbol);
	void removeAt(size_t index);
	void trimStart();
	void trimEnd();
	void trimStart(size_t n);
	void trimEnd(size_t n);

	bool Contains(String& newString);

	bool operator> (String& other);
	bool operator< (String& other);
	String& operator+(const String& other);
	String& operator+=(const String& other);
	bool operator== (String& other);
	bool operator== (const char* other);
	bool operator== (const char other);

	void push(char element);

	friend std::istream& operator>>(std::istream& in, String& data);
	friend std::ostream& operator<<(std::ostream& out, const String& data);





};


#pragma once
#include <iostream>

template <typename T>
class Vector
{
private:
	T* data;
	int size;
	int capacity;

	void copy(const Vector<T>& other);
	void erase();
	void resize();

public:
	Vector();
	Vector(const Vector<T>& other);
	Vector<T>& operator=(const Vector<T>& other);
	~Vector();

	void push_back(const T& element);
	void pop_back();

	bool isEmpty()const;
	void print()const;

	T& operator[](size_t index);
	T& operator[](size_t index) const;

	size_t getSize()const;

};

template<typename T>
void Vector<T>::copy(const Vector<T>& other)
{
	this->data = new T[other.capacity];
	this->capacity = other.capacity;
	this->size = other.size;
	for (size_t i = 0; i < this->size; i++)
	{
		this->data[i] = other.data[i];
	}
}

template<typename T>
void Vector<T>::erase()
{
	delete[] this->data;
}

template<typename T>
void Vector<T>::resize()
{
	this->capacity *= 2;
	T* newData = new T[this->capacity];
	for (size_t i = 0; i < this->size; i++)
	{
		newData[i] = this->data[i];

	}
	this->erase();
	this->data = newData;
}

template<typename T>
Vector<T>::Vector()
{
	this->capacity = 8;
	this->size = 0;
	this->data = new T[this->capacity];
}

template<typename T>
Vector<T>::Vector(const Vector<T>& other)
{
	this->copy(other);
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
	if (this != &other)
	{
		this->erase();
		this->copy(other);
	}
	return *this;
}

template<typename T>
Vector<T>::~Vector()
{
	this->erase();
}

template<typename T>
void Vector<T>::push_back(const T& element)
{
	if (this->size >= this->capacity)
	{
		this->resize();
	}

	this->data[size] = element;
	this->size++;


}

template<typename T>
void Vector<T>::pop_back()
{
	if (this->size <= 0)
	{
		return;
	}

	this->size--;
}

template<typename T>
bool Vector<T>::isEmpty() const
{
	return this->size == 0;
}

template<typename T>
void Vector<T>::print() const
{
	for (size_t i = 0; i < this->size; i++)
	{
		std::cout << this->data[i] << std::endl;
	}
}

template<typename T>
T& Vector<T>::operator[](size_t index)
{
	return this->data[index];
}

template<typename T>
T& Vector<T>::operator[](size_t index) const
{
	return this->data[index];
}

template<typename T>
size_t Vector<T>::getSize() const
{
	return this->size;
}
#pragma once

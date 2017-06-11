/*
* @Author
* Student Name: Emre Özdil
* Student ID : 150120138
* Date: 08/05/2016
*/

#include <cxxabi.h> //gcc only
#include "box.h"

// Constructions
template<class Type>
Box<Type>::Box()
{
	setIndex(0);
	// Initial List capacity
	capacity = 2;
	list = new Type[capacity];
}
template<class Type>
Box<Type>::Box(float weight, float length, float width, float maximumAllowedWeight)
{
	this->weight = weight;
	setLength(length);
	setWidth(width);
	setMaximumAllowedWeight(maximumAllowedWeight);
	this->boxTare = weight;
	setIndex(0);
	// Initial List capacity
	capacity = 2;
	list = new Type[capacity];
}

// Getter Methods
template<class Type>
float Box<Type>::getWeight() const { return weight; }
template<class Type>
float Box<Type>::getLength() const { return length; }
template<class Type>
float Box<Type>::getWidth() const { return width; }
template<class Type>
float Box<Type>::getMaximumAllowedWeight() const { return maximumAllowedWeight; }
template<class Type>
float Box<Type>::getBoxTare() const { return boxTare; }
template<class Type>
int Box<Type>::getIndex() const { return index; }


// Setter Methods
template<class Type>
void Box<Type>::setWeight(float weight) { this->weight += weight; }
template<class Type>
void Box<Type>::setLength(float length) { this->length = length; }
template<class Type>
void Box<Type>::setWidth(float width) { this->width = width; }
template<class Type>
void Box<Type>::setMaximumAllowedWeight(float maximumAllowedWeight) { this->maximumAllowedWeight = maximumAllowedWeight; }
template<class Type>
void Box<Type>::setBoxTare(float boxTare) { this->boxTare = boxTare; }
template<class Type>
void Box<Type>::setIndex(int index) { this->index = index; }

// Add functions
template<class Type>
void Box<Type>::add(const Type &var)
{
	setWeight(var.getWeight());
	string dimensionError = "The dimensions of the contained object should be equal or smaller than those of the box!";
	string weightError = "The total weight of the contained objects including the box may not exceed the maximum allowed weight for the box!";

	// Check dimension error
	if ((length < var.getLength() || width < var.getWidth()) &&
		(length < var.getWidth() || width < var.getLength()))
	{
		setWeight(-1 * var.getWeight());
		throw dimensionError;
	}

	// Check weight error
	if (weight > maximumAllowedWeight)
	{
		setWeight(-1*var.getWeight());
		throw weightError;
	}
	// Adding list
	list[index++] = var;
	// List capasity is doubled
	if (index==capacity)
	{
		Type *listTemp;
		capacity *= 2;
		listTemp = new Type[capacity];
		for (int i = 0; i < index; i++)
		{
			// copy list to new memory
			listTemp[i] = list[i];
		}
		// list pointer point to new memeory
		list = listTemp;
	}
}
template<class Type>
void Box<Type>::add(Type* var, int size)
{
	for (int i = 0; i < size; i++)
	{
		add(var[i]);
	}
}

// Type Name function
// gcc and VS has return different typename. In order to compile in gcc, uncomment <cxxabi.h> library and only gcc scope.
// On the other hand compile in VS comment these lines.
template<class Type>
string Box<Type>::getTypeName()
{
	int status;
	string tname = typeid(Type).name();
	// ****** only gcc begin ******
	char *demangledName = abi::__cxa_demangle(tname.c_str(), NULL, NULL, &status);
	if (status == 0)
	{
		tname = demangledName;
		free(demangledName);
	}
	// ****** only gcc end ******
	return tname;
}


/*
* @Author
* Student Name: Emre Özdil
* Student ID : 150120138
* Date: 08/05/2016
*/

#pragma once
#include <cstdlib>
#include <iostream>
#include <string>
#include <typeinfo>
#include "toy.h"
#include "book.h"
using namespace std;

template <class Type>
class Box
{
public:
	Box<Type>();
	Box<Type>(float weight, float length, float width, float maximumAllowedWeight);
	// Getter Methods
	float getWeight() const;
	float getLength() const;
	float getWidth() const;
	float getMaximumAllowedWeight() const;
	float getBoxTare() const;
	int getIndex() const;
	string getTypeName();

	// Setter Methods
	void setWeight(float);
	void setLength(float);
	void setWidth(float);
	void setMaximumAllowedWeight(float);
	void setBoxTare(float);
	void setIndex(int);

	// Functions
	void add(const Type&);
	void add(Type*, int);

	// Operator overloading
	Type&  operator[] (int i)
	{
		string indexError = "Index out of bounds!";
		if (i >= index) throw indexError;
		return list[i];
	}
	friend ostream &operator<<(ostream &output, Box<Type> &D)
	{
		output << "***** Box<" << D.getTypeName() << "> *****" << endl;
		output << "Box item count:" << D.getIndex() << endl;
		output << "Size: " << D.getLength() << "x" << D.getWidth() << " Box Weight:" << D.getBoxTare() << "kg";
		output << " Total/Maximum Allowed Weight:" << D.getWeight() << "kg/" << D.getMaximumAllowedWeight() << "kg" << endl;
		output << "Items:" << endl;
		for (int i = 0; i < D.getIndex(); i++)
			cout << i + 1 << ":" << D[i];
		output << "********************" << endl;
		return output;
	}

private:
	float weight, length, width, maximumAllowedWeight;
	float boxTare;
	int index, capacity;
	Type *list;
};



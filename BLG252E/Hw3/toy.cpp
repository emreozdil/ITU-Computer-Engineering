/*
* @Author
* Student Name: Emre Özdil
* Student ID : 150120138
* Date: 08/05/2016
*/

#include "toy.h"

// Constructor
Toy::Toy()
{
}

Toy::Toy(string label, float weight, float length, float width, bool containsBattery)
{
	setLabel(label);
	setWeight(weight);
	setLength(length);
	setWidth(width);
	setContainsBattery(containsBattery);
}

// Destructor
Toy::~Toy()
{
}

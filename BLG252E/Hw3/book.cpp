/*
* @Author
* Student Name: Emre Özdil
* Student ID : 150120138
* Date: 08/05/2016
*/

#include "book.h"
using namespace std;

// Constructor
Book::Book()
{
}

Book::Book(string label, float weight, float length, float width)
{
	setLabel(label);
	setWeight(weight);
	setLength(length);
	setWidth(width);
}

// Destructor
Book::~Book()
{
}


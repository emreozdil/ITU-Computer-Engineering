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
using namespace std;

class Book
{
public:
	Book();
	Book(string, float, float, float);
	~Book();

	// Getter Methods
	string getLabel() const { return label; };
	float getWeight() const { return weight; };
	float getLength() const { return length; };
	float getWidth() const { return width; };

	// Setter Methods
	void setLabel(string label) { this->label = label; };
	void setWeight(float weight) { this->weight = weight; };
	void setLength(float length) { this->length = length; };
	void setWidth(float width) { this->width = width; };

	// Operator overloading
	friend ostream &operator<<(ostream &output, Book &D)
	{
		output << "Book Label: " << D.getLabel() << " # " << D.getLength() << "x" << D.getWidth() << " " << D.getWeight() << "kg " << endl;
		return output;
	}
private:
	string label;
	float weight, length, width;
};

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
#include "book.h"
using namespace std;

class Toy:public Book
{
public:
	Toy();
	Toy(string, float, float, float, bool);
	~Toy();

	// Getter Method
	bool getContainsBattery() const { return containsBattery; };

	// Setter Method
	void setContainsBattery(bool containsBattery) { this->containsBattery = containsBattery; };

	// Operator overloading
	friend ostream &operator<<(ostream &output, Toy &D)
	{
		output << "Toy Label: " << D.getLabel() << " # " << D.getLength() << "x" << D.getWidth() << " " << D.getWeight() << "kg ";
		if (D.getContainsBattery())
			cout << "Contains Battery" << endl;
		else
			cout << "No Battery" << endl;
		return output;
	}
private:
	bool containsBattery;
};

/*
* @Author
* Student Name: Emre Özdil
* Student ID : 150120138
* Date: 26/11/2016
*/
#pragma once
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

class Number
{
public:
	Number() {};
	// Getter
	int getId() { return id; };
	string getNumber() { return number; };
	// Setter
	void setId(int id) { this->id = id; };
	void setNumber(string number) { this->number = number; };

	~Number() {};

private:
	int id;
	string number;
};

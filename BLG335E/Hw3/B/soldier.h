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
#include <cmath>

using namespace std;

class Soldier
{
public:
	Soldier() {};
	~Soldier() {};
	int getId() { return id; };
	int getCp() { return cp; };
	void setId(int id) { this->id = id; };
	void setCp(int cp) { this->cp = cp; };	

private:
	int id;
	int cp;
};


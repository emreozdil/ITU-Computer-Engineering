/*
* @Author
* Student Name: Emre Özdil
* Student ID : 150120138
* Date: 04/11/2016
*/
#pragma once
#include "line.h"


class Book {
    vector<Line> lines;
    
public:
	Book() {};
	vector<Line>& getLines() { return lines; };
	void addLines(Line&);
};

void Book::addLines(Line& line)
{
	lines.pb(line);
}


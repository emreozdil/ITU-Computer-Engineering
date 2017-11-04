/*
* @Author
* Student Name: Emre Özdil
* Student ID : 150120138
* Date: 04/11/2016
*/

#pragma once

#include "word.h"

class Line
{
private:
	int lineId;
	vector<Word> words;

public:
	Line() {};
	Line(int lineId) { this->lineId = lineId; };

	int getLineId() { return lineId; };
	void setLineId(int lineId) { this->lineId = lineId; };

	void addWord(Word&);
	vector<Word>& getWords();
};

void Line::addWord(Word& word)
{
	words.pb(word);
}

vector<Word>& Line::getWords()
{
	return this->words;
}
/*
* @Author
* Student Name: Emre Özdil
* Student ID : 150120138
* Date: 04/11/2016
*/
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>

#define pb push_back

using namespace std;

class Word
{
private:
	int wordId;
	string word;

public:
	Word() {};
	Word(int wordId, string word) { this->wordId = wordId; this->word = word; };

	int getWordId() { return wordId; };
	void setWordId(int wordId) { this->wordId = wordId; };
	
	string& getWord() { return word; };
	void setWord(string word) { this->word = word; };
};

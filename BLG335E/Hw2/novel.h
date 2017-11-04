/*
* @Author
* Student Name: Emre Özdil
* Student ID : 150120138
* Date: 04/11/2016
*/
#pragma once

#include "book.h"

int quickSortCounter = 0;

void sortBook(int,int);
void readBook(Book*);
void writeBook(Book*);
Line& addLine(int, string&, string&);
void quickSortLines(vector<Line>&, int, int, int, int);
int partitionLines(vector<Line>&, int, int);
void randomizedQuickSortWords(vector<Word>&, int, int);
int randomizedPartitionWords(vector<Word>&, int, int);

void sortBook(int M,int N)
{
	Book* mobyDick;
	mobyDick = new Book();
	readBook(mobyDick);
	//For first and second question.
	quickSortLines(mobyDick->getLines(), 0, mobyDick->getLines().size() - 1, M, N);
	writeBook(mobyDick);
}

void readBook(Book* mobyDick)
{
	char* novel;
	novel = (char*)"mobydick.txt";
	ifstream inputStream;
	inputStream.open(novel, ios::in);
	int lineId;
	string words;
	string wordsId;
	while (inputStream >> lineId >> words >> wordsId)
	{
		mobyDick->addLines(addLine(lineId, words, wordsId));
	}
	inputStream.close();
}

void writeBook(Book* mobyDick)
{
	char* novel;
	novel = (char*)"novel.txt";
	ofstream outputStream;
	outputStream.open(novel, ios::out | ios::trunc);
	for (int i = 0; i < mobyDick->getLines().size(); i++)
	{
		for (int j = 0; j < mobyDick->getLines()[i].getWords().size(); j++)
		{
			outputStream << mobyDick->getLines()[i].getWords()[j].getWord() << " ";
		}
		outputStream << endl;
	}
	outputStream.close();
}

Line& addLine(int lineId, string& words, string& wordsId)
{
	Word* tempWord;
	Line* tempLine;
	tempLine = new Line(lineId);

	string id;

	string word;
	int wordId;
	for (int i = 1, j = 1; i < words.size(); i++)
	{
		if (words[i] != '_' && words[i] != '}')
		{
			word += words[i];
		}
		else
		{
			for (; j < (wordsId.size()); j++)
			{
				if (wordsId[j] != '_' && wordsId[j] != '}')
				{
					id += wordsId[j];
				}
				else
				{
					wordId = atoi(id.c_str());
					tempWord = new Word(wordId, word);
					tempLine->addWord(*tempWord);
					word = "";
					id = "";
					j++;
					break;
				}
			}
		}
	}
	randomizedQuickSortWords(tempLine->getWords(), 0, tempLine->getWords().size() - 1);
	return *tempLine;
}

void quickSortLines(vector<Line>& lines, int low, int high, int M, int N)
{
	quickSortCounter++;
	if (quickSortCounter == M)
	{
		cout << "If M= " << M << "and N= " << N << ",Nth line ID is equals to " << lines[N].getLineId() << endl;
	}
	if (low < high)
	{
		int partitioningIndex = partitionLines(lines, low, high);

		// Separately sort elements before
		// partition and after partition
		quickSortLines(lines, low, partitioningIndex - 1, M, N);
		quickSortLines(lines, partitioningIndex + 1, high, M, N);
	}

}

int partitionLines(vector<Line>& lines, int low, int high)
{
	int pivot = lines[high].getLineId();    // pivot
	int i = (low - 1);  // Index of smaller element

	for (int j = low; j <= high - 1; j++)
	{
		// If current element is smaller than or
		// equal to pivot
		if (lines[j].getLineId() < pivot)
		{
			i++;    // increment index of smaller element
			swap(lines[i], lines[j]);
		}
	}
	swap(lines[i + 1], lines[high]);
	return (i + 1);
}

void randomizedQuickSortWords(vector<Word>& words, int low, int high)
{
	if (low < high)
	{
		int partitioningIndex = randomizedPartitionWords(words, low, high);

		// Separately sort elements before
		// partition and after partition
		randomizedQuickSortWords(words, low, partitioningIndex - 1);
		randomizedQuickSortWords(words, partitioningIndex + 1, high);
	}

}

int randomizedPartitionWords(vector<Word>& words, int low, int high)
{
	srand(255);
	swap(words[high], words[rand() % (high - low + 1) + low]);
	int pivot = words[high].getWordId();// pivot
	int i = (low - 1);  // Index of smaller element

	for (int j = low; j <= high - 1; j++)
	{
		// If current element is smaller than or
		// equal to pivot
		if (words[j].getWordId() < pivot)
		{
			i++;    // increment index of smaller element
			swap(words[i], words[j]);
		}
	}
	swap(words[i + 1], words[high]);
	return (i + 1);
}

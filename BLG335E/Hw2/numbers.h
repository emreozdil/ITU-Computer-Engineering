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
#include <ctime>

#define pb push_back

using namespace std;

void sortNumbers(int);
void readNumbers(vector<int>&, int);
void quickSortNumbers(vector<int>&, int, int);
int partitionNumbers(vector<int>&, int, int);
void writeNumbers(vector<int>&);

void sortNumbers(int K)
{
	//For the third question.
	vector<int> numbers;
	readNumbers(numbers, K);
	clock_t t = clock();
	quickSortNumbers(numbers, 0, numbers.size() - 1);
	t = clock() - t;
	cout << (float)t / CLOCKS_PER_SEC << " seconds" << endl;
	writeNumbers(numbers);
}
void readNumbers(vector<int>& numbers, int K)
{
	int number;
	char* unsortedNumbers;
	unsortedNumbers = (char*)"numbers_to_sort.txt";
	ifstream inputStream;
	inputStream.open(unsortedNumbers, ios::in);
	for (int i = 0; i < K; i++)
	{
		inputStream >> number;
		numbers.pb(number);
	}
	inputStream.close();
}

void quickSortNumbers(vector<int>& numbers, int low, int high)
{
	if (low < high)
	{
		int partitioningIndex = partitionNumbers(numbers, low, high);

		// Separately sort elements before
		// partition and after partition
		quickSortNumbers(numbers, low, partitioningIndex - 1);
		quickSortNumbers(numbers, partitioningIndex + 1, high);
	}
}

int partitionNumbers(vector<int>& numbers, int low, int high)
{
	int pivot = numbers[high];    // pivot
	int i = (low - 1);  // Index of smaller element

	for (int j = low; j <= high - 1; j++)
	{
		// If current element is smaller than or
		// equal to pivot
		if (numbers[j] < pivot)
		{
			i++;    // increment index of smaller element
			swap(numbers[i], numbers[j]);
		}
	}
	swap(numbers[i + 1], numbers[high]);
	return (i + 1);
}

void writeNumbers(vector<int>& numbers)
{
	char* sortedNumbers;
	sortedNumbers = (char*)"numbers.txt";
	ofstream outputStream;
	outputStream.open(sortedNumbers, ios::out | ios::trunc);
	for (int i = 0; i < numbers.size(); i++)
	{
		outputStream << numbers[i] << endl;
	}
	outputStream.close();
}
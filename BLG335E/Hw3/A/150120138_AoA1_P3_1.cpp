/*
* @Author
* Student Name: Emre Özdil
* Student ID : 150120138
* Date: 26/11/2016
*/
#include "number.h"

void readNumbers(int, Number*);
void writeNumbers(int, Number*);

void radixSort(int, Number*);
void countSort(int, Number*, int);

// MAIN Function
int main(int argc, char** argv)
{
	int N = atoi(argv[1]);
	Number* numbers;
	numbers = new Number[N];
	
	readNumbers(N, numbers);
	
	clock_t t = clock();
	radixSort(N, numbers);
	t = clock() - t;
	cout << (float)t / CLOCKS_PER_SEC << " seconds" << endl;
	
	writeNumbers(N, numbers);
	delete[] numbers;
	return 0;
}


// Read txt
void readNumbers(int N, Number* numbers)
{
	char* unsortedFileName;
	int id;
	string number;

	unsortedFileName = (char*)"numbers_to_sort.txt";

	ifstream inputStream;
	inputStream.open(unsortedFileName, ios::in);
	for (int i = 0; i < N; i++)
	{
		inputStream >> id;
		inputStream >> number;
		numbers[i].setId(id);
		numbers[i].setNumber(number);
	}
}

// Write txt
void writeNumbers(int N, Number* numbers)
{
	char* sortedFileName;

	sortedFileName = (char*)"sorted_numbers.txt";

	ofstream outputStream;
	outputStream.open(sortedFileName, ios::out | ios::trunc);
	for (int i = 0; i < N; i++)
	{
		outputStream << numbers[i].getId() << " " << numbers[i].getNumber() << endl;
	}
}

// The main function to that sorts numbers[] of size N using 
// Radix Sort
void radixSort(int N, Number* numbers)
{
	// Do counting sort for every digit.
	for (int digit = 9; digit >= 0; digit--)
	{
		countSort(N, numbers, digit);
	}
}

// A function to do counting sort of numbers[] according to the digit
void countSort(int N, Number* numbers, int digit)
{
	// output numbers
	Number* output; 
	output = new Number[N];
	int i;
	int count[10] = { 0 };

	// Store count of occurrences in count[]
	for (i = 0; i < N; i++)
	{
		count[(numbers[i].getNumber()[digit]) - '0']++;
	}
	// Change count[i] so that count[i] now contains actual
	//  position of this digit in output[]
	for (i = 1; i < 10; i++)
	{
		count[i] += count[i - 1];
	}
	// Build the output numbers
	for (i = N - 1; i >= 0; i--)
	{
		output[count[(numbers[i].getNumber()[digit]) - '0'] - 1] = numbers[i];
		count[(numbers[i].getNumber()[digit]) - '0']--;
	}

	// Copy the output numbersay to numbers[], so that numbers[] now
	// contains sorted numbers according to current digit
	for (i = 0; i < N; i++)
	{
		numbers[i] = output[i];
	}
}

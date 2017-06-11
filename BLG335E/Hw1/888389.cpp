//
//  main.cpp
//  Algo1
//
//  Created by Emre Özdil on 18/10/16.
//  Copyright © 2016 Emre Özdil. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <climits>
#include <cstdlib>
#include <cmath>
#include <ctime>

using namespace std;

class Point
{
public:
	int id;
	int xAxis;
	int yAxis;
	float distance;
	Point() {};
	Point(int, int, int) {};
	int getId() { return this->id; };
	int getXAxis() { return this->xAxis; };
	int getYAxis() { return this->yAxis; };
	void setId(int id) { this->id = id; };
	void setXAxis(int xAxis) { this->xAxis = xAxis; };
	void setYAxis(int yAxis) { this->yAxis = yAxis; };
	void calculateDistance(int, int);
};

class BaseAlgorithm
{
private:
    char* unsortedFileName;
    char* sortedFileName;
public:
    Point* locations; // Array of the numbers to be sorted
    int total; // Total number of integers to be sorted
    BaseAlgorithm(int N);
    void takeInput(int, int);
    void writeOutput(int);
};

class MergeSort : public BaseAlgorithm
{
public:
    MergeSort(int N) : BaseAlgorithm(N) {};
    void sort(Point*, int, int);
private:
    void merge(Point*, int, int, int);
};

class InsertionSort : public BaseAlgorithm
{
public:
	InsertionSort(int N) : BaseAlgorithm(N) {};
	void sort(Point*, int);
};

class LinearSearch : public BaseAlgorithm
{
public:
	LinearSearch(int N) : BaseAlgorithm(N) {};
	void find(Point*, int);
};


void Point::calculateDistance(int xAxis, int yAxis)
{
	distance = sqrt((xAxis - this->xAxis)*(xAxis - this->xAxis) + (yAxis - this->yAxis)*(yAxis - this->yAxis));
}

BaseAlgorithm::BaseAlgorithm(int N)
{
    unsortedFileName = (char*)"warehouselocations.txt";
    sortedFileName = (char*)"output.txt";
    locations = new Point[N];
    total = N;
}



void BaseAlgorithm::takeInput(int xAxis, int yAxis)
{
    ifstream inputStream;
    inputStream.open(unsortedFileName, ios::in);
    for (int i = 0; i < total; i++)
	{
        inputStream >> locations[i].id;
        inputStream >> locations[i].xAxis;
        inputStream >> locations[i].yAxis;
		locations[i].calculateDistance(xAxis, yAxis);
    }
    inputStream.close();
}

void BaseAlgorithm::writeOutput(int K)
{
    ofstream outputStream;
    outputStream.open(sortedFileName, ios::out | ios::trunc);
    for (int i = 0; i < K; i++) 
	{
        outputStream << locations[i].id << "\t" << locations[i].xAxis << "\t" << locations[i].yAxis << "\t" << locations[i].distance << endl;
    }
    outputStream.close();
}

void MergeSort::sort(Point* unsorted, int lowerBound, int upperBound)
{
    if (lowerBound < upperBound) 
	{
        int median = (lowerBound + upperBound) / 2;
        sort(unsorted, lowerBound, median);
        sort(unsorted, median + 1, upperBound);
        merge(unsorted, lowerBound, median, upperBound);
    }
}

void MergeSort::merge(Point* unsorted, int lowerBound, int median, int upperBound)
{
    int leftLength = median - lowerBound + 1;
    int rightLength = upperBound - median;
    Point* Left = new Point[leftLength + 1];
    Point* Right = new Point[rightLength + 1];
    for (int i = 0; i < leftLength; i++) 
	{
        Left[i] = unsorted[lowerBound + i];
    }
    for (int j = 0; j < rightLength; j++) 
	{
        Right[j] = unsorted[median + 1 + j];
    }
    Left[leftLength].distance = INT_MAX;
    Right[rightLength].distance = INT_MAX;
    int i = 0;
    int j = 0;
    for (int k = lowerBound; k <= upperBound; k++)
	{
        if (Left[i].distance <= Right[j].distance)
		{
            unsorted[k] = Left[i];
            i++;
        }
        else {
            unsorted[k] = Right[j];
            j++;
        }
    }
	delete[] Left;
	delete[] Right;
}

void InsertionSort::sort(Point* unsorted, int length)
{
	int j;
	Point temp;

	for (int i = 1; i < length; i++)
	{
		j = i;
		while (j > 0 && unsorted[j].distance < unsorted[j - 1].distance)
		{
			temp = unsorted[j];
			unsorted[j] = unsorted[j - 1];
			unsorted[j - 1] = temp;
			j--;
		}
	}
}

void LinearSearch::find(Point* unsorted, int length)
{
	int higherDistance = -1;
	int higherIndex;
	int j = length;
	Point temp;

	while (j != total)
	{
		for (int i = 0; i < length; i++)
		{
			if (unsorted[i].distance > higherDistance)
			{
				higherDistance = unsorted[i].distance;
				higherIndex = i;
			}
		}
		for (j ; j < total; j++)
		{
			if (unsorted[j].distance < higherDistance)
			{
				higherDistance = unsorted[j].distance;
				temp = unsorted[j];
				unsorted[j] = unsorted[higherIndex];
				unsorted[higherIndex] = temp;
				break;
			}
		}
	}
}

int main(int argc, char ** argv)
{
	int N = atoi(argv[1]);
	int K = atoi(argv[2]);
	int xAxis = atoi(argv[4]);
	int yAxis = atoi(argv[5]);

	switch (argv[3][0])
	{
	case 'M': case 'm':
	{
		MergeSort sorter(N);
		sorter.takeInput(xAxis, yAxis);
		clock_t t = clock();
		sorter.sort(sorter.locations, 0, sorter.total - 1);
		t = clock() - t;
		cout << (float)t / CLOCKS_PER_SEC << " seconds" << endl;
		sorter.writeOutput(K);
	}
		break;
	case 'I': case 'i':
	{
		InsertionSort sorter(N);
		sorter.takeInput(xAxis, yAxis);
		clock_t t = clock();
		sorter.sort(sorter.locations, sorter.total);
		t = clock() - t;
		cout << (float)t / CLOCKS_PER_SEC << " seconds" << endl;
		sorter.writeOutput(K);
	}
		break;
	case 'L': case 'l':
	{
		LinearSearch list(N);
		list.takeInput(xAxis, yAxis);
		clock_t t = clock();
		list.find(list.locations, K);
		t = clock() - t;
		cout << (float)t / CLOCKS_PER_SEC << " seconds" << endl;
		list.writeOutput(K);
	}
		break;
	default:
		cout << "Algorithm Type is Wrong!" << endl;
		break;
	}
	return 0;
}

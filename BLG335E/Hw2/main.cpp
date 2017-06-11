/*
* @Author
* Student Name: Emre Özdil
* Student ID : 150120138
* Date: 04/11/2016
*/


#include "novel.h"
#include "numbers.h"

int main(int argc, const char ** argv)
{
	int questionNumber = atoi(argv[1]);

	if (questionNumber == 1)
	{
		int M = atoi(argv[2]);
		int N = atoi(argv[3]);
		sortBook(M,N);
	}
	else if (questionNumber == 2)
	{
		int K = atoi(argv[2]);
		sortNumbers(K);
	}
	else
		cout << "Wrong Question Number" << endl;
    return 0;
}

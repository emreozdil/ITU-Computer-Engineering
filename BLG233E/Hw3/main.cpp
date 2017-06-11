/*
* @Author
* Student Name: Emre Özdil
* Student ID : 150120138
* Date: 20/12/2015
*/
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include "queue.h"
#include "stack.h"
using namespace std;

void create();
void deck_create(int *);
void deck_shuffle(int *, int);
void add_queue(int *);
void operation(); 
void result();
void print(int);
void close();

int counter = 1;
FILE *out;

Queue que;
Queue fortune;
Stack st;

int main()
{	
	int deck[53];

	create();	
	deck_create(deck);
	deck_shuffle(deck,counter);
	add_queue(deck);
	operation();
	result();
	close();
}
void create()
{
	srand(time(NULL));
	out = fopen("output.txt", "w+");
	que.create();
	fortune.create();
	st.create();
}

void deck_create(int *d)
{
	for (int i = 1; i < 53; i++)
		d[i] = i;
}

void deck_shuffle(int *d,int c)
{
	int random = (rand() % 52) + 1;
	/*
	Change variable
	Like
	(a,b)->(b,a):
		a=a+b
		b=a-b
		a=a-b
	(b,a)
	*/
	d[c] = d[c] + d[random];
	d[random] = d[c] - d[random];
	d[c] = d[c] - d[random];
	if (c == 52)	return;//end of recursion
	deck_shuffle(d, c + 1);
}

void add_queue(int *d)
{
	fprintf(out, "Shuffled deck:\n");
	for (int i = 1; i < 53; i++)//add queue
		que.enqueue(d[i]);
	for (int i = 1; i < 53; i++)//print deck
	{
		fprintf(out,"%d:", i);
		print(d[i]);
		fprintf(out,"\n");
	}
}

void operation()
{
	fprintf(out,"Fortune-telling steps:\n");
	while (!que.isempty())
	{
		for (int i = 1; i < 14; i++)//loop 13 times 
		{
			if (que.isempty())	break;//Determining the end of counting 
			int temp = que.dequeue();
			st.push(temp);//card queue->stack
			if (i == temp % 13 || (i == 13 && temp % 13 == 0))
			{
				//match print
				fortune.enqueue(temp);//add fortune queue
				st.pop();//match card
				while (!st.isempty())
					que.enqueue(st.pop());//add deck stack->queue
				fprintf(out,"%d:", i);
				print(temp);
				fprintf(out,":match\n");
				break;
			}
			else
			{
				//unmatch print
				fprintf(out,"%d:", i);
				print(temp);
				fprintf(out,":unmatch\n");
			}
		}
	}	
}

void result()
{
	fprintf(out, "Fortune Results:\n");
	int sum=0;
	int temp;
	while (!fortune.isempty())
	{
		temp = fortune.dequeue();
		if (temp % 13 == 0)
			sum += 13;
		else
			sum += temp % 13;
		print(temp);
		fprintf(out,"\n");
	}
	fprintf(out,"Sum: %d\n", sum);
	if (sum < 50)
		fprintf(out,"Bad luck!\n");
	else
		fprintf(out,"Fortune will come true\n");
}


void print(int p)
{
	char type, card[3];
	switch ((p - 1) / 13)//according to p	 1-13->H	14-26->D	27-39->C	40-52->S
	{
	case 0:
		type = 'H';
		break;
	case 1:
		type = 'D';
		break;
	case 2:
		type = 'C';
		break;
	case 3:
		type = 'S';
		break;
	default:
		break;
	}
	switch (p % 13)
	{
	case 0:
		card[0] = 'K';
		card[1] = '\0';
		break;
	case 1:
		card[0] = 'A';
		card[1] = '\0';
		break;
	case 2:
		card[0] = '2';
		card[1] = '\0';
		break;
	case 3:
		card[0] = '3';
		card[1] = '\0';
		break;
	case 4:
		card[0] = '4';
		card[1] = '\0';
		break;
	case 5:
		card[0] = '5';
		card[1] = '\0';
		break;
	case 6:
		card[0] = '6';
		card[1] = '\0';
		break;
	case 7:
		card[0] = '7';
		card[1] = '\0';
		break;
	case 8:
		card[0] = '8';
		card[1] = '\0';
		break;
	case 9:
		card[0] = '9';
		card[1] = '\0';
		break;
	case 10:
		card[0] = '1';
		card[1] = '0';
		card[2] = '\0';
		break;
	case 11:
		card[0] = 'J';
		card[1] = '\0';
		break;
	case 12:
		card[0] = 'K';
		card[1] = '\0';
		break;
	default:
		break;
	}
	fprintf(out,"%c:%s", type, card);
}

void close()
{
	que.close();
	fortune.close();
	st.close();
}
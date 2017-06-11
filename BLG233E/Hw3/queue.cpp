/*
* @Author
* Student Name: Emre Özdil
* Student ID : 150120138
* Date: 20/12/2015
*/
#include <cstdio>
#include "queue.h"

using namespace std;



void Queue::create() 
{
	front = NULL; back = NULL;
}

void Queue::close()
{
	Node_q *p;
	while (front) {
		p = front;
		front = front->next;
		delete p;
	}
}

void Queue::enqueue(int newdata) 
{
	Node_q *newnode = new Node_q;
	newnode->data = newdata;
	newnode->next = NULL;
	if (isempty()) 
	{   
		back = newnode;
		front = back;
	}
	else 
	{
		back->next = newnode;
		back = newnode;
	}

}

int Queue::dequeue() 
{
	Node_q *topnode;
	int temp;
	topnode = front;
	front = front->next;
	temp = topnode->data;
	delete topnode;
	return temp;
}

bool Queue::isempty()
{
	return front == NULL;
}

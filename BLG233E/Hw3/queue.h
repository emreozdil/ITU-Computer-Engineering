/*
* @Author
* Student Name: Emre Özdil
* Student ID : 150120138
* Date: 20/12/2015
*/
#ifndef QUEUE_H
#define QUEUE_H

struct Node_q 
{  
	int data;
	Node_q *next;
};

struct Queue 
{
	Node_q * front;
	Node_q * back;
	void create();
	void close();
	void enqueue(int);
	int dequeue();
	bool isempty();
};
#endif // !QUEUE_H
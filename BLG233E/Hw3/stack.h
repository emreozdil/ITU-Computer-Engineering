/*
* @Author
* Student Name: Emre Özdil
* Student ID : 150120138
* Date: 20/12/2015
*/
#ifndef STACK_H
#define STACK_H

struct Node 
{
	int data;
	Node *next;
};

struct Stack 
{
	Node *head;
	void create();
	void close();
	void push(int);
	int pop();
	bool isempty();
};
#endif // !STACK_H

/*
* @Author
* Student Name: Emre Özdil
* Student ID : 150120138
* Date: 20/12/2015
*/
#include <cstdio>
#include "stack.h"

void Stack::create() 
{
	head = NULL;
}


void Stack::close() 
{
	Node *p;
	while (head) {
		p = head;
		head = head->next;
		delete p;
	}
}


void Stack::push(int newdata) 
{
	Node *newnode = new Node;
	newnode->data = newdata;
	newnode->next = head;
	head = newnode;
}


int Stack::pop()
{
	Node *topnode;
	int temp;
	topnode = head;
	head = head->next;
	temp = topnode->data;
	delete topnode;
	return temp;
}


bool Stack::isempty() 
{
	return head == NULL;
}

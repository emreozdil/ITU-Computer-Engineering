#ifndef STACK_H
#define STACK_H
#include "tree.h"

struct Node {
	node* data;
	Node *next;
};

struct Stack {
	Node *head;
	int size = 3;
	int element;
	void create();
	void close();
	void push(node*);
	node* pop();
	bool isempty();
};


#endif

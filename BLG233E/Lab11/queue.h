#ifndef QUEUE_H
#define QUEUE_H
#include "tree.h"

struct Node_q {  // Nodes of the list
	node* data;
	Node_q *next;
};

struct Queue {
	Node_q * front;
	Node_q * back;
	void create();
	void close();
	void enqueue(node *);
	node* dequeue();
	bool isempty();
	void print();
};

#endif // !QUEUE_H
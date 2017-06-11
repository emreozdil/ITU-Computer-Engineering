#ifndef QUEUE_H
#define QUEUE_H


struct Node_q {  // Nodes of the list
	char data;
	Node_q *next;
};

struct Queue {
	Node_q * front;
	Node_q * back;
	void create();
	void close();
	void enqueue(char);
	char dequeue();
	bool isempty();
	void print();
};

#endif // !QUEUE_H
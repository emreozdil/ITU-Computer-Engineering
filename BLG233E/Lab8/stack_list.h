#ifndef STACK_List_H
#define STACK_List_H


struct Node {
	char *data;
	Node *next;
};

struct Stack {
	Node *head;
	int size=3;
	int element;
	void create();
	void close();
	void push(char*);
	char* pop();
	bool isempty();
};


#endif

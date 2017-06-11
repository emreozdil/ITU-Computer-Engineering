#include <stdlib.h>
#include "stack.h"

void Stack::create() {
	head = NULL;
	size = 0;
}


void Stack::close() {
	Node *p;
	while (head) {
		p = head;
		head = head->next;
		delete p;
	}
}


void Stack::push(node* newdata) {
	Node *newnode = new Node;
	newnode->data = newdata;
	newnode->next = head;
	head = newnode;
}


node* Stack::pop() {
	Node *topnode;
	node *temp;
	topnode = head;
	head = head->next;
	temp = topnode->data;
	delete topnode;
	return temp;
}


bool Stack::isempty() {
	return head == NULL;
}

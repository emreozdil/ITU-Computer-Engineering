#include <cstdio>
#include "stack.h"
void Stack::create() {
	head = NULL;
}

void Stack::close() {
	node* traverse;
	while (head)
	{
		traverse = head;
		head = head->next;
		delete traverse;
	}
}

void Stack::push(psh newpsh) {
	node* newnode = new node;
	newnode->element = newpsh;
	newnode->next = head;
	head = newnode;
}

psh Stack::pop() {
	node* traverse = head;
	psh temp = traverse->element;
	head = head->next;
	delete traverse;
	return temp;
}

bool Stack::isEmpty() {
	if (head == NULL)
		return true;
	return false;
}
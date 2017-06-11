// QUEUE IMPLEMENTATION 
// WITH LINKED LIST.

#include <iostream>
#include <stdlib.h>
#include "queue.h"
using namespace std;



void Queue::create() {
	front = NULL; back = NULL;
}

void Queue::close() {
	Node_q *p;
	while (front) {
		p = front;
		front = front->next;
		delete p;
	}
}

void Queue::enqueue(char newdata) {
	Node_q *newnode = new Node_q;
	newnode->data = newdata;
	newnode->next = NULL;
	if (isempty()) {    // first element?
		back = newnode;
		front = back;
	}
	else {
		back->next = newnode;
		back = newnode;
	}

}

char Queue::dequeue() {
	Node_q *topnode;
	char temp;
	topnode = front;
	front = front->next;
	temp = topnode->data;
	delete topnode;
	return temp;
}

bool Queue::isempty() {
	return front == NULL;
}

void Queue::print()
{
	Node_q *p = front;
	cout << "\n";
	if (isempty()) {
		cout << "Queue empty. \n";
		return;
	}

	cout << "QUEUE : ";
	while (p != NULL) {
		cout << p->data;
		p = p->next;
	}
	cout << "\n";
}


//int main() {
//	cout << "QUEUE (WITH LINKED LIST)\n";
//
//	Queue q;
//	q.create();
//	q.enqueue('A');
//	q.enqueue('B');
//	q.enqueue('C');
//	q.print();
//
//	char c = q.dequeue();
//	q.enqueue('D');
//	q.enqueue('E');
//	q.enqueue('F');
//	c = q.dequeue();
//	if (!q.isempty())
//		q.dequeue();
//
//	q.print();
//	q.close();
//
//	system("pause");
//	return EXIT_SUCCESS;
//}


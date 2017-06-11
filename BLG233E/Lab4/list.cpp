#include "list.h"
#include <iostream>

using namespace std;

void Liste::create()
{
	head = NULL;
	nodecount = 0;
}

void Liste::close(veri *bas)
{
	veri *p;
	while (bas) {
		p = bas;
		bas = bas->next;
		delete p;
	}
	nodecount = 0;
}

void Liste::list(veri* bas)
{
	if (bas == NULL) {
		cout << " no record found";
		return;
	}

	veri* traverse;
	traverse = bas;
	bool sonlandir = true;
	int i=1;
	while ( sonlandir) {
		cout << i <<". " << traverse->name << " " << traverse->num << endl;

		traverse = traverse->next;
		if (traverse == NULL) sonlandir = false;
		i++;
	}
}

void Liste::add(veri *toadd)
{
	veri *traverse, *tail;
	veri *newnode;
	traverse = head;
	tail = NULL;
	newnode = new veri;
	*newnode = *toadd;
	newnode->next = NULL;
	if (head == NULL) {
		//first node being added
		head = newnode;
		nodecount++;
		return;
	}
	if (strcmp(newnode->name, head->name) < 0) {
		//Insert to head of list
		newnode->next = head;
		head = newnode;
		nodecount++;
		return;
	}
	while (traverse && (strcmp(newnode->name, traverse->name) > 0)) {
		tail = traverse;
		traverse = traverse->next;
	}
	if (traverse) { // Insert into a position
		newnode->next = traverse;
		tail->next = newnode;
	}
	else // Insert to end
		tail->next = newnode;
		nodecount++;
}

void Liste::remove(int ordernum)
{
	veri *traverse, *tail;
	int counter = 1;
	traverse = head;
	tail = NULL;
	if (ordernum <= 0) {
		cout << "Invalid record order number.\n";
			return;
	}

	if (ordernum == 1) {
		head = head->next;
		delete traverse;
		nodecount--;
		return;
	}	while ((traverse != NULL) &&
		(counter < ordernum)) {
		tail = traverse;
		traverse = traverse->next;
		counter++;
	}
	if (counter < ordernum) {
		// given order num too large
		cout << "Could not find record to delete.\n";
	}
	else { // record found
		tail->next = traverse->next;
		delete traverse;
		nodecount--;
	}
}

void Liste::update(int recordnum, veri * toadd)
{
	remove(recordnum);
	add(toadd);
}

veri* Liste::search(char * target)
{	
	veri *traverse;
	traverse = head;
	int counter = 0;
	int found = 0;
	veri *bulunan;
	bulunan = new veri;
	bulunan = NULL;
	veri * tail = NULL;

	while (traverse) {

		counter++;
		if (_strnicmp(traverse->name, target, strlen(target)) == 0) {
			while (_strnicmp(traverse->name, target, strlen(target)) == 0) {
				veri *yeni;
				yeni = new veri;
				yeni->name = traverse->name;
				yeni->num = traverse->num;
				yeni->next = NULL;

				if (bulunan == NULL) {
					bulunan = yeni;
					tail = yeni;
				}
				else {
					tail->next = yeni;
					tail = tail->next;
				}

				traverse = traverse->next;
				counter++;
				if (traverse == NULL) break;
			}
			return bulunan;
		}

		traverse = traverse->next;
	}
	return bulunan;
}
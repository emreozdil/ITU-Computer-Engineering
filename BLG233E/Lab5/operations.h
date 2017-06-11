#ifndef OPERATIONS_H
#define OPERATIONS_H
#include "record.h"
#include <iostream>

struct phone_list
{
	person *head;
	void create();
	void add_person(person *);
	void add_number(char *,number *);
	void del_person(char *);
	void del_number(char *);
	void update_person(char *);
	void update_number(char *);
	void search(char *);
	void list();
	void close();
};

#endif
////#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <cstdio>
#include "record.h"

struct Liste {
	veri *head;
	void create();
	void close(veri *);
	void list(veri *);
	void add(veri *);
	void remove(int ordernum);
	void update(int recordnum, veri *);
	veri* search(char *);
	int nodecount;
};//#endif
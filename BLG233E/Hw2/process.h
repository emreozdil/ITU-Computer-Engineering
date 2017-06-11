/*
* @Author
* Student Name: Emre Özdil
* Student ID : 150120138
* Date: 03/11/2015
*/
#ifndef PROCESS_H
#define PROCESS_H
#include "record.h"
#include <cstdio>
struct operations
{
	FILE *input, *output;
	customer *head, *ntail, *ptail;
	operate *t_head, *t_tail;
	void create();
	void add(customer *);
	void search(customer *);
	void process();
	void del(customer *);
	void print();
	void makeEmpty();
};
#endif
/*
* @Author
* Student Name: Emre Özdil
* Student ID : 150120138
* Date:  10/10/2015
*/

#ifndef operations_h
#define operations_h
#include <cstdio>
#include "record.h"
#define max_record 250
struct Book
{
	char *file_name;
	FILE *library;
	book_record k[max_record];
	int number_of_record;
	void create();
	void print();
	void add(book_record *);
	void del(int record_num);
	void update(int record_num, book_record *);
	int search(int);
	char type(char *);
	char author(char *);
	void save();
};
#endif

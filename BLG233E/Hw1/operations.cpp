/*
* @Author
* Student Name: Emre Özdil
* Student ID : 150120138
* Date:  10/10/2015
*/

#include <iostream>
#include <cstring>
#include "operations.h"

using namespace std;

void Book::create()
{
	number_of_record = 0;
	file_name = "library_record.txt";
	library = fopen(file_name, "r+");
	if (!library)
	{
		library = fopen(file_name, "w+");
		if (!library)
		{
			cout << "Cannot open file!" << endl;
			return;
		}		
	}
	while (!feof(library))
	{
		fread(k + number_of_record, sizeof(book_record), 1, library);
		if (feof(library))	break;
		number_of_record++;
	}
}

void Book::print()
{
	for (int i = 0; i < number_of_record; i++)
	{
		cout << i + 1 << ". " << k[i].ISBN << "\t" << k[i].title << "\t" << k[i].authorName << "\t" << k[i].authorSurname << "\t" << k[i].location << "\t" << k[i].bookType << endl;
	}
}

void Book::add(book_record *ptr)
{
	k[number_of_record].ISBN = ptr->ISBN;
	k[number_of_record].location = ptr->location;
	strcpy(k[number_of_record].title, ptr->title);
	strcpy(k[number_of_record].authorName, ptr->authorName);
	strcpy(k[number_of_record].authorSurname, ptr->authorSurname);
	strcpy(k[number_of_record].bookType, ptr->bookType);
	number_of_record++;
}

void Book::del(int record_num)
{
	for (; record_num <= number_of_record; record_num++)
		*(k + record_num - 1) = *(k + record_num);
	number_of_record--;
}

void Book::update(int record_num, book_record *ptr)
{
	k[record_num-1].ISBN = ptr->ISBN;
	k[record_num - 1].location = ptr->location;
	strcpy(k[record_num - 1].title, ptr->title);
	strcpy(k[record_num - 1].authorName, ptr->authorName);
	strcpy(k[record_num - 1].authorSurname, ptr->authorSurname);
	strcpy(k[record_num - 1].bookType, ptr->bookType);
}

int Book::search(int isbn)
{
	int i, rec=0;
	for (i = 0; i < number_of_record; i++)
	{
		if (k[i].ISBN == isbn)
		{
			rec = 1;
			break;
		}
	}
	if (rec == 0)
		return rec;
	cout << i + 1 << ". " << k[i].ISBN << "\t" << k[i].title << "\t" << k[i].authorName << "\t" << k[i].authorSurname << "\t" << k[i].location << "\t" << k[i].bookType << endl;
	return i+1;
}

char Book::type(char *ptrbook)
{
	int i,rec=0;
	for (i = 0; i < number_of_record; i++)
	{
		if (strcmp(k[i].bookType, ptrbook)==0)
		{
			rec++;
			cout << i + 1 << ". " << k[i].ISBN << "\t" << k[i].title << "\t" << k[i].authorName << "\t" << k[i].authorSurname << "\t" << k[i].location << "\t" << k[i].bookType << endl;
		}
	}
	if (rec == 0)
		return -1;
	return 0;
}

char Book::author(char *ptrbook)
{
	int i,rec=0;
	for (i = 0; i < number_of_record; i++)
	{
		if (strcmp(k[i].authorName, ptrbook) == 0)
		{
			rec++;
			cout << i + 1 << ". " << k[i].ISBN << "\t" << k[i].title << "\t" << k[i].authorName << "\t" << k[i].authorSurname << "\t" << k[i].location << "\t" << k[i].bookType << endl;
		}
	}
	if (rec == 0)
		return -1;
	return 0;
}

void Book::save()
{
	library = fopen(file_name, "w+");
	for (int i = 0; i < number_of_record; i++)
	{
		fwrite(k + i, sizeof(book_record), 1, library);
	}
	fclose(library);
}
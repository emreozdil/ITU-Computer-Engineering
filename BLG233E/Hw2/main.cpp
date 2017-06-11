/*
* @Author
* Student Name: Emre Özdil
* Student ID : 150120138
* Date: 03/11/2015
*/
#include <iostream>
#include <cstring>
#include <cstdio>
#include "process.h"
using namespace std;

operations client;

bool election(char);
void add_user();
void del_user();
void search_user();

int main()
{
	client.create();
	char choice;
	bool finish = true;
	while (finish)
	{
		fscanf(client.input, "%c;", &choice);
		finish=election(choice);
	}
	client.makeEmpty();
	return 0;
}

bool election(char choice)
{
	bool finish = true;
	switch (choice)
	{
	case'A':case'a':
		add_user();
		break;
	case'S':case's':
		search_user();
		break;
	case'V':case'v':
		client.process();
		break;
	case'R':case'r':
		del_user();
		break;
	case'P':case'p':
		client.print();
		break;
	case'E':case'e':
		fprintf(client.output, "%s", "Program exits");
		fclose(client.input);
		fclose(client.output);
		finish = false;
		break;
	default:
		break;
	}
	return finish;
}

void add_user()
{
	customer toadd;
	char name[20];
	char surname[20];
	char type;
	int transaction;
	fscanf(client.input, "%[^;];%[^;];%c;%d;", name, surname, &type, &transaction);
	strcpy(toadd.name, name);
	strcpy(toadd.surname, surname);
	toadd.type = type;
	toadd.transaction = transaction;
	client.add(&toadd);
	fprintf(client.output, "%s\n\n", "New customer is added");
}

void del_user()
{
	customer todel;
	char name[20];
	char surname[20];
	char type;
	fscanf(client.input, "%[^;];%[^;];%c", name, surname, &type);
	strcpy(todel.name, name);
	strcpy(todel.surname, surname);
	todel.type = type;
	client.del(&todel);

}

void search_user()
{
	customer tos;
	char name[20];
	char surname[20];
	fscanf(client.input, "%[^;];%[^\n]", name, surname);
	strcpy(tos.name, name);
	strcpy(tos.surname, surname);
	client.search(&tos);
}
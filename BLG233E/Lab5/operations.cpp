#include "operations.h"
#include <iostream>
#include <cstring>
using namespace std;

void phone_list::create()
{
	head = NULL;
}

void phone_list::add_person(person *toadd)
{
	person *traverse, *tail;
	traverse = head;
	person *newperson;
	newperson = new person;
	*newperson = *toadd;
	newperson->next = NULL;
	newperson->previous = NULL;
	if (head==NULL)
	{
		head = newperson;
		return;
	}
	if (strcmp(head->name,newperson->name)>0)
	{
		newperson->next = head;
		head->previous = newperson;
		head = newperson;
		return;
	}
	while (traverse&&strcmp(traverse->name, newperson->name) < 0)
	{
		tail = traverse;
		traverse = traverse->next;
	}
	if (traverse)
	{
		newperson->next = traverse;
		newperson->previous = tail;
		tail->next = newperson;
		traverse->previous = newperson;
	}
	else
	{
		tail->next = newperson;
		newperson->previous = tail;
	}
}

void phone_list::add_number(char *name,number *addnum)
{
	person *traverse;
	traverse = head;
	number *newnum;
	newnum = new number;
	newnum->next = NULL;
	*newnum = *addnum;
	while (traverse)
	{
		if (strcmp(traverse->name,name)==0)
		{
			newnum->next = traverse->hnumber;
			traverse->hnumber = newnum;
			break;
		}
		traverse = traverse->next;
	}
}

void phone_list::del_person(char *name)
{
	person *traverse;
	number *temp;
	traverse = head;
	while (traverse)
	{
		if (strcmp(traverse->name, name) == 0)
		{
			while (traverse->hnumber)
			{
				temp = traverse->hnumber;
				traverse->hnumber = traverse->hnumber->next;
				delete temp;
			}
			if (head==traverse)
			{
				head = head->next;
				delete traverse;
				return;
			}
			(traverse->previous)->next = traverse->next;
			if (traverse->next)
				(traverse->next)->previous = traverse->previous;
			delete traverse;
			return;
		}
		traverse = traverse->next;
	}
}

void phone_list::del_number(char *name)
{
	person *traverse;
	number *num_traverse,*num_tail;
	traverse = head;
	int i = 1;
	while (traverse)
	{
		if (strcmp(traverse->name, name) == 0)
		{
			num_traverse = traverse->hnumber;
			cout << traverse->name << " " << traverse->surname << endl;
			while (num_traverse)
			{
				cout << "\t" << i << ". " << num_traverse->type << " " << num_traverse->numb << endl;
				num_traverse = num_traverse->next;
				i++;
			}
			cout << "hangi siradaki numarayi silmek istiyorsunuz: ";
			cin >> i;
			num_traverse = traverse->hnumber;
			num_tail = num_traverse;
			for (int j = 1; j < i; j++)
			{
				num_tail = num_traverse;
				num_traverse = num_traverse->next;
			}
			if (num_tail==num_traverse)
			{
				delete num_traverse;
				traverse->hnumber = NULL;
				return;
			}
			num_tail->next = num_traverse->next;
			delete num_traverse;
			return;
		}
		traverse = traverse->next;
	}
}

void phone_list::update_person(char *name)
{
	person *traverse;
	number *temp;
	traverse = head;
	while (traverse)
	{
		if (strcmp(traverse->name, name) == 0)
		{
			if (head==traverse)
			{
				head = head->next;
				cout << "Name: ";
				cin >> traverse->name;
				cout << "Surname: ";
				cin >> traverse->surname;
				add_person(traverse);
				delete traverse;
				return;
			}
			(traverse->previous)->next = traverse->next;
			if (traverse->next)
				(traverse->next)->previous = traverse->previous;
			cout << "Name: ";
			cin >> traverse->name;
			cout << "Surname: ";
			cin >> traverse->surname;
			add_person(traverse);
			delete traverse;
			return;
		}
		traverse = traverse->next;
	}
}

void phone_list::update_number(char *name)
{
	person *traverse;
	number *num_traverse;
	traverse = head;
	int i = 1;
	while (traverse)
	{
		if (strcmp(traverse->name, name) == 0)
		{
			num_traverse = traverse->hnumber;
			cout << traverse->name << " " << traverse->surname;
			while (num_traverse)
			{
				cout << i << ". " << num_traverse->type << " " << num_traverse->numb << endl;
				num_traverse = num_traverse->next;
				i++;
			}
			cout << "hangi siradaki numarayi duzeltmek istiyorsunuz: ";
			cin >> i;
			num_traverse = traverse->hnumber;
			for (int j = 1; j < i; j++)
			{
				num_traverse = num_traverse->next;
			}
			cout << "yeni numarayi giriniz: ";
			cin >> num_traverse->numb;
		}
		traverse = traverse->next;
	}
}

void phone_list::search(char *name)
{
	person *traverse;
	number *num_traverse;
	number *temp;
	traverse = head;
	while (traverse)
	{
		if (strnicmp(traverse->name, name,strlen(name)) == 0)
		{
			while (traverse && strnicmp(traverse->name, name, strlen(name)) == 0)
			{
				cout << traverse->name << " " << traverse->surname << endl;
				num_traverse = traverse->hnumber;
				while (num_traverse)
				{
					cout << "\t" << num_traverse->type << " " << num_traverse->numb << endl;
					num_traverse = num_traverse->next;
				}
				traverse = traverse->next;
				cout << endl;
			}
			return;
		}
		traverse = traverse->next;
	}
}

void phone_list::list()
{
	person *traverse;
	number *num_traverse;
	traverse = head;
	while (traverse)
	{
		cout << traverse->name << " "<<traverse->surname << endl;
		num_traverse = traverse->hnumber;
		while (num_traverse)
		{
			cout <<"\t"<< num_traverse->type << " " << num_traverse->numb << endl;
			num_traverse = num_traverse->next;
		}
		traverse = traverse->next;
		cout << endl;
	}
}
void phone_list::close()
{
	person *traverse;
	number *temp;
	traverse = head;
	while (traverse)
	{
		while (traverse->hnumber)
		{
			temp = traverse->hnumber;
			traverse->hnumber = traverse->hnumber->next;
			delete temp;
		}
		traverse = traverse->next;
		delete traverse->previous;
	}
}
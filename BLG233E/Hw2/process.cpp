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

void operations::create()
{
	head = NULL;
	ptail = NULL;//last P customer
	ntail = NULL;//last N customer
	t_head = NULL;
	if ((input = fopen("input_file.txt", "r")) == NULL)
		puts("File cannot open.");
	if ((output = fopen("output_file.txt", "w+")) == NULL)
		puts("File cannot open.");
}

void operations::add(customer *toadd)
{
	customer *newnode;
	newnode = new customer;
	*newnode = *toadd;
	newnode->next = NULL;
	newnode->op = NULL;
	operate *newop;
	t_head = newnode->op;
	for (int i = 0; i < newnode->transaction; i++)
	{
		newop = new operate;
		newop->next = NULL;
		fscanf(input, "%[^;\n];", newop->trans);
		if (t_head == NULL)
		{
			t_head = newop;
			t_tail = t_head;
			continue;
		}
		t_tail->next = newop;
		t_tail = t_tail->next;
	}
	newnode->op = t_head;
	if (head == NULL)//first record
	{
		head = newnode;
		if (newnode->type == 'P')
			ptail = head;
		else
			ntail = head;
		return;
	}
	if (newnode->type=='P')
	{
		if (ptail == NULL)//bank have N type customer but no one is P type customer 
		{
			newnode->next = head;
			head = newnode;
			ptail = head;
			return;
		}
		else//bank have N type customer and P type customer 
		{
			newnode->next = ptail->next;
			ptail->next = newnode;
			ptail = ptail->next;
		}
	}
	if (newnode->type == 'N')
	{
		if (ntail == NULL)//bank have P type customer but no one is N type customer
		{
			ntail = ptail->next;
			ntail = newnode;
			return;
		}
		else//bank have N type customer and P type customer 
		{
			ntail->next = newnode;
			ntail = ntail->next;
		}
	}

}

void operations::search(customer *tosearch)
{
	customer *traverse;
	operate *t_traverse;
	traverse = head;
	while (traverse)
	{
		if ((strcmp(tosearch->name, traverse->name) == 0) && (strcmp(tosearch->surname, traverse->surname) == 0))
		{
			fprintf(output, "%s %s %s\n", tosearch->name, tosearch->surname, "is be found.");
			fprintf(output, "%s %s %c ", tosearch->name, tosearch->surname, traverse->type);
			t_traverse = traverse->op;
			for (int i = 0; i < traverse->transaction; i++)
			{
				fprintf(output, "%s ", t_traverse->trans);
				t_traverse = t_traverse->next;
			}
			fprintf(output, "\n\n");
			return;
		}
		traverse = traverse->next;
	}
	fprintf(output, "%s %s %s\n\n", tosearch->name, tosearch->surname, "could not be found.");
}

void operations::process()
{
	if (head->type=='N')
		head = head->next;
	else//P type customer do only one transaction
	{
		head->transaction--;
		customer *temp;
		temp = new customer;
		temp->next = NULL;
		head->op= head->op->next;
		if (head!=ptail)//head adding to ptail
		{
			*temp = *head;
			temp->next = ptail->next;
			ptail->next = temp;
			ptail = ptail->next;
			head = head->next;
		}		
	}
	fprintf(output, "%s\n\n", "Next transaction is processed");
}

void operations::del(customer *todel)
{
	customer *traverse, *prev;
	traverse = head;
	while (traverse)
	{
		if ((strcmp(todel->name,traverse->name)==0)&&(strcmp(todel->surname, traverse->surname) == 0)&&(todel->type==traverse->type))
		{
			if (traverse == head)
			{
				head = head->next;
				delete traverse;
			}
			else if (traverse == ptail)
			{
				prev->next = traverse->next;
				ptail= prev;
				delete traverse;
			}
			else if (traverse == ntail)
			{
				prev->next = traverse->next;
				ntail = prev;
				delete traverse;
			}
			else
			{
				prev->next = traverse->next;
				delete traverse;
			}			
			fprintf(output, "%s %s %s\n\n", todel->name, todel->surname, "is removed");
			return;
		}
		prev = traverse;
		traverse = traverse->next;
	}
	fprintf(output, "%s %s %s\n\n", todel->name, todel->surname, "could not be found; therefore, he/she is could not be deleted.");

}

void operations::print()
{
	char *temp;
	if (head == NULL)
		return;
	customer *traverse;
	operate *t_traverse;
	traverse = head;
	while (traverse)
	{
		t_traverse = traverse->op;
		fprintf(output, "%s %s %c ", traverse->name, traverse->surname, traverse->type);
		for (int i = 0; i < traverse->transaction; i++)
		{
			fprintf(output, "%s ", t_traverse->trans);
			t_traverse= t_traverse->next;
		}
		fprintf(output, "\n");
		traverse = traverse->next;
	}
	fprintf(output, "\n");
}

void operations::makeEmpty()
{
	customer *p;
	operate *q;
	while (head)
	{
		p = head;
		head = head->next;
		q = p->op;
		while (q)
		{
			p->op = p->op->next;
			delete q;
			q = p->op;
		}
		delete p;
	}
}
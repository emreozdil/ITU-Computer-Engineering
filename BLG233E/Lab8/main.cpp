//  Created by Emre Özdil
//  Copyright © 2015 Emre Özdil. All rights reserved.

#include <iostream>
#include "queue.h"
#include "stack_list.h"

using namespace std;

Stack cuval[4];


Queue kuyruk;

bool choose(char);
void add(char*);
void leave(char*);

int main()
{
	for (int i = 0; i < 4; i++)
		cuval[i].create();

	kuyruk.create();

	char choice;
	bool finish = true;
	while (finish)
	{
		cout << "A: add a car" << endl;
		cout << "L: leave a car " << endl;
		cout << "E: exit" << endl;
		cout << "sen hayirdir: ";
		cin >> choice;
		finish=choose(choice);
	}
}

bool choose(char c)
{
	char *plaka = new char[10];
	switch (c)
	{
	case 'A': case 'a':
		cout << "Enter a id: ";
		cin >> plaka;
		add(plaka);
		break;
	case 'L': case 'l':
		cout << "Enter a id: ";
		cin >> plaka;
		leave(plaka);
		break;
	case 'E': case 'e':
		return false;
	default:
		return true;
	}
}

void add(char *id)
{
	for (int i = 0; i < 4; i++)
	{
		if (cuval[i].element < cuval[i].size)
			cuval[i].push(id);
	}
}
void leave(char *id)
{
	for (int i = 0; i < 4; i++)
	{
		if (cuval[i].element < cuval[i].size)
			cuval[i].push(id);
	}
}

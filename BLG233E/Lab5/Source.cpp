//  Created by Emre Özdil
//  Copyright © 2015 Emre Özdil. All rights reserved.

#include <iostream>
#include "operations.h"
using namespace std;

phone_list book;

void print_menu();
bool process(char);
void kisi_ekle();
void numara_ekle();
void kisi_sil();
void numara_sil();
void kisi_up();
void numara_up();
void kisi_ara();

int main()
{
	char choice;
	bool finish = true;
	book.create();
	while (finish)
	{
		print_menu();
		cin >> choice;
		finish=!process(choice);
	}
	return 0;
}

void print_menu()
{
	cout << endl << endl;
	cout << "A: Add Person" << endl;
	cout << "B: Add Number" << endl;
	cout << "C: Delete Person" << endl;
	cout << "D: Delete Number" << endl;
	cout << "E: Update Person" << endl;
	cout << "F: Update Number" << endl;
	cout << "G: Search" << endl;
	cout << "H: List Records" << endl;
	cout << "I: Exit" << endl;
	cout << endl;
	cout << "Enter an option {A, B, C, D, E, F, G, H, I} : ";
}

bool process(char secim)
{
	bool sonlandir = false;
	switch (secim) {
	case 'A': case 'a':
		kisi_ekle();
		break;
	case 'B': case 'b':
		numara_ekle();
		break;
	case 'C': case 'c':
		kisi_sil();
		break;
	case 'D': case 'd':
		numara_sil();
		break;
	case 'E': case 'e':
		kisi_up();
		break;
	case 'F': case 'f':
		numara_up();
		break;
	case 'G': case 'g':
		kisi_ara();
		break;
	case 'H': case 'h':
		book.list();
		break;
	case 'I': case 'i':
		cout << "Are you sure that you want to terminate the program? (E / H) : ";
		cin >> secim;
		if (secim == 'E' || secim == 'e')
			sonlandir = true;
		break;	
	default:
		cout << "Error: You have made an invalid choice" << endl;
		cout << "Try again {A, B, C, D, E, F, G, H, I} :";
		cin >> secim;
		sonlandir = process(secim);
		break;
	}
	return sonlandir;
}

void kisi_ekle()
{
	person *np;
	np = new person;
	cout << "Please enter the information of the person you want to save " << endl;
	cout << "Name : ";
	cin >> np->name;
	cout << "Surname : ";
	cin >> np->surname;
	np->hnumber = NULL;
	book.add_person(np);
	cout << "Record has been added" << endl;
	getchar();
}
void numara_ekle()
{
	char name[20];
	number *nn;
	nn = new number;
	cout << "Please enter the number of the person you want to save " << endl;
	cout << "Name : ";
	cin >> name;
	cout << "Number type: ";
	cin >> nn->type;
	cout << "Number: ";
	cin >> nn->numb;
	book.add_number(name, nn);
	cout << "Record has been added" << endl;
	getchar();
}
void kisi_sil()
{
	char name[20];
	cout << "Please enter the name of the person you want to delete " << endl;
	cout << "Name : ";
	cin >> name;
	book.del_person(name);
	cout << "Record has been deleted" << endl;
	getchar();
}
void numara_sil()
{
	char name[20];
	cout << "Please enter the name of the person you want to delete number " << endl;
	cout << "Name : ";
	cin >> name;
	book.del_number(name);
	cout << "Number has been deleted" << endl;
	getchar();
}
void kisi_up()
{
	char name[20];
	cout << "Please enter the name of the person you want to update " << endl;
	cout << "Name : ";
	cin >> name;
	book.update_person(name);
	cout << "Record has been updated" << endl;
	getchar();
}
void numara_up()
{
	char name[20];
	cout << "Please enter the name of the person you want to update number " << endl;
	cout << "Name : ";
	cin >> name;
	book.update_number(name);
	cout << "Number has been deleted" << endl;
	getchar();
}
void kisi_ara()
{
	char name[20];
	cout << "Please enter the name of the person you want to search " << endl;
	cout << "Name : ";
	cin >> name;
	book.search(name);
	cout << "Search is completed" << endl;
	getchar();
}

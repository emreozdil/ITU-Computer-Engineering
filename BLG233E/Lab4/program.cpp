//  Created by Emre Özdil
//  Copyright © 2015 Emre Özdil. All rights reserved.

#include <iostream>
#include <cstring>
#include <cstdio>
#include "list.h"

using namespace std;

typedef Liste veriyapisi;
veriyapisi rehber;

void menu_yazdir();
bool islem_yap(char);
void kayit_ekle();
void kayit_sil();
void kayit_listele();
void kayit_ara();
void kayit_guncelle();
int main() {

	rehber.create();

	bool bitir = false;
	char secim;
	while (!bitir) {
		menu_yazdir();
		cin >> secim;
		bitir = islem_yap(secim);
	}
	rehber.close(rehber.head);
	return EXIT_SUCCESS;
}

void menu_yazdir() {
	cout << endl << endl;
	cout << "A: Search Record" << endl;
	cout << "E: Add Record" << endl;
	cout << "G: Update Record" << endl;
	cout << "S: Delete Record" << endl;
	cout << "L: List Records" << endl;
	cout << "C: Exit" << endl;
	cout << endl;
	cout << "Enter an option {A, E, G, S, C, L} : ";
}

bool islem_yap(char secim) {
	bool sonlandir = false;
	switch (secim) {
	case 'A': case 'a':
		kayit_ara();
		break;
	case 'E': case 'e':
		kayit_ekle();
		break;
	case 'G': case 'g':
		kayit_guncelle();
		break;
	case 'S': case 's':
		kayit_sil();
		break;
	case 'C': case 'c':
		cout << "Are you sure that you want to terminate the program? (E / H) : ";
		cin >> secim;
		if (secim == 'E' || secim == 'e')
			sonlandir = true;
		break;
	case 'L': case 'l':
		kayit_listele();
		break;
	default:
		cout << "Error: You have made an invalid choice" << endl;
		cout << "Try again {A, E, G, S, B, C} :";
		cin >> secim;
		sonlandir = islem_yap(secim);
		break;
	}
	return sonlandir;
}

void kayit_ekle() {
	veri yenikayit;

	char temp[20];
	cout << "Please enter the information of the person you want to save " << endl;
	cout << "Name : ";
	cin >> temp;
	char* name = new char[strlen(temp) + 1];
	strcpy(name, temp);
	yenikayit.name = name;

	cout << "Number :";
	cin >> temp;
	char* num = new char[strlen(temp) + 1];
	strcpy(num, temp);
	yenikayit.num = num;

	rehber.add(&yenikayit);
	cout << "Record has been added" << endl;
	getchar();
};

void kayit_listele() {
	rehber.list(rehber.head);
	getchar();
	getchar();
}

void kayit_sil() {
	rehber.list(rehber.head);
	int index;
	cout << "Enter index to delete" << endl;
	cin >> index;
	rehber.remove(index);
};

void kayit_ara() {
	char ad[20];
	cout << "Please enter the name of the person you want to search:" << endl;
	cin >> ad;
	veri * sonuc= rehber.search(ad);
	rehber.list(sonuc);
	rehber.close(sonuc);
		
	getchar();
};

void kayit_guncelle() {
	int index;
	veri yenikayit;
	rehber.list(rehber.head);
	cout << "Please enter the index of the person you want to update:" << endl;
	cin >> index;

	char temp[20];
	cout << "Please enter the information of the person you want to save " << endl;
	cout << "Name : ";
	cin >> temp;
	char* name = new char[strlen(temp) + 1];
	strcpy(name, temp);
	yenikayit.name = name;

	cout << "Phone number :";
	cin >> temp;
	char* num = new char[strlen(temp) + 1];
	strcpy(num, temp);
	yenikayit.num = num;

	rehber.update(index, &yenikayit);

	getchar();
};

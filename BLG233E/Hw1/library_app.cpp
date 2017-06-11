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

typedef Book datastructure;
datastructure catalog;

void print_menu();
bool perform_operation(char);
void print_record();
void author_search();
void type_search();
void add_record();
void update_record();
void delete_record();

int main()
{
	catalog.create();
	bool end = false;
	char choice;
	while (!end)
	{
		print_menu();
		cin >> choice;
		end = perform_operation(choice);
		catalog.save();
	}
	return 0;
}

void print_menu()
{
	//system("cls");
	cout << endl << endl;
	cout << "Please select the operation to perform and enter the operation code" << endl;
	cout << "(P) Print the whole catalogue" << endl;
	cout << "(A) Search the catalogue by author" << endl;
	cout << "(T) Search the catalogue by book type" << endl;
	cout << "(I) Insert a new book record" << endl;
	cout << "(U) Update an existing book record" << endl;
	cout << "(R) Remove a book record" << endl;
	cout << "(E) Exit the program" << endl;
	cout << "Your selection is: ";
}

bool perform_operation(char choice)
{
	bool terminate = false;
	switch (choice)
	{
	case 'P': case 'p':
		print_record();
		break;
	case 'A': case 'a':
		author_search();
		break;
	case 'T': case 't':
		type_search();
		break;
	case 'I': case 'i':
		add_record();
		break;
	case 'U': case 'u':
		update_record();
		break;
	case 'R': case 'r':
		delete_record();
		break;
	case 'E': case 'e':
		cout << "Are you sure you want to exit the program? (Y/N): ";
		cin >> choice;
		if (choice == 'Y' || choice == 'y')
		{
			terminate = true;
			break;
		}
	default:
		cout << "Error: You have entered an invalid choice" << endl;
		cout << "Please try again {P, A, T, I, U, R, E}: ";
		cin >> choice;
		terminate = perform_operation(choice);
		break;
	}
	return terminate;
}

void print_record()
{
	catalog.print();
}

void author_search()
{
	char author[20];
	cout << "Please enter the name of the author you want to search: ";
	cin >> author;
	if (catalog.author(author) != 0)
		cout << "Record cannot be found." << endl;
	getchar();
}
void type_search()
{
	char type[10];
	cout << "Please enter the type of the book you want to search: ";
	cin >> type;
	if (catalog.type(type) != 0)
		cout << "Record cannot be found." << endl;
	getchar();
}

void add_record()
{
	book_record new_record;
	cout << "Please enter the information of the book you want to save" << endl;
	cout << "ISBN: ";
	while (!(cin >> new_record.ISBN))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Please enter numeric characters only: ";
	}
	cout << "Title: ";
	cin >> new_record.title;
	cout << "Author Name: ";
	cin >> new_record.authorName;
	cout << "Author Surname: ";
	cin >> new_record.authorSurname;
	cout << "Location: ";
	while(!(cin >> new_record.location))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Please enter numeric characters only: ";
	}
	cout << "Book Type: ";
	cin >> new_record.bookType;
	catalog.add(&new_record);
	cout << "Record has been added." << endl;
	getchar();
}

void update_record()
{
	int isbn,choice;
	cout << "Please enter the ISBN of the book you want to update: ";
	cin >> isbn;
	if (catalog.search(isbn) == -1)
		cout << "Record cannot be found." << endl;
	else
	{
		cout << "Record has been found." << endl;
		cout << "Please enter the index of the record that you want to update(Press - 1 to exit without updating): ";
		cin >> choice;
		if (choice == -1)	return;
		book_record new_record;
		cout << "Please enter the up-to-date information" << endl;
		cout << "ISBN: ";
		while (!(cin >> new_record.ISBN))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Please enter numeric characters only: ";
		}
		cout << "Title: ";
		cin >> new_record.title;
		cout << "Author Name: ";
		cin >> new_record.authorName;
		cout << "Author Surname: ";
		cin >> new_record.authorSurname;
		cout << "Location: ";
		while (!(cin >> new_record.location))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Please enter numeric characters only: ";
		}
		cout << "Book Type: ";
		cin >> new_record.bookType;
		catalog.update(choice, &new_record);
		cout << "Record has been updated." << endl;
	}
	getchar();
}

void delete_record()
{
	int isbn, choice;
	cout << "Please enter the ISBN of the book you want to delete: " ;
	cin >> isbn;
	if (catalog.search(isbn) == 0)
		cout << "Record cannot be found." << endl;
	else
	{
		cout << "Record has been found." << endl;
		cout << "Please enter the index of the record that you want to delete (Press - 1 to exit without deletion): ";
		cin >> choice;
		if (choice == -1)	return;
		catalog.del(choice);
		cout << "Record has been deleted" << endl;
	}
	getchar();
}
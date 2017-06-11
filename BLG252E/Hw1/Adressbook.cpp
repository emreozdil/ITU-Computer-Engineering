/*
* @Author
* Student Name: Emre Özdil
* Student ID : 150120138
* Date: 26/03/2016
*/

#include <iostream>
#include <string>
#include "InstructorList.h"
using namespace std;

void Initial();
bool Operations();
void PrintMenu();
void AddInstructor();
void DeleteInstructor();
void ListAllInstructor();
void SearchByName();
void SearchBySurname();
void SearchByTelephoneNumber();
void SearchByRoomNumber();

InstructurList ITU;

int main()
{
	Initial();
	bool bPerform = true;
	// Operation loop
	while (bPerform) { bPerform = Operations(); }
}

void Initial()
{
	// Initial Instructors
	Instructor GulsenEryigit("Assist. Prof. Dr.", "Gulsen", "Eryigit", "(+90 212) 2853503", "3303", "gulsenc", "gulsenc@itu.edu.tr", "BLG252E, BLG621");
	Instructor SanemKabadayi("Assist. Prof. Dr.", "Sanem", "Kabadayi", "(+90 212) 2853633", "3311", "kabadayi", "kabadayi@itu.edu.tr", "BLG252E");
	Instructor HaticeKose("Assist. Prof. Dr.", "Hatice", "Kose", "(+90 212) 2853593", "3315", "hatice.kose", "hatice.kose@itu.edu.tr", "BLG252E");
	// Initial Instructors are adding Instructors List
	ITU.AddInstructor(GulsenEryigit);
	ITU.AddInstructor(SanemKabadayi);
	ITU.AddInstructor(HaticeKose);
}

bool Operations()
{
	char operation;
	PrintMenu();
	cin >> operation;
	switch (operation)
	{
	case '1':
		AddInstructor();
		break;
	case '2':
		DeleteInstructor();
		break;
	case '3':
		ListAllInstructor();
		break;
	case '4':
		SearchByName();
		break;
	case '5':
		SearchBySurname();
		break;
	case '6':
		SearchByTelephoneNumber();
		break;
	case '7':
		SearchByRoomNumber();
		break;
	case '8':
		return false;
	default:
		break;
	}
	cout << "Do you want to perform another operation?(Y/N)" << endl;
	cin >> operation;
	if (operation == 'N' || operation == 'n')	return false;
	// else loop continue
	return true;
}

void PrintMenu()
{
	cout << "1. Add a new instructor" << endl;
	cout << "2. Delete an instructor" << endl;
	cout << "3. List all instructors" << endl;
	cout << "4. Search by Name" << endl;
	cout << "5. Search by Surname" << endl;
	cout << "6. Search by Telephone Number" << endl;
	cout << "7. Search by Room Number" << endl;
	cout << "8. Exit" << endl;
	cout << "Enter the number for operation you want to perform: " << endl;
}

void AddInstructor()
{
	string Title;
	string FirstName;
	string LastName;
	string PhoneNumber;
	string RoomNumber;
	string UserName;
	string EmailAddress;
	string Courses;

	cout << "Enter the title: " << endl;
	cin.ignore();
	getline(cin, Title);
	cout << "Enter the First Name: " << endl;
	getline(cin, FirstName);
	cout << "Enter the Last Name: " << endl;
	getline(cin, LastName);
	cout << "Enter the Telephone Number: " << endl;
	getline(cin, PhoneNumber);
	cout << "Enter the Room Number: " << endl;
	getline(cin, RoomNumber);
	cout << "Enter the User Name: " << endl;
	getline(cin, UserName);
	cout << "Enter the Courses: " << endl;
	getline(cin, Courses);

	// Email Adress is creating username
	EmailAddress = UserName + "@itu.edu.tr";

	// Constructor call
	Instructor AddInstructor(Title, FirstName, LastName, PhoneNumber, RoomNumber, UserName, EmailAddress, Courses);
	
	// Adding Instructors List
	ITU.AddInstructor(AddInstructor);
}

void DeleteInstructor()
{
	string FirstName;
	string LastName;

	cout << "Enter the First Name of the record to be deleted: " << endl;
	cin >> FirstName;
	cout << "Enter the Last Name of the record to be deleted: " << endl;
	cin >> LastName;

	// Constructor call
	Instructor DeleteInstructor(FirstName, LastName);
}

void ListAllInstructor()
{
	ITU.PrintList();
}

// Search functions are similar Search by variable

void SearchByName()
{
	cout << "----------Search Results----------" << endl;
	string FirstName;
	cout << "Enter the First Name: " << endl;
	cin >> FirstName;
	ITU.SearchName(FirstName);
}

void SearchBySurname()
{
	cout << "----------Search Results----------" << endl;
	string LastName;
	cout << "Enter the Last Name: " << endl;
	cin >> LastName;
	ITU.SearchLastName(LastName);
}

void SearchByTelephoneNumber()
{
	cout << "----------Search Results----------" << endl;
	string PhoneNumber;
	cout << "Enter the Telephone Number: " << endl;
	cin >> PhoneNumber;
	ITU.SearchTelephoneNumber(PhoneNumber);
}

void SearchByRoomNumber()
{
	cout << "----------Search Results----------" << endl;
	string RoomNumber;
	cout << "Enter the Room Number: " << endl;
	cin >> RoomNumber;
	ITU.SearchRoomNumber(RoomNumber);
}

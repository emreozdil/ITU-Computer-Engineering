/*
* @Author
* Student Name: Emre Özdil
* Student ID : 150120138
* Date: 26/03/2016
*/

#pragma once
#include "Instructor.h"
class InstructurList
{
public:
	InstructurList();
	~InstructurList();
	void AddInstructor(Instructor&);
	void DeleteInstructor(Instructor);
	void PrintList();
	void SearchName(string);
	void SearchLastName(string);
	void SearchTelephoneNumber(string);
	void SearchRoomNumber(string);
	bool Duplicate(Instructor&);
private:
	Instructor *instructors;
	int existent; // total number of instructors
	int capasity; // dynamic array capasity
};

InstructurList::InstructurList()
{
	existent = 0;
	// Inital Instructor List capasity
	capasity = 4;
	instructors = new Instructor[capasity];
}

InstructurList::~InstructurList()
{
	delete[] instructors;
}

inline void InstructurList::AddInstructor(Instructor& addInstructor)
{
	// Check addInstructor duplicate or not via Duplicate function
	if (Duplicate(addInstructor)) return;
	// To add addInstructor index of instructor list
	instructors[existent] = addInstructor;
	existent++;
	// IF Capasity is full array extend in order to add next instructor
	if (existent==capasity)
	{
		Instructor *instructorsTemp;
		capasity *= 2;
		instructorsTemp = new Instructor[capasity];
		for (int i = 0; i < existent; i++)
		{
			// copy instructors to new memory
			instructorsTemp[i] = instructors[i];
		}
		// delete old memory
		delete[] instructors;
		// instructors pointer point to new memeory
		instructors = instructorsTemp;
	}
}

inline void InstructurList::DeleteInstructor(Instructor deleteInstructor)
{
	for (int i = 0; i < existent; i++)
	{
		if (instructors[i].getFirstName() == deleteInstructor.getFirstName() && instructors[i].getLastName() == deleteInstructor.getLastName())
		{
			//because of new instructor re-write last one
			existent--;
			for (int j = i; j < existent; j++)
			{
				// shifting all array
				instructors[j] = instructors[j + 1];
			}
			cout << "Record has been deleted." << endl;
			return; // exit function
		}
	}
	// record cannot be found
	cout << "Record has not beed found, thus record has not been deleted." << endl;
}

inline void InstructurList::PrintList()
{
	cout << "----------List of all Instructor in Computer Engineering of ITU----------" << endl;
	for (int i = 0; i < existent; i++)
	{
		// call Instructor::Print() function for all instructors
		instructors[i].Print();
	}
}

inline void InstructurList::SearchName(string name)
{
	for (int i = 0; i < existent; i++)
	{
		if (instructors[i].getFirstName() == name)
		{
			instructors[i].Print();
			return;
		}
	}
	cout << "Instructor cannot be found." << endl;
}

// Search functions are same due to use get method and compare

inline void InstructurList::SearchLastName(string lastName)
{
	for (int i = 0; i < existent; i++)
	{
		if (instructors[i].getLastName() == lastName)
		{
			instructors[i].Print();
			return;
		}
	}
	cout << "Instructor cannot be found." << endl;
}

inline void InstructurList::SearchTelephoneNumber(string phoneNumber)
{
	for (int i = 0; i < existent; i++)
	{
		if (instructors[i].getPhoneNumber() == phoneNumber)
		{
			instructors[i].Print();
			return;
		}
	}
	cout << "Instructor cannot be found." << endl;
}

inline void InstructurList::SearchRoomNumber(string roomNumber)
{
	for (int i = 0; i < existent; i++)
	{
		if (instructors[i].getRoomNumber() == roomNumber)
		{
			instructors[i].Print();
			return;
		}
	}
	cout << "Instructor cannot be found." << endl;
}

inline bool InstructurList::Duplicate(Instructor& duplicateInstructor)
{
	for (int i = 0; i < existent; i++)
	{
		if (instructors[i]==duplicateInstructor) // Operator overloading
		{
			cout << "In database, this instructors has already been present." << endl;
			return true; // Instructor is not added
		}
	}
	return false;	// Instructor is added
}


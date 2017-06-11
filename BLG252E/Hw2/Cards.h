/*
* @Author
* Student Name: Emre Özdil
* Student ID : 150120138
* Date: 26/03/2016
*/

#pragma once
#include <iostream>

using namespace std;

class Base
{
public:
	Base();
	~Base();
	virtual int compare(Base*) const= 0;
	char color;
	Base *next;
private:
	friend class HetList;
};

Base::Base()
{
}

Base::~Base()
{
}
class HetList
{
public:
	HetList();
	~HetList();
	void insert(Base*);
	void print();
	Base *head;
private:
};

HetList::HetList()
{
	head = 0;
}

HetList::~HetList()
{
}
// BLUE
class Blue : public Base
{
public:
	Blue(char);
	~Blue();
	int compare(Base*) const;

private:
};

Blue::Blue(char color)
{
	this->color = color;
}

Blue::~Blue()
{
}
inline int Blue::compare(Base* opponent) const
{
	switch (opponent->color)
	{
	case 'B':
		return 1;
	case 'G':
		return 0;
	case 'R':
		return 2;
	case 'D':
		return 0;
	default:
		break;
	}
}
// GREEN
class Green : public Base
{
public:
	Green(char);
	~Green();
	int compare(Base*) const;

private:

};

Green::Green(char color)
{
	this->color = color;
}

Green::~Green()
{
}
inline int Green::compare(Base* opponent) const
{
	switch (opponent->color)
	{
	case 'B':
		return 2;
	case 'G':
		return 1;
	case 'R':
		return 0;
	case 'D':
		return 2;
	default:
		break;
	}
}
// RED
class Red : public Base
{
public:
	Red();
	Red(char);
	~Red();
	int compare(Base*) const;

private:
};

Red::Red()
{
}
Red::Red(char color)
{
	this->color = color;
}

Red::~Red()
{
}
inline int Red::compare(Base* opponent) const
{
	switch (opponent->color)
	{
	case 'B':
		return 0;
	case 'G':
		return 2;
	case 'R':
		return 1;
	case 'D':
		return 0;
	default:
		break;
	}
}
// DARK RED
class DarkRed : public Red
{
public:
	DarkRed(char);
	~DarkRed();
	int compare(Base*) const;

private:

};

DarkRed::DarkRed(char color)
{
	this->color = color;
}

DarkRed::~DarkRed()
{
}
inline int DarkRed::compare(Base* opponent) const
{
	switch (opponent->color)
	{
	case 'B':
		return 2;
	case 'G':
		return 0;
	case 'R':
		return 2;
	case 'D':
		return 1;
	default:
		break;
	}
}

// Insert to list
inline void HetList::insert(Base *newCard)
{
	if (head)        
		newCard->next = head;
	else     			
		newCard->next = 0;   
	head = newCard;
}

// Print cards
inline void HetList::print()
{
	Base *traverse = head;
	while (traverse)
	{
		cout << traverse->color << " ";
		traverse = traverse->next;
	}
	cout << endl;
}

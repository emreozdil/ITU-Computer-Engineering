/*
* @Author
* Student Name: Emre Özdil
* Student ID : 150120138
* Date: 26/03/2016
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Cards.h"

#define pb push_back

using namespace std;

void print(HetList, HetList);
void score(HetList, HetList);


int main()
{
	HetList Player1;
	HetList Player2;
	string player1;
	string player2;
	ifstream myfile("deck.txt");
	if (myfile.is_open())
	{
		getline(myfile, player1);
		getline(myfile, player2);
	}
	else	cout << "Unable to open file";
	
	// Reverse strings in order to add to head
	reverse(player1.begin(), player1.end());
	reverse(player2.begin(), player2.end());

	// Player 1 cards are adding list
	for (unsigned i = 0; i < player1.length(); i++)
	{
		if (player1[i]=='B')
		{
			Blue *blue = new Blue(player1[i]);
			Player1.insert(blue);
		}
		else if (player1[i] == 'G')
		{
			Green *green = new Green(player1[i]);
			Player1.insert(green);
		}
		else if (player1[i] == 'R')
		{
			Red *red = new Red(player1[i]);
			Player1.insert(red);
		}
		else if (player1[i] == 'D')
		{
			DarkRed *darkRed = new DarkRed(player1[i]);
			Player1.insert(darkRed);
		}
		else continue;
	}

	// Player 2 cards are adding list
	for (unsigned i = 0; i < player2.length(); i++)
	{
		if (player2[i] == 'B')
		{
			Blue *blue = new Blue(player2[i]);
			Player2.insert(blue);
		}
		else if (player2[i] == 'G')
		{
			Green *green = new Green(player2[i]);
			Player2.insert(green);
		}
		else if (player2[i] == 'R')
		{
			Red *red = new Red(player2[i]);
			Player2.insert(red);
		}
		else if (player2[i] == 'D')
		{
			DarkRed *darkRed = new DarkRed(player2[i]);
			Player2.insert(darkRed);
		}
		else continue;
	}
	print(Player1, Player2);
	score(Player1, Player2);
	return 0;
}

void print(HetList player1, HetList player2)
{
	cout << "Player1: ";
	player1.print();
	cout << "Player2: ";
	player2.print();
}

void score(HetList player1, HetList player2)
{
	vector <int> score1;
	vector <int> score2;
	Base *traverse1 = player1.head;
	Base *traverse2 = player2.head;
	int Lose1=0, Lose2=0;
	int Tie1=0, Tie2=0;
	int Win1=0, Win2=0;
	int score;
	while (traverse1)
	{
		score = traverse1->compare(traverse2);
		score1.pb(score);
		score2.pb(2 - score);
		traverse1 = traverse1->next;
		traverse2 = traverse2->next;
	}
	cout << "Score1: ";
	for (unsigned i = 0; i < score1.size(); i++)
	{
		cout << score1[i] << " ";
		if (score1[i] == 0)
			Lose1++;
		else if (score1[i] == 1)
			Tie1++;
		else
			Win1++;
	}
	cout << endl << "Score2: ";;
	for (unsigned i = 0; i < score2.size(); i++)
	{
		cout << score2[i] << " ";
		if (score2[i] == 0)
			Lose2++;
		else if (score2[i] == 1)
			Tie2++;
		else
			Win2++;
	}
	cout << endl;
	cout << "Total Score1: Lose: " << Lose1 << " Tie: " << Tie1 << " Win: " << Win1 << endl;
	cout << "Total Score2: Lose: " << Lose2 << " Tie: " << Tie2 << " Win: " << Win2 << endl;
	if (Win1>Win2)
		cout << "Winner: Player1" << endl;
	else if (Win2>Win1)
		cout << "Winner: Player2" << endl;
	else cout << "Tie" << endl;
}
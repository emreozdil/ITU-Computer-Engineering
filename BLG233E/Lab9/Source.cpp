//  Created by Emre Özdil
//  Copyright © 2015 Emre Özdil. All rights reserved.

#include <iostream>
#include <ctime>
#include "stack.h"

#define MAZESIZE 10


using namespace std;


cell m[MAZESIZE][MAZESIZE];
Stack s;
Stack p;
psh current;

void createMaze(cell m[][MAZESIZE]);
int selectRoom(int room[]);
void print(cell m[][MAZESIZE]);
void createPath(cell m[][MAZESIZE]);
void findPath(cell m[][MAZESIZE]);
int exitA, exitB;

int main() {
	srand(time(NULL));
	s.create();
	createMaze(m);
	print(m);
	s.close();
	p.create();
	createPath(m);
	p.close();
	system("pause");
	return 0;
}

void createMaze(cell m[][MAZESIZE]) {
	for (int i = 0; i < MAZESIZE; i++) {
		for (int j = 0; j < MAZESIZE; j++) {
			m[i][j].left = true;
			m[i][j].right = true;
			m[i][j].up = true;
			m[i][j].down = true;
			m[i][j].visited = false;
			m[i][j].val= ' ';
		}
	}

	int room[4];
	int selected = 0;
	psh current;
	current.A = 0;
	current.B = 0;
	int visitnum = 1;

	while (visitnum < MAZESIZE * MAZESIZE) {

		room[0] = 0;
		room[1] = 0;
		room[2] = 0;
		room[3] = 0;

		if (current.A > 0 && m[current.A - 1][current.B].visited == false)
			room[0] = 1;
		if (current.A < (MAZESIZE - 1) && m[current.A + 1][current.B].visited == false)
			room[1] = 1;
		if (current.B > 0 && m[current.A][current.B - 1].visited == false)
			room[2] = 1;
		if (current.B < (MAZESIZE - 1) && m[current.A][current.B + 1].visited == false)
			room[3] = 1;

		if (room[0] + room[1] + room[2] + room[3] > 0) {
			selected = selectRoom(room);
			s.push(current);

			if (selected == 0) {
				m[current.A][current.B].up = false;
				m[current.A - 1][current.B].down = false;
				current.A--;
			}
			else if (selected == 1) {
				m[current.A][current.B].down = false;
				m[current.A + 1][current.B].up = false;
				current.A++;
			}
			else if (selected == 2) {
				m[current.A][current.B].left = false;
				m[current.A][current.B - 1].right = false;
				current.B--;
			}
			else if (selected == 3) {
				m[current.A][current.B].right = false;
				m[current.A][current.B + 1].left = false;
				current.B++;
			}

			m[current.A][current.B].visited = true;
			visitnum++;
		}

		else if (!s.isEmpty()) {
			current = s.pop();
		}

		else {
			current.A = rand() % MAZESIZE;
			current.B = rand() % MAZESIZE;
			if (m[current.A][current.B].visited == false) {
				m[current.A][current.B].visited = true;
				visitnum++;
			}
		}
	}
}

int selectRoom(int room[]) {
	int sum = room[0] + room[1] + room[2] + room[3];
	int rnd = rand() % sum;

	if (rnd == 0) {
		if (room[0] == 1)
			return 0;
		if (room[1] == 1)
			return 1;
		if (room[2] == 1)
			return 2;
		if (room[3] == 1)
			return 3;
	}

	if (rnd == 1) {
		if (room[0] == 1) {
			if (room[1] == 1)
				return 1;
			if (room[2] == 1)
				return 2;
			if (room[3] == 1)
				return 3;
		}
		if (room[1] == 1) {
			if (room[2] == 1)
				return 2;
			if (room[3] == 1)
				return 3;
		}
		if (room[2] == 1) {
			if (room[3] == 1)
				return 3;
		}
	}

	if (rnd == 2) {
		if (room[0] == 1) {
			if (room[1] == 1) {
				if (room[2] == 1)
					return 2;
				if (room[3] == 1)
					return 3;
			}
			if (room[2] == 1) {
				return 3;
			}
		}
		if (room[1] == 1) {
				return 3;
		}
	}

	if (rnd == 3)
		return 3;

}

void print(cell m[][MAZESIZE])
{
	for (int i = 0; i < MAZESIZE; i++)
	{
		for (int j = 0; j < MAZESIZE; j++)
		{
			if (m[i][j].up)
				cout << " -";
			else cout << "  ";
		}
		cout << endl;
		cout << "|";
		for (int j = 0; j < MAZESIZE; j++)
		{
			if (m[i][j].right)
				cout << m[i][j].val << "|";
			else
				cout << m[i][j].val << " ";
		}
		cout << endl;
	}
	for (int i = 0; i < MAZESIZE; i++)
	{
		if (m[MAZESIZE - 1][i].down)
			cout << " -";
	}
	cout << endl;
}

void createPath(cell m[][MAZESIZE])
{
	for (int i = 0; i < MAZESIZE; i++) {
		for (int j = 0; j < MAZESIZE; j++) {
			m[i][j].visited = false;
		}
	}
	cout << "Enter start point: ";
	cin >> current.A >> current.B;
	cout << "Enter exit point: ";
	cin >> exitA >> exitB;
	m[exitA][exitB].val = 'E';
	findPath(m);
}
void findPath(cell m[][MAZESIZE]) {
	if (current.A == exitA && current.B == exitB)
		return;
	m[current.A][current.B].val = 'o';
	m[current.A][current.B].visited = true;
	system("cls");
	print(m);
	system("pause");
	if (m[current.A][current.B].up == false && current.A > 0 && m[current.A-1][current.B].visited == false){
		p.push(current);
		current.A--;
		return findPath(m);
	}
	if (m[current.A][current.B].down == false && current.A < (MAZESIZE - 1) && m[current.A+1][current.B].visited == false){
		p.push(current);
		current.A++;
		return findPath(m);
	}
	if (m[current.A][current.B].left == false && current.B > 0 && m[current.A][current.B-1].visited == false){
		p.push(current);
		current.B--;
		return findPath(m);
	}
	if (m[current.A][current.B].right == false && current.B < (MAZESIZE - 1) && m[current.A][current.B+1].visited == false){
		p.push(current);
		current.B++;
		return findPath(m);
	}
	m[current.A][current.B].val = ' ';
	m[current.A][current.B].visited = true;
	current = p.pop();
	return findPath(m);
}

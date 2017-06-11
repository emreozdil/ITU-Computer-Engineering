//  Created by Emre …zdil
//  Copyright © 2015 Emre …zdil. All rights reserved.

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "stack.h"
#define RIGHT   1
#define LEFT    2
#define UP      3
#define DOWN    4
using namespace std; // cin ve cout iþlemlerinin kýsa yazýmý için
char lab[][22] =
{
	{ "#o###################" },
	{ "#     #      #    # #" },
	{ "# ### # ###### ## # #" },
	{ "# # #        # #  # #" },
	{ "# # ### ######## ## #" },
	{ "#     # # ##   #    #" },
	{ "### # # # ## # # ####" },
	{ "#   # # #    #      #" },
	{ "# # # # # ######### #" },
	{ "# # # # # #       # #" },
	{ "# # #   # # #####   #" },
	{ "# # ##### # #   #####" },
	{ "#         #   #     #" },
	{ "###################E#" }
};
int yaz_sayac = 0; // Çözüm adýmlarýnýn yazdýrýlmasý için sayac.
void printlab(char l[14][22]){
	cout << "\n\nLABYRINTH AT STEP : " << ++yaz_sayac << "\n\n";
	for (int i = 0; i<14; i++){
		for (int j = 0; j<21; j++)
			cout << l[i][j];
		cout << endl;
	}
	cout << "\n\n";
}
int main(){
	Stack s;
	Stack Current;
	Current.create();
	s.create();
	position temp;
	position entrance = { 1, 0, 0, 0, 0, 0, 0 };
	position exit = { 19, 13, 0, 0, 0, 0, 0 };
	position k = entrance;
	k.camefrom = UP;
	printlab(lab);
	bool goback = false;
	while (k.x != exit.x || k.y != exit.y){
		lab[k.y][k.x] = 'o';
		printlab(lab);
		//first find how many directions we can go
		if (!goback){//if not calculated before
			k.right = 0; k.left = 0; k.down = 0; k.up = 0;
			if (lab[k.y][k.x + 1] != '#' ) k.right = 1;//right
			if (lab[k.y][k.x - 1] != '#' ) k.left = 1;//left
			if (lab[k.y + 1][k.x] != '#') k.down = 1;//down
			if (lab[k.y - 1][k.x] != '#') k.up = 1;//up
		}
		if (!goback){//if not calculated before
			k.circle=0;
			if (lab[k.y][k.x + 1] == 'o') k.circle++;
			if (lab[k.y][k.x - 1] == 'o') k.circle++;
			if (lab[k.y + 1][k.x] == 'o') k.circle++;
			if (lab[k.y - 1][k.x] == 'o') k.circle++;
		}
		else goback = false;
		//here, one of the possible moves is selected
		bool moved = true;
		position past = k;
		if (k.circle > 1)
			moved=false;
		else if (k.down && k.camefrom != DOWN)  {
			k.y++;
			k.camefrom = UP;
			past.down = 0;
		}
		else if (k.up && k.camefrom != UP) {
			k.y--;
			k.camefrom = DOWN;
			past.up = 0;
		}
		else if (k.left && k.camefrom != LEFT) {
			k.x--;
			k.camefrom = RIGHT;
			past.left = 0;
		}
		else if (k.right && k.camefrom != RIGHT){
			k.x++;
			k.camefrom = LEFT;
			past.right = 0;
		}
		else
			moved = false;//one direction (the minimum) is open, but this is the direction we came from

		Current.push(past);
		if (k.x != exit.x || k.y != exit.y) {
			if ((k.down + k.up + k.right + k.left)>2){
				//there is more than one choice, push onto stack and //continue in that chosen direction. Let the choices  //you have not selected remain marked on the stack. 					
				s.push(past);
			}
			if (!moved){//has to go back
				if (!s.isempty()){
					while (Current.ust().x != s.ust().x || Current.ust().y != s.ust().y) {
						temp = Current.pop();
						lab[temp.y][temp.x] = ' ';
						printlab(lab);
						getchar();
					}
					k = s.pop();
					k.circle = 0;
					goback = true;
				}
			}
		}
		getchar();
	}//end of while
	lab[k.y][k.x] = 'o';
	printlab(lab);
	for (int i = 0; i < Current.top; i++)
	{
		cout << i+1<<". X: "<<Current.element[i].x << " Y: " << Current.element[i].y << endl;
	}
	cout << "\n Solution path found \n\n";
	system("pause");
	return EXIT_SUCCESS;
}

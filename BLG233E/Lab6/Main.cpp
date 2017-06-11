//  Created by Emre Özdil
//  Copyright © 2015 Emre Özdil. All rights reserved.

#include <iostream>
#include "stack.h"
using namespace std;

Process Calculate;
int main()
{
	bool finish = true;
	char infix[20];
	char decision;
	while (finish)
	{
		Calculate.create();
		cout << "Enter an infix expression: ";
		cin >> infix;
		Calculate.i_to_p(infix);
		cout << Calculate.postfix << endl;
		cout << "Value: " << Calculate.value(Calculate.postfix) << endl;
		cout << "Do you want to exit this app? (Y/N): ";
		cin >> decision;
		if (decision == 'y' || decision == 'Y')
			finish = false;
		Calculate.empty();
	}
	return 0;
}

//  Created by Emre Özdil
//  Copyright © 2015 Emre Özdil. All rights reserved.

#include <stdio.h>
#include <stdlib.h>
#define pi 3.141592
int power(int, int);
long long int factorial(int);
double absolute(double);
double sine(int);
double cosine(int);
double tangent(int);
double expo(int);

int main()
{
	int mod;
	char input[15],modulo='%';
	input[0] = '0';
	double memory = 0, temp, temp_2;
	printf("The list of operations in this simple calculator:\n");
	printf("sine (S), cosine (N), tangent (T), exponent (E)\n");
	printf("power (W), absolute (A), factorial (F)\n");
	printf("add (+), subtract (-), divide(/), multiply(*), modulus (%c)\n", modulo);
	printf("pi (P)\nQuit (Q)\nMemory (M)\nClear (C)\nMemory Clear (MC) \nMemory Return (MR)\n");
	printf("----------------------------------------------------------\n");
	while (input[0] != 'Q' && input[0] != 'q')
	{
		printf("Enter user input: ");
		scanf("%s", input);
		if ((input[0] >= '0' && input[0] <= '9')|| (input[0]=='-'&& input[1] >= '0' && input[1] <= '9'))//is a number?
		{
			temp = strtod(input, NULL);
		}
		else if (input[0] == 'S' || input[0] == 's')// go to sinus function
		{
			printf("%g\n", sine((int)temp));
			temp=sine((int)temp);
		}
		else if (input[0] == 'N' || input[0] == 'n')// go to cosinus function
		{
			printf("%g\n", cosine((int)temp));
			temp=cosine((int)temp);
		}
		else if (input[0] == 'T' || input[0] == 't')// go to tangant function
		{
			printf("%g\n", tangent((int)temp));
			temp=tangent((int)temp);
		}
		else if (input[0] == 'C' || input[0] == 'c')//clean temporary
		{
			temp = 0;
			printf("%g\n", temp);
		}
		else if ((input[0] == 'M' || input[0] == 'm') && (input[1] == 'R' || input[1] == 'r'))//write memory
		{
			printf("%g\n", memory);
			temp=memory;
		}
		else if ((input[0] == 'M' || input[0] == 'm') && (input[1] == 'C' || input[1] == 'c'))//clean memory
		{
			memory = 0;
		}
		else if (input[0] == 'M' || input[0] == 'm')//store in the memory
		{
			memory = temp;
		}
		else if (input[0] == 'P' || input[0] == 'p')//pi
		{
			temp=pi;
			printf("%lf\n",pi);
		}
		else if (input[0] == 'E' || input[0] == 'e')//go to exponential function
		{
			temp+=0.5;
			printf("%g\n", expo((int)temp));
			temp=expo((int)temp);
		}
		else if (input[0] == 'F' || input[0] == 'f')//go to factorial function
		{
			printf("Factorial(%g) = %I64d\n",temp, factorial((int)temp));
		}
		else if (input[0] == 'A' || input[0] == 'a')//go to absolute function
		{
			printf("%g\n", absolute(temp));
		}
		else if (input[0] == '*')//multiplication
		{
			while (1)
			{
				printf("Enter user input: ");//second input
				scanf("%s", input);
				if ((input[0] >= '0' && input[0] <= '9')|| (input[0]=='-'&& input[1] >= '0' && input[1] <= '9'))
				{
					temp_2 = strtod(input, NULL);
					break;
				}
				else
				{
					printf("Invalid input for the operator (*).\n");//error message
					continue;
				}
			}
			printf("%g * %g= %g\n", temp, temp_2, temp*temp_2);
			temp *= temp_2;
		}
		else if (input[0] == '+')//addition
		{
			while (1)
			{
				printf("Enter user input: ");//second input
				scanf("%s", input);
				if ((input[0] >= '0' && input[0] <= '9')|| (input[0]=='-'&& input[1] >= '0' && input[1] <= '9'))
				{
					temp_2 = strtod(input, NULL);
					break;
				}
				else
				{
					printf("Invalid input for the operator (+).\n");//error message
					continue;
				}
			}
			printf("%g + %g= %g\n", temp, temp_2, temp + temp_2);
			temp += temp_2;
		}
		else if (input[0] == '-')//substract
		{
			while (1)
			{
				printf("Enter user input: ");//second input
				scanf("%s", input);
				if ((input[0] >= '0' && input[0] <= '9')|| (input[0]=='-'&& input[1] >= '0' && input[1] <= '9'))
				{
					temp_2 = strtod(input, NULL);
					break;
				}
				else
				{
					printf("Invalid input for the operator (-).\n");//error message
					continue;
				}
			}
			printf("%g - %g= %g\n", temp, temp_2, temp - temp_2);
			temp -= temp_2;
		}
		else if (input[0] == '/')//division
		{
			while (1)
			{
				printf("Enter user input: ");//second input
				scanf("%s", input);
				if ((input[0] >= '0' && input[0] <= '9')|| (input[0]=='-'&& input[1] >= '0' && input[1] <= '9'))
				{
					temp_2 = strtod(input, NULL);
					break;
				}
				else
				{
					printf("Invalid input for the operator (/).\n");//error message
					continue;
				}
			}
			printf("%g / %g= %g\n", temp, temp_2, temp / temp_2);
			temp /= temp_2;
		}
		else if (input[0] == '%')//modulus
		{
			while (1)
			{
				printf("Enter user input: ");//second input
				scanf("%s", input);
				if ((input[0] >= '0' && input[0] <= '9')|| (input[0]=='-'&& input[1] >= '0' && input[1] <= '9'))
				{
					temp_2 = strtod(input, NULL);
					break;
				}
				else
				{
					printf("Invalid input for the operator (%c).\n",modulo);//error message
					continue;
				}
			}						
			mod = (int)temp % (int)temp_2;
			printf("%g %c %g= %d\n", temp, modulo, temp_2, mod);
		}
		else if (input[0] == 'W' || input[0] == 'w')// power
		{
			while (1)
			{
				printf("Enter user input: ");//second input
				scanf("%s", input);
				if ((input[0] >= '0' && input[0] <= '9')|| (input[0]=='-'&& input[1] >= '0' && input[1] <= '9'))
				{
					temp_2 = strtod(input, NULL);
					break;
				}
				else
				{
					printf("Invalid input for the operator (^).\n");//error message
					continue;
				}
			}
			printf("%g ^ %g= %d\n", temp, temp_2, power((int)temp, (int)temp_2));
			temp=(double)power((int)temp, (int)temp_2);
		}
		else if (input[0] == 'Q' || input[0] == 'q')//exit the program
		{
			continue;
		}
		else//error message
		{
			printf("Invalid character. Choose from the operators below:\n");
			printf("----------------------------------------------------------");
			printf("sine (S), cosine (N), tangent (T), exponent (E)\n");
			printf("power (W), absolute (A), factorial (F)\n");
			printf("add (+), subtract (-), divide(/), multiply(*), modulus (%c)\n", modulo);
			printf("pi (P)\nQuit (Q)\nMemory (M)\nClear (C)\nMemory Clear (MC) \nMemory Return (MR)\n");
			printf("----------------------------------------------------------\n"); 
		}
	}

	return 0;
}
int power(int a, int b)
{
	int pow = 1, i;
	for (i = 0; i <b; i++)
	{
		pow *= a;
	}

	return pow;
}

long long int factorial(int a)
{
	int f = a;
	while (--a)
	{
		f *= a;
	}
	return f;
}

double absolute(double a)
{
	if (a>0.0)
		return a;
	else
		return -1.0*a;
}

double sine(int degree)
{
	double solution = 0.0, radyan = (double)degree / 180 * pi, fact = 1;
	double pow = radyan;
	int i, k = 1;
	for (i = 1; i < 40; i += 2)
	{
		if (i>1)
		{
			k = k*-1;
			fact = fact*i*(i - 1);
			pow *= radyan*radyan;
		}
		solution += k*pow / fact;
	}
	return solution;
}

double cosine(int degree)
{

	double k = 1.0, solution = 1.0, radyan = (double)degree / 180 * pi, pow = 1.0, fact = 1;
	int i;
	for (i = 2; i < 40; i += 2)
	{
		k = k*-1;
		fact = fact*i*(i - 1);
		pow *= radyan*radyan;
		solution += k*pow / fact;
	}
	return solution;
}

double tangent(int a)
{
	double x = sine(a) / cosine(a);
	return x;
}

double expo(int a)
{
	double x = 1;
	while (a--)
	{
		x *= 10;
	}
	return x;
}

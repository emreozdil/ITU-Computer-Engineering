//  Created by Emre Özdil
//  Copyright © 2015 Emre Özdil. All rights reserved.

#include<stdio.h>
void factorial(int, int);
int p_digit(int);
int p,i, j, digit, number, remain, array[300];
int main()
{
    int n;
    printf("Enter N: ");
    scanf("%d",&n);
    p=p_digit(n); // find the number of digit
    factorial(n-2,p);
    factorial(n-1,p);
    factorial(n,p);
	return 0;
}
int p_digit(int n)// find digit
{
	array[0]=1; //begin 1!
    digit=1;  
    remain = 0; //remainder
	for(i=1;i<=n;i++)
	{
		for(j=0;j<digit;j++)
		{
			number = array[j]*i+remain; //number equal digit product
			array[j]=number%10; //digit value (0-9)
			remain = number/10; //remain
		}
		while(remain!=0) //increase the number of digit
		{ 
			array[digit]=remain%10;
			remain = remain/10;
			digit++;  
		}
	}
	for(j=0;j<digit;j++)
		array[j]=0;
	return digit;
}
void factorial(int n,int p)
{
	array[0]=1;  //begin 1!
    digit=1;  
    remain = 0; //remainder
	for(i=1;i<=n;i++)
	{
		for(j=0;j<digit;j++)
		{
			number = array[j]*i+remain; //number equal digit product
			array[j]=number%10; //digit value(0-9)
			remain = number/10; //remain
		}
		while(remain!=0) //increase the number of digit.
		{ 
			array[digit]=remain%10;
			remain = remain/10;
			digit++; 
		}
	}
	printf("%3d! = ", n);
	for(i=p-1;i>=0;i--) //print answer
	{
		if (array[i]==0)//print space
		{
			printf(" ");
			if(i%3==0 && i!=0)	
				printf(" "); // space for a comma
		}
		else
		{	
			while (i!=-1)
			{
				printf("%d",array[i]);
				if(i%3==0 && i!=0)	
					printf(",");
				i--;
			}
			break;		
		}			
	}
	printf("\n");
}

/*
* @Author
* Student Name: Emre Özdil
* Student ID : 150120138
* Date: 03/11/2015
*/

struct operate
{
	char trans[20];
	operate *next;
};

struct customer
{
	char name[20];
	char surname[20];
	char type;
	int transaction;
	operate *op;
	customer *next;
};
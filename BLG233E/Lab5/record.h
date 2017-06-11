struct number
{
	number *next;
	char type[10];
	char numb[20];
};

struct person
{
	char name[20];
	char surname[20];
	number *hnumber;
	person *next, *previous;
};

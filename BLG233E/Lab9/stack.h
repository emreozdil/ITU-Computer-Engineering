struct cell
{
	bool left, right, up, down;
	char val;
	bool visited;
};

struct psh
{
	int A;
	int B;
};

struct node
{
	psh element;
	node *next;
};

struct Stack
{
	node *head;
	void create();
	void close();
	void push(psh);
	psh pop();
	bool isEmpty();
};
struct Process
{
	int top;
	int ch;
	char postfix[100];
	char operate[100];
	int result[10];

	void create();
	void i_to_p(char *);
	void do_posfix(char);
	void push(char);
	char pop();
	int value(char *);
	void empty();
	int precedence(char);
};
#include <iostream>
#include <cstring>
#include "stack.h"

void Process::create()
{
	top = 0;
	ch = 0;
}

void Process::i_to_p(char *infix)
{
	for (int i = 0; i < strlen(infix); i++)
	{
		if (isdigit(infix[i]))
		{
			do_posfix(infix[i]);
		}
		else
		{
			if (ch==0||infix[i]=='(')
			{
				push(infix[i]);
				if (infix[i] == '(') continue;
				continue;
			}
			if (infix[i]==')')
			{
				while (operate[ch - 1] != '(')
				{
					do_posfix(pop());
				}
				ch--;
				continue;
			}
			if (precedence(infix[i])>precedence(operate[ch-1]))
			{
				push(infix[i]);
			}
			else
			{
				do_posfix(pop());
				push(infix[i]);
			}
		}
	}
	while (ch != 0)
	{
		do_posfix(pop());
	}
	int len = strlen(infix);
	for (int i = 0; i < len; i++)
	{
		infix[i] = NULL;
	}
}

void Process::do_posfix(char add)
{
	postfix[top++] = add;
}

void Process::push(char add)
{
	operate[ch++] = add;
}

char Process::pop()
{
	return operate[--ch];
}

int Process::value(char *post)
{
	int len = strlen(post);
	for (int i = 0; i < len; i++)
	{
		if (isdigit(post[i]))
		{
			result[ch++]=post[i]-'0';
		}
		else
		{
			if (post[i] == '*')
				result[ch - 2] = result[ch - 2] * result[ch-1];
			else if (post[i] == '/')
				result[ch - 2] = result[ch - 2] / result[ch - 1];
			else if (post[i] == '+')
				result[ch - 2] = result[ch - 2] + result[ch - 1];
			else if (post[i] == '-')
				result[ch - 2] = result[ch - 2] - result[ch - 1];
			ch--;
		}
	}
	return result[0];
}

void Process::empty()
{
	int len = strlen(postfix);
	for (int i = 0; i < len; i++)
	{
		postfix[i] = NULL;
	}
	ch = 0;
}

int Process::precedence(char op)
{
	if (op == '*' || op == '/')
		return 1;
	if (op == '+' || op == '-')
		return 0;
	return -1;
}

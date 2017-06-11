#ifndef STACK_H
#define STACK_H
#define STACKSIZE 200

typedef struct d {
	int x;
	int y;
	int right;
	int left;
	int down;
	int up;
	int circle;
	int camefrom;
} StackDataType, position;

struct Stack{
	StackDataType element[STACKSIZE];
	int top;
	StackDataType ust();
	void create();
	bool push(StackDataType);
	StackDataType pop();
	bool isempty();
};
#endif

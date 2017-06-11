#include "stack.h"

void Stack::create(){
	top = 0;
}

bool Stack::push(StackDataType newdata){
	if (top<STACKSIZE){
		element[top++] = newdata;
		return true;
	}
	return false;
}

StackDataType Stack::pop(){

	return element[--top];
}

bool Stack::isempty(){
	return (top == 0);
}

StackDataType Stack::ust() {
	return element[top - 1];
}
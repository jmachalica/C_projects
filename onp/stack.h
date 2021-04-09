#ifndef _STACK_H_AC263 
#define _STACK_H_AC263		

typedef struct tagStackItem
{
	char Key;
	tagStackItem* Next;
} StackItem;


void makeEmptyStack();
void push( char c );
char pop();
char top();
void del();
int isEmpty();

#endif

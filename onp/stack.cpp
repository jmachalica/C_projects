#include "stack.h"
#include <stdio.h>
#include <stdlib.h>



StackItem* Head = NULL; //stack is empty
				//first empty element on the stack



void push( char c )
{
	StackItem* point = ( StackItem* )malloc( sizeof (StackItem ));


	if ( point ) { 
		point->Key = c; 
		point->Next = Head;
		Head = point;
	}
	else
	{
	perror( "Stack overflow! push()\n\n'" ); 
	}
}
char pop()
{ char c = top();
	if (c)
		del();
	else
		perror( "Stack underflow! pop() \n\n" );

	return c;
}
char top()
{
	if ( !isEmpty() )
		return Head->Key;

	return 0;
}
void del()
{
	if ( !isEmpty() )
	{
		StackItem* x = Head; 
		Head = Head->Next;
		free( x );
	}
	else
		perror( "Stack underflow! del()\n\n" );
	
}
int isEmpty()
{
	return !Head;
}

void makeEmptyStack()
{
	while ( !isEmpty() )
		del();

	//memset(StackItem, 0,  sizeof(struct StackItem)); //wypelnia bajty tablicy zerami     |	 (gdzie - nazwa tablicy to adres jej pierwszej komorki, czym, ilezamienic) 
	//Head = NULL;
}

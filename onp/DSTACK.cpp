#include "DSTACK.h"
#include <stdio.h>
#include <memory.h>
#include <float.h>
#include <stdlib.h>



DStackItem* DHead = NULL;
void dpush( double c )
{
	DStackItem* x = ( DStackItem* )malloc( sizeof( DStackItem ) );

	if ( x )
	{
		x->Key = c;
		x->Next = DHead;
		DHead = x;
	}
	else perror( "Stack Overflow! dpush()\n\n" );




	
	
}
double dpop()
{
	double x = DBL_MIN;
	if (!disEmpty())
	{
		x = dtop();
		ddel();
		return x;
	}
	perror( "Stack underflow! dpop() \n\n" ) ;
	return 0;
}
double dtop()	
{
	if ( !disEmpty() )
		return DHead->Key;
	perror("Stack underflow! dtop() \n\n");
	return 0;
}
void ddel()
{
	if ( !disEmpty() )
		{	
			DStackItem* x = DHead;
			DHead = DHead->Next;
			free(x);
		}
	else
		perror( "Error:STACK underflow! ddel()\n" );
}
int disEmpty()
{
	return !DHead;
}

void makeDEmptyStack()
{

	while ( !disEmpty() )
		ddel();
	//memset(dStackItem, 0, sizeof(struct dStackItem)); //wypelnia bajty tablicy zerami     |	 (gdzie - nazwa tablicy to adres jej pierwszej komorki, czym, ilezamienic) 
	//DHead = NULL;
}


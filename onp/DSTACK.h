#ifndef _DSTACK_H_FAA2345 
#define _DSTACK_H_FAA2345		

typedef struct DtagStackItem
{
	double Key;
	DtagStackItem* Next;
} DStackItem;



void makeDEmptyStack();
void dpush( double c );
double dpop();
double dtop();
void ddel();
int disEmpty();
#endif

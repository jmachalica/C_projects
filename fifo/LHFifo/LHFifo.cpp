#include <stdio.h>
#include "FQueue.h"
#include <stdlib.h>

void printque( QFIFO* p );
void freeinfo( QInfo* info );
void addinfo( int key, QFIFO* q );
#define PRINT

int main()
{
	QFIFO* p = NULL;
	p = QFCreate();
	if( !p )return 1; 

	addinfo( 1, p );
	addinfo( 2, p );
	addinfo( 3, p );
	addinfo( 4, p );

#ifdef PRINT
	printque( p );
#endif

	freeinfo( QFDequeue( p ) );
	freeinfo( QFDequeue( p ) );
	freeinfo( QFDequeue( p ) );

#ifdef PRINT
	printque( p );
#endif

	addinfo( 5, p );
	addinfo( 6, p );

#ifdef PRINT
	printque( p );
#endif


	QFClear( p );
	
#ifdef PRINT
	printque( p );
#endif

	addinfo( 7, p );
	addinfo( 8, p );
	addinfo( 9, p );
#ifdef PRINT
	printque( p );
#endif


	freeinfo( QFDequeue( p ) );

#ifdef PRINT
	printque( p );
#endif

	QFRemove( &p );
	printf( "Kolejka zostala usunieta" );

	return 0;
}




void printque( QFIFO* q )
{
	if( !QFEmpty( q ) ) 
	{
		printf( "Queue's elements: " );
		QFItem* p = q->pHead->pNext;
		while( p )
		{
			printf( " %d ", p->pinfo->n_Key );
			p = p->pNext;
		}
		printf("\n");
	}
	else printf( "Queue is empty " );

}


void freeinfo( QInfo* info )
{
	if( info )
	{
		printf( "Deleted info: %d\n", info->n_Key );
		free( info );
	}
	
}

void addinfo( int key,QFIFO* q )
{
	QInfo* info = ( QInfo* )calloc( 1, sizeof( QInfo ) );

	if( info )
	{
		info->n_Key = key;
		if( !QFEnqueue( q, info ) )
		{
			printf( "Error: QFEnqueue\n" );
			free( info );
		}
	}
	else printf( "Allocation Error: Qinfo" );
	
	
}



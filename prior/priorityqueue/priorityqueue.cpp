#include <stdio.h>
#include <stdlib.h>
#include "PQueue.h"
#include "global.h"

#define QUESIZE 20
#define PRINT

void printinfo( const void* x );
int compare( const void* first, const void* sec );
void freeitem( const void* x );
void addelement( PQueue* q, int value,int prior );
void delelement(PQueue* q);

int main()
{
	
	PQueue* que = PQInit( QUESIZE );
	
	if ( !que )return 1;

	addelement( que, 1, 1 );
	addelement( que, 2, 3 );
	addelement( que, 12, 9 );
	addelement( que, 33, 7 );
	addelement( que, 11, 7 );
	addelement( que, 5, 4 );
	PQEnqueue( que, NULL, 5); 

#ifdef PRINT
	QPrint( que, &printinfo, 0 );
	printf("\n");
#endif
	
	printf( "Max priorytet to: %d\n", PGMaxPrior( que ) ); 


	delelement( que );
	printf( "\n" );
	
#ifdef PRINT
	QPrint( que, &printinfo, 0 );
	printf("\n");
#endif
	
	addelement( que, 10, 5 );
	addelement( que, 7, 9 );

#ifdef PRINT
	QPrint( que, &printinfo, 0 );
	printf( "\n" );
#endif

	
	PQINFO* find = ( PQINFO* )calloc( 1, sizeof( PQINFO ) );
	if( !find )
	{
		printf( "Allocation Error: PQINFO" );
		return 1;
	}

	find->pTab = ( int* )calloc( 2, sizeof( int ) );
	if( !find->pTab )
	{
		printf( "Allocation Error: pTab" );
		free( find );
		return 2;
		
	}
	find->pTab[ 0 ] = 10;
	find->pTab[ 1 ] = 10;
	find->nKey = 10;

	PQSetPrior( que, find, find->nKey +1, &compare );

#ifdef PRINT
	QPrint( que, &printinfo, 0 );
	printf( "\n" );
#endif

	
	int oldprior = PQgetPrior( que, 3 );
	if( oldprior != PRIOR_ERROR && oldprior != POS_ERROR ) PQsetPrior( que, oldprior-1 , 3 );

#ifdef PRINT
	QPrint( que, &printinfo, 0 );
	printf("\n");
#endif

	PQClear( que, &freeitem );
	
#ifdef PRINT
	QPrint( que, &printinfo, 0 );
	printf("\n");
#endif

	PQRelease( &que, &freeitem );
	
	return 0;
}


void printinfo( const void* x )
{
	if( !x )printf("Info is empty \n"); 
	else printf( "Nkey=%d, tab[0]=%d, tab[1]=%d\n", ( (PQINFO*)x )->nKey, ( ( PQINFO* )x )->pTab[ 0 ], ( ( PQINFO* )x )->pTab[ 1 ] );
}

int compare( const void* first, const void* sec )
{
	if( !first && !sec )return 0;
	if( !first && sec )return -1;
	if( first  && !sec )return 1;

	/*if( first == NULL && sec == NULL )return 0;
	if( first == NULL && sec != NULL )return -1;
	if( first != NULL && sec == NULL )return 1;	*/

	if( ( ( PQINFO* )first )->nKey < ( ( PQINFO* )sec )->nKey )return -1;
	if( ( ( PQINFO* )first )->nKey > ( ( PQINFO* )sec )->nKey )return 1;
	return 0;

}

void freeitem( const void* x )
{
	if( x ) 
	{
		free( ( ( PQINFO* )x )->pTab );
		free( ( PQINFO*) x );
	}
}
void addelement( PQueue* q, int value,int prior )
{
	PQINFO* a = ( PQINFO* )calloc( 1, sizeof( PQINFO ) );
	if( !a ) 
	{
		printf( "Allocation Error: PQINFO\n" );
		return;
	}

	a->pTab = ( int* )calloc( 2, sizeof( int ) );

	if( !a->pTab )
	{
		printf( "Allocation Error: pTab\n" );
		free( a );
		return;
	}
	a->pTab[ 0 ] = value;
	a->pTab[ 1 ] = value;
	a->nKey = value;
	if( !PQEnqueue( q, a, prior ) ) freeitem( a );
}

void delelement( PQueue* q )
{
	if( !q )
	{
		printf( "Error delelement\n" );
		return;
	}
	PQINFO* del = PQDequeue( q );
	
	
	printf( "Deleted element:");
	printinfo( del );
	freeitem( del ); 
	

}
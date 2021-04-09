#include <stdio.h>
#include "FQueue.h"
#include <stdlib.h>
#include "global.h"

void addelement( QFIFO* q, int value );
void delelement( QFIFO* q ); 
void print( QFIFO* q );

#define SIZE 4
#define PRINT

int main()
{
	QFIFO* p = NULL;
	p = QFCreate( SIZE );
	if ( !p )return 1;
	
	addelement( p,1 );
	addelement( p,2 );
	addelement( p,3 );
	addelement( p,4 );
	
#ifdef PRINT
	print( p );
#endif

	delelement( p );
	delelement( p );
	delelement( p );
#ifdef PRINT
	print( p );
#endif

	addelement( p,5 );
	addelement( p,6 );

	
	QFClear( p, &freeItem );

#ifdef PRINT
	print( p );
#endif
	
	addelement( p,7 );
	addelement( p,8 );
	addelement( p,9 );
	
#ifdef PRINT
	print( p );
#endif
	
	delelement( p );
	
#ifdef PRINT
	print( p );
#endif
	
	QFRemove( &p, &freeItem );
	
	return 0;
}


void addelement( QFIFO* q, int value)
{
	QFITEM* i = ( QFITEM* )calloc( 1,sizeof( QFITEM ) );

	if( !i )
	{
		printf( "Allocation Error: QFITEM\n" );
		return;
	}
	i->pTab = ( int* )calloc( 2,sizeof( int ) );

	if( !i->pTab )
	{
		printf( "Allocation Error: pTab\n" );
		free( i );
		return;
	}
	i->n_Key = value;
	i->pTab[ 0 ] = value;
	i->pTab[ 1 ] = value + 1;

	if( !QFEnqueue( q, i ) ) 
	{
		free( i->pTab );
		free( i );
	}
		
}

void delelement( QFIFO* q )
{
	QFITEM* x = QFDequeue( q );
	if( x )
	{
		printf("Deleted element:tab[0]= %d, tab[1]=%d, nkey=%d \n", x->pTab[0], x->pTab[1], x->n_Key);
		freeItem(x);
	}
}


void print( QFIFO* q )
{
 if( !QFEmpty( q ) )
 {
		int j = q->nHead;
		for( int i = 1; i <= q->nNoElem; i++ )
		{
			if( j >= q->nMaxElem ) j = 0;
			printf( "%d- element: tab[0]= %d, tab[1]=%d, nkey=%d \n", i,  q->pFQItems[ j ]->pTab[ 0 ], q->pFQItems[ j ]->pTab[ 1 ], q->pFQItems[ j ]->n_Key );
			j++;
		}
		printf("\n");
	}
	else printf( "Queue is empty \n" );

}


void freeItem( const void*  t )
{	 
	free( ( ( QFITEM* )t )->pTab );
	 free( ( QFITEM* )t );
}


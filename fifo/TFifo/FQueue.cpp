#include <stdio.h>
#include <stdlib.h>
#include "FQueue.h"

void QFDEL( QFIFO* q );


QFIFO* QFCreate( int nSize )
{
	if( nSize<1 )
	{
		printf( "Error: invalid queue's size, queue can't be created \n ");
		return NULL;
	}

	QFIFO* fifo = ( QFIFO* )calloc( 1, sizeof( QFIFO ) );
	
	if( !fifo )
	{
		printf( "Allocation Error: QFIFO" );
		return NULL;
	}

	fifo->pFQItems= ( QFITEM** )calloc( nSize, sizeof( QFITEM* ) );

	if( !fifo->pFQItems )
	{
		printf( "Allocation Error:  pFQItems\n" );
		free( fifo );
		return NULL;
	}
	fifo->nMaxElem = nSize;
	return fifo;
}

int QFEmpty( QFIFO* q )
{
	  return !q || !q->nNoElem;
	//return !q ? !q : !q->nNoElem;

}

int QFEnqueue( QFIFO* q, QFITEM* pItem )
{
	if( !q || !pItem )
	{
		printf( "Error: QFEnqueue, element can't be added \n" );
		return 0;
	}
	
	if( q->nNoElem >= q->nMaxElem )
	{
		printf( "Error: QFEnqueue is full, element can't be added\n" );
		return 0;
	}

	q->pFQItems[ q->nTail ] = pItem;
	q->nTail = ( q->nTail + 1 ) % q->nMaxElem;
	q->nNoElem++;
	return 1;
	
}

QFITEM* QFDequeue( QFIFO* q )
{
	if( !q )
	{
		printf("Error QFDequeue, element can't be deleted \n");
		return NULL;
	}
	if( !QFEmpty( q ) ) 
	{
		QFITEM* item = q->pFQItems[ q->nHead ];
		QFDEL( q );   
		return item;
	}
	printf( "Queue is empty, element can't be deleted\n" );
	return NULL;
}

void QFClear( QFIFO* q, void(__cdecl* freeItem )( const void* ) )
{
	if( !q )
	{
		printf( "Error QFClear, queue can't be cleared\n" );
		return;
	}
	while( !QFEmpty( q ) )  freeItem( QFDequeue( q ) );		
}

void QFRemove(QFIFO** q, void(__cdecl* freeItem)(const void*))
{
	if( !q ||  !*q )
	{
		printf( "Error QFRemove, queue can't be removed\n" );
		return;
	}
			QFClear( *q, freeItem ); 
			free( ( *q )->pFQItems );
				free( *q );
				*q = NULL;
}

void QFDEL( QFIFO* q )
{
	if( !q || QFEmpty( q ) )
	{
		printf( "Error QFDel, element can't be deleted \n" );
		return;
	}

	q->pFQItems[ q->nHead ] = NULL;
	q->nHead = ( q->nHead + 1 ) % q->nMaxElem;
	q->nNoElem--;
}

#include <stdio.h>
#include <stdlib.h>
#include "FQueue.h"


void  QFDel( QFIFO* q );

QFIFO* QFCreate()
{
	QFIFO* fifo = ( QFIFO* )calloc( 1, sizeof( QFIFO ) );

	if( !fifo )
	{
		printf( "Allocation Error: QFIFO\n" );
		return NULL;

	}
	
	QFItem* h = ( QFItem* )calloc( 1, sizeof( QFItem ) );
	
	if( !h )
	{
		printf( "Allocation Error: queue's head\n" );
		free( fifo );
		return NULL;

	}
	
	fifo->pHead = fifo->pTail = h;

	return fifo;
}

int QFEmpty( QFIFO* q )
{
	  return !q || !q->pHead;
	  //return !q ? !q : !q->pHead;

}

int QFEnqueue( QFIFO* q, QInfo* info )
{
	if( !q || !info )
	{
		printf( "Error: QFEnqueue, element can't be added \n" );
		return 0;
	}
	
	QFItem* pItem = ( QFItem* )calloc( 1, sizeof( QFItem ) );
	
	if( !pItem )
	{
		printf( "Allocation Error: QFItem \n " );
		return 0;
	}

	q->pTail =q->pTail->pNext = pItem; 
	pItem->pinfo = info;

	return 1;
}

QInfo* QFDequeue( QFIFO* q )
{
	if( !q ) 
	{
		printf( "Error QFDequeue, element can't be deleted \n" );
		return NULL;
	}
	if( QFEmpty( q ) )
	{
		printf("Queue is empty, element can't be deleted\n");
		return NULL;
	}
	QInfo* info = q->pHead->pNext->pinfo;
	QFDel( q );
	return info;

}

void QFClear( QFIFO* q )
{

	if( !q )
	{
		printf( "Error QFClear, queue can't be cleared\n" );
		return;
	}
	
	while( !QFEmpty( q ) )	free( QFDequeue(q) );  
		
}

void QFRemove( QFIFO** q )
{
	if( !q || !*q ) 
	{
		printf("Error QFRemove, queue can't be removed\n");
		return;	
	}
	
	QFClear( *q );
	free( ( *q )->pHead ); 
	free( *q );  
	*q = NULL; 
}

void  QFDel( QFIFO* q )
{

	if( !q || QFEmpty( q )  )
	{
		printf( "Error QFDel, element can't be deleted \n" );
		return;
	}
	QFItem* temp = q->pHead->pNext;
	q->pHead->pNext = temp->pNext;
	free( temp );
	
	if( QFEmpty( q ) ) q->pTail = q->pHead;  


}
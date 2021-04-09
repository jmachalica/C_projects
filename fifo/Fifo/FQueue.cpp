#include <stdio.h>
#include <stdlib.h>
#include "FQueue.h"

void  QFDel( QFIFO* q );

QFIFO* QFCreate()
{
	QFIFO* fifo = ( QFIFO* )calloc( 1, sizeof( QFIFO ) );

	if( !fifo )printf( "Allocation Error: QFIFO\n" );	

	return fifo;
}

int QFEmpty( QFIFO* q )
{
	return !q || !q->pHead;

}

int QFEnqueue( QFIFO* q, QInfo* info )
{
	if( !q || !info )
	{
		printf( "Error: QFEnqueue, element can't be added\n" );
		return 0;
	}
	
	QFItem* pItem =( QFItem* )calloc( 1, sizeof( QFItem ) );
	
	if( !pItem )
	{
		printf( "Allocation Error: QFItem \n" );
		return 0;
	}

	 if( QFEmpty( q ) ) q->pHead = pItem;
	 else  q->pTail->pNext = pItem;
	
	 q->pTail = pItem;

	pItem->pinfo = info;
	
	return 1;
}

 QInfo* QFDequeue( QFIFO* q )
 {
	 if( !q )
	 {
		 printf( "Error QFDequeue, element can't be deleted\n" );
		 return NULL;
	 }

	 if( QFEmpty( q ) )
	 {
		 printf( "Queue is empty, element can't be deleted\n" );
		 return NULL;
	 }
	 QInfo* info = q->pHead->pinfo;	 
	 QFDel( q );
	 return info;
	
 }

void QFClear( QFIFO* q )
{
	if( !q )
	{
		printf( "Error: QFClear, queue can't be cleared\n" );
		return;
	}
	while( !QFEmpty( q ) ) free( QFDequeue( q ) );
}

void QFRemove( QFIFO** q )
{
	if( !q || !*q )
	{
		printf( "Error: QFRemove, queue can't be deleted\n" );
		return;
	}
	
	QFClear( *q );
	free( *q );
	*q = NULL;
}

void QFDel( QFIFO* q )
{
	if( !q || QFEmpty( q ) )
	{
		printf( "Error QFDel, element can't be deleted \n" ); 
		return;
	}

	QFItem* temp = q->pHead;
	q->pHead = temp->pNext;
	free( temp ); 

	if( QFEmpty( q ) ) q->pTail = NULL;;
	
}
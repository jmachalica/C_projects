#ifndef FQUEUE_H_26AB76
#define  FQUEUE_H_26AB76
#include "global.h"

typedef struct QFIFO
{
	QFITEM** pFQItems;
	int nHead;
	int nTail;
	int nNoElem;
	int nMaxElem;
} QFIFO;





QFIFO* QFCreate( int nSize );  


int QFEmpty( QFIFO* q );


int  QFEnqueue( QFIFO* q, QFITEM* pItem );

QFITEM* QFDequeue( QFIFO* q );

void QFClear( QFIFO* q, void( __cdecl* freeItem )( const void* ) );

void QFRemove( QFIFO** q , void( __cdecl* freeItem )( const void* ) );

#endif

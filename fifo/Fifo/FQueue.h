#ifndef _FQUEUE_H_26BA7
#define _FQUEUE_H_26BA7

typedef struct
{
    int n_Key;
} QInfo;


typedef struct tagQFItem
{
    QInfo* pinfo;
    tagQFItem* pNext;

}QFItem;

typedef struct QFIFO
{
    QFItem* pHead;
    QFItem* pTail;
} QFIFO;

QFIFO* QFCreate();

int QFEmpty( QFIFO* q );

int QFEnqueue( QFIFO* q, QInfo* info );

QInfo* QFDequeue( QFIFO* q ); 

void QFClear( QFIFO* q );

void QFRemove( QFIFO** q );


#endif

#pragma once

#include "global.h"
#include <limits.h>

#define PRIOR_ERROR INT_MIN
#define POS_ERROR -1

typedef struct 
{
    PQINFO* pInfo; // pInfo; // Ptr to user info
    int nPrior;// nPrior; // prior value (int) for the user info
} PQItem; // type of the queue item

typedef struct
{
    PQItem** pPQueue;
    int nPQSize;  
    int nPQCurrSize;   
} PQueue;

PQueue* PQInit( int size ); 

int PQisEmpty( PQueue* x ); 

int PQSize( PQueue* x ); 

int PGMaxPrior( PQueue* x );

int PQEnqueue( PQueue* x, PQINFO* y,int prior );

PQINFO* PQDequeue( PQueue* x );

void PQClear( PQueue* x, void( __cdecl* freeitem )( const void* ) );

void PQRelease( PQueue** x, void( __cdecl* freeitem )( const void* ) ); 

void QPrint( PQueue* x, void( __cdecl* printinfo )( const void* ), int place ); 

int PQSetPrior( PQueue* x, PQINFO* y, int newprior, int( __cdecl* compare )( const void*, const void* ) );

int PQsetPrior( PQueue* x, int prior, int place ); 

int PQGetPrior( PQueue* x, PQINFO* y, int( __cdecl* compare )( const void*, const void* ) ); 

int PQgetPrior( PQueue* x, int place ); 

int PQFind( PQueue* x, PQINFO* y, int( __cdecl* compare )( const void*, const void* ) ); 

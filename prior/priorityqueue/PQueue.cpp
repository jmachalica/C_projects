#include "PQueue.h"
#include "stdio.h"
#include <stdlib.h>

void UpdateDown( PQItem** pPQueue, int l, int p );
void UpdateUp( PQItem** pPQueue, int l, int p );

PQueue* PQInit( int size )
{
	
    if( size < 1 ) return NULL;
     
    PQueue* x = ( PQueue* )calloc( 1, sizeof( PQueue ) );
	 
    if( !x )  return NULL;
	
    x->pPQueue = ( PQItem** )calloc( size, sizeof( PQItem* ) );
	
	if( !x->pPQueue )
	{
        free( x );
        return NULL;
	}
    x->nPQSize = size;
    return x;
}

int PQisEmpty( PQueue* x )
{
    return !x || !PQSize( x );
}

int PQSize( PQueue* x )
{
	return ( x ) ? x->nPQCurrSize: PRIOR_ERROR;
}

int PGMaxPrior( PQueue* x )  
{
	return ( !x || PQisEmpty( x ) ) ? PRIOR_ERROR : ( *x->pPQueue )->nPrior;
}


int PQEnqueue( PQueue* x, PQINFO* y,int prior )  
{
    if( !x ) return 0;
    
    int size = PQSize( x );

    if( size == PRIOR_ERROR || size >= x->nPQSize ) return 0;
    
    x->pPQueue[ size ] = ( PQItem* )calloc( 1, sizeof( PQItem ) );
	
    if( !x->pPQueue[ size ] ) return 0;
    
    x->pPQueue[ size ]->pInfo = y;
    x->pPQueue[ size ]->nPrior = prior;
    x->nPQCurrSize++;
	
    if( PQSize( x ) > 1  ) UpdateUp( x->pPQueue, 0, size ); 

    return 1;
}


PQINFO* PQDequeue( PQueue* x ) 
{
	
    if( !x || PQisEmpty( x ) ) return NULL;
    
    PQINFO* info = ( *x->pPQueue )->pInfo; 
    int size = --x->nPQCurrSize;
    free( *x->pPQueue );
	
    if( size )*x->pPQueue = x->pPQueue[ size ];
    x->pPQueue[ size ] = NULL;
    
    if( size > 1 )  UpdateDown( x->pPQueue, 0, size - 1 );

    return info;

}


void PQClear( PQueue* x, void( __cdecl* freeitem )( const void* ) )
{
	if( !x || !freeitem )
	{
        printf( "Error: PQClear, queue can't be cleared\n" );
        return;
	}
	
    while( !PQisEmpty( x ) ) freeitem( PQDequeue( x ) );
    
  }


void PQRelease( PQueue** x, void( __cdecl* freeitem )( const void* ) )   
{
    if( !x || !*x )
    {
        printf( "Error: PQRelease, queue can't be released\n" );
        return;
    }
   
    PQClear( *x,freeitem );
    free( ( *x )->pPQueue );
    free( *x );
   *x = NULL;
		
}

void QPrint( PQueue* x, void( __cdecl* printinfo )( const void* ),  int place  )
{
    if( !x || place < 0  )
    {
        printf( "Error: QPrint, queue can't be printed\n\n" );
        return;
    }

	if( PQisEmpty( x ) )
	{
        printf( "Queue is empty\n\n" );
        return;
	}
    if( place >= PQSize( x ) )return;
	
     printf( " Priority: ( %d ), place in the queue: [%d], ", x->pPQueue[ place ]->nPrior, place );
    if( printinfo ) printinfo( x->pPQueue[ place ]->pInfo );

	//preorder
      QPrint( x, printinfo, 2 * place + 1 );
      QPrint( x, printinfo, 2 * place + 2 );
    
}

int PQSetPrior( PQueue* x, PQINFO* y,int newprior, int( __cdecl* compare )( const void*, const void* ) )
{
	return PQsetPrior( x, newprior, PQFind( x, y, compare ) );
}


int PQsetPrior( PQueue* x, int prior, int place )
{
   // if( !x )  return PRIOR_ERROR;
 
    int oldprior = PQgetPrior( x, place );
	if( oldprior != PRIOR_ERROR && oldprior != POS_ERROR  )
    {
		x->pPQueue[ place ]->nPrior = prior;
		if( prior > oldprior ) UpdateUp( x->pPQueue, 0, place );
		else if( prior < oldprior ) UpdateDown( x->pPQueue, place, PQSize( x ) - 1 );
        return oldprior;
    }
    return PRIOR_ERROR;
  
}


int PQGetPrior(  PQueue* x,PQINFO* y , int( __cdecl* compare )( const void*, const void* ) )
{
	return PQgetPrior( x, PQFind( x, y, compare ) );
}



int PQgetPrior(PQueue* x, int place)
{
    if( !x || PQisEmpty( x ) )  return PRIOR_ERROR;
    
    if( place >= PQSize( x ) || place < 0 ) return POS_ERROR;
   
	return x->pPQueue[ place ]->nPrior;
 
}


int PQFind( PQueue* x, PQINFO* y, int( __cdecl* compare )( const void*, const void* ) )
{
    if( !x  ) return PRIOR_ERROR;
    if( !compare ) return POS_ERROR;

    for( int i = 0; i < PQSize( x ); i++ )
    {
        if( !compare( x->pPQueue[ i ]->pInfo, y ) ) return i;
    }
    return POS_ERROR;
}

void UpdateUp( PQItem** pPQueue, int l, int p )
{
   
    if( l >= p )return;

    int j = ( p - 1 ) / 2;
    int i = p; 
    PQItem* item = pPQueue[ i ];
	
    while( j >= l && pPQueue[ j ]->nPrior < item->nPrior )
    {
        pPQueue[ p ] = pPQueue[ j ];
        i = j;
        j = ( i + 1 ) / 2 - 1 ;
    }
    pPQueue[ i ] = item;  
}

   

void UpdateDown( PQItem** pPQueue,  int l, int p )
{
 
    if( l >= p )return;
    int i = l;
    int j = 2 * i + 1;  //left child

    PQItem* item = pPQueue[ i ]; /// parent

    while( j <= p )  
    {
        if( j < p )
            if( pPQueue[ j ]->nPrior < pPQueue[ j + 1 ]->nPrior) j++;
    	
        if( pPQueue[ i ]->nPrior < item->nPrior ) break; //if correct

        pPQueue[ i ] = pPQueue[ j ];
        i = j;
        j = 2 * i + 1;
    }

    pPQueue[ i ] = item;
}

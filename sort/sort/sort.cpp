#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>
#include "functions.h"

#define PRINT1
#define PRINT2
#define PRINTSIZE 50
#define ROWSIZE 10

void printtab( int* tab, int size );
int createtab( int** tab, int size );
void random( int* tab, int size );

typedef void ( *pFp )( int*, int );


int main( int argc, char* argv[] )
{


	if ( argc != 2 )
	{
		printf( "Usage: %s <tab_size>", argv[0] );
		return 1;
	}

	int n = atoi( argv[1] );

	int* modetab = NULL;
	int* sorttab = NULL;
	
	if ( !createtab( &modetab, n ) || !createtab( &sorttab, n ))
	{
		perror( "Error: createtab, memory allocation failed " );
		return 2;
	}
	

	pFp pSortTab[]= { bubblesort,insertionsort,quicksort2,selectionsort,halfsort,heapsort,mixsort };

	random( modetab, n );
	
#ifdef PRINT1
	printf( "Tab to be sorted:\n" );
	printtab( modetab, ( PRINTSIZE<=n ) ? PRINTSIZE:n );
	printf( "\n" );
#endif
	
	
    const char* arr[] ={ "bubblesort","insertionsort","quicksort","selectionsort","halfsort","heapsort","mixsort" };

	int size = sizeof( pSortTab ) / sizeof( pFp );
	
	for( int i=0;i<size;i++ )
	{
		
		memcpy( sorttab, modetab, n * sizeof( int ) );
		
		clock_t start_t = clock();
	    pSortTab[i]( sorttab,n );
		clock_t end_t = clock();

		double total = ( double )( end_t - start_t ) / CLOCKS_PER_SEC;
		printf( "%s took: %lf\n",arr[i], total );
	
#ifdef PRINT2
		printtab( sorttab, ( PRINTSIZE <= n ) ? PRINTSIZE : n );
		printf( "\n" );
#endif
		
	}


	free( sorttab );
	free( modetab );
	return 0;
}

void printtab( int* tab, int size )
{
	for( int i = 0; i < size; i++ )
	{
		printf( "%d ", *tab++ );
		if ( ( i + 1 ) % ROWSIZE== 0 )printf( "\n" );
	}
	
}

int createtab( int** tab, int size )
{
	*tab = ( int* )malloc( size * sizeof(int ) );
	if( !*tab )return 0;

	memset( *tab, 0, sizeof( int ) * size );
	return 1;
}

void random( int* tab, int size )
{
	srand( ( unsigned int )time( NULL ) );
	for( int i = 0; i <size; i++ ) *tab++ = rand() % size;
	
}

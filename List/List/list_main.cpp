#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include <time.h>
#include  "global.h"

#define SIZE 20
#define KEY_SIZE 50
#define PRINT

void addinfo( ListItem* item, int key,int id );
void printlist( ListItem* item );
void printinfo( const void* x );

int main()
{

	ListItem* list=CreateList();

	if( !list )return 1;
	
	srand( ( unsigned int )time( NULL ) );
	

	for( int i=0;i<SIZE;i++ ) addinfo( list, ( rand()% KEY_SIZE ),i );

	
#ifdef PRINT
	printlist( list );
#endif

	SortList( list, &compare );

#ifdef PRINT
	printlist( list );
#endif
	
	LISTINFO* info = ( LISTINFO* )calloc( 1, sizeof( LISTINFO ) );
	

	if( info )
	{ 
			info->nKey = 2000;
			ListItem* pprev = NULL;
			ListItem* found = Find( list, info, &pprev, &compare );
			
			if( found ) 
			{
				info->nKey = 3000;
				Insert( pprev, info );
				freeInfo( Remove( pprev->pNext ) );

			#ifdef PRINT
				printlist( list );
			#endif
			}
			else
			{
				freeInfo( info ); 
				printf("Info not found\n");
			}
	}
	else printf( "Allocation Error: info\n" );

	
	ClearList( list, &freeInfo );
#ifdef PRINT
	printlist( list );
#endif

	for( int i=0;i<2;i++ ) addinfo( list, ( rand()% KEY_SIZE),i );

#ifdef PRINT
	printlist( list );
#endif

	RemoveList( &list, &freeInfo );
	return 0;
}



void addinfo( ListItem* item, int key,int id )
{

	LISTINFO* info = ( LISTINFO* )calloc( 1, sizeof( LISTINFO ) );
	
	if( !info )
	{
		printf("Allocation Error: info\n");
		return;
	}
	
	if( id != 9) info->nKey = key;
	else info->nKey = 2000;

	info->p = ( int* )calloc( 2, sizeof( int ) ); 
	if( info->p ) info->p[ 0 ] = id;
	
	if( !InsertFront( item, info ) ) freeInfo( info );
}


int compare( const void* first, const void* sec )
{
	if( !first && !sec )return 0;
	if( !first )return -1;
	if( !sec )return 1;

		if( ( ( LISTINFO* )first )->nKey < ( ( LISTINFO* )sec )->nKey )return -1;
		if( ( ( LISTINFO* )first )->nKey > ( ( LISTINFO* )sec )->nKey )return 1;
	
		return 0;
}

void printlist( ListItem* item )
{
	 if( IsEmpty( item ))
	 {
	 	printf( "List is empty\n" );
		return;
	}

	ListItem* temp = item->pNext;
	printf("List's elements:\n");
	int i = 0;
	while( temp )
	{
		printf("%d - list's element:", i);
		printinfo( temp->pInfo );
		temp = temp->pNext;
		i++;
	}
	printf("\n\n");
	
}

void freeInfo( const void* x )
{
	if( x ) 
	{
		if( ( ( LISTINFO* )x )->p ) free( ( ( LISTINFO* )x )->p ); 
		//free( ( ( LISTINFO* )x )->p );
		free( ( LISTINFO* )x );
	}
}

void printinfo( const void* x )
{
	if( !x ) printf("Info is empty \n");
	else if( ( ( LISTINFO* )x )->p ) 
		printf( "Nkey=%d, t[0]=%d, t[1]=%d\n", ( ( LISTINFO* )x )->nKey, ((LISTINFO*)x)->p[0], ((LISTINFO*)x)->p[1]);
	else 
		printf( "Nkey=%d, t jest puste", ( ( LISTINFO* )x )->nKey );
	
}
	


/*
 
 if( info )
	{
		info->p = ( int* )calloc( 2, sizeof( int ) );
		if( info->p ) 
		{
			info->nKey = 2000;
			ListItem* pprev = NULL;
			ListItem* found = Find( list, info, &pprev, &compare );
			 
			if( found ) 
			{
				info->nKey = 3000;
				Insert( pprev, info );
				freeInfo( Remove( pprev->pNext ) );

			#ifdef PRINT
				printlist( list );
			#endif
			}
			else freeInfo( info ); //if not found
			
		}
		else  
		{
			free( info );
			printf( "Allocation Error: info->p\n" );
		}
	}
	else printf( "Allocation Error: info\n" );   
	*/
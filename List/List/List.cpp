#include <stdio.h>
#include <stdlib.h>
#include "List.h"

ListItem* CreateList()
{
	ListItem* list = ( ListItem* )calloc( 1, sizeof( ListItem ) );
	return list;
}

int InsertFront( ListItem* pList, LISTINFO* pInfo )
{
	return Insert( pList, pInfo );
}

int Insert( ListItem* pAfter, LISTINFO* pInfo )
{
	if( !pAfter ) return 0;
		
	ListItem* temp= ( ListItem* )calloc( 1, sizeof( ListItem ) );
	
	if( !temp ) return 0;
	
	temp->pNext = pAfter->pNext;
	pAfter->pNext = temp;
	temp->pInfo = pInfo;
	
	return 1;
	
}

LISTINFO* RemoveFront( ListItem* pList )
{
	return Remove( pList ); 	
}

LISTINFO* Remove( ListItem* pAfter )
{
	if( !pAfter || IsEmpty( pAfter ) ) return NULL;

	ListItem* temp = pAfter->pNext; 
	LISTINFO* temp2 = temp->pInfo; 
	pAfter->pNext = temp->pNext;
	free( temp ); 
	return temp2;
	
}

LISTINFO* Front( ListItem* pList )
{
	return ( !pList || IsEmpty( pList ) ) ? NULL: pList->pNext->pInfo;
}

int IsEmpty( ListItem* pList )
{
	return  !pList  || !pList->pNext;
}

void ClearList( ListItem* pList, void( __cdecl* freeInfo )( const void* ) )
{	
	
	if( !pList || !freeInfo )
	{
		printf( "Error: ClearList, list can't be cleared\n" );
		return;
	}
	
	while(  !IsEmpty( pList ) ) freeInfo( RemoveFront( pList ) );
	
	
}

void RemoveList( ListItem** pList, void( __cdecl* freeInfo )( const void* ) )
{
	
	if( !pList || !*pList )
	{
		printf( "RemoveList, list can't be removed\n" );
		return;
	}
	
	ClearList( *pList ,freeInfo );
	free( *pList );
	*pList = NULL;
}



void SortList( ListItem* pList, int( __cdecl* compare)( const void*, const void* ) )
{
	if( !pList || !compare )
	{
		printf( "Error: Sortlist, list can't be sorted \n" );
		return;
	}
	
	ListItem* pFirst = pList; 

	while( pFirst->pNext ) 
	{
		ListItem* pMin = pFirst; 
		ListItem* pCurr = pFirst->pNext; 
		
		
		while( pCurr->pNext ) 
		{
			if( compare( pMin->pNext->pInfo, pCurr->pNext->pInfo ) == 1 )pMin = pCurr;
			pCurr = pCurr->pNext;
		}
		
		if( pMin->pNext != pFirst->pNext )
		{
			
			pCurr = pMin->pNext->pNext; 
			pMin->pNext->pNext = pFirst->pNext;
			pFirst->pNext = pMin->pNext;
			pMin->pNext = pCurr;
			
		}
		pFirst = pFirst->pNext; 

		
		
	}
	
}

ListItem* Find( ListItem* pList,const void* find, ListItem** pPrev, int( __cdecl* compare )( const void*, const void* ) )
{
	if( !pList || !compare ) return NULL;
	
	
	*pPrev= pList;
	while( ( *pPrev )->pNext )
	{
		if( !compare( ( *pPrev )->pNext->pInfo, find ) ) return ( *pPrev )->pNext; 
	
		*pPrev =( *pPrev )->pNext; 
		
	}
	 
	return *pPrev = NULL;
}



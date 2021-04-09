#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//DIrection of movement
typedef enum { UP = 1, RIGHT, DOWN, LEFT }DIRECTIONS;


int move( int** pDepthTab, int nRow, int nCol, int nDepth, int nextMove, int x, int y, int* px, int* py, int** pRoot )
{
  switch( nextMove )
  {
  case UP: *px = x -1;*py = y; break;
  case RIGHT:*py = y + 1;*px = x; break;
  case DOWN:*px = x + 1;*py = y;break;
  case LEFT:*py = y - 1;*px = x;break;
  }
	
  return  !( *px < 0 || *px >= nRow || *py < 0 || *py >= nCol || pDepthTab[*px][*py] <= nDepth || pRoot[*px][*py] !=0 );   
	
}



int root( int** pDepthTab, int nRow, int nCol, int nDepth, int x, int y, int** pRoot, int x_dest, int y_dest )
{

 static int movs = 1; 
 pRoot[x][y] = movs++;

 if ( x == x_dest && y == y_dest )return 1;
	
 int x2 = 0;
 int y2 = 0;
	
	for ( int i = UP; i <= LEFT; i++ )
	if( move( pDepthTab, nRow, nCol, nDepth, i, x, y, &x2, &y2, pRoot ) )
		if( root( pDepthTab, nRow, nCol, nDepth, x2, y2, pRoot, x_dest, y_dest ) )return 1;
			
	movs--;
	pRoot[x][y] = 0;
	return 0;
	
}



int readDepthTab( char* sFile, int** pTab, int nRow, int nCol )  
{
	FILE* f = fopen( sFile, "r" );
	if ( !f )
	{
		printf( "Error: opening file %s failed\n", sFile );
		return 0;
	}

	for ( int i = 0; i < nRow; i++ )
	{
		int* x = *pTab++;
		for ( int j = 0; j < nCol; j++ )
			fscanf( f, "%d", x++ );
		
	}
	fclose( f );
	return 1;
}

int** createTab( int nRow, int nCol )
{
	
	int** pTab = ( int** )malloc( nRow * sizeof( int* ) );

		if ( !pTab )return NULL;
		memset( pTab, 0, sizeof( int* ) * nRow );

	
		int* p = ( int* )malloc( sizeof( int ) * nRow*nCol );
	
		if (!p)
		{
			free(pTab);
			return NULL;
		}
			memset( p, 0, sizeof( int ) * nRow * nCol );
	
		
	
			int** tab = pTab; 
			 for( int i = 0; i < nRow; i++ )			
			 {
			 	*tab++ = p;
				p += nCol;
			 }
			
			return pTab;
}

void printTab( int** pRoot, int nRow, int nCol )
{	
		for ( int i = 0; i < nRow; i++ )
		{
			int* t = *pRoot++;
			for( int j = 0; j < nCol; j++ )
			{
				printf( "%d   ", *t++ );
			}
			printf( "\n" );
		}
	
}

void freeTab( int*** pTab )
{
	free( **pTab ); 
	free( *pTab );
	*pTab = NULL;
}


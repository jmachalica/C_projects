//Temat projektu: Rozwiazanie ukl rownan (6x6)  Ax=b => x=A^-1 * b  */
#include <stdio.h>
#include <memory>
#include "matrix.h"
#include <stdlib.h>
#include <math.h>
#include <float.h>
using namespace std;
#define _DEBUG1_

void printvec( double* tab, int size );
void ReadData( FILE* fin, double** pMatrix, double* b, int nDim );

int main( int argc,char* argv[] )
{

	  if ( argc != 2 )
	  {
	  	printf( "Usage: %s <input file>",argv[0] );
	  	return 1;
	  }

	FILE* f = fopen( argv[1], "r" );
		if ( f == NULL ) 
		{
			printf( "Error: opening file %s failed\n",argv[1] );
			return 2;
		}
		
	int nDim = 0;
	fscanf( f, "%d", &nDim );
	
	double** pTab = NULL;


	
	double* vec = NULL;
	vec= ( double* )malloc( nDim * sizeof(double) );
	if ( !vec || !CreateMatrix( &pTab, nDim ) )
	{
		perror( "Error: vector and matrix allocation " );
		return 4;
	}
	memset( vec, 0, nDim * sizeof(double) );
	
	ReadData( f, pTab, vec, nDim );
	fclose( f );

	
#ifdef _DEBUG1_
	printf( "MATRIX CREATED AND READ\n" );
#endif

	PrintMatrix( pTab, nDim );
	printf("\n");
	printvec( vec, nDim );
	printf("\n");

	//obliczenie wyznacznika
	
	double det = Det( pTab, nDim );
	
	if ( fabs(det)< 1e-16) 
	{
		perror( "DET = 0, can't solve this set of equations" );
		return 6;
	}
	printf("DET = %lf \n", det);
	
	double** invTab = NULL;
	if ( !CreateMatrix( &invTab, nDim ) )
	{
		perror( "Error: invTab allocation " );
		return 7;
	}

	InverseMatrix( invTab, pTab, nDim, det );	
	
	
#ifdef _DEBUG1_
	printf("INVERSE MATRIX CALCULATED \n" );
#endif
	

	double* res = NULL;
	res = ( double* )malloc( nDim * sizeof( double ) );
	if ( !res )
	{
		perror( "Error: create res" );
		return 8;
	}
	memset( res, 0, nDim * sizeof( double ) );

	
	
	LayoutEqu( invTab, vec, res, nDim );
	

	printf("Results are:\n");
	printvec( res, nDim );

	
	DeleteMatrix( &invTab, nDim );
	DeleteMatrix(&pTab, nDim);
	free( vec );
	free( res );
		
	return 0;	
	
}

void printvec( double* tab,int size )
{
	for ( int i = 0; i < size; i++ )
		printf( "%lf\n", *tab++ );
}

void ReadData( FILE* fin, double** pMatrix, double* b, int nDim )
{
	for ( int i = 0; i < nDim; i++ )
	{
		double* x = *pMatrix++;
		for ( int j = 0; j < nDim; j++ )
		{
			fscanf( fin, "%lf", x++ );

		}
		fscanf( fin, "%lf", b++ );

	}
}
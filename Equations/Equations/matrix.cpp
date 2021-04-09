#include "matrix.h"
#include <stdio.h>
#include <memory>
#include <stdlib.h>
#include <float.h>


void complement( double** pTabO, double** pTabI, int nRow, int nCol, int nDim );

void ComplMatrix( double** pTabD, double** pTab, int nDim ); 


void TransMatrix( double** pTab, int nDim ) 
{
	double** tab1 = pTab;
	for ( int i = 0; i < nDim - 1; i++ )
	{
		double* tab2 = *tab1++ + i+1;
		for ( int j = i + 1; j < nDim; j++,tab2++ )
		{
			double temp = *tab2;
			*tab2 = pTab[j][i];
			pTab[j][i] = temp;
		}
	}
}

int CreateMatrix( double*** pTab, int nSize )
{
*pTab = ( double** )malloc( nSize * sizeof( double* ) );

	if ( !pTab )//(*pMatrix == NULL)
		return 0;
	
	memset( *pTab, 0, sizeof(double*) * nSize );
	
	double** p = *pTab;
	for ( int i = 0; i < nSize; i++ )
	{
		*p = ( double* )malloc( sizeof( double ) * nSize );	//(*pMatrix)[i] = (double*)malloc(nDim * sizeof(double));

		if ( !*p )return 0;           // (  ( (*pMatrix)[i]) == NULL)
		memset( *p++, 0, sizeof( double ) * nSize );
	}
	return 1;
}

void DeleteMatrix( double*** pTab, int nSize )
{
	double** v = *pTab;
	 for ( int i = 0; i < nSize; i++ ) 
		free( *v++ );
	
	  	free( *pTab );
	  	*pTab = NULL;
	
 // for (int i = 0; i < nSize; i++)
	//  free((*pTab)[i]);
	//
	//  free(*pTab);
	//  *pTab = NULL;
}

void InverseMatrix( double** pInv, double** pTab, int nSize, double det )
{
	if (nSize == 1)
	{
		**pInv= 1/det; 
		return;
	}
	ComplMatrix( pInv, pTab, nSize );
	TransMatrix( pInv, nSize );
	
	for ( int nRow = 0; nRow < nSize; nRow++ )
	{
		double* v = *pInv++;
		for ( int nCol = 0; nCol < nSize; nCol++, v++ )
			*v = *v / det;
	}
}

double Det( double** pTab, int nSize )
{
	if ( nSize == 1 )return **pTab;
	if( nSize==2 )return ( **pTab * pTab[1][1] - pTab[0][1] * pTab[1][0]) ;


	double* t = *pTab;
	double** temp = NULL;
	if ( !CreateMatrix( &temp, nSize - 1 ) ) 
	{
		perror( "Error: create pTab in Det" );
		return DBL_MIN;

		
	}
	double sign = 1;
	double res = 0;

	
	for ( int i = 0; i < nSize; i++ )
	{
		complement( temp, pTab, 0, i,nSize );
		res += sign * *t++ * Det( temp, nSize - 1);
		sign = -sign;
	}
	
	DeleteMatrix( &temp, nSize-1 );
		return res;
}

 void LayoutEqu( double** pInv, double* pB, double* pRes, int nSize )
 {
 	for ( int i = 0; i < nSize; i++,pRes++)
 	{
 		double* pB2 = pB;
 		double* t = *pInv++;
 		for ( int j = 0; j < nSize; j++ ) 
 			*pRes +=  *t++  *  *pB2++;	
 	}
 }

void PrintMatrix( double** pTab, int nSize )
{
	for ( int i = 0; i < nSize; i++ )
	{
		double* t = *pTab++;
		for ( int j = 0; j < nSize; j++ )
		{	
			printf( "%.2lf ", *t++ );
		}
		printf( "\n" ); 
	}
}


void complement( double** pTabO, double** pTabI, int nRow, int nCol, int nDim )
{
	for ( int i = 0; i < nDim; i++ )
	{
		double* tI = *pTabI++; 
		if ( i == nRow )continue; 

		double* t0 = *pTabO++;

		for ( int j = 0; j < nDim; j++,tI++ )
		{
			if ( j == nCol )continue; 
			*t0++ = *tI;
		}
	}
}




void ComplMatrix( double** pTabD, double** pTab, int nDim )
{
	
	double** temp = NULL;
	if ( !CreateMatrix( &temp, nDim - 1 ) )
	{
		perror( "Error: create pTab in ComplMatrix");
		return;
	}
	
	for ( int i = 0; i < nDim; i++ )
	{
		int sign = (i % 2 == 1) ? -1 : 1;
	
		double* t = *pTabD++;
		for ( int j = 0; j < nDim; j++ )
		{
			complement( temp, pTab, i, j, nDim );
			*t++ = sign * Det( temp, nDim - 1 );
			sign = -sign;
		}		
	}
	DeleteMatrix( &temp, nDim - 1 );
}





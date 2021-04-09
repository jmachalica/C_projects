#include "functions.h"

void quicksort( int l, int r, int* tab);
void sifts( int l, int r, int* tab);

void quicksort( int l, int r, int* tab)
{
	int i = l;
	int j = r;
	int x = tab[ ( l + r ) / 2 ];
	
	do
	{
		while( tab[i] < x )i++;
		
		while( x < tab[j] )j--;
		
		if (i <= j)
		{
			int w = tab[i];
			tab[i] = tab[j];
			tab[j] = w;
			i++;
			j--;

		}

	} while ( i <= j );
	
	if ( l < j )quicksort( l, j, tab );
	if ( i < r )quicksort( i, r, tab );




}
void quicksort2( int* tab, int nsize )
{
	quicksort( 0, nsize - 1, tab );
}



void halfsort( int* tab, int nsize )
{
	/*
	 wirth 2004 version
	 for (int i = 1; i < nsize; i++)
	{
		int x = tab[i];
		int l = 0;
		int r = i;
		while (l < r)
		{
	
			int m = (l + r) / 2;
		
			if (tab[m] < x)l=m+1;
			else r = m;
		}
	
		for(int j = i; j >= r + 1; j--)
			tab[j] = tab[j - 1];
		tab[r] = x;
	}*/

	for ( int i = 1; i < nsize; i++ )
	{
		int x = tab[i];
		int l = 0;
		int r = i;
		while ( l < r )
		{

			int m = ( l + r ) / 2;

			if ( tab[m] > x )r = m;
			else l = m+1;
		}
		
		for ( int j = i-1; j >= l; j-- )
			tab[j+1] = tab[j];
		tab[l] = x;
	
	}

}

void update( int l, int r, int* tab)
{
	if( l >= r ) return;
	
	int i = l;
	int j = 2 * i +1;

	int x = tab[i];

	while( j <= r )
	{
		if( j < r )	
			if ( tab[j] < tab[j + 1] ) j++;
		if( x >= tab[j] )break;

		tab[i] = tab[j];
		i = j;
		j = 2 * i+1;
	}

	tab[i] = x;

}



void heapsort( int* tab, int nsize )
{
	
	int p = nsize - 1;

    for( int l = nsize / 2; l>=0;--l ) update( l, p,tab );
	
	for( p;p>0;p-- )
	{
		int x = tab[0]; 
		tab[0] = tab[p];
		tab[p] = x;
		update( 0, p-1,tab );
	}

	/*int l = nsize / 2;
	int r = nsize - 1;
	while (l > 0)
	{
		l--;
		update(l, r, tab);
	}
	while (r > 0)
	{
		int x = tab[0];
		tab[0] = tab[r];
		tab[r--] = x;
		update(l, r, tab);
	}*/
	
}

	
void mixsort( int* tab, int nsize )
{
	int l = 1;
	int p = nsize - 1;
	int k = nsize - 1;
do
{

	for( int j = p; j >= l; j-- )
	{
		if( tab[j - 1] > tab[j] )
		{
			int x = tab[j - 1];
			tab[j - 1] = tab[j];
			tab[j] = x;
			k = j;
		}

	}
	l = k + 1;
	for( int j = l; j <= p; j++ )
	{
		if( tab[j - 1] > tab[j] )
		{
			int x = tab[j - 1];
			tab[j - 1] = tab[j];
			tab[j] = x;
			k = j;
		}
	}
	p = k - 1;
} while( l <= p );


}

void bubblesort( int* tab, int nsize )
{
	for ( int i = 0; i < nsize; i++ )
		for ( int j = nsize - 1; j > i; j-- )
			if ( tab[j] < tab[j - 1] )
			{
				int temp = tab[j];
				tab[j] = tab[j - 1];
				tab[j - 1] = temp;
			}

}
void insertionsort( int* tab, int nsize )
{
	for( int i = 1; i < nsize; i++ )
	{
		int x = tab[i];
		int j = i - 1;
		while ( j >= 0 && tab[j] > x )
			tab[j + 1] = tab[j--];
		tab[j + 1] = x;
	}
}
void selectionsort( int* tab, int nsize )
{
	for ( int i = 0; i < nsize - 1; i++ )
	{
		int min = tab[i];
		int temp = i;
		for( int j = i + 1; j < nsize; j++ )
			if( tab[j] < min )
			{
				min = tab[j];
				temp = j;
			}
		tab[temp] = tab[i];
		tab[i] = min;

	}
}

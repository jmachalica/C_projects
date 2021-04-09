#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#define N 8
#define M 8
#define SHIP_DEPTH 6
#define READ1

int main( int argc, char* argv[] )
{

	if ( argc != 2 )
	{
		printf("Usage: %s <plik wejsciowy>", argv[0]);
		return 1;
	}



	int** proot = NULL;
	int** depth = NULL;
	proot = createTab( N, M );
	depth = createTab( N, M );

	if ( !depth || !proot )
	{
		perror( "Error createtab" );
		return 2;

	}


	if (readDepthTab(argv[1], depth, N, M))
	{
		
		
#ifdef READ1

		printf("Map of sea's depth: \n\n");
		printTab(depth, N, M);
		printf("\n");

#endif


		if (!root(depth, N, M, SHIP_DEPTH, 0, 0, proot, N - 1, M - 1))
		{
			printf("You cant get to the harbor!! \n \n");
			
		}
		else
		{
		
			printf("Ship got the the harbor, path: \n\n");
			printTab(proot, N, M);

		}
		
	}
	else perror("Error: Read_Depth");
	
	
	freeTab( &proot );
	freeTab( &depth );
	
	return 0;

}


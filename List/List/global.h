#ifndef _GLOBAL_H_26BA7
#define _GLOBAL_H_26BA7

typedef struct
{
	int nKey;
	int* p;
} ListInfo;

#define LISTINFO ListInfo

void  freeInfo( const void* x );
int compare( const void* first, const void* sec );

#endif
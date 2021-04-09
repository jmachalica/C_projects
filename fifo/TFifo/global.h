#ifndef GLOBAL_H_26AB5
#define GLOBAL_H_26AB5

typedef struct
{
    int n_Key; 
    int* pTab; 
} QInfo;

#define QFITEM QInfo

void freeItem( const void* );

#endif

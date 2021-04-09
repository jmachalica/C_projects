#include <stdio.h>
#include "onpfunction.h"
#include <math.h>
#include "stack.h"
#include "DSTACK.h"
#include <float.h>

#define DOT '.'


void skipSpaces() 
{
	char c;
	while ( ( c = getchar() ) == ' ' );
	ungetc( c, stdin ); 

}

double getNum() {
	char c;
	double num = 0;
	int sign=0;
	
	// horner
	skipSpaces();

		if ( (c =getchar())=='-' ) sign=1;
		else if ( c !='+' ) ungetc( c,stdin );

	while ( isDigit(c = getchar() ) )
		num = num * 10 + c - '0';

	if ( c== DOT) 
	{
		double coef=0.1;
		while ( isDigit( c = getchar() ) )
		{
			num += (c-'0')*coef;
			coef*=0.1;
			
		}
		

	}
	
	ungetc( c, stdin ); 
	if( sign ) num=-num; 
	
	return num;
}
double isDigit( char c ) {
	return (c >= '0') && (c <= '9'); 
}

int prior( char cOper )
{
	switch ( cOper )
	{
	case '+':
	case '-': return 1;
	case '*':
	case '/': return 2;
	case '^':  return 3;
	}
	return 0;
}
int isOper( char cOper ) {
	switch ( cOper )
	{
	case '+':
	case '-':
	case '*':
	case '^':
	case '/': return 1;
	}
	return 0;
}


char getOper() {
	skipSpaces();
	return getchar();
}

double eval( char cOper,double arg1,double arg2 )
{	switch ( cOper )
	{
	case '+': return arg1+arg2;
	case '-':return arg1-arg2;
	case '*':return arg1*arg2;
	case '^':return pow( arg1, arg2 );
	case '/': if( fabs( arg2 )>1e-15 ) return arg1/arg2;
		perror( "Error:Division by 0" );
		return DBL_MIN;
		
	}
	return 0;
}




void ONP() 
{
	char c;
	skipSpaces();
	makeEmptyStack();
	printf( " %.3f ", getNum() );//start
	{
		
			while ( isOper( c = getOper() ) )
			{
				while ( prior( c ) <= prior (top() ) )
				{  
					printf( "%c",pop() ); 
					putchar(' ');
				}
				push(c); 
				//ungetc(c, stdin);
				printf( "%.3f ", getNum() );
			}
			//ungetc(c, stdin);
			//printf("%lf", getNum());
	}

	while ( !isEmpty() )
		putchar( pop() );

	
	}



double onp_calc()
{
	char c;
	skipSpaces();
	makeEmptyStack();
	makeDEmptyStack();

	
	dpush( getNum() );//start

		while ( isOper( c = getOper() ) )
		{
			while ( prior( c ) <= prior( top() ) )
			{
				double arg1 = dpop();
				dpush( eval( pop(), dpop(), arg1 ) );
			}
			push( c );
			dpush(getNum());
		}
		
		
		
	

	while ( !isEmpty() )
	{
		double arg1 = dpop();
		dpush( eval( pop(), dpop(), arg1 ));
		
	}
	return dpop();


	
}









	




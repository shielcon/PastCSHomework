/*	stack.c: Stack application. */

/*

Connor Shields
1/29/18
This program includes the nextChar and isBalanced functions.

Input:

A string of characters.

Output:

An expression stating whether or not the parenthesis, brackets, and angled
brackets are properly balanced.

*/




#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dynArray.h"


/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string 	
	pre: s is not null		
*/
char nextChar(char* s)
{
	static int i = -1;	
	char c;
	++i;	
	c = *(s+i);			
	if ( c == '\0' )
		return '\0';	
	else 
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string 	
	pre: s is not null	
	post:	
*/
int isBalanced(char* s)
{
	DynArr* dyn = newDynArr(20);
	char tempChar = *s;
	while (tempChar != '\0')
	{
		tempChar = nextChar(s);
		if (tempChar == '(' || tempChar == '[' || tempChar == '{')
			pushDynArr(dyn, tempChar);
		if (tempChar == ')')
		{
			if (topDynArr(dyn) == '(')
				popDynArr(dyn);
			else
			{
				deleteDynArr(dyn);
				return 0;
			}
		}
		if (tempChar == ']')
		{
			if (topDynArr(dyn) == '[')
				popDynArr(dyn);
			else
			{
				deleteDynArr(dyn);
				return 0;
			}
		}
		if (tempChar == '}')
		{
			if (topDynArr(dyn) == '{')
				popDynArr(dyn);
			else
			{
				deleteDynArr(dyn);
				return 0;
			}
		}
	}
	if (isEmptyDynArr(dyn))
	{
		deleteDynArr(dyn);
		return 1;
	}
	deleteDynArr(dyn);
	return 0;

}

int main(int argc, char* argv[]){
	
	char* s = argv[1];

	int res;

	res = isBalanced(s);

	
	
	if (res)
		printf("The string %s is balanced\n",s);
	else 
		printf("The string %s is not balanced\n",s);
	
	return 0;	
}


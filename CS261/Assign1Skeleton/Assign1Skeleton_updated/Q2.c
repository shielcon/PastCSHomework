/* CS261- Assignment 1 - Q.2*/
/* Name: Connor Shields
 * Date: 1/22/18
 * Solution description:
 This program passes three integers
 to the foo function, which modifies the
 value of each integer. However, the integer
 z remains unchanged, because it is not passed
 as a pointer, but as a copy of the value.
 Input: none
 Output: Three integers, followed by the result of foo,
 followed by the value of those three integers after 
 calling foo.
 */
 
#include <stdio.h>
#include <stdlib.h>

int foo(int* a, int* b, int c){
    /*Set a to double its original value*/
	*a = *a * 2;
    
    /*Set b to half its original value*/
	*b = *b / 2;
    
    /*Assign a+b to c*/
	c = *a + *b;
    
    /*Return c*/
	return c;
}

int main(){
    /*Declare three integers x,y and z and initialize them to 5, 6, 7 respectively*/
	int x, y, z;
	x = 5;
	y = 6;
	z = 7;
    
    /*Print the values of x, y and z*/
	printf("%d\n%d\n%d\n", x, y, z);
    
    /*Call foo() appropriately, passing x,y,z as parameters*/
	int newZ = foo(&x, &y, z);
    
    /*Print the value returned by foo*/
	printf("%d\n", newZ);
    
    /*Print the values of x, y and z again*/
	printf("%d\n%d\n%d\n", x, y, z);
 
    /*Is the return value different than the value of z?  Why?*/
    return 0;
}
    
    

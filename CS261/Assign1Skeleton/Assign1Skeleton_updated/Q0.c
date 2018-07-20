/* CS261- Assignment 1 - Q. 0*/
/* Name: Connor Shields
 * Date: 1/22/18
 * Solution description:
 This program passes the address of x
 to foo, which prints the address, the
 address of the pointer, and the dereferenced
 value of the pointer.
 Input: none
 Output: The address of x, the
 dereferenced value of x's pointer,
 the value of the pointer, the address of
 the pointer, and the value of x.
 */
 
#include <stdio.h>
#include <stdlib.h>

void fooA(int* iptr){
     /*Print the value pointed to by iptr*/
	printf("%d \n", *iptr);
     /*Print the address pointed to by iptr*/
	printf("%p \n", iptr);
     /*Print the address of iptr itself*/
	printf("%p \n", &iptr);
}

int main(){
    
    /*declare an integer x*/
	int x = 3;
    
    /*print the address of x*/
	printf("%p \n", &x);
    /*Call fooA() with the address of x*/
	fooA(&x);
    /*print the value of x*/
	printf("%d \n", x);
    return 0;
}

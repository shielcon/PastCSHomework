/* CS261- Assignment 1 - Q. 0*/
/* Name:
 * Date:
 * Solution description:
 */
 
#include <stdio.h>
#include <stdlib.h>

void fooA(int* iptr){
	printf("%d \n", *iptr);
	printf("%p \n", iptr);
	printf("%p \n", &iptr);
     /*Print the value pointed to by iptr*/
     
     /*Print the address pointed to by iptr*/
     
     /*Print the address of iptr itself*/
}

int main(){
	int x = 3;
	printf("%p \n", &x);
	fooA(&x);
	printf("%d \n", x);
    
    /*declare an integer x*/
    
    /*print the address of x*/
    
    /*Call fooA() with the address of x*/
    
    /*print the value of x*/
    
    return 0;
}

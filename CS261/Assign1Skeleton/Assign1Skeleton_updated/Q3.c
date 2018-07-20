/* CS261- Assignment 1 - Q.3*/
/* Name: Connor Shields
 * Date: 1/22/2018
 * Solution description:
  This program dynamically allocates an integer array
  of size n, which is assigned to 20. It is then filled
  with random numbers, printed, sorted, and then printed
  again.

  Input: none
  Output: an unsorted array of random numbers, followed by a sorted
  array of those same numbers.
 */
 
#include <stdio.h>
#include<stdlib.h>
#include<math.h>


/*I chose to use the selection sort algorithm*/
void sort(int* number, int n){
     /*Sort the given array number , of length n*/
	int position, temp;
	for (int i = 0; i < n - 1; i++)
	{
		position = i;
		for (int j = i + 1; j < n; j++)
		{
			if (number[j] < number[position])
				position = j;
		}
		if (position != i)
		{
			temp = number[i];
			number[i] = number[position];
			number[position] = temp;
		}
	}
}

int main(){
    /*Declare an integer n and assign it a value of 20.*/
	int n = 20;
    /*Allocate memory for an array of n integers using malloc.*/
	int* ptr;
	ptr = malloc((n) * sizeof(int));
    /*Fill this array with random numbers, using rand().*/
	for (int i = 0; i < n; i++)
		ptr[i] = rand();
    /*Print the contents of the array.*/
	printf("unsorted");
	printf("\n");
	for (int i = 0; i < n; i++)
		printf("%d\n", ptr[i]);
    /*Pass this array along with n to the sort() function of part a.*/
	sort(ptr, n);
    /*Print the contents of the array.*/
	printf("Sorted");
	printf("\n");
	for (int i = 0; i < n; i++)
		printf("%d\n", ptr[i]);
	free(ptr);
    return 0;
}

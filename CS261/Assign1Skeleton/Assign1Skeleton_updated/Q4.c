/* CS261- Assignment 1 - Q.4*/
/* Name: Connor Shields
 * Date: 1/22/18
 * Solution description:
 This program dynamically allocates an array of student structs of size n,
 randomly generates student IDs and test scores for those structs, and then
 sorts them in ascending order by test score.

 Input:
 None, but the program could easily be modified to accept
 a user-defined n for the size of the array.

 Output:
 First, an unsorted array, followed by an array
 sorted in ascending order by test scores.
 */
 
#include <stdio.h>
#include<stdlib.h>
#include<math.h>

struct student{
	int id;
	int score;
};

void sort(struct student* students, int n) {
	/*Sort the n students based on their score*/
   /*I used the selection sort algorithm*/
	int minimum, tempScore, tempId;
	for (int i = 0; i < n - 1; i++)
	{
		minimum = i;
		for (int j = i + 1; j < n; j++)
		{
			if (students[j].score < students[minimum].score)
				minimum = j;
		}
		tempScore = students[minimum].score;
		tempId = students[minimum].id;
		students[minimum].score = students[i].score;
		students[minimum].id = students[i].id;
		students[i].id = tempId;
		students[i].score = tempScore;
	}


}

int main(){
    /*Declare an integer n and assign it a value.*/

	int n = 10;

    /*Allocate memory for n students using malloc.*/

	struct student *structPtr;
	structPtr = malloc((n) * sizeof(struct student));

    /*Generate random and unique IDs and random scores for the n students, using rand().*/
	/*I used the Fisher-Yates Shuffle*/

	for (int i = 0; i < n; i++)
	{
		structPtr[i].score = rand() % 101;
	}
	int temp, index;
	int* idPtr = malloc((n) * sizeof(int));
	for (int i = 1; i <= n; i++)
		idPtr[i - 1] = i;
	for (int i = 0; i < n - 1; i++)
	{
		index = rand() % (i + 1);
		temp = idPtr[index];
		idPtr[index] = idPtr[i];
		idPtr[i] = temp;
	}
	for (int i = 0; i < n; i++)
		structPtr[i].id = idPtr[i];
	free(idPtr);

    /*Print the contents of the array of n students.*/
	for (int i = 0; i < n; i++)
	{
		printf("Student #%d: %d\n", structPtr[i].id, structPtr[i].score);
	}
	printf("\n");
    /*Pass this array along with n to the sort() function*/
	sort(structPtr, n);
    /*Print the contents of the array of n students.*/
	for (int i = 0; i < n; i++)
	{
		printf("Student #%d: %d\n", structPtr[i].id, structPtr[i].score);
	}
	free(structPtr);
    return 0;
}

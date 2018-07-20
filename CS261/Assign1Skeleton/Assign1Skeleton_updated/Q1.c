/* CS261- Assignment 1 - Q.1*/
/* Name: Connor Shields
 * Date: 1/22/18
 * Solution description:
 This program dynamically allocates an array
 of ten student structs. Then, it assigns unique
 random ids to each student and random test scores.
 It sorts the test scores and prints them, and then
 prints the average, minimum, and maximum scores.

 Input: none
 Output: sorted list of students by scores, average
 score, maximum score, and minimum score.
 */
 
#include <stdio.h>
#include<stdlib.h>
#include<math.h>

struct student{
	int id;
	int score;
};

struct student* allocate(){
     /*Allocate memory for ten students*/
	struct student* stdPtr = malloc((10) * sizeof(struct student));
     /*return the pointer*/
	return stdPtr;
}

void generate(struct student* students){
     /*Generate random and unique ID and scores for ten students, ID being between 1 and 10, scores between 0 and 100*/
	for (int i = 0; i < 10; i++)
	{
		students[i].score = rand() % 101;
	 }
	int temp, index;
	int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	for (int i = 0; i < 9; i++)
	{
		index = rand() % (i + 1);
		temp = arr[index];
		arr[index] = arr[i];
		arr[i] = temp;
	}
	for (int i = 0; i < 10; i++)
		students[i].id = arr[i];
}

void output(struct student* students){
     /*Output information about the ten students in the format:
              ID1 Score1
              ID2 score2
              ID3 score3
              ...
              ID10 score10*/
	for (int i = 0; i < 10; i++)
	{
		printf("ID%d %d ", i + 1, students[i].id);
		printf("Score: %d \n", students[i].score);
	}
}

void summary(struct student* students){
     /*Compute and print the minimum, maximum and average scores of the ten students*/
	int maximum = students[0].score;
	int minimum = students[0].score;
	int total = 0;
	for (int i = 0; i < 10; i++)
	{
		if (students[i].score > maximum)
			maximum = students[i].score;
		if (students[i].score < minimum)
			minimum = students[i].score;
		total += students[i].score;
	}
	printf("Total: %d\n", total);
	printf("Maximum: %d\n", maximum);
	printf("Minimum: %d\n", minimum);
}

void deallocate(struct student* stud){
     /*Deallocate memory from stud*/
	free(stud);
}

int main(){
    struct student* stud = NULL;
    
    /*call allocate*/
	stud = allocate();
    /*call generate*/
	generate(stud);
    /*call output*/
	output(stud);
    /*call summary*/
	summary(stud);
    /*call deallocate*/
	deallocate(stud);

    return 0;
}

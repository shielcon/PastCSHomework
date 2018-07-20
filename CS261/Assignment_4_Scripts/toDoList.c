/*
Connor Shields
CS 261 - Assignment 4
this includes the implementations of the todolist functions
*/



#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "toDoList.h"


/*  Create a task from the description and the priority

    param:  priority    priority of the task
    param:  desc    	pointer to the description string
    pre:    none
    post:   none
	ret: 	a task with description and priority
*/
TYPE createTask (int priority, char *desc) 
{
	TYPE newTask;
	newTask.priority = priority;
	strcpy(newTask.description, desc);
	return newTask;
}

/*  Save the list to a file

    param:  heap    pointer to the list
    param:  filePtr	pointer to the file to which the list is saved
    pre:    The list is not empty
    post:   The list is saved to the file in tab-delimited format.
			Each line in the file stores a task, starting with the 
			task priority, followed by a tab character (\t), and 
			the task description.
			
			The tasks are not necessarily stored in the file in 
			priority order. 
	
*/
void saveList(DynArr *heap, FILE *filePtr)
{
	assert(heap->size > 0);
	TYPE *currentTask;
	for (int i = 0; i < sizeDynArr(heap); i++)
	{
		*currentTask = getDynArr(heap, i);
		fprintf(filePtr, "%d\t%s\n", currentTask->priority, currentTask->description);
	}
}

/*  Load the list from a file

    param:  heap    pointer to the list
    param:  filePtr	pointer to the file
    pre:    none
    post:   The tasks are retrieved from the file and are added to the list.
			Refer to the saveList() function for the format of tasks in the file				
*/
void loadList(DynArr *heap, FILE *filePtr)
{
	TYPE currentTask;
	char currentLine[250]; 
	char taskName[128];			//equal to TASK_NAME_SIZE
	int taskPriority;
	char *nullPtr;
	int *priorityPtr;
	if (fscanf)
	{
		while ((fscanf(filePtr, "%d\t", priorityPtr)) != EOF)
		{
			fgets(taskName, sizeof(taskName), filePtr);
			nullPtr = strchr(taskName, '\n');
			if (nullPtr)
				*nullPtr = '\0';			//stores the endline to remove from feed
			currentTask = createTask(taskPriority, taskName);
			addHeap(heap, currentTask);
		}
	}
	else
	{
		while (fgets(currentLine, sizeof(currentLine), filePtr) != 0)
		{
			sscanf(currentLine, "%d\t%[^n]", priorityPtr, taskName); //stores digit in priority and non-whitespace charss in taskName
			currentTask = createTask(taskPriority, taskName);
			addHeap(heap, currentTask);
		}
	}

}

/*  Print the list

    param:  heap    pointer to the list
    pre:    the list is not empty
    post:   The tasks from the list are printed out in priority order.
			The tasks are not removed from the list.
*/
void printList(DynArr *heap)
{
	DynArr *tempDynArr = newDynArr(heap->size);
	copyDynArr(heap, tempDynArr);
	printf("\n");
	while (tempDynArr->size > 0)
	{
		DynArr *currentTask = newDynArr(heap->size);
		taskPrint(currentTask);
		printf("\n");
		removeMinHeap(tempDynArr);
	}
	deleteDynArr(tempDynArr);
}

/*  Compare two tasks by priority

    param:  left    first task
    param:  right 	second task
    pre:    none
    post:   none
	ret: 	-1 if priority of left < priority of right
			1 if priority of left > priority of right
			0 if priority of left = priority of right
*/
int compare(TYPE left, TYPE right)
{
	if (left.priority < right.priority)
		return -1;
	else if (left.priority > right.priority)
		return 1;
	else
		return 0;
}

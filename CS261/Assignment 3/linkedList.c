#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

/*
Connor Shields
2/5/18
Assignment 3
This is the implementation of the double-linked list ADT
*/

// Double link
struct Link
{
	TYPE value;
	struct Link* next;
	struct Link* prev;
};

// Double linked list with front and back sentinels
struct LinkedList
{
	int size;
	struct Link* frontSentinel;
	struct Link* backSentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinels' next and prev should point to eachother or NULL
 * as appropriate.
 */
static void init(struct LinkedList* list) {//written by me
	 list->frontSentinel = malloc(sizeof(struct Link));
	 list->backSentinel = malloc(sizeof(struct Link));
	 assert(list->frontSentinel != 0 && list->backSentinel != 0);
	 list->frontSentinel->next = list->backSentinel;
	 list->frontSentinel->prev = 0;
	 list->backSentinel->prev = list->frontSentinel;
	 list->backSentinel->next = 0;
}

/**
 * Adds a new link with the given value before the given link and
 * increments the list's size.
 */
static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE value)
{//written by me
	assert(link != 0);
	struct Link* newLink = malloc(sizeof(struct Link));
	newLink->value = value;
	newLink->prev = link->prev;
	newLink->next = link;
	link->prev->next = newLink;
	link->prev = newLink;
	list->size++;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct LinkedList* list, struct Link* link)
{//written by me
	link->next->prev = link->prev;
	link->prev->next = link->next;
	free(link);
	list->size--;
	
}

/**
 * Allocates and initializes a list.
 */
struct LinkedList* linkedListCreate()
{
	struct LinkedList* newDeque = malloc(sizeof(struct LinkedList));
	init(newDeque);
	return newDeque;
}

/**
 * Deallocates every link in the list including the sentinels,
 * and frees the list itself.
 */
void linkedListDestroy(struct LinkedList* list)
{
	while (!linkedListIsEmpty(list))
	{
		linkedListRemoveFront(list);
	}
	free(list->frontSentinel);
	free(list->backSentinel);
	free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void linkedListAddFront(struct LinkedList* list, TYPE value)
{//written by me
	struct Link* newLink = malloc(sizeof(struct Link));
	newLink->value = value;
	newLink->next = list->frontSentinel->next;
	newLink->prev = list->frontSentinel;
	list->frontSentinel->next->prev = newLink;
	list->frontSentinel->next = newLink;
	list->size++;

}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void linkedListAddBack(struct LinkedList* list, TYPE value)
{//written by me
	struct Link* newLink = malloc(sizeof(struct Link));
	newLink->value = value;
	newLink->prev = list->backSentinel->prev;
	newLink->next = list->backSentinel;
	list->backSentinel->prev->next = newLink;
	list->backSentinel->prev = newLink;
	list->size++;
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE linkedListFront(struct LinkedList* list)
{//written by me
	return list->frontSentinel->next->value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE linkedListBack(struct LinkedList* list)
{//written by me
	return list->backSentinel->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void linkedListRemoveFront(struct LinkedList* list)
{//written by me
	list->frontSentinel->next = list->frontSentinel->next->next;
	free(list->frontSentinel->next->prev);
	list->frontSentinel->next->prev = list->frontSentinel;
	list->size--;
}

/**
 * Removes the link at the back of the deque.
 */
void linkedListRemoveBack(struct LinkedList* list)
{//written by me
	list->backSentinel->prev = list->backSentinel->prev->prev;
	free(list->backSentinel->prev->next);
	list->backSentinel->prev->next = list->backSentinel;
	list->size--;
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int linkedListIsEmpty(struct LinkedList* list)
{//written by me
	if (list->size > 0)
		return 1;
	else
		return 0;
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void linkedListPrint(struct LinkedList* list)
{
	struct Link* iterator = list->frontSentinel->next;
	while (iterator != list->backSentinel)
	{
		printf("%d\n", iterator->value);
		iterator = iterator->next;
	}
}

/**
 * Adds a link with the given value to the bag.
 */
void linkedListAdd(struct LinkedList* list, TYPE value)
{
	linkedListAddFront(list, value);
}

/**
 * Returns 1 if a link with the value is in the bag and 0 otherwise.
 */
int linkedListContains(struct LinkedList* list, TYPE value)
{
	assert(list != 0);
	assert(!linkedListIsEmpty(list));
	struct Link* current = list->frontSentinel->next;

	while (current != list->backSentinel)
	{
		if(current->value == value)
		{
			return 1;
		}
		current = current->next;
	}

	return 0;

}

/**
 * Removes the first occurrence of a link with the given value.
 */
void linkedListRemove(struct LinkedList* list, TYPE value)
{
	assert(list != 0);
	assert(!linkedListIsEmpty(list));

	struct Link* current = list->frontSentinel->next;

	while ((current != list->backSentinel))
	{
		if(current->value == value)
		{
			removeLink(list, current);
			break;
		}
		current = current->next;
	}

}

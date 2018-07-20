#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circularList.h"
/*
Connor Shields
2/5/18
Assignment 3
This is the implementation of the circular list ADT
*/

// Double link
struct Link
{
	TYPE value;
	struct Link * next;
	struct Link * prev;
};

struct CircularList
{
	int size;
	struct Link* sentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinel's next and prev should point to the sentinel itself.
 */
static void init(struct CircularList* list)
{//written by me
	list->sentinel = malloc(sizeof(struct Link));
	list->size = 0;
	list->sentinel->next = list->sentinel;
	list->sentinel->prev = list->sentinel;
}

/**
 * Creates a link with the given value and NULL next and prev pointers.
 */
static struct Link* createLink(TYPE value)
{//written by me
	struct Link* newLink = malloc(sizeof(struct Link));
	newLink->value = value;
	newLink->next = NULL;
	newLink->prev = NULL;
	return newLink;
}

/**
 * Adds a new link with the given value after the given link and
 * increments the list's size.
 */
static void addLinkAfter(struct CircularList* list, struct Link* link, TYPE value)
{//written by me
	struct Link* newLink = createLink(value);
	link->next->prev = newLink;
	newLink->next = link->next;
	link->next = newLink;
	newLink->prev = link;
	list->size++;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct CircularList* list, struct Link* link)
{//written by me
	link->prev->next = link->next;
	link->next->prev = link->prev;
	free(link);
	list->size--;
}

/**
 * Allocates and initializes a list.
 */
struct CircularList* circularListCreate()
{
	struct CircularList* list = malloc(sizeof(struct CircularList));
	init(list);
	return list;
}

/**
 * Deallocates every link in the list and frees the list pointer.
 */
void circularListDestroy(struct CircularList* list)
{//written by me
	struct Link* current = list->sentinel->next->next;
	while (current != list->sentinel)
	{
		free(current->prev);
		current = current->next;
	}
	free(current->prev);
	free(current);
	free(list);

}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void circularListAddFront(struct CircularList* list, TYPE value)
{//written by me
	addLinkAfter(list, list->sentinel, value);
	/*struct Link* newLink = malloc(sizeof(struct Link));
	newLink->next = list->sentinel->next;
	newLink->prev = list->sentinel;
	newLink->value = value;
	list->sentinel->next = newLink;
	newLink->next->prev = newLink;
	list->size++;*/
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void circularListAddBack(struct CircularList* list, TYPE value)
{//written by me
	addLinkAfter(list, list->sentinel->prev, value);
	/*struct Link* newLink = malloc(sizeof(struct Link));
	newLink->prev = list->sentinel->prev;
	newLink->next = list->sentinel;
	newLink->value = value;
	list->sentinel->prev = newLink;
	newLink->prev->next = newLink;
	list->size++;*/
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE circularListFront(struct CircularList* list)
{//written by me
	return list->sentinel->next->value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE circularListBack(struct CircularList* list)
{
	return list->sentinel->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void circularListRemoveFront(struct CircularList* list)
{//written by me
	list->sentinel->next = list->sentinel->next->next;
	free(list->sentinel->next->prev);
	list->sentinel->next->prev = list->sentinel;

}

/**
 * Removes the link at the back of the deque.
 */
void circularListRemoveBack(struct CircularList* list)
{//written by me
	list->sentinel->prev = list->sentinel->prev->prev;
	free(list->sentinel->prev->next);
	list->sentinel->prev->next = list->sentinel;
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int circularListIsEmpty(struct CircularList* list)
{
	if (list->size > 0)
		return 0;
	else
		return 1;
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void circularListPrint(struct CircularList* list)
{
	struct Link* current = list->sentinel->next;
	while (current != list->sentinel)
	{
		printf("%g\n", current->value);
		current = current->next;
	}
}

/**
 * Reverses the deque.
 */
void circularListReverse(struct CircularList* list)
{//written by me
	struct Link* current = list->sentinel->next;
	struct Link* temp;
	while (current != list->sentinel)
	{
		temp = current->prev;
		current->prev = current->next;
		current->next = temp;
		current = current->prev;
	}
	temp = list->sentinel->next;
	list->sentinel->next = list->sentinel->prev;
	list->sentinel->prev = temp;

}

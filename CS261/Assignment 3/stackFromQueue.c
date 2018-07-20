/*
* This is the file in which you'll write the functions required to implement
* a stack using two queues.  Make sure to add your name and @oregonstate.edu
* email address below:
*
* Name: Connor Shields
* Email: shielcond@oregonstate.edu
* 2/5/18
* Description:
* this is the implementation of the queue and
* stack from queue data structure
*/

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#define TYPE int

struct link
{
	TYPE value;
	struct link* next;
};
struct listQueue
{
	struct link* firstLink;
	struct link* lastLink;
};
/*
allocate memory for the first link (which is also the last link)
set the next value to NULL
*/
void listQueueInit(struct listQueue *q) {
	struct link *lnk = (struct link *) malloc(sizeof(struct link));
	assert(lnk != 0); /* lnk is the sentinel */
	lnk->next = 0;
	q->firstLink = q->lastLink = lnk;
}
struct listQueue* listQueueCreate()
{
	struct listQueue* newQueue = malloc(sizeof(struct listQueue));
	listQueueInit(newQueue);
	return newQueue;
}
/*
allocate memory for a new link
set the value of the new link to e
make the new link point to the second link
make the current last link point to the new link
set the new link equal to the last link
*/
void listQueueAddBack(struct listQueue *q, TYPE e) {

	struct link *newlink = malloc(sizeof(struct link));
	assert(newlink != 0);
	newlink->next = 0;
	newlink->value = e;
	q->lastLink->next = newlink;
	q->lastLink = newlink;
}
/*
check if the queue is empty
*/
int listQueueIsEmpty(struct listQueue *q) {

	if ((!q->firstLink->value) && (!q->lastLink->value))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*
return the front of the queue
*/
TYPE listQueueFront(struct listQueue *q) {

	assert(!listQueueIsEmpty(q));
	return q->firstLink->next->value;
}
/*
set templink equal to the link to be removed.
make make firstlink point to the link one after
the one to be removed.
free the link pointed to by templink
*/
void listQueueRemoveFront(struct listQueue *q) {

	assert(!listQueueIsEmpty(q));
	struct link* templink = q->firstLink->next;
	q->firstLink->next = q->firstLink->next->next;
	free(templink);
}

/*
linked list implementations
*/
/*
use the queue struct to initialize the first
link of the linked list
*/
void linkedListStackInit(struct listQueue * s)
{
	s->firstLink = 0;
}
/*
use the queue method to check for emptiness in the stack
*/
int linkedListStackIsEmpty(struct listQueue* s)
{
	return listQueueIsEmpty(s);
}
/*
ensure linkedList is not empty
create a temp pointer to the current first link
reassign the top of the stack to the next link
free the memory for the link being removed
*/
void linkedListStackPop(struct listQueue *s)
{
	listQueueRemoveFront(s);
}
/*
pop every link off the stack
free the stack
*/
void linkedListStackFree(struct listQueue *s)
{
	while (listQueueIsEmpty(s))
		listQueueRemoveFront(s);
	free(s);
}
/*
allocate memory for a new link
set the new link value equal to d
make new link point to the first link
assign newLink as the first link
*/
void linkedListStackPush(struct listQueue *s, TYPE d) {
	struct link* newLink = (struct link*)malloc(sizeof(struct link));
	newLink->value = d;
	assert(newLink != 0);
	newLink->next = s->firstLink;
	s->firstLink = newLink;
}
//return the top of the stack
TYPE linkedListStackTop(struct listQueue *s) {
	assert(!linkedListStackIsEmpty(s));
	return s->firstLink->value;
}

/*
int main()
{
	struct listQueue* queueTest = listQueueCreate();
	printf("%d\n", listQueueIsEmpty(queueTest));
	listQueueAddBack(queueTest, 1);
	listQueueAddBack(queueTest, 2);
	listQueueAddBack(queueTest, 3);
	listQueueAddBack(queueTest, 4);
	printf("%d\n", listQueueFront(queueTest));
	listQueueRemoveFront(queueTest);
	printf("%d\n", listQueueFront(queueTest));
	linkedListStackFree(queueTest);
	free(queueTest);
	return 0;
}*/
#include "circularList.h"
#include <stdio.h>

int main()
{	
	struct CircularList* deque = circularListCreate(); 
	circularListAddBack(deque, (TYPE)1);
	circularListAddBack(deque, (TYPE)2);
	circularListAddBack(deque, (TYPE)3);
	circularListAddFront(deque, (TYPE)4);
	circularListAddFront(deque, (TYPE)5);
	circularListAddFront(deque, (TYPE)6);
	circularListPrint(deque);
	//6 5 4 1 2 3
	printf("%g\n", circularListFront(deque));
	//6
	printf("%g\n", circularListBack(deque));
	//3
	
	circularListRemoveFront(deque);
	circularListRemoveBack(deque);
	circularListPrint(deque);
	//5 4 1 2
	
	circularListReverse(deque);
	circularListPrint(deque);
	//2 1 4 5
	
	circularListDestroy(deque);
	
	return 0;
}

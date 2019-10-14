/*************************************************************************
File name:  pqueue.c
Author:     Damon Holland
Date:       Oct 10, 2019
Class:      CS300
Assignment: GenericDynamicPriorityQ
Purpose:    This file implements the functions for the Priority Queue
*************************************************************************/


#include "stdio.h"
#include "../include/pqueue.h"

#define EMPTY_PQ 0

char gszPQErrors[NUMBER_OF_LIST_ERRORS][MAX_ERROR_LIST_CHARS];

/*************************************************************************
 Function: 	 	processError

 Description: Process the error code passed to this routine

 Parameters:	pszFunctionName - function causing the error
 	 	 	 	 	 	 	errorCode - identifies the stack error

 Returned:	 	None
 ************************************************************************/
static void processError (const char *pszFunctionName, int errorCode)
{
	printf ("Function: %s %s \n ", pszFunctionName,
					 gszPQErrors [errorCode]);
	exit (EXIT_FAILURE);
}


//************************************************************************
//										Allocation and Deallocation
//************************************************************************
void pqueueCreate (PriorityQueuePtr psQueue /*, 	cmpFunction cmpFunct */)
{
	lstCreate (&psQueue->sTheList);

	//Error Checking
	if ((NULL != psQueue) && !pqueueIsEmpty (psQueue))
	{
		processError ("pqueueCreate", ERROR_NO_PQ_CREATE);
	}

	return;
}

void pqueueTerminate (PriorityQueuePtr psQueue)
{
	lstTerminate (&psQueue->sTheList);
	return;
}

void pqueueLoadErrorMessages ()
{
	lstLoadErrorMessages ();
	LOAD_PQ_ERRORS;
	return;
}

//************************************************************************
//									Checking number of elements in priority queue
//************************************************************************
int pqueueSize (const PriorityQueuePtr psQueue)
{
	//Error Checking
	if (NULL == psQueue)
	{
		processError ("pqueueSize", ERROR_INVALID_PQ);
	}

	return (lstSize (&psQueue->sTheList));
}

bool pqueueIsEmpty (const PriorityQueuePtr psQueue)
{
	//Error Checking
	if (NULL == psQueue)
	{
		processError ("pqueueIsEmpty", ERROR_INVALID_PQ);
	}

	return (EMPTY_PQ == pqueueSize (psQueue));
}

//************************************************************************
//									Inserting and retrieving values
//************************************************************************
void pqueueEnqueue (PriorityQueuePtr psQueue, const void *pBuffer,
										int size, int priority)
{
	PriorityQueueElement newPQElement;
	PriorityQueueElementPtr currentPQElement;

	//Error Checking
	if (NULL == psQueue)
	{
		processError ("pqueueEnqueue", ERROR_INVALID_PQ);
	}
	if (NULL == pBuffer)
	{
		processError ("pqueueEnqueue", ERROR_NULL_PQ_PTR);
	}

	//Create an element and fill with the given information
	newPQElement.priority = priority;
	newPQElement.pData = (void*)malloc (size);
	memcpy (newPQElement.pData, pBuffer, size);

	//Now add the element to the list
	//If the queue is empty, just add the element as the first
	if (pqueueIsEmpty (psQueue))
	{
		lstInsertAfter (&psQueue->sTheList, &newPQElement,
										 sizeof (newPQElement));
	}
	else
	{
		//If the queue is not empty, move the current element in the list to
		//the first element with a lower priority than the data being added
		//or to the end of the list, whichever is first
		lstFirst (&psQueue->sTheList);
		currentPQElement = psQueue->sTheList.psCurrent->pData;
		while ((currentPQElement->priority <= newPQElement.priority) &&
						(NULL != psQueue->sTheList.psCurrent->psNext))
		{
			lstNext (&psQueue->sTheList);
			currentPQElement = psQueue->sTheList.psCurrent->pData;
		}

		//Then insert the new element before the current element
		lstInsertBefore (&psQueue->sTheList, &newPQElement,
										 sizeof (newPQElement));
	}

	return;
}

//void *pqueueDequeue (PriorityQueuePtr psQueue, void *pBuffer,
//														int size, int  *pPriority);

//************************************************************************
//													Peek Operations
//************************************************************************
//void *pqueuePeek (PriorityQueuePtr psQueue, void *pBuffer, int size,
//								 int *priority);

//void pqueueChangePriority (PriorityQueuePtr psQueue,
//																	int change);

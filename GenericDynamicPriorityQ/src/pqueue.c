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
void pqueueCreate (PriorityQueuePtr psQueue)
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
	PriorityQueueElementPtr currentElement;

	if (!pqueueIsEmpty (psQueue))
	{
		lstFirst (&psQueue->sTheList);
		currentElement = psQueue->sTheList.psCurrent->pData;
		free (currentElement->pData);
		while (NULL != psQueue->sTheList.psCurrent->psNext)
		{
			lstNext (&psQueue->sTheList);
			currentElement = psQueue->sTheList.psCurrent->pData;
			free (currentElement->pData);
		}

		lstTerminate (&psQueue->sTheList);
	}

	//Error Checking
	if (!pqueueIsEmpty (psQueue))
	{
		processError ("pqueueTerminate", ERROR_NO_PQ_TERMINATE);
	}

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
	PriorityQueueElement currentPQElement;

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
		lstPeek (&psQueue->sTheList, &currentPQElement,
						 sizeof (PriorityQueueElement));
		while ((currentPQElement.priority <= newPQElement.priority) &&
						(NULL != psQueue->sTheList.psCurrent->psNext))
		{
			lstNext (&psQueue->sTheList);
			lstPeek (&psQueue->sTheList, &currentPQElement,
							 sizeof (PriorityQueueElement));
		}
		//If the list reached the end before finding a lower priority,
		//add the element to the end
		if ((NULL == psQueue->sTheList.psCurrent->psNext) &&
				(currentPQElement.priority <= newPQElement.priority))
		{
			lstInsertAfter (&psQueue->sTheList, &newPQElement,
											sizeof (newPQElement));
		}
		//else, add it before the element with the lower priority
		else
		{
			lstInsertBefore (&psQueue->sTheList, &newPQElement,
											 sizeof (newPQElement));
		}
	}

	return;
}

void *pqueueDequeue (PriorityQueuePtr psQueue, void *pBuffer,
														int size, int  *pPriority)
{
	PriorityQueueElement tempBuffer;

	//Error Checking
	if (NULL == psQueue)
	{
		processError ("pqueueDequeue", ERROR_INVALID_PQ);
	}
	if (NULL == pBuffer)
	{
		processError ("pqueueDequeue", ERROR_NULL_PQ_PTR);
	}
	if (pqueueIsEmpty (psQueue))
	{
		processError ("pqueueDequeue", ERROR_EMPTY_PQ);
	}

	pqueuePeek (psQueue, pBuffer, size, pPriority);
	lstDeleteCurrent (&psQueue->sTheList, &tempBuffer,
										sizeof (PriorityQueueElement));

	return pBuffer;
}

//************************************************************************
//													Peek Operations
//************************************************************************
void *pqueuePeek (PriorityQueuePtr psQueue, void *pBuffer, int size,
								 int *priority)
{
	PriorityQueueElement firstPQElement;

	//Error Checking
	if (NULL == psQueue)
	{
		processError ("pqueuePeek", ERROR_INVALID_PQ);
	}
	if (NULL == pBuffer)
	{
		processError ("pqueuePeek", ERROR_NULL_PQ_PTR);
	}
	if (pqueueIsEmpty (psQueue))
	{
		processError ("pqueuePeek", ERROR_EMPTY_PQ);
	}

	//Set firstElement to the first element in the queue
	lstFirst (&psQueue->sTheList);
	lstPeek (&psQueue->sTheList, &firstPQElement,
					 sizeof (PriorityQueueElement));

	//Set the priority and buffer to the values in the element to
	//be returned outside of this functions
	*priority = firstPQElement.priority;
	memcpy (pBuffer, firstPQElement.pData, size);

	return pBuffer;
}

void pqueueChangePriority (PriorityQueuePtr psQueue,
																	int change)
{
	PriorityQueueElement tempPQElement;

	//Error Checking
	if (NULL == psQueue)
	{
		processError ("pqueueChangePriority", ERROR_INVALID_PQ);
	}

	if (!lstIsEmpty (&psQueue->sTheList))
	{
		lstFirst (&psQueue->sTheList);
		lstPeek (&psQueue->sTheList, &tempPQElement,
						 sizeof (PriorityQueueElement));
		tempPQElement.priority += change;
		lstUpdateCurrent (&psQueue->sTheList, &tempPQElement,
											sizeof (PriorityQueueElement));

		while (lstHasNext (&psQueue->sTheList))
		{
			lstNext (&psQueue->sTheList);
			lstPeek (&psQueue->sTheList, &tempPQElement,
							 sizeof (PriorityQueueElement));
			tempPQElement.priority += change;
			lstUpdateCurrent (&psQueue->sTheList, &tempPQElement,
												sizeof (PriorityQueueElement));
		}
	}


	return;
}

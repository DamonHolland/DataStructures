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

 Parameters:	pszFunctionName - string containing the name of the function
  															causing the error
 	 	 	 	 	 	 	errorCode - an integer that identifies the queue error

 Returned:	 	None
 ************************************************************************/
static void processError (const char *pszFunctionName, int errorCode)
{
	printf ("Function: %s %s \n ", pszFunctionName, gszPQErrors[errorCode]);
	exit (EXIT_FAILURE);
}

//************************************************************************
//										Allocation and Deallocation
//************************************************************************
/*************************************************************************
 Function: 	 	pqueueCreate

 Description: Creates and initializes the queue

 Parameters:	psQueue - pointer to the priority queue to create

 Returned:	 	None
 ************************************************************************/
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

/*************************************************************************
 Function: 	 	pqueueTerminate

 Description: Terminates and frees memory of the queue

 Parameters:	psQueue - pointer to the priority queue to terminate

 Returned:	 	None
 ************************************************************************/
void pqueueTerminate (PriorityQueuePtr psQueue)
{
	PriorityQueueElement sCurrentElement;

	if (!pqueueIsEmpty (psQueue))
	{
		lstFirst (&psQueue->sTheList);
		lstPeek (&psQueue->sTheList, &sCurrentElement,
						 sizeof (PriorityQueueElement));
		free (sCurrentElement.pData);
		while (lstHasNext (&psQueue->sTheList))
		{
			lstNext (&psQueue->sTheList);
			lstPeek (&psQueue->sTheList, &sCurrentElement,
							 sizeof (PriorityQueueElement));
			free (sCurrentElement.pData);
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

/*************************************************************************
 Function: 	 	pqueueLoadErrorMessages

 Description: Loads the error message strings for other functions to use

 Parameters:	none

 Returned:	 	None
 ************************************************************************/
void pqueueLoadErrorMessages ()
{
	lstLoadErrorMessages ();
	LOAD_PQ_ERRORS;
	return;
}

//************************************************************************
//									Checking number of elements in priority queue
//************************************************************************
/*************************************************************************
 Function: 	 	pqueueSize

 Description: Returns the size of the queue

 Parameters:	psQueue - pointer to the priority queue to retrieve the size
  											of

 Returned:	 	int - an integer which contains the number of elements in
 	 	 	 	 	 	 	 	 	 	the queue
 ************************************************************************/
int pqueueSize (const PriorityQueuePtr psQueue)
{
	//Error Checking
	if (NULL == psQueue)
	{
		processError ("pqueueSize", ERROR_INVALID_PQ);
	}

	return (lstSize (&psQueue->sTheList));
}

/*************************************************************************
 Function: 	 	pqueueIsEmpty

 Description: Returns whether or not the queue is empty

 Parameters:	psQueue - pointer to the priority queue to check is empty
  											or not

 Returned:	 	bool - a boolean which contains true if the queue is empty
 	 	 	 	 	 	 	 	 	 	 or contains false if the queue is not empty
 ************************************************************************/
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
/*************************************************************************
 Function: 	 	pqueueEnqueue

 Description: Inserts data into the priority queue into the correct
 	 	 	 	 	 	 	position. A lower integer priority will be placed at the
 	 	 	 	 	 	 	front of the queue. If the priorities are equal, the newest
 	 	 	 	 	 	 	added data is added behind of those with equal priority

 Parameters:	psQueue - pointer to the priority queue to add data
 	 	 	 	 	 	 	pBuffer - pointer to the data you would like to add to the
 	 	 	 	 	 	 	 	 	 	 	 	queue
 	 	 	 	 	 	 	size - integer that contains the size in bytes of the data
 	 	 	 	 	 	 				 you are adding
 	 	 	 	 	 	 	priority - integer that contains the priority of the data
 	 	 	 	 	 	 	 	 	 	 	 	 you are adding. 0 is the highest priority

 Returned:	 	None
 ************************************************************************/
void pqueueEnqueue (PriorityQueuePtr psQueue, const void *pBuffer,
										int size, int priority)
{
	PriorityQueueElement sNewPQElement;
	PriorityQueueElement sCurrentPQElement;

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
	sNewPQElement.priority = priority;
	sNewPQElement.pData = (void*)malloc (size);
	memcpy (sNewPQElement.pData, pBuffer, size);

	//Now add the element to the list
	//If the queue is empty, just add the element as the first
	if (pqueueIsEmpty (psQueue))
	{
		lstInsertAfter (&psQueue->sTheList, &sNewPQElement,
									  sizeof (sNewPQElement));
	}
	else
	{
		//If the queue is not empty, move the current element in the list to
		//the first element with a lower priority than the data being added
		//or to the end of the list, whichever is first
		lstFirst (&psQueue->sTheList);
		lstPeek (&psQueue->sTheList, &sCurrentPQElement,
						 sizeof (PriorityQueueElement));
		while ((sCurrentPQElement.priority <= sNewPQElement.priority) &&
						lstHasNext (&psQueue->sTheList))
		{
			lstNext (&psQueue->sTheList);
			lstPeek (&psQueue->sTheList, &sCurrentPQElement,
							 sizeof (PriorityQueueElement));
		}
		//If the list reached the end before finding a lower priority,
		//add the element to the end
		if (!lstHasNext (&psQueue->sTheList) &&
				(sCurrentPQElement.priority <= sNewPQElement.priority))
		{
			lstInsertAfter (&psQueue->sTheList, &sNewPQElement,
											sizeof (sNewPQElement));
		}
		//else, add it before the element with the lower priority
		else
		{
			lstInsertBefore (&psQueue->sTheList, &sNewPQElement,
											 sizeof (sNewPQElement));
		}
	}

	return;
}

/*************************************************************************
 Function: 	 	pqueueDequeue

 Description: Removes the data from the front of the queue and returns the
 	 	 	 	 	 	  data and priority

 Parameters:	psQueue - pointer to the priority queue to remove data from
 	 	 	 	 	 	 	pBuffer - pointer to the buffer that will store the removed
 	 	 	 	 	 	 					  data
 	 	 	 	 	 	 	size - integer that contains the size in bytes of the data
 	 	 	 	 	 	 				 you are removing
 	 	 	 	 	 	 	priority - pointer to the integer that will store the
 	 	 	 	 	 	 	 	 	 	 	 	 priority of the data being removed

 Returned:	 	void* - the pointer to the buffer where the removed data is
 	 	 	 	 	 	 	 	 	 	 	stored
 ************************************************************************/
void *pqueueDequeue (PriorityQueuePtr psQueue, void *pBuffer,
														int size, int  *pPriority)
{
	PriorityQueueElement sTempElement;

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
	//Peek the data to return outside of function
	pqueuePeek (psQueue, pBuffer, size, pPriority);
	//Since Peek sets current to the first element, you can delete current
	lstDeleteCurrent (&psQueue->sTheList, &sTempElement,
										sizeof (PriorityQueueElement));
	//sTempElement holds the element on the heap, so you can free the data
	free (sTempElement.pData);

	return pBuffer;
}

//************************************************************************
//													Peek Operations
//************************************************************************
/*************************************************************************
 Function: 	 	pqueuePeek

 Description: Peeks the data from the front of the priority queue

 Parameters:	psQueue - pointer to the priority queue to peek the data of
 	 	 	 	 	 	 	pBuffer - pointer to the buffer that will store the peeked
 	 	 	 	 	 	 	 	 	 	 	  data
 	 	 	 	 	 	 	size - integer that contains the size in bytes of the data
 	 	 	 	 	 	 				 you are peeking
 	 	 	 	 	 	 	priority - pointer to the integer that will store the
 	 	 	 	 	 	 						 priority of the peeked data

 Returned:	 	void* - the pointer to the buffer where the peeked data is
 	 	 	 	 	 	 	 	 	 	 	stored
 ************************************************************************/
void *pqueuePeek (PriorityQueuePtr psQueue, void *pBuffer, int size,
								  int *priority)
{
	PriorityQueueElement sFirstPQElement;

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
	lstPeek (&psQueue->sTheList, &sFirstPQElement,
					 sizeof (PriorityQueueElement));

	//Set the priority and buffer to the values in the element to
	//be returned outside of this functions
	*priority = sFirstPQElement.priority;
	memcpy (pBuffer, sFirstPQElement.pData, size);

	return pBuffer;
}

/*************************************************************************
 Function: 	 	pqueueChangePriority

 Description: Changes the priority of all of the data in the priority
 	 	 	 	 	 	  queue by a specified amount

 Parameters:	psQueue - pointer to the priority queue to change the
  										  priority of the data within
 	 	 	 	 	 	 	change - integer that contains the amount you would like to
 	 	 	 	 	 	 				   change the priority of the data in the queue by

 Returned:	 	None
 ************************************************************************/
void pqueueChangePriority (PriorityQueuePtr psQueue, int change)
{
	PriorityQueueElement sTempPQElement;

	//Error Checking
	if (NULL == psQueue)
	{
		processError ("pqueueChangePriority", ERROR_INVALID_PQ);
	}

	//Only do anything if the queue is not empty
	if (!lstIsEmpty (&psQueue->sTheList))
	{
		//Since the queue is not empty, we know there is at least a first
		//element. So, update the first element
		lstFirst (&psQueue->sTheList);
		lstPeek (&psQueue->sTheList, &sTempPQElement,
						 sizeof (PriorityQueueElement));
		sTempPQElement.priority += change;
		lstUpdateCurrent (&psQueue->sTheList, &sTempPQElement,
											sizeof (PriorityQueueElement));
		//Then, keep moving through the queue until the end, updating all of
		//the elements along the way
		while (lstHasNext (&psQueue->sTheList))
		{
			lstNext (&psQueue->sTheList);
			lstPeek (&psQueue->sTheList, &sTempPQElement,
							 sizeof (PriorityQueueElement));
			sTempPQElement.priority += change;
			lstUpdateCurrent (&psQueue->sTheList, &sTempPQElement,
												sizeof (PriorityQueueElement));
		}
	}

	return;
}

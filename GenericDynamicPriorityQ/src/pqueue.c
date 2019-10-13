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

//void pqueueTerminate (PriorityQueuePtr psQueue);

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
//void pqueueEnqueue (PriorityQueuePtr psQueue, const void *pBuffer,
//										int size, int priority);

//void *pqueueDequeue (PriorityQueuePtr psQueue, void *pBuffer,
//														int size, int  *pPriority);

//************************************************************************
//													Peek Operations
//************************************************************************
//void *pqueuePeek (PriorityQueuePtr psQueue, void *pBuffer, int size,
//								 int *priority);

//void pqueueChangePriority (PriorityQueuePtr psQueue,
//																	int change);

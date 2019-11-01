/*************************************************************************
File name:  queue.c
Author:     Damon Holland
Date:       Oct 20, 2019
Class:      CS300
Assignment: Airport
Purpose:    Implement the functions for the queue
*************************************************************************/

#include "stdio.h"
#include "../include/queue.h"

#define EMPTY_Q 0
#define SAME_PRIORITY 0

char gszQErrors[NUMBER_OF_Q_ERRORS][MAX_ERROR_Q_CHARS];

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
	printf ("Function: %s %s \n ", pszFunctionName, gszQErrors[errorCode]);
	exit (EXIT_FAILURE);
}

/**************************************************************************
*										Allocation and Deallocation
**************************************************************************/
/*************************************************************************
 Function: 	 	queueCreate

 Description: Creates and initializes the queue

 Parameters:	psQueue - pointer to the queue to create

 Returned:	 	None
 ************************************************************************/
extern void queueCreate (QueuePtr psQueue)
{
	//Error Checking
	if (NULL == psQueue)
	{
		processError ("queueCreate", ERROR_INVALID_Q);
	}

	pqueueCreate (&psQueue->sTheQueue);

	//Error Checking
	if ((NULL != psQueue) && !queueIsEmpty (psQueue))
	{
		processError ("queueCreate", ERROR_NO_Q_CREATE);
	}

	return;
}

/*************************************************************************
 Function: 	 	queueTerminate

 Description: Terminates and frees memory of the queue

 Parameters:	psQueue - pointer to the queue to terminate

 Returned:	 	None
 ************************************************************************/
extern void queueTerminate (QueuePtr psQueue)
{
	//Error Checking
	if (NULL == psQueue)
	{
		processError ("queueTerminate", ERROR_INVALID_Q);
	}

	pqueueTerminate (&psQueue->sTheQueue);

	//Error Checking
	if (!queueIsEmpty (psQueue))
	{
		processError ("queueTerminate", ERROR_NO_Q_TERMINATE);
	}

	return;
}

/*************************************************************************
 Function: 	 	queueLoadErrorMessages

 Description: Loads the error message strings for other functions to use

 Parameters:	none

 Returned:	 	None
 ************************************************************************/
extern void queueLoadErrorMessages ()
{
	pqueueLoadErrorMessages ();
	LOAD_Q_ERRORS
	return;
}

/**************************************************************************
*									Checking number of elements in queue
**************************************************************************/
/*************************************************************************
 Function: 	 	queueSize

 Description: Returns the size of the queue

 Parameters:	psQueue - pointer to the queue to retrieve the size of

 Returned:	 	int - an integer which contains the number of elements in
 	 	 	 	 	 	 	 	 	 	the queue
 ************************************************************************/
extern int queueSize (const QueuePtr psQueue)
{
	//Error Checking
	if (NULL == psQueue)
	{
		processError ("queueSize", ERROR_INVALID_Q);
	}

	return pqueueSize (&psQueue->sTheQueue);
}

/*************************************************************************
 Function: 	 	queueIsEmpty

 Description: Returns whether or not the queue is empty

 Parameters:	psQueue - pointer to the queue to check is empty or not

 Returned:	 	bool - a boolean which contains true if the queue is empty
 	 	 	 	 	 	 	 	 	 	 or contains false if the queue is not empty
 ************************************************************************/
extern bool queueIsEmpty (const QueuePtr psQueue)
{
	//Error Checking
	if (NULL == psQueue)
	{
		processError ("queueIsEmpty", ERROR_INVALID_Q);
	}

	return (EMPTY_Q == queueSize (psQueue));
}

/**************************************************************************
*									Inserting and retrieving values
**************************************************************************/
/*************************************************************************
 Function: 	 	queueEnqueue

 Description: Inserts data into the end of the queue.

 Parameters:	psQueue - pointer to the queue to add data
 	 	 	 	 	 	 	pBuffer - pointer to the data you would like to add to the
 	 	 	 	 	 	 	 	 	 	 	 	queue
 	 	 	 	 	 	 	size - integer that contains the size in bytes of the data
 	 	 	 	 	 	 				 you are adding

 Returned:	 	None
 ************************************************************************/
extern void queueEnqueue (QueuePtr psQueue, const void *pBuffer, int size)
{
	//Error Checking
	if (NULL == psQueue)
	{
		processError ("queueEnqueue", ERROR_INVALID_Q);
	}
	if (NULL == pBuffer)
	{
		processError ("queueEnqueue", ERROR_NULL_Q_PTR);
	}

	pqueueEnqueue (&psQueue->sTheQueue, pBuffer, size, SAME_PRIORITY);

	return;
}

/*************************************************************************
 Function: 	 	queueDequeue

 Description: Removes the data from the front of the queue and returns the
 	 	 	 	 	 	  data

 Parameters:	psQueue - pointer to the queue to remove data from
 	 	 	 	 	 	 	pBuffer - pointer to the buffer that will store the removed
 	 	 	 	 	 	 					  data
 	 	 	 	 	 	 	size - integer that contains the size in bytes of the data
 	 	 	 	 	 	 				 you are removing

 Returned:	 	void* - the pointer to the buffer where the removed data is
 	 	 	 	 	 	 	 	 	 	 	stored
 ************************************************************************/
extern void *queueDequeue (QueuePtr psQueue, void *pBuffer, int size)
{
	int tempPriorityBuffer;

	//Error Checking
	if (NULL == psQueue)
	{
		processError ("queueDequeue", ERROR_INVALID_Q);
	}
	if (NULL == pBuffer)
	{
		processError ("queueDequeue", ERROR_NULL_Q_PTR);
	}
	if (queueIsEmpty (psQueue))
	{
		processError ("queueDequeue", ERROR_EMPTY_Q);
	}

	pqueueDequeue (&psQueue->sTheQueue, pBuffer, size, &tempPriorityBuffer);

	return pBuffer;
}

/**************************************************************************
*													Peek Operations
**************************************************************************/
/*************************************************************************
 Function: 	 	queuePeek

 Description: Peeks the data from the front of the queue

 Parameters:	psQueue - pointer to the queue to peek the data of
 	 	 	 	 	 	 	pBuffer - pointer to the buffer that will store the peeked
 	 	 	 	 	 	 	 	 	 	 	  data
 	 	 	 	 	 	 	size - integer that contains the size in bytes of the data
 	 	 	 	 	 	 				 you are peeking

 Returned:	 	void* - the pointer to the buffer where the peeked data is
 	 	 	 	 	 	 	 	 	 	 	stored
 ************************************************************************/
extern void *queuePeek (QueuePtr psQueue, void *pBuffer, int size)
{
	int tempPriorityBuffer;

	//Error Checking
	if (NULL == psQueue)
	{
		processError ("queuePeek", ERROR_INVALID_Q);
	}
	if (NULL == pBuffer)
	{
		processError ("queuePeek", ERROR_NULL_Q_PTR);
	}
	if (queueIsEmpty (psQueue))
	{
		processError ("queuePeek", ERROR_EMPTY_Q);
	}

	pqueuePeek (&psQueue->sTheQueue, pBuffer, size, &tempPriorityBuffer);

	return pBuffer;
}


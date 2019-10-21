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
extern void queueCreate (QueuePtr psQueue)
{
	pqueueCreate (&psQueue->sTheQueue);

	//Error Checking
	if ((NULL != psQueue) && !queueIsEmpty (psQueue))
	{
		processError ("queueCreate", ERROR_NO_Q_CREATE);
	}

	return;
}


extern void queueTerminate (QueuePtr psQueue)
{
	pqueueTerminate (&psQueue->sTheQueue);

	//Error Checking
	if (!queueIsEmpty (psQueue))
	{
		processError ("queueTerminate", ERROR_NO_Q_TERMINATE);
	}

	return;
}

extern void queueLoadErrorMessages ()
{
	LOAD_Q_ERRORS
	return;
}

/**************************************************************************
*									Checking number of elements in queue
**************************************************************************/
extern int queueSize (const QueuePtr psQueue)
{
	//Error Checking
	if (NULL == psQueue)
	{
		processError ("queueSize", ERROR_INVALID_Q);
	}

	return pqueueSize (&psQueue->sTheQueue);
}

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


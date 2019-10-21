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

char gszQErrors[NUMBER_OF_Q_ERRORS][MAX_ERROR_Q_CHARS];

/**************************************************************************
*										Allocation and Deallocation
**************************************************************************/
extern void queueCreate (QueuePtr psQueue)
{
	return;
}


extern void queueTerminate (QueuePtr psQueue)
{
	return;
}

extern void queueLoadErrorMessages ()
{
	return;
}

/**************************************************************************
*									Checking number of elements in queue
**************************************************************************/
extern int queueSize (const QueuePtr psQueue)
{
	return 0;
}

extern bool queueIsEmpty (const QueuePtr psQueue)
{
	return 0;
}



/**************************************************************************
*									Inserting and retrieving values
**************************************************************************/
extern void queueEnqueue (QueuePtr psQueue, const void *pBuffer, int size)
{
	return;
}

extern void *queueDequeue (QueuePtr psQueue, void *pBuffer, int size)
{
	return pBuffer;
}

/**************************************************************************
*													Peek Operations
**************************************************************************/
extern void *queuePeek (QueuePtr psQueue, void *pBuffer, int size)
{
	return pBuffer;
}


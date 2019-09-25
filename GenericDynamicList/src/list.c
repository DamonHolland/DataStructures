/***************************************************************************
File name:  list.c
Author:     Damon Holland
Date:       Sep 19, 2019
Class:      CS300
Assignment: Generic Dynamic List
Purpose:    
***************************************************************************/

#include "stdio.h"
#include "../include/list.h"

#define EMPTY_LIST 0

char gszListErrors[NUMBER_OF_LIST_ERRORS][MAX_ERROR_LIST_CHARS];

/**************************************************************************
 Function: 	 	processError

 Description: Process the error code passed to this routine

 Parameters:	pszFunctionName - function causing the error
 	 	 	 	 	 	 	errorCode 	    - identifies the stack error

 Returned:	 	None
 *************************************************************************/
static void processError (const char *pszFunctionName, int errorCode)
{
	printf ("Function: %s %s \n ", pszFunctionName,
					 gszListErrors [errorCode]);
	exit (EXIT_FAILURE);
}


//*************************************************************************
// Allocation and Deallocation
//*************************************************************************
/**************************************************************************
 Function: 	 	lstCreate

 Description: Creates the list

 Parameters:	psList - pointer to the list to create

 Returned:	 	None
 *************************************************************************/
void lstCreate (ListPtr psList)
{
	psList->numElements = EMPTY_LIST;
	psList->psCurrent = psList->psFirst = psList->psLast = NULL;

	//Error Checking
	if((NULL == psList) || (EMPTY_LIST != lstSize(psList)) )
	{
				processError("lstCreate", ERROR_NO_LIST_CREATE);
	}

	return;
}

/**************************************************************************
 Function: 	 	lstTerminate

 Description: Terminate the list

 Parameters:	psList              - Pointer to the list to terminate

 Returned:	 	None
 *************************************************************************/
void lstTerminate (ListPtr psList)
{
	//Error Checking
	if(NULL == psList)
	{
		processError("lstTerminate", ERROR_INVALID_LIST);
	}

	//Freeing memory starting from the first element
	psList->psCurrent = psList->psFirst;
	while(NULL != psList->psCurrent)
	{
		ListElement *nextElement = psList->psCurrent->psNext;
		free(psList->psCurrent->pData);
		psList->psCurrent->pData = NULL;
		free(psList->psCurrent);
		psList->psCurrent = nextElement;
		psList->numElements--;
	}

	//Error Checking
	if(EMPTY_LIST != lstSize(psList))
	{
		processError("lstTerminate", ERROR_NO_LIST_TERMINATE);
	}

	return;
}

/**************************************************************************
 Function: 	 	lstLoadErrorMessages

 Description: defines the constant strings that are used for error messages

 Parameters:	none

 Returned:	 	None
 *************************************************************************/
void lstLoadErrorMessages ()
{
	LOAD_LIST_ERRORS;
	return;
}

//*************************************************************************
// Checking number of elements in list
//*************************************************************************
/**************************************************************************
 Function: 	 	lstSize

 Description: retrieves the size of the given list

 Parameters:	psList              - Pointer to the list to return size of

 Returned:	 	int                 - the size of the list
 *************************************************************************/
int lstSize (const ListPtr psList)
{
	//Error Checking
	if(NULL == psList)
	{
		processError("lstSize", ERROR_INVALID_LIST);
	}
	return psList->numElements;
}

/**************************************************************************
 Function: 	 	lstIsEmpty

 Description: Returns if the given list is empty

 Parameters:	psList              - Pointer to the list to check empty

 Returned:	 	bool                - If the list is empty or not
 *************************************************************************/
bool lstIsEmpty (const ListPtr psList)
{
	if(NULL == psList)
	{
		processError("lstIsEmpty", ERROR_INVALID_LIST);
	}
	return (lstSize(psList) == EMPTY_LIST);
}

//*************************************************************************
//												List Testing
//*************************************************************************

//*************************************************************************
//													Peek Operations
//*************************************************************************
/**************************************************************************
 Function: 	 	lstPeek

 Description: Peeks the Data at the current element in the list

 Parameters:	psList              - Pointer to the list to Peek
 	 	 	 	 	 	 	pBuffer             - Pointer to the buffer in which to store
 	 	 	 	 	 	 												the peeked data
 	 	 	 	 	 	 	size								- The byte size of the data

 Returned:	 	void*               - Pointer of the Buffer given
 *************************************************************************/
void *lstPeek (const ListPtr psList, void *pBuffer, int size)
{
	//Error checking
	if(NULL == psList)
	{
		processError("lstPeek", ERROR_INVALID_LIST);
	}
	if(NULL == pBuffer)
	{
		processError("lstPeek", ERROR_NULL_PTR);
	}
	if(lstIsEmpty(psList))
	{
		processError("lstPeek", ERROR_EMPTY_LIST);
	}
	if(NULL == psList->psCurrent)
	{
		processError("lstPeek", ERROR_NO_CURRENT);
	}

	memcpy(pBuffer, psList->psCurrent->pData, size);
	return pBuffer;
}

//*************************************************************************
//							Updating current
//*************************************************************************
/**************************************************************************
 Function: 	 	lstFirst

 Description: Sets the current element to the first element in the list

 Parameters:	psList              - Pointer to the list which you are
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	switching elements

 Returned:	 	None
 *************************************************************************/
void lstFirst (ListPtr psList)
{
	//Error Checking
	if(NULL == psList)
	{
		processError("lstFirst", ERROR_INVALID_LIST);
	}
	if(EMPTY_LIST == lstSize(psList))
	{
		processError("lstFirst", ERROR_EMPTY_LIST);
	}

	psList->psCurrent = psList->psFirst;

	return;
}

/**************************************************************************
 Function: 	 	lstNext

 Description: Sets the current element to the next element in the list

 Parameters:	psList              - Pointer to the list which you are
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	switching elements

 Returned:	 	None
 *************************************************************************/
void lstNext (ListPtr psList)
{
	//Error Checking
	if(NULL == psList)
	{
		processError("lstNext", ERROR_INVALID_LIST);
	}
	if(EMPTY_LIST == lstSize(psList))
	{
		processError("lstNext", ERROR_EMPTY_LIST);
	}
	if(NULL == psList->psCurrent)
	{
		processError("lstNext", ERROR_NO_CURRENT);
	}

		psList->psCurrent = psList->psCurrent->psNext;

	return;
}

//*************************************************************************
//									Insertion, Deletion, and Updating
//*************************************************************************
/**************************************************************************
 Function: 	 	lstInsertAfter

 Description: Inserts an element after the current element in the list

 Parameters:	psList              - Pointer to the list which you are
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	inserting an element
 	 	 	 	 	 	 	pBuffer             - Pointer to the data you are inserting
 	 	 	 	 	 	 	size                - byte size of the data you are inserting

 Returned:	 	None
 *************************************************************************/
void lstInsertAfter (ListPtr psList, const void *pBuffer, int size)
{
	//Error Checking
	if(NULL == psList)
	{
		processError("lstInsertAfter", ERROR_INVALID_LIST);
	}
	if(NULL == pBuffer)
	{
		processError("lstInsertAfter", ERROR_NULL_PTR);
	}

		//If List is Empty, create new element as current, head, and tail
		if(EMPTY_LIST == lstSize(psList))
		{
			//Add the element
			psList->psFirst = (ListElement*)malloc(sizeof(ListElement));
			psList->numElements++;
			psList->psFirst->psNext = NULL;
			psList->psCurrent = psList->psFirst;
			psList->psLast = psList->psFirst;
			//Add the data
			psList->psCurrent->pData = (void*)malloc(size);
			memcpy(psList->psCurrent->pData, pBuffer, size);
		}
		else
		{
			//Check for error
			if(NULL == psList->psCurrent)
			{
				processError("lstInsertAfter", ERROR_NO_CURRENT);
			}
			//If the List is NOT empty, check if the current element is the last
			//element in the list
			if(NULL == psList->psCurrent->psNext)
			{
				//Add a new tail
				psList->psCurrent->psNext =
							(ListElement*)malloc(sizeof(ListElement));
				psList->numElements++;
				psList->psCurrent = psList->psCurrent->psNext;
				psList->psCurrent->psNext = NULL;
				psList->psLast = psList->psCurrent;
				//Add the data
				psList->psCurrent->pData = (void*)malloc(size);
				memcpy(psList->psCurrent->pData, pBuffer, size);
			}else
			{
				//Add between elements
				ListElement *newElement;
				newElement = (ListElement*)malloc(sizeof(ListElement));
				newElement->psNext = psList->psCurrent->psNext;
				psList->psCurrent->psNext = newElement;
				psList->psCurrent = newElement;
				//Add the data
				psList->psCurrent->pData = (void*)malloc(size);
				memcpy(psList->psCurrent->pData, pBuffer, size);
			}
		}
	return;
}

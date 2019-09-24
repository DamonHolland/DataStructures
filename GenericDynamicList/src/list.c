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

char gszListErrors[NUMBER_OF_LIST_ERRORS][MAX_ERROR_LIST_CHARS];

static void processError (const char *pszFunctionName, int errorCode)
{
	printf ("Function: %s %s \n ", pszFunctionName,
					 gszListErrors [errorCode]);
	exit (EXIT_FAILURE);
}

void lstLoadErrorMessages (){
	LOAD_LIST_ERRORS;
	return;
}


void lstCreate (ListPtr psList){
	if(NULL == psList){
		processError("lstCreate", ERROR_NO_LIST_CREATE);
	}
	else{
	psList->numElements = 0;
	psList->psCurrent = psList->psFirst = psList->psLast = NULL;
	}
	return;
}

void lstTerminate (ListPtr psList){

	return;
}


int lstSize (const ListPtr psList){
	return psList->numElements;
}



void lstInsertAfter (ListPtr psList, const void *pBuffer, int size){

	if(NULL == psList){
		processError("lstInsertAfter", ERROR_INVALID_LIST);
	}
	if(NULL == pBuffer){
			processError("lstInsertAfter", ERROR_NULL_PTR);
	}

		//If List is Empty, create new element as current, head, and tail
		if(0 == lstSize(psList)){
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
		else{
			//Check for error
			if(NULL == psList->psCurrent){
				processError("lstInsertAfter", ERROR_NO_CURRENT);
			}
			//If the List is NOT empty, check if the current element is the last element in the list
			if(NULL == psList->psCurrent->psNext){
				//Add a new tail
				psList->psCurrent->psNext = (ListElement*)malloc(sizeof(ListElement));
				psList->numElements++;
				psList->psCurrent = psList->psCurrent->psNext;
				psList->psLast = psList->psCurrent;
				//Add the data
				psList->psCurrent->pData = (void*)malloc(size);
				memcpy(psList->psCurrent->pData, pBuffer, size);
			}else{
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

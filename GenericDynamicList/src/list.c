/***************************************************************************
File name:  list.c
Author:     Damon Holland
Date:       Sep 19, 2019
Class:      CS300
Assignment: Generic Dynamic List
Purpose:    
***************************************************************************/

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

	if(NULL == psList->psCurrent){
		if(NULL == psList->psFirst){
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
	}
	return;
}

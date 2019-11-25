/**************************************************************************
File name:  ht.c
Author:     holl9358
Date:       Nov 17, 2019
Class:      CS300
Assignment: 
Purpose:    
**************************************************************************/

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../GenericDynamicList/include/list.h"
#include "../include/ht.h"


char gszHTErrors[HT_NUMBER_OF_ERRORS][HT_MAX_ERROR_CHARS];

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
	printf ("Function: %s %s \n ", pszFunctionName,
					gszHTErrors[errorCode]);
	exit (EXIT_FAILURE);
}

void htLoadErrorMessages ()
{
	lstLoadErrorMessages();
	LOAD_ERRORS;
	return;
}

void htCreate (HashTablePtr psHashTable, int bucketSize, int keySize,
							 int dataSize, hashFunction pHashFunc,
							 printFunction pPrintFunc)
{
	//Error Checking
	if (NULL == psHashTable)
	{
		processError ("trCreate", HT_NO_MEMORY_ERROR);
	}

	int i;

	psHashTable->bucketSize = bucketSize;

	for (i = 0; i < bucketSize; ++i)
	{
		lstCreate (&psHashTable->bucket[i]);
	}

	psHashTable->keySize = keySize;
	psHashTable->dataSize = dataSize;
	psHashTable->pHashFunction = pHashFunc;
	psHashTable->pPrintFunction = pPrintFunc;

	return;
}

void htTerminate (HashTablePtr psHashTable)
{
	int i;

	for (i = 0; i < psHashTable->bucketSize; ++i)
	{
		lstTerminate (&psHashTable->bucket[i]);
	}

	psHashTable->bucketSize = 0;

	return;
}

bool htIsEmpty (HashTablePtr psHashTable)
{

	bool bIsEmpty = true;
	int i;

	for (i = 0; i < psHashTable->bucketSize && bIsEmpty; ++i)
	{
		if (!lstIsEmpty (&psHashTable->bucket[i]))
		{
			bIsEmpty = false;
		}
	}

	return bIsEmpty;
}

bool htInsert (HashTablePtr psHashTable, void* pKey, void* pData)
{
	int hash = psHashTable->pHashFunction (pKey, psHashTable->keySize) %
						 psHashTable->bucketSize;

	HashTableElement newElement;

	memcpy(&newElement.pKey, pKey, psHashTable->keySize);
	memcpy(&newElement.pData, pData, psHashTable->dataSize);

	lstInsertAfter (&psHashTable->bucket[hash], &newElement,
									sizeof (newElement));

	return false;
}

bool htDelete ()
{
	return false;
}

bool htUpdate ()
{
	return false;
}

bool htFind ()
{
	return false;
}

void htPrint(HashTablePtr psHashTable)
{
	HashTableElement currentElement;
	int i, j;

	for (i = 0; i < psHashTable->bucketSize; ++i)
	{
		if (!lstIsEmpty (&psHashTable->bucket[i]))
		{
			lstFirst (&psHashTable->bucket[i]);
			for (j = 0; j < lstSize(&psHashTable->bucket[i]); ++j)
			{
				lstPeek (&psHashTable->bucket[i], &currentElement,
						 	 	 sizeof (currentElement));
				printf ("Bucket: %d | ", i);
				psHashTable->pPrintFunction (&currentElement.pKey,
																		 psHashTable->keySize,
																		 &currentElement.pData,
																		 psHashTable->dataSize);
				lstNext (&psHashTable->bucket[i]);
		}
		}
	}

	return;
}

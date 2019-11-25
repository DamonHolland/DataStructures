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
							 cmpFunction pCmpFunc, printFunction pPrintFunc)
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
	psHashTable->pCmpFunction = pCmpFunc;
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
	int i;
	bool bAdded = true;
	HashTableElement tmpElement;

	//Get The hash for the key being inserted
	int hash = psHashTable->pHashFunction (pKey, psHashTable->keySize) %
						 psHashTable->bucketSize;

	//Check if the key is already in the Hash Table
	if (!lstIsEmpty (&psHashTable->bucket[hash]))
	{
		lstFirst (&psHashTable->bucket[hash]);
		for (i = 0; i < lstSize (&psHashTable->bucket[hash]) && bAdded; ++i)
		{
			lstPeek (&psHashTable->bucket[hash], &tmpElement,
							 sizeof (HashTableElement));
			if (psHashTable->pCmpFunction (pKey, &tmpElement.pKey,
					psHashTable->keySize) == 0)
			{
				bAdded = false;
			}
			lstNext (&psHashTable->bucket[hash]);
		}
	}

	//Add the new element if the key was not already in the Hash Table
	if (bAdded)
	{
		memcpy(&tmpElement.pKey, pKey, psHashTable->keySize);
		memcpy(&tmpElement.pData, pData, psHashTable->dataSize);

		if (!lstIsEmpty (&psHashTable->bucket[hash]))
		{
			lstLast (&psHashTable->bucket[hash]);
		}

		lstInsertAfter (&psHashTable->bucket[hash], &tmpElement,
										sizeof (HashTableElement));
	}

	return bAdded;
}

bool htDelete (HashTablePtr psHashTable, void* pKey)
{
	int i;
	bool bDeleted = false;
	HashTableElement tmpElement;
	int hash = psHashTable->pHashFunction(pKey, psHashTable->keySize) %
						 psHashTable->bucketSize;

	//Check if the key is already in the Hash Table
	if (!lstIsEmpty (&psHashTable->bucket[hash]))
	{
		lstFirst (&psHashTable->bucket[hash]);
		for (i = 0; i < lstSize (&psHashTable->bucket[hash]) && !bDeleted; ++i)
		{
			lstPeek (&psHashTable->bucket[hash], &tmpElement,
								sizeof (HashTableElement));
			if (psHashTable->pCmpFunction (pKey, &tmpElement.pKey,
					psHashTable->keySize) == 0)
			{
				lstDeleteCurrent (&psHashTable->bucket[hash], &tmpElement,
												  sizeof (HashTableElement));
				bDeleted = true;
			}
			if (!lstIsEmpty (&psHashTable->bucket[hash]))
			{
				lstNext (&psHashTable->bucket[hash]);
			}
		}
	}


	return bDeleted;
}

bool htUpdate (HashTablePtr psHashTable, void* pKey, void* pData)
{
	int i;
	bool bUpdated = false;
	HashTableElement tmpElement;
	int hash = psHashTable->pHashFunction(pKey, psHashTable->keySize) %
						 psHashTable->bucketSize;


	//Check if the key is already in the Hash Table
		if (!lstIsEmpty (&psHashTable->bucket[hash]))
		{
			lstFirst (&psHashTable->bucket[hash]);
			for (i = 0; i < lstSize (&psHashTable->bucket[hash]) && !bUpdated; ++i)
			{
				lstPeek (&psHashTable->bucket[hash], &tmpElement,
								 sizeof (HashTableElement));
				if (psHashTable->pCmpFunction (pKey, &tmpElement.pKey,
						psHashTable->keySize) == 0)
				{
					memcpy (&tmpElement.pData, pData, psHashTable->dataSize);
					lstUpdateCurrent (&psHashTable->bucket[hash], &tmpElement,
														sizeof (HashTableElement));
					bUpdated = true;
				}
				lstNext (&psHashTable->bucket[hash]);
			}
		}

	return bUpdated;
}

bool htFind (HashTablePtr psHashTable, void* pKey, void* pBuffer)
{
	int i;
	bool bFound = false;
	HashTableElement tmpElement;
	int hash = psHashTable->pHashFunction(pKey, psHashTable->keySize) %
						 psHashTable->bucketSize;


	//Check if the key is already in the Hash Table
		if (!lstIsEmpty (&psHashTable->bucket[hash]))
		{
			lstFirst (&psHashTable->bucket[hash]);
			for (i = 0; i < lstSize (&psHashTable->bucket[hash]) && !bFound; ++i)
			{
				lstPeek (&psHashTable->bucket[hash], &tmpElement,
								 sizeof (HashTableElement));
				if (psHashTable->pCmpFunction (pKey, &tmpElement.pKey,
						psHashTable->keySize) == 0)
				{
					memcpy (pBuffer, &tmpElement.pData, psHashTable->dataSize);
					bFound = true;
				}
				lstNext (&psHashTable->bucket[hash]);
			}
		}

	return bFound;
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

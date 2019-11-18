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

void htLoadErrorMessages ()
{
	lstLoadErrorMessages();
	LOAD_ERRORS;
	return;
}

void htCreate (HashTablePtr psHashTable, int bucketSize)
{
	int i;

	psHashTable->bucketSize = bucketSize;

	for (i = 0; i < bucketSize; ++i)
	{
		lstCreate (&psHashTable->bucket[i]);
	}

	return;
}

void htTerminate (HashTablePtr psHashTable)
{
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

bool htInsert (HashTablePtr psHashTable, void* pKey, int keySize,
							 void* pData, int dataSize, hashFunction hashFunc)
{
	int hash = hashFunc (pKey, keySize) % psHashTable->bucketSize;

	HashTableElement newElement;

	memcpy(&newElement.pKey, pKey, keySize);
	memcpy(&newElement.pData, pData, dataSize);

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

void htPrint(HashTablePtr psHashTable, printFunction printFunc, int keySize,
						 int dataSize)
{
	HashTableElement currentElement;
	int i, j;

	for (i = 0; i < psHashTable->bucketSize; ++i)
	{
		if (!lstIsEmpty (&psHashTable->bucket[i]))
		{
			lstFirst (&psHashTable->bucket[i]);
		}
		for (j = 0; j < lstSize(&psHashTable->bucket[i]); ++j)
		{
			lstPeek (&psHashTable->bucket[i], &currentElement,
						 	 sizeof (currentElement));
			printf ("Bucket: %d | ", i);
			printFunc (&currentElement.pKey, keySize, &currentElement.pData,
								 dataSize);
			lstNext (&psHashTable->bucket[i]);
		}
	}
	return;
}

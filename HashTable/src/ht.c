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
	psHashTable->bucketSize = bucketSize;

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
	printf ("Hashed to: %d\n", hash);
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

void htPrint()
{
	return;
}

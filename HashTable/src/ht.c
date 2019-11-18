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

void htCreate (HashTablePtr psHashTable, int bucketSize){}

void htTerminate (HashTablePtr psHashTable)
{
	return;
}

bool htIsEmpty (HashTablePtr psHashTable)
{
	return false;
}

bool htInsert (HashTablePtr psHashTable, void* pKey, int keySize,
							 void* pData, int dataSize, hashFunction hashFunc)
{
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

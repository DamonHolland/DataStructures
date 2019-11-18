/**************************************************************************
File name:  htdriver.c
Author:     Damon Holland
Date:       Nov 17, 2019
Class:      CS300
Assignment: Hash Table
Purpose:    Test the functionality of the hash table ADT
**************************************************************************/

#include "stdlib.h"
#include "stdio.h"
#include "../include/ht.h"

/*************************************************************************
 Function: 	 	success

 Description: print a success message

 Parameters:	szStr - the message to print
 Returned:	 	none
 ************************************************************************/
static void success (char * szStr)
{
	printf ("SUCCESS: %s\n", szStr);
}

/*************************************************************************
 Function: 	 	failure

 Description: print a failure message

 Parameters:	szStr - the message to print
 Returned:	 	none
 ************************************************************************/
static void failure (char * szStr)
{
	printf ("FAILURE: %s\n", szStr);
	exit (EXIT_FAILURE);
}

/*************************************************************************
 Function: 	 	assert

 Description: if the expression is true, assert success; otherwise, assert
 	 	 	 	 	 	 	failure

 Parameters:	szStr - the message to print

 Returned:	 	none
 ************************************************************************/
static void assert (bool bExpression, char *pTrue, char *pFalse)
{
	if (bExpression)
	{
		success (pTrue);
	}
	else
	{
		failure (pFalse);
	}
}

int stringHash (void* pKey, int keySize)
{
	char aKey[keySize];
	memcpy(&aKey, pKey, keySize);

	int hash = 0, i;

	for (i = 0; i < keySize; ++i)
	{
		hash += aKey[i];
	}

	return hash;
}

void printStringInt (void* pKey, int keySize, void* pData, int dataSize)
{
	char aKey[keySize];
	memcpy(&aKey, pKey, keySize);

	int data;
	memcpy(&data, pData, dataSize);

	printf ("Key: %s | Data: %d |\n", aKey, data);

	return;
}

int main()
{
	//Constant ints
	const int HASH_TABLE_SIZE = 10;
	const int STRING_KEY_SIZE = 7;
	const int NUM_ELEMENTS = 10;

	//Variables for keys
	char* keys[] = {"MyKey1", "MyKey2", "MyKey3",
			"MyKey4", "MyKey5", "MyKey6", "MyKey7", "MyKey8", "MyKey9", "AKey10"};

	//Variables for data
	int data[] = {25, 92, 57, 110, 297, 12, 3, 98, 8, 879};
	int i;

	HashTable sTheHashTable;

	//************************* Test htCreate *************************
	htLoadErrorMessages ();
	htCreate (&sTheHashTable, HASH_TABLE_SIZE);
	assert (htIsEmpty (&sTheHashTable), "ht is empty after creation",
																			"ht is NOT empty after creation");

	for (i = 0; i < NUM_ELEMENTS; ++i)
	{
		htInsert (&sTheHashTable, keys[i], STRING_KEY_SIZE, &data[i],
							sizeof (data[i]), stringHash);
	}

	htPrint (&sTheHashTable, printStringInt, STRING_KEY_SIZE , sizeof (int));

	htTerminate (&sTheHashTable);

	return EXIT_SUCCESS;
}

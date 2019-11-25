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
	//From ZyBooks: Daniel J. Bernstein created a popular version of a
	//multiplicative string hash function that uses an initial value of 5381
	//and a multiplier of 33. Bernstein's hash function performs well for
	//hashing short English strings. (Why I use these constants)
	const int HASH_INITIAL = 5381, HASH_MULTIPLIER = 33;

	char aKey[keySize];

	int i;
	int hash = HASH_INITIAL;

	memcpy(&aKey, pKey, keySize);

	for (i = 0; i < keySize; ++i)
	{
		hash = (hash * HASH_MULTIPLIER) + aKey[i];
	}

	return hash;
}

void printStringInt (void* pKey, int keySize, void* pData, int dataSize)
{
	char aKey[keySize];
	int data;

	memcpy(&aKey, pKey, keySize);
	memcpy(&data, pData, dataSize);

	printf ("Key: %10s | Data: %10d |\n", aKey, data);

	return;
}

int main()
{
	//Constant ints
	const int NUM_ELEMENTS = 10;
	const int HASH_TABLE_SIZE = 10;
	const int STRING_KEY_SIZE = 7;
	//Change previous 2 constants based on keys and data given below

	//Variables for keys
	char* keys[] = {"MyKey1", "MyKey2", "MyKey3", "MyKey4", "MyKey5",
									"MyKey6", "MyKey7", "MyKey8", "MyKey9", "AKey10"};

	//Variables for data
	int data[] = {25, 92, 57, 110, 297, 12, 3, 98, 8, 879};

	//iterator
	int i;

	//The Hash Table
	HashTable sTheHashTable;

	//************************* Test htCreate *************************
	htLoadErrorMessages ();
	htCreate (&sTheHashTable, HASH_TABLE_SIZE, STRING_KEY_SIZE, sizeof (int),
						stringHash, printStringInt);
	assert (htIsEmpty (&sTheHashTable), "ht is empty after creation",
																			"ht is NOT empty after creation");

	//************************* Test htInsert *************************
	for (i = 0; i < NUM_ELEMENTS; ++i)
	{
		htInsert (&sTheHashTable, keys[i], &data[i]);
	}
	assert (!htIsEmpty (&sTheHashTable), "ht is not empty after insertion",
																			 "ht IS empty after insertion");

	//************************* Test htPrint *************************
	htPrint (&sTheHashTable);

	//************************* Test htTerminate *************************
	htTerminate (&sTheHashTable);
	assert (htIsEmpty (&sTheHashTable), "ht is empty after termination",
																			"ht is NOT empty after termination");

	return EXIT_SUCCESS;
}

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
	char aKey[keySize / sizeof (char)];
	memcpy(&aKey, pKey, keySize);

	int hash = 0, i;

	for (i = 0; i < keySize; ++i)
	{
		hash += aKey[i];
	}

	return hash;
}

int main()
{
	const int HashTableSize = 10;

	char key[] = "TestKey";
	int data = 25;

	HashTable sTheHashTable;

	htLoadErrorMessages ();
	htCreate (&sTheHashTable, HashTableSize);
	assert (htIsEmpty (&sTheHashTable), "ht is empty after creation",
																			"ht is NOT empty after creation");

	htInsert (&sTheHashTable, &key, sizeof (key), &data, sizeof (data),
						stringHash);


	printf ("Build Success");
	return EXIT_SUCCESS;
}

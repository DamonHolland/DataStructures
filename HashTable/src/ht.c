/**************************************************************************
File name:  ht.c
Author:     holl9358
Date:       Nov 17, 2019
Class:      CS300
Assignment: Hash Table
Purpose:    Implement functions for the hash table
**************************************************************************/

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../GenericDynamicList/include/list.h"
#include "../include/ht.h"

char gszHTErrors[HT_NUMBER_OF_ERRORS][HT_MAX_ERROR_CHARS];

/**************************************************************************
 Function: 	 	processError

 Description: Process the error code passed to this routine

 Parameters:	pszFunctionName - string containing the name of the function
  															causing the error
 	 	 	 	 	 	 	errorCode - an integer that identifies the queue error

 Returned:	 	None
 *************************************************************************/
static void processError (const char *pszFunctionName, int errorCode)
{
	printf ("Function: %s %s \n ", pszFunctionName,
					gszHTErrors[errorCode]);
	exit (EXIT_FAILURE);
}

/**************************************************************************
 Function: 	 	htLoadErrorMessages

 Description: Loads error message strings that the hash table may need.

 Parameters:	None

 Returned:	 	None
 *************************************************************************/
void htLoadErrorMessages ()
{
	lstLoadErrorMessages ();
	LOAD_ERRORS;
	return;
}

/**************************************************************************
 Function: 	 	htCreate

 Description: Creates the hash table, gathers needed information for the
 	 	 	 	 	 	 	hash table, and stores it within the hash table struct.

 Parameters:	psHashTable - Pointer to the hash table to create.
 	 	 	 	 	 	 	bucketSize  - An integer containing the size of the hash
 	 	 	 	 	 	 								table to create.
 	 	 	 	 	 	 	keySize     - An integer containing the size in bytes of the
 	 	 	 	 	 	 								keys that will be stored.
 	 	 	 	 	 	 	dataSize    - An integer containing the size in bytes of the
 	 	 	 	 	 	 								data that will be stored.
 	 	 	 	 	 	 	pHashFunc   - A pointer to the function that will generate
 	 	 	 	 	 	 								the hash value for the given keys.
 	 	 	 	 	 	 	pCmpFunc    - A pointer to the function that will compare
 	 	 	 	 	 	 								keys in the hash table.
 	 	 	 	 	 	  pPrintFunc  - A pointer to the function that will print
 	 	 	 	 	 	  							key/data pairs in the hash table.

 Returned:	 	None
 *************************************************************************/
void htCreate (HashTablePtr psHashTable, int bucketSize, int keySize,
							 int dataSize, hashFunction pHashFunc,
							 cmpFunction pCmpFunc, printFunction pPrintFunc)
{
	//Error Checking
	if (NULL == psHashTable)
	{
		processError ("htCreate", HT_NO_MEMORY_ERROR);
	}

	int i;

	// ********** Set up hash table for given input **********
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

/**************************************************************************
 Function: 	 	htTerminate

 Description: Terminates the hash table, freeing the stored memory.

 Parameters:	psHashTable - Pointer to the hash table to terminate.

 Returned:	 	None
 *************************************************************************/
void htTerminate (HashTablePtr psHashTable)
{
	//Error Checking
	if (NULL == psHashTable)
	{
		processError ("htTerminate", HT_NO_MEMORY_ERROR);
	}

	HashTableElement tmpElement;
	int i, j;

	//Terminate all bucket lists in hash table
	for (i = 0; i < psHashTable->bucketSize; ++i)
	{
		if (!lstIsEmpty (&psHashTable->bucket[i]))
		{
			lstFirst (&psHashTable->bucket[i]);
			for (j = 0; j < lstSize (&psHashTable->bucket[i]); ++j)
			{
				lstPeek (&psHashTable->bucket[i], &tmpElement,
								 sizeof (HashTableElement));
				free (tmpElement.pKey);
				free (tmpElement.pData);
				lstNext (&psHashTable->bucket[i]);
			}
		}
		lstTerminate (&psHashTable->bucket[i]);
	}
	psHashTable->bucketSize = 0;

	return;
}

/**************************************************************************
 Function: 	 	htIsEmpty

 Description: Checks if the given hash table is empty or not.

 Parameters:	psHashTable - Pointer to the hash table to check is empty
 	 	 	 	 	 	 	 	 	 	 	 	 	 	or not

 Returned:	 	bool        - true if the hash table is empty / false if not
 *************************************************************************/
bool htIsEmpty (HashTablePtr psHashTable)
{
	//Error Checking
	if (NULL == psHashTable)
	{
		processError ("htIsEmpty", HT_NO_MEMORY_ERROR);
	}

	bool bIsEmpty = true;
	int i;

	//Check if the list for every bucket is empty
	for (i = 0; i < psHashTable->bucketSize && bIsEmpty; ++i)
	{
		if (!lstIsEmpty (&psHashTable->bucket[i]))
		{
			bIsEmpty = false;
		}
	}

	return bIsEmpty;
}

/**************************************************************************
 Function: 	 	htInsert

 Description: Attempts to insert a key/data pair into the given hash table.
 	 	 	 	 	 	 	Only inserts if the key is not already contained.

 Parameters:	psHashTable - Pointer to the hash table to insert into.
 	 	 	 	 	 	 	pKey        - Pointer to the key to insert.
 	 	 	 	 	 	 	pData       - Pointer to the data to insert.

 Returned:	 	bool        - True if the key/data pair was inserted, false
 	 	 	 	 	 	 	 	 	 	 	 	 	 	if not.
 *************************************************************************/
bool htInsert (HashTablePtr psHashTable, const void* pKey,
							const void* pData)
{
	//Error Checking
	if (NULL == psHashTable || NULL == pKey || NULL == pData)
	{
		processError ("htInsert", HT_NO_MEMORY_ERROR);
	}

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
			if (psHashTable->pCmpFunction (pKey, tmpElement.pKey,
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
		tmpElement.pKey = (void*)malloc (psHashTable->keySize);
		tmpElement.pData = (void*)malloc (psHashTable->dataSize);
		memcpy (tmpElement.pKey, pKey, psHashTable->keySize);
		memcpy (tmpElement.pData, pData, psHashTable->dataSize);

		if (!lstIsEmpty (&psHashTable->bucket[hash]))
		{
			lstLast (&psHashTable->bucket[hash]);
		}

		lstInsertAfter (&psHashTable->bucket[hash], &tmpElement,
										sizeof (HashTableElement));
	}

	return bAdded;
}

/**************************************************************************
 Function: 	 	htDelete

 Description: Attempts to delete a key/data pair from the given hash table.
 	 	 	 	 	 	 	Will only delete key/data pair if the key is found.
 	 	 	 	 	 	 	Frees the memory of the deleted element

 Parameters:	psHashTable - Pointer to the hash table to delete from.
 	 	 	 	 	 	 	pKey        - Pointer to the key to delete.

 Returned:	 	bool        - True if the key/data pair was deleted, false
 	 	 	 	 	 	 	 	 	 	 	 	 	 	if not.
 *************************************************************************/
bool htDelete (HashTablePtr psHashTable, const void* pKey)
{
	//Error Checking
	if (NULL == psHashTable || NULL == pKey)
	{
		processError ("htDelete", HT_NO_MEMORY_ERROR);
	}

	int i;
	bool bDeleted = false;
	HashTableElement tmpElement;
	int hash = psHashTable->pHashFunction (pKey, psHashTable->keySize) %
						 psHashTable->bucketSize;

	//Check if the key is in the Hash table. delete it if it is found
	if (!lstIsEmpty (&psHashTable->bucket[hash]))
	{
		lstFirst (&psHashTable->bucket[hash]);
		for (i = 0; i < lstSize (&psHashTable->bucket[hash]) && !bDeleted; ++i)
		{
			lstPeek (&psHashTable->bucket[hash], &tmpElement,
								sizeof (HashTableElement));
			if (psHashTable->pCmpFunction (pKey, tmpElement.pKey,
					psHashTable->keySize) == 0)
			{
				free (tmpElement.pKey);
				free (tmpElement.pData);
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

/**************************************************************************
 Function: 	 	htUpdate

 Description: Attempts to update the data of a specified key in the given
 	 	 	 	 	 	 	hash table. The data will only be updated if the given key
 	 	 	 	 	 	 	is found.

 Parameters:	psHashTable - Pointer to the hash table to update.
 	 	 	 	 	 	 	pKey        - Pointer to the key to update the corresponding
 	 	 	 	 	 	 	 	 	 	 	 	 	 	data.
 	 	 	 	 	 	 	pData       - Pointer to the new data to overwrite the
 	 	 	 	 	 	 								existing data with.

 Returned:	 	bool        - True if the key/data pair was updated, false
 	 	 	 	 	 	 	 	 	 	 	 	 	 	if not.
 *************************************************************************/
bool htUpdate (HashTablePtr psHashTable, const void* pKey,
							 const void* pData)
{
	//Error Checking
	if (NULL == psHashTable || NULL == pKey || NULL == pData)
	{
		processError ("htUpdate", HT_NO_MEMORY_ERROR);
	}

	int i;
	bool bUpdated = false;
	HashTableElement tmpElement;
	int hash = psHashTable->pHashFunction (pKey, psHashTable->keySize) %
						 psHashTable->bucketSize;


	//Check if the key is in the hash table, update it if it is found
	if (!lstIsEmpty (&psHashTable->bucket[hash]))
	{
		lstFirst (&psHashTable->bucket[hash]);
		for (i = 0; i < lstSize (&psHashTable->bucket[hash]) && !bUpdated; ++i)
		{
			lstPeek (&psHashTable->bucket[hash], &tmpElement,
							 sizeof (HashTableElement));
			if (psHashTable->pCmpFunction (pKey, tmpElement.pKey,
					psHashTable->keySize) == 0)
			{
				memcpy (tmpElement.pData, pData, psHashTable->dataSize);
				lstUpdateCurrent (&psHashTable->bucket[hash], &tmpElement,
													sizeof (HashTableElement));
				bUpdated = true;
			}
			lstNext (&psHashTable->bucket[hash]);
		}
	}

	return bUpdated;
}

/**************************************************************************
 Function: 	 	htFind

 Description: Attempts to find the data corresponding to the given key in
  						the given hash table. Will only return data if the given key
  						is found.

 Parameters:	psHashTable - Pointer to the hash table to find data in.
 	 	 	 	 	 	 	pKey        - Pointer to the key to find data of.
 	 	 	 	 	 	 	pBuffer     - Buffer which will be used to return the found
 	 	 	 	 	 	 								data.

 Returned:	 	bool        - True if the key was found and data returned,
  													false if not
 *************************************************************************/
bool htFind (HashTablePtr psHashTable, const void* pKey,
						 void* pBuffer)
{
	//Error Checking
	if (NULL == psHashTable || NULL == pKey)
	{
		processError ("htFind", HT_NO_MEMORY_ERROR);
	}
	if (NULL == pBuffer)
	{
		processError ("htFind", HT_NO_BUFFER_ERROR);
	}

	int i;
	bool bFound = false;
	HashTableElement tmpElement;
	int hash = psHashTable->pHashFunction (pKey, psHashTable->keySize) %
						 psHashTable->bucketSize;


	//Check if the key is in the hash table, set the buffer to the matching
	//data if it is
	if (!lstIsEmpty (&psHashTable->bucket[hash]))
	{
		lstFirst (&psHashTable->bucket[hash]);
		for (i = 0; i < lstSize (&psHashTable->bucket[hash]) && !bFound; ++i)
		{
			lstPeek (&psHashTable->bucket[hash], &tmpElement,
							 sizeof (HashTableElement));
			if (psHashTable->pCmpFunction (pKey, tmpElement.pKey,
					psHashTable->keySize) == 0)
			{
				memcpy (pBuffer, tmpElement.pData, psHashTable->dataSize);
				bFound = true;
			}
			lstNext (&psHashTable->bucket[hash]);
		}
	}

	return bFound;
}

/**************************************************************************
 Function: 	 	htPrint

 Description: Prints the given hash table.

 Parameters:	psHashTable - Pointer to the hash table to print.

 Returned:	  None
 *************************************************************************/
void htPrint(HashTablePtr psHashTable, FILE* pOutStream)
{
	//Error Checking
	if (NULL == psHashTable)
	{
		processError ("htPrint", HT_NO_MEMORY_ERROR);
	}

	HashTableElement currentElement;
	int i, j;

	//Loop through each list in the bucket, and print the key/data pairs
	for (i = 0; i < psHashTable->bucketSize; ++i)
	{
		if (!lstIsEmpty (&psHashTable->bucket[i]))
		{
			lstFirst (&psHashTable->bucket[i]);
			for (j = 0; j < lstSize(&psHashTable->bucket[i]); ++j)
			{
				lstPeek (&psHashTable->bucket[i], &currentElement,
						 	 	 sizeof (currentElement));
				fprintf (pOutStream, "Bucket: %d | ", i);
				psHashTable->pPrintFunction (pOutStream, &currentElement.pKey,
																		 psHashTable->keySize,
																		 &currentElement.pData,
																		 psHashTable->dataSize);
				lstNext (&psHashTable->bucket[i]);
			}
		}
	}

	return;
}

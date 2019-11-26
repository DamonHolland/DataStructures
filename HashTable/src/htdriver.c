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
#include <stdint.h>

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

/*************************************************************************
 Function: 	 	stringHash

 Description: Hashes a given string to an integer hash value - Uses the
 	 	 	 	 	 	 	multiplicative string hash

 Parameters:	pKey     - The pointer to the string key to hash
 	 	 	 	 	 	 	keySize  - An integer that contains the size in bytes of the
 	 	 	 	 	 	 	 	 	 	 	 	 key

 Returned:	 	uint32_t - The hash value
 ************************************************************************/
uint32_t stringHash (const void* pKey, int keySize)
{
	//From ZyBooks: Daniel J. Bernstein created a popular version of a
	//multiplicative string hash function that uses an initial value of 5381
	//and a multiplier of 33. Bernstein's hash function performs well for
	//hashing short English strings. (Why I use these constants)
	const int HASH_INITIAL = 5381, HASH_MULTIPLIER = 33;

	char aKey[keySize];

	int i;
	uint32_t hash = HASH_INITIAL;

	memcpy (&aKey, pKey, keySize);

	for (i = 0; i < keySize; ++i)
	{
		hash = (hash * HASH_MULTIPLIER) + aKey[i];
	}

	return hash;
}

/*************************************************************************
 Function: 	 	intHash

 Description: Hashes a given integer to an integer hash - Uses the
  						mid square hash function

 Parameters:	pKey     - The pointer to the integer key to hash
 	 	 	 	 	 	 	keySize  - An integer that contains the size in bytes of the
 	 	 	 	 	 	 	 	 	 	 	 	 key

 Returned:	 	uint32_t - The hash value
 ************************************************************************/
uint32_t intHash (const void* pKey, int keySize)
{
	uint32_t hash;
	int key;

	memcpy (&key, pKey, keySize);

	hash = key * key;
	hash = (hash & 0x000ff000) >> 12;

	return hash;
}

/*************************************************************************
 Function: 	 	stringCmp

 Description: Compares two string values

 Parameters:	pKey1    - A pointer to the first string to compare.
 	 	 	 	 	 	 	pKey2    - A pointer to the second string to compare.
 	 	 	 	 	 	 	keySize  - An integer that contains the size in bytes of the
 	 	 	 	 	 	 	 	 	 	 	 	 key.

 Returned:	 	int      - An integer that will equal 0 if the keys were
  											 equal, or the difference between the first and
  											 second key using strncmp.
  											 (Signed Integer: Key1 - Key2)
 ************************************************************************/
int stringCmp (const void* pKey1, const void* pKey2, int keySize)
{
	char aKey1[keySize], aKey2[keySize];

	memcpy (&aKey1, pKey1, keySize);
	memcpy (&aKey2, pKey2, keySize);

	return strcmp (aKey1, aKey2);
}

/*************************************************************************
 Function: 	 	intCmp

 Description: Compares two integer values

 Parameters:	pKey1    - A pointer to the first integer to compare.
 	 	 	 	 	 	 	pKey2    - A pointer to the second integer to compare.
 	 	 	 	 	 	 	keySize  - An integer that contains the size in bytes of the
 	 	 	 	 	 	 	 	 	 	 	 	 key.

 Returned:	 	int      - An integer that will equal 0 if the keys were
  											 equal, or the difference between the first and
  											 second key. (Signed Integer: Key1 - Key2)
 ************************************************************************/
int intCmp (const void* pKey1, const void* pKey2, int keySize)
{
	int key1, key2;

	memcpy (&key1, pKey1, keySize);
	memcpy (&key2, pKey2, keySize);

	return key1 - key2;
}

/*************************************************************************
 Function: 	 	printStringInt

 Description: Prints a String-Int Key/Data pair to the given output

 Parameters:	pOutStream - The output stream to print to
 	 	 	 	 	 	 	pKey       - A pointer to the string key to print.
 	 	 	 	 	 	 	keySize    - An integer that contains the size in bytes of the
 	 	 	 	 	 	 	 	 	 	 	 	 	 key.
 	 	 	 	 	 	 	pData      - A pointer to the integer data to print.
 	 	 	 	 	 	 	dataSize   - An integer that contains the size in bytes of the
 	 	 	 	 	 	 	 	 	 	 	 	   data.

 Returned:	 	None
 ************************************************************************/
void printStringInt (FILE* pOutStream, const void* pKey, int keySize,
										 const void* pData, int dataSize)
{
	char aKey[keySize];
	int data;

	memcpy (&aKey, pKey, keySize);
	memcpy (&data, pData, dataSize);

	fprintf (pOutStream, "Key: %10s | Data: %10d |\n", aKey, data);

	return;
}

/*************************************************************************
 Function: 	 	printIntString

 Description: Prints a Int-String Key/Data pair to the given output

 Parameters:	pOutStream - The output stream to print to
 	 	 	 	 	 	 	pKey       - A pointer to the integer key to print.
 	 	 	 	 	 	 	keySize    - An integer that contains the size in bytes of the
 	 	 	 	 	 	 	 	 	 	 	 	 	 key.
 	 	 	 	 	 	 	pData      - A pointer to the string data to print.
 	 	 	 	 	 	 	dataSize   - An integer that contains the size in bytes of the
 	 	 	 	 	 	 	 	 	 	 	 	   data.

 Returned:	 	None
 ************************************************************************/
void printIntString (FILE* pOutStream, const void* pKey, int keySize,
										 const void* pData, int dataSize)
{
	int key;
	char aData[keySize];

	memcpy (&key, pKey, keySize);
	memcpy (&aData, pData, dataSize);

	fprintf (pOutStream, "Key: %10d | Data: %10s |\n", key, aData);

	return;
}

/*************************************************************************
 Function: 	 	main

 Description: Test all the functions of the hash table

 Parameters:	none

 Returned:	 	Exit Status
 ************************************************************************/
int main()
{
	//Constants
	const int NUM_ELEMENTS = 10;
	const int TEST_INDEX = 5;
	const int UPDATE_VALUE = 1000;
	const char* pFILE_NAME = "testOutput/printTest1.txt";
	const char* pNOT_INSERTED_KEY = "NOT_IN";
	const int HASH_TABLE_SIZE = 10;
	const int STRING_KEY_SIZE = 8;
	//Change previous 2 constants based on arrays given below

	//Variables for keys / data
	char* apStrings[] = {"String1", "String2", "String3", "String4",
											 "String5", "String6", "String7", "String8",
											 "String9", "Strng10"};
	int aInts[] = {25, 92, 57, 110, 297, 12, 3, 98, 8, 879};

	//Variables to test insertion of duplicates
	char* pDupKey = "String1";
	int dupData = 5;

	//Buffer Variables
	int intBuffer;
	char aStringBuffer[STRING_KEY_SIZE];

	//iterator
	int i;

	//Output File
	FILE* pOutFile;

	//********** Open and validate file **********
	pOutFile = fopen (pFILE_NAME, "w");
	if (!pOutFile)
	{
		printf ("Error: Unable to open file\n");
		exit (EXIT_FAILURE);
	}

	//The Hash Table
	HashTable sStringIntHashTable;
	HashTable sIntStringHashTable;

	//************************* Test htCreate *************************
	htLoadErrorMessages ();
	htCreate (&sStringIntHashTable, HASH_TABLE_SIZE, STRING_KEY_SIZE,
						sizeof (int), stringHash, stringCmp, printStringInt);
	htCreate (&sIntStringHashTable, HASH_TABLE_SIZE, sizeof (int),
						STRING_KEY_SIZE, intHash, intCmp, printIntString);
	assert (htIsEmpty (&sStringIntHashTable) &&
					htIsEmpty (&sIntStringHashTable),
					"Hash tables empty after creation",
					"Hash tables are NOT empty after creation");

	//************************* Test htInsert *************************
	for (i = 0; i < NUM_ELEMENTS; ++i)
	{
		htInsert (&sStringIntHashTable, apStrings[i], &aInts[i]);
		htInsert (&sIntStringHashTable, &aInts[i], apStrings[i]);
	}
	assert (!htIsEmpty (&sStringIntHashTable) &&
					!htIsEmpty (&sIntStringHashTable),
					"Hash tables are not empty after insertion",
					"Hash tables ARE empty after insertion");
	assert (!htInsert (&sStringIntHashTable, pDupKey, &dupData),
					"Insert did not add duplicate key",
					"Insert added duplicate key");

	//************************* Test htFind *************************
	htFind (&sStringIntHashTable, apStrings[TEST_INDEX], &intBuffer);
	htFind (&sIntStringHashTable, &aInts[TEST_INDEX], &aStringBuffer);
	assert (aInts[TEST_INDEX] == intBuffer &&
					!strcmp (aStringBuffer, apStrings[TEST_INDEX]),
					"Found correct data for given keys",
					"Found INCORRECT data for given keys");
	assert (!htFind (&sStringIntHashTable, pNOT_INSERTED_KEY, &intBuffer),
					"Find returns false when key not in table",
					"Find does NOT return false when key not in table");

	//************************* Test htUpdate *************************
	htUpdate (&sStringIntHashTable, apStrings[TEST_INDEX], &UPDATE_VALUE);
	htFind (&sStringIntHashTable, apStrings[TEST_INDEX], &intBuffer);
	assert (UPDATE_VALUE == intBuffer,
					"Data updated correctly",
					"Data NOT updated correctly");
	assert (!htUpdate (&sStringIntHashTable, pNOT_INSERTED_KEY,
					&UPDATE_VALUE),
					"Update returns false when key not in table",
					"Update does NOT return false when key not in table");

	//************************* Test htDelete *************************
	for (i = 0; i < NUM_ELEMENTS; ++i)
	{
		htDelete (&sStringIntHashTable, apStrings[i]);
	}
	assert (htIsEmpty (&sStringIntHashTable),
					"ht is empty after deleting all elements",
				  "ht is NOT empty after deleting all elements");
	assert (!htDelete (&sStringIntHashTable, pNOT_INSERTED_KEY),
					"Delete returns false when key not in table",
					"Delete did NOT return false when key not in table");

	//************************* Test htPrint *************************
	//Check Visually
	htPrint (&sIntStringHashTable, pOutFile);

	//************************* Test htTerminate *************************
	htTerminate (&sStringIntHashTable);
	htTerminate (&sIntStringHashTable);
	assert (htIsEmpty (&sStringIntHashTable) &&
					htIsEmpty (&sIntStringHashTable),
					"ht is empty after termination",
					"ht is NOT empty after termination");

	fclose (pOutFile);
	return EXIT_SUCCESS;
}

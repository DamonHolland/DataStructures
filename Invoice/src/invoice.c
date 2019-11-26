/**************************************************************************
File name:  invoice.c
Author:     Damon Holland
Date:       Nov 25, 2019
Class:      CS300
Assignment: Hash Tables
Purpose:    
**************************************************************************/
#include "stdlib.h"
#include "stdio.h"
#include <stdint.h>
#include <string.h>
#include "../../HashTable/include/ht.h"

typedef struct Item
{
	char manufacturer[10];
	char itemName[10];
} Item;

/*************************************************************************
 Function: 	 	stringHash

 Description: Hashes a given string to an integer hash value - Uses the
 	 	 	 	 	 	 	multiplicative string hash

 Parameters:	pKey     - The pointer to the string key to hash
 	 	 	 	 	 	 	keySize  - An integer that contains the size in bytes of the
 	 	 	 	 	 	 	 	 	 	 	 	 key

 Returned:	 	uint32_t - The hash value
 ************************************************************************/
int stringHash (const void* pKey, int keySize)
{
	//From ZyBooks: Daniel J. Bernstein created a popular version of a
	//multiplicative string hash function that uses an initial value of 5381
	//and a multiplier of 33. Bernstein's hash function performs well for
	//hashing short English strings. (Why I use these constants)
	const int HASH_INITIAL = 5381, HASH_MULTIPLIER = 33;

	char aKey[keySize];

	int i;
	int hash = HASH_INITIAL;

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
int intHash (const void* pKey, int keySize)
{
	int hash;
	int key;

	memcpy (&key, pKey, keySize);

	hash = (key & 0x000ff000) >> 12;

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
 Function: 	 	printStringDouble

 Description: Prints a String-Double Key/Data pair to the given output

 Parameters:	pOutStream - The output stream to print to
 	 	 	 	 	 	 	pKey       - A pointer to the string key to print.
 	 	 	 	 	 	 	keySize    - An integer that contains the size in bytes of the
 	 	 	 	 	 	 	 	 	 	 	 	 	 key.
 	 	 	 	 	 	 	pData      - A pointer to the double data to print.
 	 	 	 	 	 	 	dataSize   - An integer that contains the size in bytes of the
 	 	 	 	 	 	 	 	 	 	 	 	   data.

 Returned:	 	None
 ************************************************************************/
void printStringInt (FILE* pOutStream, const void* pKey, int keySize,
										 const void* pData, int dataSize)
{
	char aKey[keySize];
	double data;

	memcpy (&aKey, pKey, keySize);
	memcpy (&data, pData, dataSize);

	fprintf (pOutStream, "Key: %10s | Data: %.2lf |\n", aKey, data);

	return;
}

/*************************************************************************
 Function: 	 	printIntItem

 Description: Prints a Int-Item Key/Data pair to the given output

 Parameters:	pOutStream - The output stream to print to
 	 	 	 	 	 	 	pKey       - A pointer to the integer key to print.
 	 	 	 	 	 	 	keySize    - An integer that contains the size in bytes of the
 	 	 	 	 	 	 	 	 	 	 	 	 	 key.
 	 	 	 	 	 	 	pData      - A pointer to the Item data to print.
 	 	 	 	 	 	 	dataSize   - An integer that contains the size in bytes of the
 	 	 	 	 	 	 	 	 	 	 	 	   data.

 Returned:	 	None
 ************************************************************************/
void printIntItem (FILE* pOutStream, const void* pKey, int keySize,
										 const void* pData, int dataSize)
{
	int key;
	Item sData;

	memcpy (&key, pKey, keySize);
	memcpy (&sData, pData, dataSize);

	fprintf (pOutStream, "%d %s, %s ", key, sData.itemName,
					 sData.manufacturer);

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
	//Constant file names
	const char* pACTIONS_FILE = "data/actions.txt";
	const char* pCONVERSIONS_FILE = "data/conversions.txt";
	const char* pITEMS_FILE = "data/items.txt";
	const char* pINVOICE_FILE = "data/invoice.txt";

	//Max hash table size constants
	const int MAX_CONVERSIONS = 12;
	const int MAX_ITEMS = 20;

	//Max string length constants
	const int DENOM_LENGTH = 4;

	//Variables to store key/data pairs
	char aDenom[DENOM_LENGTH];
	double conversion;
	int ID;
	Item sItem;
	char aManufacturer[10];
	char aItemName[10];

	//Variables to store actions
	int givenID;
	int givenQuantity;
	int givenCost;
	char aGivenDenom[DENOM_LENGTH];

	//Variables for calculations
	double neededConversion;

	//File used to read data
	FILE* pInFile;
	FILE* pOutFile;

	//The hash tables
	HashTable sConversionsTable;
	HashTable sItemsTable;

	//******************** Create the hash tables ********************
	htCreate (&sConversionsTable, MAX_CONVERSIONS, DENOM_LENGTH,
						sizeof (double), stringHash, stringCmp, printStringInt);
	htCreate (&sItemsTable, MAX_ITEMS, sizeof (int),
						sizeof (Item), intHash, intCmp, printIntItem);

	//******************** Fill the hash tables ********************
	//Open and validate conversions file
	pInFile = fopen (pCONVERSIONS_FILE, "r");
	if(!pInFile)
	{
		printf ("Error: Unable to open file\n");
		exit (EXIT_FAILURE);
	}
	//Read from file and fill conversions table, the close file
	while (!feof (pInFile))
	{
		fscanf(pInFile, "%s %lf", aDenom, &conversion);
		htInsert (&sConversionsTable, &aDenom, &conversion);
	}
	fclose (pInFile);

	//Open and validate items file
	pInFile = fopen (pITEMS_FILE, "r");
	if(!pInFile)
	{
		printf ("Error: Unable to open file\n");
		exit (EXIT_FAILURE);
	}
	//Read from file and fill items table, then close file
	while (!feof (pInFile))
	{
		fscanf(pInFile, "%d %s %s ", &ID,  aItemName, aManufacturer);
		strcpy (sItem.itemName, aItemName);
		strcpy (sItem.manufacturer , aManufacturer);
		htInsert (&sItemsTable, &ID, &sItem);
	}
	fclose (pInFile);

	//******************* Read actions and print results ********************
	//Open and validate actions file
	pInFile = fopen (pACTIONS_FILE, "r");
	if(!pInFile)
	{
		printf ("Error: Unable to open file\n");
		exit (EXIT_FAILURE);
	}
	//Open and validate invoice file
	pOutFile = fopen (pINVOICE_FILE, "w");
	if(!pOutFile)
	{
		printf ("Error: Unable to open file\n");
		exit (EXIT_FAILURE);
	}

	//Print invoice corresponding to actions
	while (!feof (pInFile))
	{
		fscanf (pInFile, "%d %d %d %s ", &givenID, &givenQuantity, &givenCost,
					 aGivenDenom);
		htPrint (&sItemsTable, &givenID, pOutFile);
		htFind (&sConversionsTable, &aGivenDenom, &neededConversion);
		fprintf (pOutFile, "%d %.2f %.2f", givenQuantity, neededConversion *
						 givenCost, neededConversion * givenCost * givenQuantity );
		if (!feof (pInFile))
		{
			fprintf (pOutFile, "\n");
		}
	}

	fclose (pInFile);
	fclose (pOutFile);
	htTerminate (&sConversionsTable);
	htTerminate (&sItemsTable);

	return EXIT_SUCCESS;
}

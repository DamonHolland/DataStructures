/**************************************************************************
File name:  ht.h
Author:     Damon Holland
Date:       Nov 17, 2019
Class:      CS300
Assignment: Hash Table
Purpose:    Interface for a hash table
**************************************************************************/

#ifndef HT_H_
#define HT_H_

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../../GenericDynamicList/include/list.h"

//*************************************************************************
// Constants
//*************************************************************************
#define HT_MAX_ERROR_CHARS 64
#define MAX_BUCKET_SIZE 128
enum {HT_NO_ERROR = 0,
			HT_NO_CREATE_ERROR,
			HT_NO_TERMINATE_ERROR,
			HT_NO_MEMORY_ERROR,
			HT_NO_BUFFER_ERROR}; // If this error name changes, change stmt below
#define HT_NUMBER_OF_ERRORS HT_NO_BUFFER_ERROR - HT_NO_ERROR + 1

//*************************************************************************
// Error Messages
//*************************************************************************
#define LOAD_ERRORS strcpy (gszHTErrors[HT_NO_ERROR], "No Error.");\
strcpy (gszHTErrors[HT_NO_CREATE_ERROR], "Error: No HT Create.");\
strcpy (gszHTErrors[HT_NO_TERMINATE_ERROR], "Error: No HT Terminate.");\
strcpy (gszHTErrors[HT_NO_MEMORY_ERROR], "Error: No HT Memory.");\
strcpy (gszHTErrors[HT_NO_BUFFER_ERROR], "Error: No Buffer.");


//*************************************************************************
// User-defined types
//*************************************************************************
typedef int (*hashFunction)(void* pKey, int keySize);
typedef int (*cmpFunction)(void* pKey1, void* pKey2, int keySize);
typedef void (*printFunction)(void* pKey, int keySize, void* pData,
															int dataSize);

typedef struct HashTableElement* HashTableElementPtr;
typedef struct HashTableElement
{
	void* pKey;
	void* pData;
} HashTableElement;


typedef struct HashTable* HashTablePtr;
typedef struct HashTable
{
	int bucketSize;
	List bucket[MAX_BUCKET_SIZE];

	int keySize;
	int dataSize;

	hashFunction pHashFunction;
	cmpFunction pCmpFunction;
	printFunction pPrintFunction;

} HashTable;

//*************************************************************************
// Function prototypes
//*************************************************************************
extern void htLoadErrorMessages ();

extern void htCreate (HashTablePtr psHashTable, int bucketSize,
											int keySize, int dataSize, hashFunction pHashFunc,
											cmpFunction pCmpFunc, printFunction pPrintFunc);

extern void htTerminate (HashTablePtr psHashTable);

extern bool htIsEmpty (HashTablePtr psHashTable);

extern bool htInsert (HashTablePtr psHashTable, void* pKey, void* pData);

extern bool htDelete (HashTablePtr psHashTable, void* pKey);

extern bool htUpdate (HashTablePtr psHashTable, void* pKey, void* pData);

extern bool htFind (HashTablePtr psHashTable, void* pKey, void* pBuffer);

extern void htPrint(HashTablePtr psHashTable);

#endif /* HT_H_ */

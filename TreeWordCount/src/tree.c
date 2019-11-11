/**************************************************************************
File name:  tree.c
Author:     Damon Holland
Date:       Nov 4, 2019
Class:      CS300
Assignment: TreeWordCount
Purpose:    Contains implementation for the functions declared in tree.h
						Contains all of the functionality for the tree data structure
**************************************************************************/

#include "stdio.h"
#include "../include/tree.h"


char gszTreeErrors[TR_NUMBER_OF_ERRORS][TR_MAX_ERROR_CHARS];

/*************************************************************************
 Function: 	 	processError

 Description: Process the error code passed to this routine

 Parameters:	pszFunctionName - string containing the name of the function
  															causing the error
 	 	 	 	 	 	 	errorCode - an integer that identifies the queue error

 Returned:	 	None
 ************************************************************************/
static void processError (const char *pszFunctionName, int errorCode)
{
	printf ("Function: %s %s \n ", pszFunctionName,
					gszTreeErrors[errorCode]);
	exit (EXIT_FAILURE);
}

/*************************************************************************
 Function: 	 	trLoadErrorMessages

 Description: Loads the error message strings to be used for error
 	 	 	 	 	 	 	messages in the program

 Parameters:	None

 Returned:	 	None
 ************************************************************************/
extern void trLoadErrorMessages ()
{
	LOAD_ERRORS;
	return;
}

/*************************************************************************
 Function: 	 	trCreate

 Description: Initializes the tree so it can be used

 Parameters:	hsTree - A handle to the tree to create

 Returned:	 	None
 ************************************************************************/
extern void trCreate (TreeNodePtr *hsTree)
{
	//Error Checking
	if (NULL == hsTree)
	{
		processError ("trCreate", TR_NO_CREATE_ERROR);
	}

	//Set the root node to a null pointer
	*hsTree = NULL;

	return;
}

/*************************************************************************
 Function: 	 	trTerminate

 Description: Terminates the tree, freeing the memory on the heap

 Parameters:	hsTree - A handle to the tree to terminate

 Returned:	 	None
 ************************************************************************/
extern void trTerminate (TreeNodePtr *hsTree)
{
	//Error Checking
	if (NULL == hsTree)
	{
		processError ("trTerminate", TR_NO_TERMINATE_ERROR);
	}

	//Do nothing if the given node is NULL
	if (NULL != *hsTree)
	{
		//If the given node is a leaf, free its memory
		if (NULL == (*hsTree)->psLeft && NULL == (*hsTree)->psRight)
		{
			free (*hsTree);
			*hsTree = NULL;
		}
		else
		{
			//If the given node is not a leaf, then treat it like the root of a
			//tree, and free the nodes to the left and right sides of the tree,
			//then itself
			trTerminate (&(*hsTree)->psLeft);
			trTerminate (&(*hsTree)->psRight);
			free (*hsTree);
			*hsTree = NULL;
		}
	}

	return;
}

/*************************************************************************
 Function: 	 	trIsEmpty

 Description: Checks if the given tree is empty or not

 Parameters:	psTree - A pointer to the tree to check if empty or not

 Returned:	 	bool - true if the tree is empty, false if not
 ************************************************************************/
extern bool trIsEmpty (const TreeNodePtr psTree)
{
	bool bIsEmpty = false;

	if (NULL == psTree)
	{
		bIsEmpty = true;
	}

	return bIsEmpty;
}

/*************************************************************************
 Function: 	 	trInsert

 Description: Attempts to insert a new node into the tree. If the tree
 	 	 	 	 	 	  already contains a node with the same key, does nothing

 Parameters:	hsTree - A handle to the tree to insert a node into
 	 	 	 	 	 	 	key - a string containing the key for the node
 	 	 	 	 	 	 	value - an integer containing the data to store in the node

 Returned:	 	bool - true if the key was not already in the tree and a new
 	 	 	 	 	 	 	 	 	 	 node was added, false if the key was already in the
 	 	 	 	 	 	 	 	 	 	 tree and was not added
 ************************************************************************/
extern bool trInsert (TreeNodePtr *hsTree, const char* key, int value)
{
	bool bIsNewKey = false;
	TreeNodePtr psCurrentNode = *hsTree;
	TreeNodePtr psPrevNode;

	//Error Checking
	if (NULL == hsTree)
	{
		processError ("trInsert", TR_NO_MEMORY_ERROR);
	}
	if (NULL == key)
	{
		processError ("trInsert", TR_NO_BUFFER_ERROR);
	}

	//If the key is not already in the tree, add it
	if (!trFind (psCurrentNode, key, &value))
	{
		//If the tree is empty, create a new root node
		if (trIsEmpty (psCurrentNode))
		{
			psCurrentNode = (TreeNodePtr) malloc (sizeof (TreeNode));
			strncpy (psCurrentNode->szWord , key, WORD_MAX);
			psCurrentNode->count = value;
			psCurrentNode->psLeft = NULL;
			psCurrentNode->psRight = NULL;
			*hsTree = psCurrentNode;
		}
		//If the tree is not empty, find where the new node belongs and add it
		else
		{
			//Search through the tree until you find a NULL node
			while (psCurrentNode != NULL)
			{
				psPrevNode = psCurrentNode;
				if (strncmp (psCurrentNode->szWord, key, WORD_MAX) > 0)
				{
					psCurrentNode = psCurrentNode->psLeft;
				}
				else
				{
					psCurrentNode = psCurrentNode->psRight;
				}
			}
			//Move back to the node before the NULL node
			psCurrentNode = psPrevNode;
			//Insert the new node where it belongs
			if (strncmp (psCurrentNode->szWord, key, WORD_MAX) > 0)
			{
				psCurrentNode->psLeft = (TreeNodePtr) malloc (sizeof (TreeNode));
				psCurrentNode = psCurrentNode->psLeft;
			}
			else
			{
				psCurrentNode->psRight = (TreeNodePtr) malloc (sizeof (TreeNode));
				psCurrentNode = psCurrentNode->psRight;
			}
			strncpy (psCurrentNode->szWord , key, WORD_MAX);
			psCurrentNode->count = value;
			psCurrentNode->psLeft = NULL;
			psCurrentNode->psRight = NULL;
		}
		bIsNewKey = true;
	}

	return bIsNewKey;
}

/*************************************************************************
 Function: 	 	trUpdate

 Description: Updates the data of the node with the given key in the tree

 Parameters:	psTree - A pointer to the tree to update the data of
 	 	 	 	 	 	 	key - a strong containing the key of the node to update
 	 	 	 	 	 	 	value - the new data to be set in the node

 Returned:	 	bool - true if the key was contained in the tree and the
 	 	 	 	 	 	 	 	 	 	 node was updated, false if the key was not contained
 	 	 	 	 	 	 	 	 	 	 	in the tree and the node was not updated.
 ************************************************************************/
extern bool trUpdate (TreeNodePtr psTree, const char* key, int value)
{
	bool bKeyExists = false;
	int tempValue;
	TreeNodePtr psCurrentNode = psTree;

	//Error Checking
	if (NULL == key)
	{
		processError ("trUpdate", TR_NO_BUFFER_ERROR);
	}

	//Only update the key if it exists
	if (trFind (psTree, key, &tempValue))
	{
		bKeyExists = true;
		//Navigate the tree until the matching node is found
		while (strncmp (psCurrentNode->szWord, key, WORD_MAX) != 0)
		{
			if (strncmp (psCurrentNode->szWord, key, WORD_MAX) > 0)
			{
				psCurrentNode = psCurrentNode->psLeft;
			}
			else
			{
				psCurrentNode = psCurrentNode->psRight;
			}
		}
		//Set the new data in the node to the given value
		psCurrentNode->count = value;
	}

	return bKeyExists;
}

/*************************************************************************
 Function: 	 	trFind

 Description: Retrieves the data in the tree with the given key

 Parameters:	psTree - pointer to the tree to retrieve data from
 	 	 	 	 	 	 	key - a string containing the key of the node to
 	 	 	 	 	 	 				retrieve data from
 	 	 	 	 	 	 	pValue - a pointer to the integer that will be used to store
 	 	 	 	 	 	 					 the retrieved data

 Returned:	 	bool - true if a node with the given key was found and the
 	 	 	 	 	 	 	 	 	 	 data was retrieved, false if a node with the given
 	 	 	 	 	 	 	 	 	 	 key was not found.
 ************************************************************************/
extern bool trFind (const TreeNodePtr psTree, const char* key, int *pValue)
{
	bool bFound = true;
	TreeNodePtr psCurrentNode = psTree;

	//Error Checking
	if (NULL == key)
	{
		processError ("trFind", TR_NO_BUFFER_ERROR);
	}
	if (NULL == pValue)
	{
		processError ("trFind", TR_NO_BUFFER_ERROR);
	}

	//Look for the key in the tree, stop if found or reached the end of tree
	while (psCurrentNode != NULL &&
				 strncmp (psCurrentNode->szWord, key, WORD_MAX) != 0)
	{
		if (strncmp (psCurrentNode->szWord, key, WORD_MAX) > 0)
		{
			psCurrentNode = psCurrentNode->psLeft;
		}
		else
		{
			psCurrentNode = psCurrentNode->psRight;
		}
	}
	//If the key was found, retrieve the data
	if (psCurrentNode == NULL)
	{
		bFound = false;
	}
	else
	{
		*pValue = psCurrentNode->count;
		bFound = true;
	}

	return bFound;
}

/*************************************************************************
 Function: 	 	trPrintInOrder

 Description: Prints the given tree in alphabetical order of the keys.
 	 	 	 	 	 	 	Each key will be printed with the accompanying data.

 Parameters:	psTree - A pointer to the tree to print

 Returned:	 	None
 ************************************************************************/
extern void trPrintInOrder(const TreeNodePtr psTree)
{
	//If the given node is NULL, do nothing
	if (NULL != psTree)
	{
		//If the current node is a leaf, print it
		if (NULL == psTree->psLeft && NULL == psTree->psRight)
		{
			printf ("%s %d\n", psTree->szWord, psTree->count);
		}
		else
		{
			//If the node is not a leaf, print the left tree first, then
			//print itself, then print the right tree
			trPrintInOrder (psTree->psLeft);
			printf ("%s %d\n", psTree->szWord, psTree->count);
			trPrintInOrder (psTree->psRight);
		}
	}

	return;
}


/***************************************************************************
File name:  tree.c
Author:     Damon Holland
Date:       Nov 4, 2019
Class:      CS300
Assignment: 
Purpose:    
***************************************************************************/

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

extern void trLoadErrorMessages ()
{
	LOAD_ERRORS;
	return;
}

extern void trCreate (TreeNodePtr *hsTree)
{
	//Error Checking
	if (NULL == hsTree)
	{
		processError ("trCreate", TR_NO_CREATE_ERROR);
	}

	//Empty the tree
	trTerminate (hsTree);

	return;
}
// results: If the tree can be created, then the tree exists and is empty;
//					otherwise, TR_NO_CREATE_ERROR if psTree is NULL

extern void trTerminate (TreeNodePtr *hsTree)
{
	return;
}
// results: If the tree can be terminated, then the tree no longer exists
//				  and is empty; otherwise, TR_NO_TERMINATE_ERROR

extern bool trIsEmpty (const TreeNodePtr psTree)
{
	bool bIsEmpty = false;

	if (NULL == psTree)
	{
		bIsEmpty = true;
	}

	return bIsEmpty;
}
// results: If tree is empty, return true; otherwise, return false
// 					error code priority: TR_NO_MEMORY_ERROR


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
			strncpy((psCurrentNode)->szWord , key, WORD_MAX);
			(psCurrentNode)->count = value;
			(psCurrentNode)->psLeft = NULL;
			(psCurrentNode)->psRight = NULL;
			*hsTree = psCurrentNode;
		}
		//If the tree is not empty, find where it belongs and add it
		else
		{
			//Search through the tree until you find a null node
			while (psCurrentNode != NULL)
			{
				psPrevNode = psCurrentNode;
				if (strncmp(psCurrentNode->szWord, key, WORD_MAX) > 0)
				{
					psCurrentNode = psCurrentNode->psLeft;
				}
				else
				{
					psCurrentNode = psCurrentNode->psRight;
				}
			}
			psCurrentNode = psPrevNode;
			if (strncmp(psCurrentNode->szWord, key, WORD_MAX) > 0)
			{
				psCurrentNode->psLeft = (TreeNodePtr) malloc (sizeof (TreeNode));
				psCurrentNode = psCurrentNode->psLeft;
			}
			else
			{
				psCurrentNode->psRight = (TreeNodePtr) malloc (sizeof (TreeNode));
				psCurrentNode = psCurrentNode->psRight;
			}
			strncpy((psCurrentNode)->szWord , key, WORD_MAX);
			(psCurrentNode)->count = value;
			(psCurrentNode)->psLeft = NULL;
			(psCurrentNode)->psRight = NULL;
		}

		bIsNewKey = true;
	}



	return bIsNewKey;
}
// results: if the tree is valid, and the key does not exist in the
//					tree, insert the key/value and return true
//					If the key does exist in the tree return false and
//					do not alter the tree
//					error code priority: TR_NO_MEMORY_ERROR

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

	if (trFind (psTree, key, &tempValue))
	{
		bKeyExists = true;
		while (strncmp(psCurrentNode->szWord, key, WORD_MAX) != 0)
		{
			if (strncmp(psCurrentNode->szWord, key, WORD_MAX) > 0)
			{
				psCurrentNode = psCurrentNode->psLeft;
			}
			else
			{
				psCurrentNode = psCurrentNode->psRight;
			}
		}
		psCurrentNode->count = value;
	}
	return bKeyExists;
}
// results: if the tree is valid, and the key does exist in the
//					tree, update the node with the new value passed in and return
//					true.  If the key does not exist in the tree, return false
//					and do not alter the tree.
//					error code priority: TR_NO_MEMORY_ERROR

extern bool trFind (const TreeNodePtr psTree, const char* key, int *pValue)
{
	bool bFound = false;
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

	//Look for the key in the tree, stop when found or reached the end of tree
	while (psCurrentNode != NULL && strncmp(psCurrentNode->szWord, key, WORD_MAX) != 0)
	{
		if (psCurrentNode->szWord < key)
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
// results: if the tree is valid, and the key does exist in the
//					tree, return the value through pValue and return true.
//					The user must supply valid memory for pValue.
//					This function does not call malloc.
//				 	If the key does not exist in the tree, return false;
//					error code priority: TR_NO_MEMORY_ERROR, TR_NO_BUFFER_ERROR

extern void trPrintInOrder(const TreeNodePtr psTree)
{
	//If the given node is NULL, do nothing
	if (NULL != psTree)
	{
		//If the current node is a leaf, print it
		if (NULL == psTree->psLeft && NULL == psTree->psRight)
		{
			printf ("%s\n", psTree->szWord);
		}
		else
		{
			//If the node is not a leaf, print the left tree first, then
			//print itself, then print the right tree
			trPrintInOrder(psTree->psLeft);
			printf ("%s\n", psTree->szWord);
			trPrintInOrder(psTree->psRight);
		}
	}

	return;
}
// results: if the tree is valid, print the key and value for each node
//					in key order (ascending).
//					error code priority: TR_NO_MEMORY_ERROR

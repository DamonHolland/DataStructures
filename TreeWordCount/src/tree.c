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

	//Error Checking
	if (NULL == hsTree)
	{
		processError ("trInsert", TR_NO_MEMORY_ERROR);
	}
	if (NULL == key)
	{
		processError ("trInsert", TR_NO_BUFFER_ERROR);
	}

	if (!trFind (psCurrentNode, key, &value))
	{

		if (trIsEmpty (psCurrentNode))
		{
			psCurrentNode = (TreeNodePtr) malloc (sizeof (TreeNode));
			strncpy((psCurrentNode)->szWord , key, WORD_MAX);
			(psCurrentNode)->count = value;
			(psCurrentNode)->psLeft = NULL;
			(psCurrentNode)->psRight = NULL;
			*hsTree = psCurrentNode;
		}
		else
		{
			while (psCurrentNode != NULL)
			{
				if (psCurrentNode->szWord > key)
				{
					psCurrentNode = psCurrentNode->psLeft;
				}
				else
				{
					psCurrentNode = psCurrentNode->psRight;
				}
				psCurrentNode = (TreeNodePtr) malloc (sizeof (TreeNode));
				strncpy((psCurrentNode)->szWord , key, WORD_MAX);
				(psCurrentNode)->count = value;
				(psCurrentNode)->psLeft = NULL;
				(psCurrentNode)->psRight = NULL;
			}

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
	return false;
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
	while (psCurrentNode != NULL && psCurrentNode->szWord != key)
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
	if (NULL == psTree)
	{
		return;
	}

	//The current node is a leaf, so print it
	if (NULL == psTree->psLeft && NULL == psTree->psRight)
	{
		printf ("%s\n", psTree->szWord);
	}
	else
	{
		trPrintInOrder(psTree->psLeft);
		trPrintInOrder(psTree->psRight);
		printf ("%s\n", psTree->szWord);
	}
}
// results: if the tree is valid, print the key and value for each node
//					in key order (ascending).
//					error code priority: TR_NO_MEMORY_ERROR

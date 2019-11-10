/***************************************************************************
File name:  treeDriver.c
Author:     Damon Holland
Date:       Nov 4, 2019
Class:      CS300
Assignment: 
Purpose:    
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "../include/tree.h"


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

int main ()
{
	TreeNodePtr psRoot;

	trLoadErrorMessages ();

	//******************** Test trCreate ********************
	trCreate (&psRoot);
	//Ensure the tree is initially empty
	assert (trIsEmpty (psRoot), "Tree empty after creation",
					"Tree is NOT empty after creation");

	//******************** Test trInsert ********************
	trInsert (&psRoot, "F", 6);
	assert (!trIsEmpty (psRoot), "Tree is not empty after insertion",
						"Tree IS empty after insertion");
	trInsert (&psRoot, "D", 6);
	trInsert (&psRoot, "A", 6);
	trInsert (&psRoot, "C", 6);
	trInsert (&psRoot, "H", 6);
	trInsert (&psRoot, "G", 6);

	trUpdate (psRoot, "I", 12);

	trPrintInOrder (psRoot);

	trTerminate (&psRoot);
	assert (trIsEmpty (psRoot), "Tree empty after Termination",
					"Tree is NOT empty after Termination");

	return EXIT_SUCCESS;
}

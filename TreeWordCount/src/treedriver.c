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

	//******************** Test queueCreate ********************
	trCreate (&psRoot);
	assert (trIsEmpty (psRoot), "Tree empty after creation",
					"Tree is NOT empty after creation");

	trInsert (&psRoot, "F", 6);
	trInsert (&psRoot, "C", 3);
	trInsert (&psRoot, "A", 1);
	trInsert (&psRoot, "B", 2);
	trInsert (&psRoot, "G", 7);
	trInsert (&psRoot, "D", 4);
	trInsert (&psRoot, "I", 9);

	trUpdate (psRoot, "I", 12);

	trPrintInOrder (psRoot);

	printf ("Build Success\n");

	return EXIT_SUCCESS;
};

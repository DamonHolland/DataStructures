/*************************************************************************
File name:  pqueuedriver.c
Author:     Damon Holland
Date:       Oct 10, 2019
Class:      CS300
Assignment: GenericDynamicPriorityQ
Purpose:    This file is the driver used to test the priority queue
*************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "../include/pqueue.h"

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
 Function: 	 	main

 Description: Test all the functionality of the Priority Queue

 Parameters:	none

 Returned:	 	Exit Status
 ************************************************************************/
int main()
{

	pqueueLoadErrorMessages ();


	assert (true, "Program Builds Successfully!", "Program Build Failed");

	return EXIT_SUCCESS;
}

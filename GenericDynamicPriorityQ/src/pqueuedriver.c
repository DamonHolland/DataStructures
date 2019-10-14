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
	//Constant variables to be inserted into the queue
	const int EXPECTED_INT = 42;
	const char EXPECTED_CHAR = 'K';
	const bool bEXPECTED_BOOL = true;

	//Constant variables to reset test data
	const int RESET_INT = 0;
	const char RESET_CHAR = 'A';
	const bool bRESET_BOOL = false;

	//Constant variables to be used as priorities
	const int HIGH_PRIORITY = 0;
	const int MEDIUM_PRIORITY = 5;
	const int LOW_PRIORITY = 10;

	//Constants to be used for testing within loops
	const bool bLOOP_TEST_RESET = true;
	const bool bLOOP_TEST_SUCCESS = true;
	const bool bLOOP_TEST_FAILED = false;

	//Constants to be used for loop testing
	const int LOOP_AMOUNT_LOW = 10;
	const int LOOP_AMOUNT_MEDIUM = 50;
	const int LOOP_AMOUNT_HIGH = 200;
	const int LOOP_AMOUNT_STRESS = 100000000;

	//Iterator to be used for loop testing
	int i = 0;

	//Variable used to test loops
	bool bLoopTest = bLOOP_TEST_RESET;

	//Variables used to store and test data from queue
	int actualInt = RESET_INT;
	char actualChar = RESET_CHAR;
	bool actualBool = bRESET_BOOL;

	//The queue being used for testing
	PriorityQueue sTheQueue;

	pqueueLoadErrorMessages ();

	//******************** Test pqueueCreate ********************
	pqueueCreate (&sTheQueue);
	//Ensure the queue is initially empty
	assert (pqueueIsEmpty (&sTheQueue), "PQ is empty after creation",
					"PQ is NOT empty after creation");

	//******************** Test pqueueSize ********************
	//Reset variables used for testing
	pqueueTerminate(&sTheQueue);
	pqueueCreate (&sTheQueue);
	//Ensure the size is 0 after creation
	assert (pqueueSize (&sTheQueue) == 0,
					"pqueueSize returns 0 after creation",
					"pqueueSize DOES NOT return 0 after creation");
	//Now insert one element and ensure the size becomes 1
	pqueueEnqueue (&sTheQueue, &EXPECTED_INT, sizeof (EXPECTED_INT),
								 MEDIUM_PRIORITY);
	assert (pqueueSize (&sTheQueue) == 1,
					"pqueueSize returns 1 after adding 1 element",
					"pqueueSize DOES NOT return 1 after adding 1 element");
	//Test queue size within a loop
	//Reset Variables for loop test;
	pqueueTerminate(&sTheQueue);
	pqueueCreate (&sTheQueue);
	bLoopTest = bLOOP_TEST_RESET;
	//Add multiple elements to queue and ensure pqueueSize returns
	//correct size after each add
	for (i = 1; i <= LOOP_AMOUNT_MEDIUM; i++)
	{
		pqueueEnqueue (&sTheQueue, &EXPECTED_INT, sizeof (EXPECTED_INT),
									 MEDIUM_PRIORITY);
		if (pqueueSize (&sTheQueue) != i)
		{
			bLoopTest = bLOOP_TEST_FAILED;
		}
	}
	assert (bLoopTest,
					"pqueueSize returns correct value when adding many elements",
					"pqueueSize returns incorrect value when adding many elements");

	//******************** Test pqueueIsEmpty ********************
	//Reset variables used for testing
	pqueueTerminate(&sTheQueue);
	pqueueCreate (&sTheQueue);
	//Ensure pqueueIsEmpty is true after creation
	assert (pqueueIsEmpty (&sTheQueue),
					"pqueueIsEmpty returns true after creation",
					"pqueueIsEmpty DOES NOT return true after creation");
	//Test queueIsEmpty within a loop
	//Reset Variables for loop test;
	pqueueTerminate(&sTheQueue);
	pqueueCreate (&sTheQueue);
	bLoopTest = bLOOP_TEST_RESET;
	//Add multiple elements to queue and ensure pqueueIsEmpty returns
	//false after each add
	for (i = 1; i <= LOOP_AMOUNT_MEDIUM; i++)
	{
		pqueueEnqueue (&sTheQueue, &EXPECTED_INT, sizeof (EXPECTED_INT),
									 MEDIUM_PRIORITY);
		if (pqueueIsEmpty (&sTheQueue))
		{
			bLoopTest = bLOOP_TEST_FAILED;
		}
	}
	assert (bLoopTest,
					"pqueueIsEmpty is false with multiple elements added",
					"pqueueIsEmpty is NOT false with multiple elements added");


	//******************** Test pqueueTerminate ********************
	pqueueTerminate(&sTheQueue);




	return EXIT_SUCCESS;
}

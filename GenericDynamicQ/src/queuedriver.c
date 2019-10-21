/*************************************************************************
File name:  queuedriver.c
Author:     Damon Holland
Date:       Oct 20, 2019
Class:      CS300
Assignment: Airport
Purpose:    This file is the driver used to test the queue
*************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "../include/queue.h"

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

 Description: Test all the functionality of the Queue

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
	const int RESET_INT = -5;
	const char RESET_CHAR = 'A';
	const bool bRESET_BOOL = false;

	//Constants to be used for testing within loops
	const bool bLOOP_TEST_RESET = true;
	const bool bLOOP_TEST_SUCCESS = true;
	const bool bLOOP_TEST_FAILED = false;

	//Constants to be used for loop testing
	const int LOOP_AMOUNT_MEDIUM = 50;
	const int LOOP_AMOUNT_STRESS = 10000;

	//Iterator to be used for loop testing
	int i = 0;

	//Boolean to store result multiple conditions
	bool bLoopTest = bLOOP_TEST_RESET;

	//Variables used to store and test data from queue
	int actualInt = RESET_INT;
	char actualChar = RESET_CHAR;
	bool bActualBool = bRESET_BOOL;

	//The queue being used for testing
	Queue sTheQueue;

	queueLoadErrorMessages ();

	//******************** Test queueCreate ********************
	queueCreate (&sTheQueue);
	//Ensure the queue is initially empty
	assert (queueIsEmpty (&sTheQueue), "Q is empty after creation",
					"Q is NOT empty after creation");

	//******************** Test queueSize ********************
	//Reset variables used for testing
	queueTerminate (&sTheQueue);
	queueCreate (&sTheQueue);
	//Ensure the size is 0 after creation
	assert (queueSize (&sTheQueue) == 0,
					"queueSize returns 0 after creation",
					"queueSize DOES NOT return 0 after creation");
	//Now insert one element and ensure the size becomes 1
	queueEnqueue (&sTheQueue, &EXPECTED_INT, sizeof (EXPECTED_INT));
	assert (queueSize (&sTheQueue) == 1,
					"queueSize returns 1 after adding 1 element",
					"queueSize DOES NOT return 1 after adding 1 element");
	//Test queue size within a loop
	//Reset Variables for loop test;
	queueTerminate (&sTheQueue);
	queueCreate (&sTheQueue);
	bLoopTest = bLOOP_TEST_RESET;
	//Add multiple elements to queue and ensure queueSize returns
	//correct size after each add
	for (i = 1; i <= LOOP_AMOUNT_MEDIUM; i++)
	{
		queueEnqueue (&sTheQueue, &EXPECTED_INT, sizeof (EXPECTED_INT));
		if (queueSize (&sTheQueue) != i)
		{
			bLoopTest = bLOOP_TEST_FAILED;
		}
	}
	assert (bLOOP_TEST_SUCCESS == bLoopTest,
					"queueSize returns correct value when adding many elements",
					"queueSize returns incorrect value when adding many elements");

	//******************** Test queueIsEmpty ********************
	//Reset variables used for testing
	queueTerminate (&sTheQueue);
	queueCreate (&sTheQueue);
	//Ensure queueIsEmpty is true after creation
	assert (queueIsEmpty (&sTheQueue),
					"queueIsEmpty returns true after creation",
					"queueIsEmpty DOES NOT return true after creation");
	//Test queueIsEmpty within a loop
	//Reset Variables for loop test;
	queueTerminate (&sTheQueue);
	queueCreate (&sTheQueue);
	bLoopTest = bLOOP_TEST_RESET;
	//Add multiple elements to queue and ensure queueIsEmpty returns
	//false after each add
	for (i = 1; i <= LOOP_AMOUNT_MEDIUM; i++)
	{
		queueEnqueue (&sTheQueue, &EXPECTED_INT, sizeof (EXPECTED_INT));
		if (queueIsEmpty (&sTheQueue))
		{
			bLoopTest = bLOOP_TEST_FAILED;
		}
	}
	assert (bLOOP_TEST_SUCCESS == bLoopTest,
					"queueIsEmpty is false with multiple elements added",
					"queueIsEmpty is NOT false with multiple elements added");

	//******************** Test queueEnqueue ********************
	//Reset variables used for testing
	queueTerminate (&sTheQueue);
	queueCreate (&sTheQueue);
	actualInt = RESET_INT;
	actualChar = RESET_CHAR;
	//Enqueue data
	queueEnqueue (&sTheQueue, &EXPECTED_INT,
								 sizeof (EXPECTED_INT));
	queueEnqueue (&sTheQueue, &EXPECTED_CHAR,
								 sizeof (EXPECTED_CHAR));
	//Peek the data, checking if the data is correct
	//The Peeked data should match the data added first
	queuePeek (&sTheQueue, &actualInt, sizeof (actualInt));
	assert ((EXPECTED_INT == actualInt),
					"elements added to queue correctly",
					"elements NOT added to queue correctly");
	//Test queueEnqueue within a very large loop for a stress test, then
	//use queueDequeue to verify the data that was added
	//Reset variables used for testing
	queueTerminate (&sTheQueue);
	queueCreate (&sTheQueue);
	actualInt = RESET_INT;
	bLoopTest = bLOOP_TEST_RESET;
	//Add a very large amount of items to the queue
	for (i = 0; i < LOOP_AMOUNT_STRESS; i++)
	{
		queueEnqueue (&sTheQueue, &i, sizeof (i));
	}
	//Dequeue to test all data added
	for (i = 0; i < LOOP_AMOUNT_STRESS; i++)
	{
		queueDequeue (&sTheQueue, &actualInt, sizeof (actualInt));
		if ((actualInt != i))
		{
			bLoopTest = bLOOP_TEST_FAILED;
		}
	}
	assert (bLOOP_TEST_SUCCESS == bLoopTest,
					"Many elements added to queue correctly",
					"Many elements NOT added to queue correctly");

	//******************** Test queueDequeue ********************
	//Reset variables used for testing
	queueTerminate (&sTheQueue);
	queueCreate (&sTheQueue);
	actualInt = RESET_INT;
	actualChar = RESET_CHAR;
	bActualBool = bRESET_BOOL;
	bLoopTest = bLOOP_TEST_RESET;
	//Enqueue data
	queueEnqueue (&sTheQueue, &EXPECTED_INT,
								 sizeof (EXPECTED_INT));
	queueEnqueue (&sTheQueue, &EXPECTED_CHAR,
								 sizeof (EXPECTED_CHAR));
	queueEnqueue (&sTheQueue, &bEXPECTED_BOOL,
								 sizeof (bEXPECTED_BOOL));
	//Dequeue data and ensure the correct data was dequeued,
	//and the size of the queue decreases accordingly
	queueDequeue (&sTheQueue, &actualInt, sizeof (actualInt));
	if ((EXPECTED_INT != actualInt) || (queueSize (&sTheQueue) != 2))
	{
		bLoopTest = bLOOP_TEST_FAILED;
	}
	queueDequeue (&sTheQueue, &actualChar, sizeof (actualChar));
	if ((EXPECTED_CHAR != actualChar) || (queueSize (&sTheQueue) != 1))
	{
		bLoopTest = bLOOP_TEST_FAILED;
	}
	queueDequeue (&sTheQueue, &bActualBool, sizeof (bActualBool));
	if ((bEXPECTED_BOOL != bActualBool) || (queueSize (&sTheQueue) != 0))
	{
		bLoopTest = bLOOP_TEST_FAILED;
	}
	assert (bLOOP_TEST_SUCCESS == bLoopTest,
					"Many elements dequeued correctly",
					"Many elements NOT dequeued correctly");

	//******************** Test queuePeek ********************
	//Reset variables used for testing
	queueTerminate (&sTheQueue);
	queueCreate (&sTheQueue);
	actualInt = RESET_INT;
	actualChar = RESET_CHAR;
	//Enqueue 1 element
	queueEnqueue (&sTheQueue, &EXPECTED_INT,
								 sizeof (EXPECTED_INT));
	//Peek the element
	queuePeek (&sTheQueue, &actualInt, sizeof (actualInt));
	//Ensure the data was peeked correctly
	assert ((EXPECTED_INT == actualInt),
					"Peeked correctly with 1 element in queue",
					"Peeked INCORRECTLY with 1 element in queue");
	//Enqueue another element
	queueEnqueue (&sTheQueue, &EXPECTED_CHAR, sizeof (EXPECTED_CHAR));
	//Peek again, should still be the first element, it was never removed
	queuePeek (&sTheQueue, &actualInt, sizeof (actualInt));
	//Ensure the data was peeked correctly
	assert ((EXPECTED_INT == actualInt),
						"Peeked correctly with 2 elements in queue",
						"Peeked INCORRECTLY with 2 elements in queue");
	//Enqueue another element then dequeue the first
	queueEnqueue (&sTheQueue, &bEXPECTED_BOOL,
								 sizeof (bEXPECTED_BOOL));
	queueDequeue (&sTheQueue, &actualInt, sizeof(actualInt));
	//Peek the new first element
	queuePeek (&sTheQueue, &actualChar, sizeof (actualChar));
	//Ensure the data was peeked correctly
	assert ((EXPECTED_CHAR == actualChar),
					"Peeked correctly after dequeue",
					"Peeked INCORRECTLY after dequeue");

	//******************** Test queueTerminate ********************
	//Reset variables used for testing
	queueTerminate (&sTheQueue);
	queueCreate (&sTheQueue);
	//Add a few elements to the queue
	for (i = 1; i <= LOOP_AMOUNT_MEDIUM; i++)
	{
	queueEnqueue (&sTheQueue, &EXPECTED_INT, sizeof (EXPECTED_INT));
	}
	//Terminate the queue and ensure the queue is now empty
	queueTerminate (&sTheQueue);
	assert (queueIsEmpty (&sTheQueue),
					"Queue is empty after termination",
					"Queue is NOT empty after termination");



	return EXIT_SUCCESS;
}

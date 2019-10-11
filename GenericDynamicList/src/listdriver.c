/***************************************************************************
File name:  listdriver.c
Author:     Damon Holland
Date:       Sep 19, 2019
Class:      CS300
Assignment: Generic Dynamic List
Purpose:    The driver used to test list functions
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "../include/list.h"

/**************************************************************************
 Function: 	 	success

 Description: print a success message

 Parameters:	szStr - the message to print
 Returned:	 	none
 *************************************************************************/
static void success (char * szStr)
{
	printf ("SUCCESS: %s\n", szStr);
}

/**************************************************************************
 Function: 	 	failure

 Description: print a failure message

 Parameters:	szStr - the message to print
 Returned:	 	none
 *************************************************************************/
static void failure (char * szStr)
{
	printf ("FAILURE: %s\n", szStr);
	exit (EXIT_FAILURE);
}

/****************************************************************************
 Function: 	 	assert

 Description: if the expression is true, assert success; otherwise, assert
 	 	 	 	 	 	 	failure

 Parameters:	szStr - the message to print

 Returned:	 	none
 ****************************************************************************/
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

/**************************************************************************
 Function: 	 	main

 Description: test all the functionality of the list

 Parameters:	none

 Returned:	 	Exit Status
 *************************************************************************/
int main(){
	List sTheList;

	//The expected data inserted into lists
	const char EXPECTED_CHAR = 'A';
	const int EXPECTED_INT = 10;
	const double EXPECTED_DOUBLE = 5.8;

	//The values to reset buffers
	const char RESET_CHAR = 'Z';
	const int RESET_INT = 0;
	const double RESET_DOUBLE = 0;

	//The constant values to use for loop tests
	const bool LOOP_TEST_RESET = true;
	const bool LOOP_TEST_FAIL = false;
	const int LOOP_TEST_AMOUNT = 100;

	//The variables used as buffers
	char actualChar = RESET_CHAR;
	int actualInt = RESET_INT;
	double actualDouble = RESET_DOUBLE;

	//variables used for loop tests
	bool bLoopTest = LOOP_TEST_RESET;
	int i = 0;




	//Initialize List Functions
	lstLoadErrorMessages();

	//********** Test lstCreate **********
	lstCreate(&sTheList);
	//Check if List is initially empty
	assert(lstIsEmpty(&sTheList), "List is empty after creation",
				 "List is NOT empty after creation");
	success("List Created Successfully");

	//********** Test lstInsertAfter **********
	//Reset Items needed to test
	lstTerminate(&sTheList);
	lstCreate(&sTheList);
	actualChar = RESET_CHAR;
	actualInt = RESET_INT;
	actualDouble = RESET_DOUBLE;
	//Insert data
	lstInsertAfter(&sTheList, &EXPECTED_CHAR, sizeof(EXPECTED_CHAR));
	//Check if data inserted is correct
	lstPeek(&sTheList, &actualChar, sizeof(actualChar));
	assert(EXPECTED_CHAR == actualChar, "Data was inserted correctly",
				 "Data was inserted incorrectly");
	//Check if size is correct after insertion
	assert(1 == lstSize(&sTheList), "Size is correct after insertion",
				 "Size is incorrect after insertion");
	//Insert another element to the list
	lstInsertAfter(&sTheList, &EXPECTED_INT, sizeof(EXPECTED_INT));
	//Check if data is correct
	lstPeek(&sTheList, &actualInt, sizeof(actualInt));
	assert(EXPECTED_INT == actualInt, "2nd element was inserted correctly",
				 "2nd element was inserted incorrectly");
	//Check If Size is Correct
	assert(2 == lstSize(&sTheList), "Size is correct after insertion",
					 "Size is incorrect after insertion");
	//Add another element to the list
	lstInsertAfter(&sTheList, &EXPECTED_DOUBLE, sizeof(EXPECTED_DOUBLE));
	//Check if data is correct
	lstPeek(&sTheList, &actualDouble, sizeof(actualDouble));
	assert(EXPECTED_DOUBLE == actualDouble,
				  "3rd element was inserted correctly",
					"3rd element was inserted incorrectly");
	//Check if the size is correct
	assert(3 == lstSize(&sTheList), "Size is correct after insertion",
				 "Size is incorrect after insertion");
	//Insert in a loop
	//Reset testing variables
	lstTerminate(&sTheList);
	lstCreate(&sTheList);
	bLoopTest = LOOP_TEST_RESET;
	for(i = 1; i <= LOOP_TEST_AMOUNT; i++)
	{
		//Insert and Peek Data
		lstInsertAfter(&sTheList, &i, sizeof(i));
		lstPeek(&sTheList, &actualInt, sizeof(actualInt));
		//Make sure size and data are correct
		if( !((i) == lstSize(&sTheList)))
		{
			bLoopTest = false;
		}
		if(actualInt != i)
		{
			bLoopTest = false;
		}
	}
	//Print if the loop test was successful
	assert(bLoopTest, "Elements were inserted correctly in loop",
				 "Elements added incorrectly in loop");


	//********** Test lstSize **********
	//Reset Items needed to test
	lstTerminate(&sTheList);
	lstCreate(&sTheList);
	bLoopTest = LOOP_TEST_RESET;
	//Check if size is correct after creation
	assert(0 == lstSize(&sTheList), "List size correct after creation",
				 "List size NOT correct after creation");
	//Insert data
	lstInsertAfter(&sTheList, &EXPECTED_CHAR, sizeof(EXPECTED_CHAR));
	//Check if size is correct after insertion
	assert(1 == lstSize(&sTheList), "List size correct after insertion",
				 "List size NOT correct after insertion");
	//Test the lstSize with many elements in a loop
	lstTerminate(&sTheList);
	lstCreate(&sTheList);
	for(i = 1; i <= LOOP_TEST_AMOUNT; i++)
	{
		lstInsertAfter(&sTheList, &EXPECTED_CHAR, sizeof(EXPECTED_CHAR));
		if(i != lstSize(&sTheList))
		{
			bLoopTest = false;
		}
	}
	//Check if size was correct during loop test
	assert(bLoopTest, "List size correct during multiple insertions",
				 "List size NOT correct during multiple insertions");


	//********** Test lstIsEmpty **********
	//Reset Items needed to test
	lstTerminate(&sTheList);
	lstCreate(&sTheList);
	bLoopTest = LOOP_TEST_RESET;
	//Check if List is initially empty
	assert(lstIsEmpty(&sTheList), "List is empty after creation",
				 "List is NOT empty after creation");
	//Insert data
	lstInsertAfter(&sTheList, &EXPECTED_CHAR, sizeof(EXPECTED_CHAR));
	//Check if List is empty after insertion
	assert(!lstIsEmpty(&sTheList), "List is not empty after insertion",
				 "List is empty after insertion");
	//Insert multiple items
	for(i = 1; i <= LOOP_TEST_AMOUNT; i++)
	{
		if(lstIsEmpty(&sTheList))
		{
			bLoopTest = LOOP_TEST_FAIL;
		}
	}
	//Check if list is still empty after inserting multiple items
	assert(bLoopTest, "List is not empty after multiple insertions",
					 "List is empty after multiple insertions");


	//********** Test lstFirst **********
	//Reset Items needed to test
	lstTerminate(&sTheList);
	lstCreate(&sTheList);
	bLoopTest = LOOP_TEST_RESET;
	actualChar = RESET_CHAR;
	actualInt = RESET_INT;
	actualDouble = RESET_DOUBLE;
	//Insert 2 items into the list
	lstInsertAfter(&sTheList, &EXPECTED_CHAR, sizeof(EXPECTED_CHAR));
	lstInsertAfter(&sTheList, &EXPECTED_INT, sizeof(EXPECTED_INT));
	//Move to first in list
	lstFirst(&sTheList);
	//Peek first element
	lstPeek(&sTheList, &actualChar, sizeof(actualChar));
	//Ensure peeked data was the first added
	assert(EXPECTED_CHAR == actualChar,
				 "Moved to first element in list with 2 elements",
				 "Did NOT move to first element in list with 2 elements");
	//Test again with another element added
	actualChar = RESET_CHAR;
	lstInsertAfter(&sTheList, &EXPECTED_DOUBLE, sizeof(EXPECTED_DOUBLE));
	lstFirst(&sTheList);
	lstPeek(&sTheList, &actualChar, sizeof(actualChar));
	assert(EXPECTED_CHAR == actualChar,
				 "Moved to first element in list with 3 elements",
				 "Did NOT move to first element in list with 3 elements");
	//Test lstFirst with a loop
	lstTerminate(&sTheList);
	lstCreate(&sTheList);
	//First element is a character
	lstInsertAfter(&sTheList, &EXPECTED_CHAR, sizeof(EXPECTED_CHAR));
	for(i = 1; i <= LOOP_TEST_AMOUNT; i++)
	{
		//All elements other than first are integers
		lstInsertAfter(&sTheList, &EXPECTED_INT, sizeof(EXPECTED_INT));
		lstFirst(&sTheList);
		lstPeek(&sTheList, &actualChar, sizeof(actualChar));
		//Loop test will fail if first element was not peeked
		if(EXPECTED_CHAR != actualChar)
		{
			bLoopTest = LOOP_TEST_FAIL;
		}
	}
	assert(bLoopTest, "Moved to first element in a loop",
				 "Did NOT move to first element in a loop");


	//********** Test lstPeek **********
	//Reset Items needed to test
	lstTerminate(&sTheList);
	lstCreate(&sTheList);
	actualChar = RESET_CHAR;
	actualInt = RESET_INT;
	actualDouble = RESET_DOUBLE;
	bLoopTest = LOOP_TEST_RESET;
	//Insert data
	lstInsertAfter(&sTheList, &EXPECTED_CHAR, sizeof(EXPECTED_CHAR));
	lstPeek(&sTheList, &actualChar, sizeof(actualChar));
	//Check if peeked data matches inserted data
	assert(EXPECTED_CHAR == actualChar, "Data was peeked correctly",
				 "Data was peeked incorrectly");
	//Insert another element to the list
	lstInsertAfter(&sTheList, &EXPECTED_INT, sizeof(EXPECTED_INT));
	lstPeek(&sTheList, &actualInt, sizeof(actualInt));
	//Check if peeked data matches inserted data
	assert(EXPECTED_CHAR == actualChar, "Data was peeked correctly",
						 "Data was peeked incorrectly");
	//Add another element to the list
	lstInsertAfter(&sTheList, &EXPECTED_DOUBLE, sizeof(EXPECTED_DOUBLE));
	lstPeek(&sTheList, &actualDouble, sizeof(actualDouble));
	//Check if peeked data matches inserted data
	assert(EXPECTED_DOUBLE == actualDouble, "Data was peeked correctly",
						"Data was peeked incorrectly");
	//Test lstPeek in a loop
	lstTerminate(&sTheList);
	lstCreate(&sTheList);
	for(i = 1; i <= LOOP_TEST_AMOUNT; i++)
	{
		//Insert and Peek Data
		lstInsertAfter(&sTheList, &i, sizeof(i));
		lstPeek(&sTheList, &actualInt, sizeof(actualInt));
		//Make sure peeked data matches inserted data
		if(actualInt != i)
		{
			bLoopTest = LOOP_TEST_FAIL;
		}
	}
	//Print if the loop test was successful
	assert(bLoopTest, "Elements were peeked correctly in loop",
				 "Elements were peeked incorrectly in loop");


	//********** Test lstNext **********
	//Reset Items needed to test
	lstTerminate(&sTheList);
	lstCreate(&sTheList);
	actualChar = RESET_CHAR;
	actualInt = RESET_INT;
	actualDouble = RESET_DOUBLE;
	//Insert data
	lstInsertAfter(&sTheList, &EXPECTED_CHAR, sizeof(EXPECTED_CHAR));
	lstInsertAfter(&sTheList, &EXPECTED_INT, sizeof(EXPECTED_INT));
	lstInsertAfter(&sTheList, &EXPECTED_DOUBLE, sizeof(EXPECTED_DOUBLE));
	//Move to front of list
	lstFirst(&sTheList);
	//Move to next element
	lstNext(&sTheList);
	lstPeek(&sTheList, &actualInt, sizeof(actualInt));
	//Check if peeked value matches the 2nd element
	assert(EXPECTED_INT == actualInt, "Moved to next element correctly",
							"Moved to next element incorrectly");
	//Repeat
	lstNext(&sTheList);
	lstPeek(&sTheList, &actualDouble, sizeof(actualDouble));
	//Check if peeked value matches the 3rd element
	assert(EXPECTED_INT == actualInt, "Moved to next element correctly",
								"Moved to next element incorrectly");


	//********** Test lstHasCurrent **********
	//Reset Items needed to test
	lstTerminate(&sTheList);
	lstCreate(&sTheList);
	assert(!lstHasCurrent(&sTheList), "No current element after creation",
				 "Current element after creation");
	//Add an element
	lstInsertAfter(&sTheList, &EXPECTED_CHAR, sizeof(EXPECTED_CHAR));
	assert(lstHasCurrent(&sTheList), "Current element after insertion",
				 "No current element after insertion");
	//Move to null with lstNext
	lstNext(&sTheList);
	assert(!lstHasCurrent(&sTheList),
				 "No current element after moving to NULL element",
				 "Current element after moving to NULL element");
	//Move back to element with lstFirst
	lstFirst(&sTheList);
	assert(lstHasCurrent(&sTheList),
				 "Current element after moving back to element",
				 "No current element after moving to back to element");


	//********** Test lstUpdateCurrent **********
	//Reset Items needed to test
	lstTerminate(&sTheList);
	lstCreate(&sTheList);
	actualInt = RESET_INT;
	//Insert data
	lstInsertAfter(&sTheList, &EXPECTED_CHAR, sizeof(EXPECTED_CHAR));
	//Change data using update current
	lstUpdateCurrent(&sTheList, &EXPECTED_INT, sizeof(EXPECTED_INT));
	//Ensure the data was changed
	lstPeek(&sTheList, &actualInt, sizeof(actualInt));
	assert(EXPECTED_INT == actualInt, "Data was updated correctly",
				 "Data was updated incorrectly");


	//********** Test lstHasNext **********
	//Reset Items needed to test
	lstTerminate(&sTheList);
	lstCreate(&sTheList);
	//Insert data
	lstInsertAfter(&sTheList, &EXPECTED_CHAR, sizeof(EXPECTED_CHAR));
	//Ensure list has no next element after single element inserted
	assert(!lstHasNext(&sTheList),
			   "No next element after single element inserted",
				 "Next element after single element inserted");
	//Insert another element and switch to first
	lstInsertAfter(&sTheList, &EXPECTED_CHAR, sizeof(EXPECTED_CHAR));
	lstFirst(&sTheList);
	assert(lstHasNext(&sTheList), "There is a next element",
				 "There is NO next element");


	//********** Test lstPeekNext **********
	//Reset Items needed to test
	lstTerminate(&sTheList);
	lstCreate(&sTheList);
	actualInt = RESET_INT;
	actualDouble = RESET_DOUBLE;
	//Insert Elements and set current to first element
	lstInsertAfter(&sTheList, &EXPECTED_CHAR, sizeof(EXPECTED_CHAR));
	lstInsertAfter(&sTheList, &EXPECTED_INT, sizeof(EXPECTED_INT));
	lstInsertAfter(&sTheList, &EXPECTED_DOUBLE, sizeof(EXPECTED_DOUBLE));
	lstFirst(&sTheList);
	//Check if PeekNext retrieves data from 2nd element
	lstPeekNext(&sTheList, &actualInt, sizeof(actualInt));
	assert(EXPECTED_INT == actualInt, "Peeked the next element",
				 "Did NOT peek the next element");
	//Set current to 2nd element
	lstNext(&sTheList);
	//Check if PeekNext retrieves data from 3rd element
	lstPeekNext(&sTheList, &actualDouble, sizeof(actualDouble));
	assert(EXPECTED_DOUBLE == actualDouble, "Peeked the next element",
				 "Did NOT peek the next element");


	//********** Test lstDeleteCurrent **********
	//Reset Items needed to test
	lstTerminate(&sTheList);
	lstCreate(&sTheList);
	actualChar = RESET_CHAR;
	//Test Deletion with 1 element
	//Add data to the list, then delete current
	lstInsertAfter(&sTheList, &EXPECTED_CHAR, sizeof(EXPECTED_CHAR));
	lstDeleteCurrent(&sTheList, &actualChar, sizeof(actualChar));
	//Ensure the list is now empty, and the correct data was retrieved
	assert((lstIsEmpty(&sTheList)) && (EXPECTED_CHAR == actualChar),
					"Correctly deleted the only element in list",
					"Incorrectly deleted the only element in list");
	//Test lstDeleteCurrent with 2 elements, starting with
	//current as the first
	//Reset Items needed to test
	lstTerminate(&sTheList);
	lstCreate(&sTheList);
	actualChar = RESET_CHAR;
	actualInt = RESET_INT;
	//Add data to the list
	lstInsertAfter(&sTheList, &EXPECTED_CHAR, sizeof(EXPECTED_CHAR));
	lstInsertAfter(&sTheList, &EXPECTED_INT, sizeof(EXPECTED_INT));
	lstFirst(&sTheList);
	//Delete Current
	lstDeleteCurrent(&sTheList, &actualChar, sizeof(actualChar));
	lstDeleteCurrent(&sTheList, &actualInt, sizeof(actualInt));
	//Ensure the correct data was retrieved and list is now empty
	assert((lstIsEmpty(&sTheList)) && (EXPECTED_CHAR == actualChar)
					&& (EXPECTED_INT == actualInt),
					"Correctly deleted two elements in list",
					"Incorrectly deleted two elements in list");
	//Test lstDeleteCurrent with 2 elements, starting with
	//current as the last
	//Reset Items needed to test
	lstTerminate(&sTheList);
	lstCreate(&sTheList);
	actualChar = RESET_CHAR;
	actualInt = RESET_INT;
	//Add data to the list
	lstInsertAfter(&sTheList, &EXPECTED_CHAR, sizeof(EXPECTED_CHAR));
	lstInsertAfter(&sTheList, &EXPECTED_INT, sizeof(EXPECTED_INT));
	//Delete Current
	lstDeleteCurrent(&sTheList, &actualInt, sizeof(actualInt));
	lstDeleteCurrent(&sTheList, &actualChar, sizeof(actualChar));
	//Ensure the correct data was retrieved and list is now empty
	assert((lstIsEmpty(&sTheList)) && (EXPECTED_CHAR == actualChar) &&
					(EXPECTED_INT == actualInt),
					"Correctly deleted two elements in list",
					"Incorrectly deleted two elements in list");
	//Test lstDeleteCurrent with current between elements
	//Reset Items needed to test
	lstTerminate(&sTheList);
	lstCreate(&sTheList);
	actualInt = RESET_INT;
	//Add data to the list
	lstInsertAfter(&sTheList, &EXPECTED_CHAR, sizeof(EXPECTED_CHAR));
	lstInsertAfter(&sTheList, &EXPECTED_INT, sizeof(EXPECTED_INT));
	lstInsertAfter(&sTheList, &EXPECTED_DOUBLE, sizeof(EXPECTED_DOUBLE));
	lstFirst(&sTheList);
	lstNext(&sTheList);
	//Delete Current
	lstDeleteCurrent(&sTheList, &actualInt, sizeof(actualInt));
	//Ensure the correct data was retrieved
	assert((EXPECTED_INT == actualInt),
					"Correctly deleted between elements in list",
					"Incorrectly deleted between elements in list");


	//********** Test lstInsertBefore **********
	//Test insert before with empty list
	//Reset Items needed to test
	lstTerminate(&sTheList);
	lstCreate(&sTheList);
	actualChar = RESET_CHAR;
	lstInsertBefore(&sTheList, &EXPECTED_CHAR, sizeof(EXPECTED_CHAR));
	lstPeek(&sTheList, &actualChar, sizeof(actualChar));
	//Ensure the data was added correctly
	assert((EXPECTED_CHAR == actualChar), "Correctly inserted before",
					"Incorrectly inserted before");
	//Test insert before with 1 element
	//Reset Items needed to test
	lstTerminate(&sTheList);
	lstCreate(&sTheList);
	actualChar = RESET_CHAR;
	actualInt = RESET_INT;
	lstInsertAfter(&sTheList, &EXPECTED_INT, sizeof(EXPECTED_INT));
	lstInsertBefore(&sTheList, &EXPECTED_CHAR, sizeof(EXPECTED_CHAR));
	lstPeek(&sTheList, &actualChar, sizeof(actualChar));
	//Ensure the data was added correctly
	assert((EXPECTED_CHAR == actualChar), "Correctly inserted before",
					"Incorrectly inserted before");
	//Test insert before with 2 elements
	//Reset Items needed to test
	lstTerminate(&sTheList);
	lstCreate(&sTheList);
	actualChar = RESET_CHAR;
	actualInt = RESET_INT;
	actualDouble = RESET_DOUBLE;
	lstInsertAfter(&sTheList, &EXPECTED_INT, sizeof(EXPECTED_INT));
	lstInsertAfter(&sTheList, &EXPECTED_DOUBLE, sizeof(EXPECTED_DOUBLE));
	lstInsertBefore(&sTheList, &EXPECTED_CHAR, sizeof(EXPECTED_CHAR));
	lstPeek(&sTheList, &actualChar, sizeof(actualChar));
	//Ensure the data was added correctly
	assert((EXPECTED_CHAR == actualChar), "Correctly inserted before",
					"Incorrectly inserted before");


	//********** Test lstLast **********
	//Reset Items needed to test
	lstTerminate(&sTheList);
	lstCreate(&sTheList);
	actualChar = RESET_CHAR;
	actualInt = RESET_INT;
	actualDouble = RESET_DOUBLE;
	//Add the data by inserting before, so the char will be the last element
	//but not the current element
	lstInsertBefore(&sTheList, &EXPECTED_CHAR, sizeof(EXPECTED_CHAR));
	lstInsertBefore(&sTheList, &EXPECTED_INT, sizeof(EXPECTED_INT));
	lstInsertBefore(&sTheList, &EXPECTED_DOUBLE, sizeof(EXPECTED_DOUBLE));
	//Change current to last element
	lstLast(&sTheList);
	//Check if peek matches the expected char
	lstPeek(&sTheList, &actualChar, sizeof(actualChar));
	assert((EXPECTED_CHAR == actualChar), "Set current to last element",
					"Did NOT set current to last element");


	//********** Test lstTerminate **********
	lstTerminate(&sTheList);
	lstCreate(&sTheList);
	//Add some elements
	lstInsertAfter(&sTheList, &EXPECTED_INT, sizeof(EXPECTED_INT));
	lstInsertAfter(&sTheList, &EXPECTED_INT, sizeof(EXPECTED_INT));
	lstInsertAfter(&sTheList, &EXPECTED_INT, sizeof(EXPECTED_INT));
	lstTerminate(&sTheList);
	//Ensure the list is now empty
	assert((lstIsEmpty(&sTheList)), "List is empty after termination",
					"List is NOT empty after termination");
	success("List Terminated Successfully\n TESTING COMPLETE");

	return EXIT_SUCCESS;
}

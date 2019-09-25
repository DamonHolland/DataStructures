/***************************************************************************
File name:  driver.c
Author:     holl9358
Date:       Sep 19, 2019
Class:      CS300
Assignment: 
Purpose:    
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "../include/list.h"

#define MAX_MESSAGE_LENGTH 100;


/**************************************************************************
 Function: 	 	main

 Description: test all the functionality of the list

 Parameters:	none

 Returned:	 	Exit Status
 *************************************************************************/
int main(){
	List sTheList;
	const char TEST_CHAR1 = 'A';
	const int TEST_INT1 = 10;
	const double TEST_DOUBLE1 = 5.8;



	char charDataBuffer = 'Z';
	int intDataBuffer = 0, i = 0;
	double doubleDataBuffer = 0;
	bool loopTest = true;

	lstLoadErrorMessages();
	lstCreate(&sTheList);

	//Check if List is initially empty
	if(lstIsEmpty(&sTheList))
	{
		printf("Success: List is empty after creation\n");
	}
	else
	{
		printf("Failed: List is NOT empty after creation\n");
	}

	//Add an element to the list
	lstInsertAfter(&sTheList, &TEST_CHAR1, sizeof(TEST_CHAR1));
	//Check if data is correct
	lstPeek(&sTheList, &charDataBuffer, sizeof(charDataBuffer));
	if(TEST_CHAR1 == charDataBuffer){
		printf("Success: Data was added correctly\n");
	}
	else
	{
		printf("Failed: Data was added incorrectly\n");
	}
	//Check If Size is Correct
	if(1 == lstSize(&sTheList))
	{
		printf("Success: Size of list is 1\n");
	}
	else
	{
		printf("Failed: Size of list is NOT 1\n");
	}


	//Add another element to the list
	lstInsertAfter(&sTheList, &TEST_INT1, sizeof(TEST_INT1));
	//Check if data is correct
	lstPeek(&sTheList, &intDataBuffer, sizeof(intDataBuffer));
	if(TEST_INT1 == intDataBuffer)
	{
		printf("Success: Data was added correctly\n");
	}
	else
	{
		printf("Failed: Data was added incorrectly\n");
	}
	//Check If Size is Correct
	if(2 == lstSize(&sTheList))
	{
		printf("Success: Size of list is 2\n");
	}
	else
	{
		printf("Failed: Size of list is NOT 2\n");
	}
	//Add another element to the list
	lstInsertAfter(&sTheList, &TEST_DOUBLE1, sizeof(TEST_DOUBLE1));
	//Check if data is correct
	lstPeek(&sTheList, &doubleDataBuffer, sizeof(doubleDataBuffer));
	if(TEST_DOUBLE1 == doubleDataBuffer)
	{
		printf("Success: Data was added correctly\n");
	}
	else
	{
		printf("Failed: Data was added incorrectly\n");
	}
	//Check if the size is correct
	if(3 == lstSize(&sTheList))
	{
		printf("Success: Size of list is 3\n");
	}
	else
	{
		printf("Failed: Size of list is NOT 3\n");
	}

	//Check if list is not empty after some elements were added
	if(!lstIsEmpty(&sTheList))
	{
		printf("Success: List is NOT empty\n");
	}
	else
	{
		printf("Failed: List is empty\n");
	}


	//Insert and Peek in a loop
	loopTest = true;
	for(i = 1; i <= 5; i++)
	{
		//Insert and Peek Data
		lstInsertAfter(&sTheList, &i, sizeof(i));
		lstPeek(&sTheList, &intDataBuffer, sizeof(intDataBuffer));

		//Make sure size and data are correct
		if( !((3 + i) == lstSize(&sTheList)))
		{
			loopTest = false;
		}
		if(intDataBuffer != i)
		{
			loopTest = false;
		}
	}
	//Print if the loop test was successful
	if(loopTest)
	{
		printf("Success: Elements added correctly in loop\n");
	}
	else
	{
		printf("Failed: Elements added incorrectly in loop\n");
	}

	//Move to the first element
	lstFirst(&sTheList);
	//Check if the current data matches the first added data
	charDataBuffer = 'Z';
	lstPeek(&sTheList, &charDataBuffer, sizeof(charDataBuffer));
	if(TEST_CHAR1 == charDataBuffer)
	{
		printf("Success: Moved to first element\n");
	}
	else
	{
		printf("Failed: Did not move to first element\n");
	}

	//Move to the next element
		lstNext(&sTheList);
		//Check if the current data matches the second added data
		intDataBuffer = 0;
		lstPeek(&sTheList, &intDataBuffer, sizeof(intDataBuffer));
		if(TEST_INT1 == intDataBuffer)
		{
			printf("Success: Moved to next element\n");
		}
		else
		{
			printf("Failed: Did not move to next element\n");
		}

	//Terminate list
	lstTerminate(&sTheList);
	//Ensure list is empty
	if(lstIsEmpty(&sTheList))
	{
		printf("Success: List is empty after termination\n");
	}
	else
	{
		printf("Success: List is NOT empty after termination\n");
	}

	return EXIT_SUCCESS;
}

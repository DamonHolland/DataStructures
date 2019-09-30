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
		printf("Failed: List is NOT empty after termination\n");
	}

	//Ensure there is no current element
	if(!lstHasCurrent(&sTheList))
		{
			printf("Success: No current element after termination\n");
		}
		else
		{
			printf("Failed: There is a current element after termination\n");
		}

	//Now add an element
	lstInsertAfter(&sTheList, &TEST_CHAR1, sizeof(TEST_CHAR1));
	//Ensure there is now a current element
	if(lstHasCurrent(&sTheList))
			{
				printf("Success: There is a current element\n");
			}
			else
			{
				printf("Failed: There is NOT a current element\n");
			}
	//Switch to the next element
	lstNext(&sTheList);
	//Ensure there is now no current element
	if(!lstHasCurrent(&sTheList))
			{
				printf("Success: No current element\n");
			}
			else
			{
				printf("Failed: There is a current element\n");
			}

	//UpdateCurrent
	lstFirst(&sTheList);
	lstUpdateCurrent(&sTheList, &TEST_INT1, sizeof(TEST_INT1));
	intDataBuffer = 0;
	lstPeek(&sTheList, &intDataBuffer, sizeof(intDataBuffer));
	if(TEST_INT1 == intDataBuffer)
	{
		printf("Success: The current element was updated\n");
	}
	else
	{
		printf("Failed: The current element was NOT updated\n");
	}

	//Ensure there is no next element
	if(!lstHasNext(&sTheList))
		{
			printf("Success: There is no next element\n");
		}
		else
		{
			printf("Failed: There is a next element\n");
		}

	//Add a second element an ensure there is a next element
	lstInsertAfter(&sTheList, &TEST_CHAR1, sizeof(TEST_CHAR1));
	lstFirst(&sTheList);
	if(lstHasNext(&sTheList))
			{
				printf("Success: There is a next element\n");
			}
			else
			{
				printf("Failed: There is NOT a next element\n");
			}

	//Ensure lstPeekNext gives correct value
	charDataBuffer = 'Z';
	lstPeekNext(&sTheList, &charDataBuffer, sizeof(charDataBuffer));
	if(TEST_CHAR1 == charDataBuffer)
	{
		printf("Success: Peek next data correct\n");
	}
	else
	{
		printf("Failed: Peek next data incorrect\n");
	}

	//Test lstDeleteCurrent with 1 element
	lstTerminate(&sTheList);
	lstCreate(&sTheList);
	charDataBuffer = 'Z';
	//Add data to the list
	lstInsertAfter(&sTheList, &TEST_CHAR1, sizeof(TEST_CHAR1));
	//Delete Current
	lstDeleteCurrent(&sTheList, &charDataBuffer, sizeof(charDataBuffer));
	//Ensure the list is now empty, and the correct data was retrieved
	if((lstIsEmpty(&sTheList)) && (TEST_CHAR1 == charDataBuffer))
	{
		printf("Success: Deleted current correctly\n");
	}
	else
	{
		printf("Failed: Deleted current incorrectly\n");
	}

	//Test lstDeleteCurrent with 2 elements, starting with
	//current as the first
	lstTerminate(&sTheList);
	lstCreate(&sTheList);
	charDataBuffer = 'Z';
	intDataBuffer = 0;
	//Add data to the list
	lstInsertAfter(&sTheList, &TEST_CHAR1, sizeof(TEST_CHAR1));
	lstInsertAfter(&sTheList, &TEST_INT1, sizeof(TEST_INT1));
	lstFirst(&sTheList);
	//Delete Current
	lstDeleteCurrent(&sTheList, &charDataBuffer, sizeof(charDataBuffer));
	lstDeleteCurrent(&sTheList, &intDataBuffer, sizeof(intDataBuffer));
	//Ensure the correct data was retrieved
	if((TEST_CHAR1 == charDataBuffer) && (TEST_INT1 == intDataBuffer))
	{
		printf("Success: Deleted current correctly\n");
	}
	else
	{
		printf("Failed: Deleted current incorrectly\n");
	}

	//Test lstDeleteCurrent with 2 elements, starting with
	//current as the last
	lstTerminate(&sTheList);
	lstCreate(&sTheList);
	charDataBuffer = 'Z';
	intDataBuffer = 0;
	//Add data to the list
	lstInsertAfter(&sTheList, &TEST_CHAR1, sizeof(TEST_CHAR1));
	lstInsertAfter(&sTheList, &TEST_INT1, sizeof(TEST_INT1));
	//Delete Current
	lstDeleteCurrent(&sTheList, &intDataBuffer, sizeof(intDataBuffer));
	lstDeleteCurrent(&sTheList, &charDataBuffer, sizeof(charDataBuffer));
	//Ensure the correct data was retrieved
	if((TEST_CHAR1 == charDataBuffer) && (TEST_INT1 == intDataBuffer))
	{
		printf("Success: Deleted current correctly\n");
	}
	else
	{
		printf("Failed: Deleted current incorrectly\n");
	}

	//Test lstDeleteCurrent with current between elements
	lstTerminate(&sTheList);
	lstCreate(&sTheList);
	charDataBuffer = 'Z';
	intDataBuffer = 0;
	doubleDataBuffer = 0;
	//Add data to the list
	lstInsertAfter(&sTheList, &TEST_CHAR1, sizeof(TEST_CHAR1));
	lstInsertAfter(&sTheList, &TEST_INT1, sizeof(TEST_INT1));
	lstInsertAfter(&sTheList, &TEST_DOUBLE1, sizeof(TEST_DOUBLE1));
	lstFirst(&sTheList);
	lstNext(&sTheList);
	//Delete Current
	lstDeleteCurrent(&sTheList, &intDataBuffer, sizeof(intDataBuffer));
	//Ensure the correct data was retrieved
	if((TEST_INT1 == intDataBuffer))
	{
		printf("Success: Deleted current correctly\n");
	}
	else
	{
		printf("Failed: Deleted current incorrectly\n");
	}


	//Test insert before with empty list
	lstTerminate(&sTheList);
	lstCreate(&sTheList);
	charDataBuffer = 'Z';
	lstInsertBefore(&sTheList, &TEST_CHAR1, sizeof(TEST_CHAR1));
	lstPeek(&sTheList, &charDataBuffer, sizeof(charDataBuffer));
	//Ensure the data was added correctly
	if((TEST_CHAR1 == charDataBuffer))
	{
		printf("Success: Inserted before current correctly\n");
	}
	else
	{
		printf("Failed: Inserted before current incorrectly\n");
	}

	//Test insert before with 1 element
	lstTerminate(&sTheList);
	lstCreate(&sTheList);
	charDataBuffer = 'Z';
	intDataBuffer = 0;
	lstInsertAfter(&sTheList, &TEST_INT1, sizeof(TEST_INT1));
	lstInsertBefore(&sTheList, &TEST_CHAR1, sizeof(TEST_CHAR1));
	lstPeek(&sTheList, &charDataBuffer, sizeof(charDataBuffer));
	//Ensure the data was added correctly
	if((TEST_CHAR1 == charDataBuffer))
	{
		printf("Success: Inserted before current correctly\n");
	}
	else
	{
		printf("Failed: Inserted before current incorrectly\n");
	}


	//Test insert before with 2 elements
	lstTerminate(&sTheList);
	lstCreate(&sTheList);
	charDataBuffer = 'Z';
	intDataBuffer = 0;
	doubleDataBuffer = 0;
	lstInsertAfter(&sTheList, &TEST_INT1, sizeof(TEST_INT1));
	lstInsertAfter(&sTheList, &TEST_DOUBLE1, sizeof(TEST_DOUBLE1));
	lstInsertBefore(&sTheList, &TEST_CHAR1, sizeof(TEST_CHAR1));
	lstPeek(&sTheList, &charDataBuffer, sizeof(charDataBuffer));
	//Ensure the data was added correctly
	if((TEST_CHAR1 == charDataBuffer))
	{
		printf("Success: Inserted before current correctly\n");
	}
	else
	{
		printf("Failed: Inserted before current incorrectly\n");
	}

	//Test lstLast
	lstTerminate(&sTheList);
	lstCreate(&sTheList);
	charDataBuffer = 'Z';
	intDataBuffer = 0;
	doubleDataBuffer = 0;
	//Add the data by inserting before, so the char will be the last element
	lstInsertBefore(&sTheList, &TEST_CHAR1, sizeof(TEST_CHAR1));
	lstInsertBefore(&sTheList, &TEST_INT1, sizeof(TEST_INT1));
	lstInsertBefore(&sTheList, &TEST_DOUBLE1, sizeof(TEST_DOUBLE1));
	lstLast(&sTheList);
	lstPeek(&sTheList, &charDataBuffer, sizeof(charDataBuffer));
	if((TEST_CHAR1 == charDataBuffer))
	{
		printf("Success: Last element peeked\n");
	}
	else
	{
		printf("Failed: Last element NOT peeked\n");
	}



	lstTerminate(&sTheList);

	return EXIT_SUCCESS;
}

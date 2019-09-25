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


int main(){
	List sTheList;
	char Data = 'A';

	lstLoadErrorMessages();
	lstCreate(&sTheList);

	//Check if List is initially empty
	if(lstIsEmpty(&sTheList)){
		printf("List is empty\n");
	}
	else{
			printf("List is NOT empty\n");
		}

	//Add a few elements to list
	lstInsertAfter(&sTheList, &Data, sizeof(Data));
	printf("Size of list: %d\n", lstSize(&sTheList));

	lstInsertAfter(&sTheList, &Data, sizeof(Data));
	printf("Size of list: %d\n", lstSize(&sTheList));

	lstInsertAfter(&sTheList, &Data, sizeof(Data));
	printf("Size of list: %d\n", lstSize(&sTheList));

	//Check if list is not empty
	if(lstIsEmpty(&sTheList)){
			printf("List is empty\n");
		}
	else{
		printf("List is NOT empty\n");
	}

	lstTerminate(&sTheList);

	if(lstIsEmpty(&sTheList)){
				printf("List is empty\n");
			}
		else{
			printf("List is NOT empty\n");
		}

	return EXIT_SUCCESS;
}

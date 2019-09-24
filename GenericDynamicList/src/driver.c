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
	char Data;

	lstLoadErrorMessages();

	lstCreate(&sTheList);

	lstInsertAfter(&sTheList, &Data, sizeof(Data));

	printf("Test");
	return EXIT_SUCCESS;

}

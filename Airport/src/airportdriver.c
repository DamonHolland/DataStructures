/***************************************************************************
File name:  airportdriver.c
Author:     Damon Holland
Date:       Oct 21, 2019
Class:      CS300
Assignment: Airport
Purpose:    The driver for the airport assignment
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>


int main ()
{
	//******************** CONSTANT VARIABLES ********************
	char FILE_NAME[] = "data/airport.txt";

	//******************** VARIABLES ********************
	//Variables to store information from the file
	int numNewTakeoffPlanes, numNewLandingPlanes;
	int fuelPlane1, fuelPlane2, fuelPlane3;

	//The file used to read data
	FILE* inFile = fopen(FILE_NAME, "r");;
	if(!inFile)
	{
		printf("Error: Unable to open file\n");
		exit (EXIT_FAILURE);
	}

	fscanf(inFile, "%d %d %d %d %d", &numNewTakeoffPlanes, &numNewLandingPlanes,
													         &fuelPlane1, &fuelPlane2, &fuelPlane3);

	printf("%d %d %d %d %d\n", numNewTakeoffPlanes, numNewLandingPlanes,
													  fuelPlane1, fuelPlane2, fuelPlane3);


	//Read data from the file




	printf("build success\n");
	return EXIT_SUCCESS;
}

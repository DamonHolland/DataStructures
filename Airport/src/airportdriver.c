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
#include "../include/airport.h"


int main ()
{
	//******************** CONSTANT VARIABLES ********************
	char FILE_NAME[] = "data/airport.txt";

	//******************** VARIABLES ********************
	//Variables to store information from the file
	int numNewTakeoffPlanes, numNewLandingPlanes;
	int MAX_PLANES_ADDED = 3, PLANE1 = 0, PLANE2 = 1, PLANE3 = 2;
	int fuelCounts[MAX_PLANES_ADDED];

	//Formatting Variables

	//Iterator variable
	int i;

	//The file used to read data, file is validated
	FILE* inFile = fopen(FILE_NAME, "r");
	if(!inFile)
	{
		printf("Error: Unable to open file\n");
		exit (EXIT_FAILURE);
	}

	//The airport
	Airport sTheAirport;


	//******************** PRINT HEADER TO SCREEN ********************
	printf ("     |           Planes Added            |      Runways      |"
					"   Queue  Lengths\n");
	printf ("Time | Takeoff  Landing (Fuel Remaining) |  1   2   3  Crash |"
					" Takeoff  Landing\n");
	printf ("---- | -------  ------------------------ | --- --- --- ----- |"
					" -------  -------");


	//******************** MAIN AIRPORT LOOP ********************
	//******************** 1) Read data from file ********************
	fscanf(inFile, "%d %d %d %d %d", &numNewTakeoffPlanes, &numNewLandingPlanes,
				 &fuelCounts[PLANE1], &fuelCounts[PLANE2], &fuelCounts[PLANE3]);
	//******************** 2) Insert Data into airport ********************
	for (i = 0; i < numNewTakeoffPlanes; i++)
	{
		airportAddTakeoffPlane (&sTheAirport);
	}
	for (i = 0; i < numNewLandingPlanes; i++)
	{
		airportAddLandingPlane (&sTheAirport, fuelCounts[i]);
	}
	//******************** 3) Decrement fuel from planes ********************
	airportDecrementFuel (&sTheAirport);


	return EXIT_SUCCESS;
}

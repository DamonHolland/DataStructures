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



static void printHeader ()
{
	printf ("     |           Planes Added            |      Runways      |"
						"   Queue  Lengths\n");
	printf ("Time | Takeoff  Landing (Fuel Remaining) |  1   2   3  Crash |"
					" Takeoff  Landing\n");
	printf ("---- | -------  ------------------------ | --- --- --- ----- |"
					" -------  -------\n");
}

int main ()
{
	//******************** CONSTANT VARIABLES ********************
	char FILE_NAME[] = "data/airport.txt";
	const int FUEL_DECREMENT = -1;
	const int NUM_RUNWAYS = 3;
	const int MAX_PLANES_ADDED = 3, PLANE1 = 0, PLANE2 = 1, PLANE3 = 2;
	const int NO_FUEL = 0;

	//******************** VARIABLES ********************
	//Variables to store information from the file
	int numNewTakeoffPlanes, numNewLandingPlanes;
	int fuelCounts[MAX_PLANES_ADDED];

	//Formatting Variables

	//Iterator variable
	int i;

	int runwaysUsed = 0;

	int clock = 1;

	//The file used to read data, file is validated
	FILE* inFile = fopen (FILE_NAME, "r");
	if(!inFile)
	{
		printf ("Error: Unable to open file\n");
		exit (EXIT_FAILURE);
	}

	//The airport
	Airport sTheAirport;


	printHeader ();

	airportLoadErrorMessages ();
	airportCreate (&sTheAirport);

	//******************** MAIN AIRPORT LOOP ********************
	while (!feof (inFile) || !airportIsEmpty (&sTheAirport))
	{
		if (feof (inFile))
		{
			numNewTakeoffPlanes = 0;
			numNewLandingPlanes = 0;
		}
		else
		{
			runwaysUsed = 0;
			//******************** 1) Read data from file ********************
			fscanf(inFile, "%d %d %d %d %d", &numNewTakeoffPlanes, &numNewLandingPlanes,
						 &fuelCounts[PLANE1], &fuelCounts[PLANE2], &fuelCounts[PLANE3]);
		}
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
	airportDecrementFuel (&sTheAirport, FUEL_DECREMENT);
	//******************** 4) Emergency Land Planes ********************
	while (!(runwaysUsed >= NUM_RUNWAYS) &&
				 (airportLengthOfLandingQueue (&sTheAirport) != 0)
				 && NO_FUEL == airportLowestFuelAmount (&sTheAirport))
	{
		airportLandPlane (&sTheAirport);
	}
	//******************** 5) Land Leftover Planes ********************
	while ((runwaysUsed < NUM_RUNWAYS) && !airportIsEmpty (&sTheAirport))
	{
		if ((airportLengthOfLandingQueue (&sTheAirport) >=
				airportLengthOfTakeoffQueue (&sTheAirport)))
		{
			airportLandPlane (&sTheAirport);
		}
		else
		{
			airportTakeoffPlane (&sTheAirport);
		}
	}
	//******************** 6) Print Result of Turn ********************
	printf ("%4d | %8d%8d | \n", clock, numNewTakeoffPlanes, numNewLandingPlanes);
	//******************** 7) Increment Clock ********************
	clock++;

	}

	airportTerminate (&sTheAirport);
	fclose (inFile);

	return EXIT_SUCCESS;
}

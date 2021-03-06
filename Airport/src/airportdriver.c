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

/*************************************************************************
 Function: 	 	printHeader

 Description: print the header for the airport output

 Parameters:	none
 Returned:	 	none
 ************************************************************************/
static void printHeader ()
{
	printf ("     |           Planes Added            |      Runways      |"
						"   Queue  Lengths\n");
	printf ("Time | Takeoff  Landing (Fuel Remaining) |  1   2   3  Crash |"
					" Takeoff  Landing\n");
	printf ("---- | -------  ------------------------ | --- --- --- ----- |"
					" -------  -------\n");
}

/*************************************************************************
 Function: 	 	main

 Description: Main driver for the airport assignment

 Parameters:	argc - an integer that contains the number of arguments
 	 	 	 	 	 	 	argv[] - array of characters which are the arguments

 Returned:	 	Exit Status
 ************************************************************************/
int main (int argc, char *argv[])
{
	//******************** CONSTANT VARIABLES ********************
	const int FUEL_DECREMENT = 1;
	const int NUM_RUNWAYS = 3;
	const int MAX_PLANES_ADDED = 3, PLANE1 = 0, PLANE2 = 1, PLANE3 = 2;
	const int NO_FUEL = 0;
	const int HEADER_TICK_FREQUENCY = 20;
	//Runway Statuses
	const char UNUSED_RUNWAY = '-', TAKEOFF_RUNWAY = 'T',
						 EMERGENCY_RUNWAY = 'E', LANDING_RUNWAY = 'L';

	//******************** VARIABLES ********************
	//Iterator variable
	int i;

	//Variables to store information from the file
	int numNewTakeoffPlanes, numNewLandingPlanes;
	int fuelCounts[MAX_PLANES_ADDED];

	//Array of chars which contain runway statuses
	char runwayStatus[NUM_RUNWAYS];
	//The amount of runways used in each turn
	int runwaysUsed = 0;

	//Statistics
	int crashedPlanes = 0;
	int totalCrashedPlanes = 0;
	int emergencyLandings = 0;
	int totalTakeoffWaitingTime = 0;
	int totalTakeoffs = 0;
	int totalLandingWaitingTime = 0;
	int totalLandings = 0;
	int fuelRemainingOnLanding = 0;
	int totalFuelRemainingOnLanding = 0;

	//Current time
	int currentTick = 1;

	//The airport
	Airport sTheAirport;

	//The file used to read data
	FILE* inFile = fopen (argv[1], "r");

	//Open and validate file
	if(!inFile)
	{
		printf ("Error: Unable to open file\n");
		exit (EXIT_FAILURE);
	}

	//Initialize airport
	airportLoadErrorMessages ();
	airportCreate (&sTheAirport);

	printHeader ();

	//******************** MAIN AIRPORT LOOP ********************
	while (!feof (inFile) || !airportIsEmpty (&sTheAirport))
	{
		//******************** Reset Variables ********************
		runwaysUsed = 0;
		crashedPlanes = 0;
		for (i = 0; i < MAX_PLANES_ADDED; i++)
		{
			fuelCounts[i] = 0;
		}
		//Initialize all runways to unused
		for (i = 0; i < NUM_RUNWAYS; i++)
		{
			runwayStatus[i] = UNUSED_RUNWAY;
		}

		//******************** 1) Read data from file ********************
		//Only read data if there is new data to be read, If there isn't
		//allow program to continue landing and takeing off planes until the
		//queues are empty
		if (feof (inFile))
		{
			numNewTakeoffPlanes = 0;
			numNewLandingPlanes = 0;
		}
		else
		{
			fscanf(inFile, "%d %d %d %d %d", &numNewTakeoffPlanes,
						 &numNewLandingPlanes, &fuelCounts[PLANE1],
						 &fuelCounts[PLANE2], &fuelCounts[PLANE3]);
		}

		//******************** 2) Insert Data into airport ********************
		for (i = 0; i < numNewTakeoffPlanes; i++)
		{
			airportAddTakeoffPlane (&sTheAirport, currentTick);
		}
		for (i = 0; i < numNewLandingPlanes; i++)
		{
			airportAddLandingPlane (&sTheAirport, currentTick, fuelCounts[i]);
		}

		//******************** 3) Decrement fuel from planes ********************
		airportDecrementFuel (&sTheAirport, FUEL_DECREMENT);

		//******************** 4) Emergency Land Planes ********************
		while (!airportLandingQueueIsEmpty (&sTheAirport)
				 	 && NO_FUEL == airportLowestFuelAmount (&sTheAirport))
		{
			//If there are available runways, land plane
			if (runwaysUsed < NUM_RUNWAYS)
			{
				runwayStatus[runwaysUsed] = EMERGENCY_RUNWAY;
				totalLandingWaitingTime += airportLandPlane (&sTheAirport,
																	 	 currentTick, &fuelRemainingOnLanding);
				totalFuelRemainingOnLanding += fuelRemainingOnLanding;
				runwaysUsed++;
				emergencyLandings++;
				totalLandings++;
			}
			//If not, crash the plane
			else
			{
				totalLandingWaitingTime += airportLandPlane (&sTheAirport,
																	 	 currentTick, &fuelRemainingOnLanding);
				crashedPlanes++;
				totalCrashedPlanes++;
				totalLandings++;
			}
		}

		//******************** 5) Land Leftover Planes ********************
		while ((runwaysUsed < NUM_RUNWAYS) && !airportIsEmpty (&sTheAirport))
		{
			if ((airportLengthOfLandingQueue (&sTheAirport) >=
					 airportLengthOfTakeoffQueue (&sTheAirport)))
			{
				runwayStatus[runwaysUsed] = LANDING_RUNWAY;
				totalLandingWaitingTime += airportLandPlane (&sTheAirport,
																	 	 currentTick, &fuelRemainingOnLanding);
				totalFuelRemainingOnLanding += fuelRemainingOnLanding;
				runwaysUsed++;
				totalLandings++;
			}
			else
			{
				runwayStatus[runwaysUsed] = TAKEOFF_RUNWAY;
				totalTakeoffWaitingTime += airportTakeoffPlane (&sTheAirport,
																												currentTick);
				runwaysUsed++;
				totalTakeoffs++;
			}
		}

		//******************** 6) Print Result of Turn ********************
		//Print Time, Takeoff planes, and Landing Planes
		printf ("%4d |%8d %8d |", currentTick, numNewTakeoffPlanes,
						numNewLandingPlanes);

		//Print Fuel Counts
		for (i = 0; i < MAX_PLANES_ADDED; i++)
		{
			if (NO_FUEL == fuelCounts[i])
			{
				printf ("    -");
			}
			else
			{
				printf ("%5d", fuelCounts[i]);
			}
		}

		//Print Runway Statuses
		printf (" |");
		for (i = 0; i < NUM_RUNWAYS; i++)
		{
			printf ("%3c ", runwayStatus[i]);
		}

		//Print Crashed Planes
		printf ("%6d |", crashedPlanes);

		//Print Takeoff Queue and Landing Queue Lengths
		printf ("%8d %8d\n", airportLengthOfTakeoffQueue (&sTheAirport),
						airportLengthOfLandingQueue (&sTheAirport));

		//******************** 7) Increment Clock ********************
		if (currentTick % HEADER_TICK_FREQUENCY == 0)
		{
			printHeader ();
		}
		currentTick++;

		//******************** 8) Repeat Main Loop ********************
		//					until airport is empty and end of file is reached
		}

	//******************** 9) Print Summary ********************
	printf ("\nAverage takeoff waiting time: %.6g\n",
					totalTakeoffWaitingTime / (double)totalTakeoffs);
	printf ("Average landing waiting time: %.6g\n", totalLandingWaitingTime /
					(double)totalLandings);
	printf ("Average flying time remaining on landing: %.6g\n",
					totalFuelRemainingOnLanding / (double)totalLandings);
	printf ("Number of planes landing with zero fuel: %d\n",
					emergencyLandings);
	printf ("Number of crashes: %d",
					totalCrashedPlanes);

	//Terminate Airport and close the file
	airportTerminate (&sTheAirport);
	fclose (inFile);

	return EXIT_SUCCESS;
}

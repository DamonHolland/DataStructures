/***************************************************************************
File name:  airport.c
Author:     Damon Holland
Date:       Oct 27, 2019
Class:      CS300
Assignment: Airport
Purpose:    Implement functions in airport.h
***************************************************************************/

#include "stdio.h"
#include "../include/airport.h"

#define MINIMUM_WAIT 1

char gszAirportErrors[NUMBER_OF_AIRPORT_ERRORS][MAX_ERROR_AIRPORT_CHARS];

/*************************************************************************
 Function: 	 	processError

 Description: Process the error code passed to this routine

 Parameters:	pszFunctionName - string containing the name of the function
  															causing the error
 	 	 	 	 	 	 	errorCode - an integer that identifies the queue error

 Returned:	 	None
 ************************************************************************/
static void processError (const char *pszFunctionName, int errorCode)
{
	printf ("Function: %s %s \n ", pszFunctionName,
					gszAirportErrors[errorCode]);
	exit (EXIT_FAILURE);
}

/**************************************************************************
*										Allocation and Deallocation
**************************************************************************/
/*************************************************************************
 Function: 	 	airportCreate

 Description: Creates and initializes the airport

 Parameters:	psAirport - pointer to the airport to create

 Returned:	 	None
 ************************************************************************/
void airportCreate (AirportPtr psAirport)
{
	//Error Checking
	if (NULL == psAirport)
	{
		processError ("airportCreate", ERROR_INVALID_AIRPORT);
	}

	queueCreate (&psAirport->sTakeoffQueue);
	pqueueCreate (&psAirport->sLandingQueue);

	//Error Checking
	if ((NULL != psAirport) && (!airportIsEmpty (psAirport)))
	{
		processError ("airportCreate", ERROR_NO_AIRPORT_CREATE);
	}

	return;
}

/*************************************************************************
 Function: 	 	airportTerminate

 Description: Terminates the airport

 Parameters:	psAirport - pointer to the airport to terminate

 Returned:	 	None
 ************************************************************************/
void airportTerminate (AirportPtr psAirport)
{
	//Error Checking
	if (NULL == psAirport)
	{
		processError ("airportTerminate", ERROR_INVALID_AIRPORT);
	}

	queueTerminate (&psAirport->sTakeoffQueue);
	pqueueTerminate (&psAirport->sLandingQueue);

	//Error Checking
	if (!airportIsEmpty (psAirport))
	{
		processError ("airportTerminate", ERROR_NO_AIRPORT_TERMINATE);
	}

	return;
}

/*************************************************************************
 Function: 	 	airportLoadErrorMessages

 Description: Loads the error message strings for other functions to use

 Parameters:	None

 Returned:	 	None
 ************************************************************************/
void airportLoadErrorMessages ()
{
	queueLoadErrorMessages ();
	LOAD_AIRPORT_ERRORS;
	return;
}

/**************************************************************************
*									Checking number of planes in queues
**************************************************************************/
/*************************************************************************
 Function: 	 	airportIsEmpty

 Description: Returns if the given airport is empty or not

 Parameters:	psAirport - pointer to the airport to check if empty or not

 Returned:	 	bool - a bool which contains true if the airport is empty
 	 	 	 	 	 	 	 	 	 	 and false if not empty
 ************************************************************************/
bool airportIsEmpty (AirportPtr psAirport)
{
	//Error Checking
	if (NULL == psAirport)
	{
		processError ("airportIsEmpty", ERROR_INVALID_AIRPORT);
	}

	return airportLandingQueueIsEmpty (psAirport) &&
				 airportTakeoffQueueIsEmpty (psAirport);
}

/*************************************************************************
 Function: 	 	airportLandingQueueIsEmpty

 Description: Returns if the given airports landing queue is empty or not

 Parameters:	psAirport - pointer to the airport to check if the landing
 	 	 	 	 	 	 	 	 	 	 	 	 	queue is empty or not

 Returned:	 	bool - a bool which contains true if the airports landing
 	 	 	 	 	 	 	 	 	   queue is empty and false if not empty
 ************************************************************************/

bool airportLandingQueueIsEmpty (AirportPtr psAirport)
{
	//Error Checking
	if (NULL == psAirport)
	{
		processError ("airportLandingQueueIsEmpty", ERROR_INVALID_AIRPORT);
	}

	return pqueueIsEmpty (&psAirport->sLandingQueue);
}

/*************************************************************************
 Function: 	 	airportTakeoffQueueIsEmpty

 Description: Returns if the given airports takeoff queue is empty or not

 Parameters:	psAirport - pointer to the airport to check if the takeoff
 	 	 	 	 	 	 	 	 	 	 	 	 	queue is empty or not

 Returned:	 	bool - a bool which contains true if the airports takeoff
 	 	 	 	 	 	 	 	 	   queue is empty and false if not empty
 ************************************************************************/

bool airportTakeoffQueueIsEmpty (AirportPtr psAirport)
{
	//Error Checking
	if (NULL == psAirport)
	{
		processError ("airportTakeoffQueueIsEmpty", ERROR_INVALID_AIRPORT);
	}

	return queueIsEmpty (&psAirport->sTakeoffQueue);
}

/*************************************************************************
 Function: 	 	airportLengthOfLandingQueue

 Description: Returns an int the size of the landing queue

 Parameters:	psAirport - pointer to the airport to check the size of the
 	 	 	 	 	 	 	 	 	 	 	 		landing queue of

 Returned:	 	int - and integer which contains the size of the airports
 	 	 	 	 	 	 	 	 	 	landing queue
 ************************************************************************/

int airportLengthOfLandingQueue (AirportPtr psAirport)
{
	//Error Checking
	if (NULL == psAirport)
	{
		processError ("airportLengthOfLandingQueue", ERROR_INVALID_AIRPORT);
	}

	return pqueueSize (&psAirport->sLandingQueue);
}

/*************************************************************************
 Function: 	 	airportLengthOfTakeoffQueue

 Description: Returns an int the size of the takeoff queue

 Parameters:	psAirport - pointer to the airport to check the size of the
 	 	 	 	 	 	 	 	 	 	 	 		takeoff queue of

 Returned:	 	int - and integer which contains the size of the airports
 	 	 	 	 	 	 	 	 	 	takeoff queue
 ************************************************************************/

int airportLengthOfTakeoffQueue (AirportPtr psAirport)
{
	//Error Checking
	if (NULL == psAirport)
	{
		processError ("airportLengthOfTakeoffQueue", ERROR_INVALID_AIRPORT);
	}

	return queueSize (&psAirport->sTakeoffQueue);
}


/**************************************************************************
*												Add planes to queues
**************************************************************************/
/*************************************************************************
 Function: 	 	airportAddTakeoffPlane

 Description: Adds a plane to the given airports takeoff queue and records
 	 	 	 	 	 	 	the time that the plane was added

 Parameters:	psAirport - pointer to the airport to add a plane to the
 	 	 	 	 	 	 	 	 	 	 	 	 	takeoff queue of
 	 	 	 	 	 	 	currentTime - an integer that contains the current time

 Returned:	 	None
 ************************************************************************/
void airportAddTakeoffPlane (AirportPtr psAirport, int currentTime)
{
	Airplane sNewPlane;

	//Error Checking
	if (NULL == psAirport)
	{
		processError ("airportAddTakeoffPlane", ERROR_INVALID_AIRPORT);
	}

	sNewPlane.timeAdded = currentTime;
	queueEnqueue (&psAirport->sTakeoffQueue, &sNewPlane, sizeof(sNewPlane));

	return;
}

/*************************************************************************
 Function: 	 	airportAddLandingPlane

 Description: Adds a plane to the given airports landing queue with a
  						priority of the given fuel and records the time that the
  						plane was added

 Parameters:	psAirport - pointer to the airport to add a plane to the
 	 	 	 	 	 	 	 	 	 	 	 	 	landing queue of
 	 	 	 	 	 	 	currentTime - an integer that contains the current time
 	 	 	 	 	 	 	fuel - an integer that contains the amount of fuel in the
 	 	 	 	 	 	 				 plane

 Returned:	 	None
 ************************************************************************/

void airportAddLandingPlane (AirportPtr psAirport, int currentTime,
														 int fuel)
{
	Airplane sNewPlane;

	//Error Checking
	if (NULL == psAirport)
	{
		processError ("airportAddLandingPlane", ERROR_INVALID_AIRPORT);
	}

	sNewPlane.timeAdded = currentTime;
	pqueueEnqueue (&psAirport->sLandingQueue, &sNewPlane, sizeof(sNewPlane),
								 fuel);

	return;
}

/**************************************************************************
*												Remove planes to queues
**************************************************************************/
/*************************************************************************
 Function: 	 	airportLandPlane

 Description: Removes a plane from the front of the airports landing queue

 Parameters:	psAirport - pointer to the airport to land a plane in
 	 	 	 	 	 	 	currentTime - an integer that contains the current time
 	 	 	 	 	 	 	*fuelRemainingBuffer - a pointer to an integer that will be
																		 used to store the amount of fuel left
																		 in the plane upon landing

 Returned:	 	int - the amount of time the plane had to wait before landing
 ************************************************************************/
int airportLandPlane (AirportPtr psAirport, int currentTime,
											int *fuelRemainingBuffer)
{
	Airplane sPlaneBuffer;
	int waitTime;

	//Error Checking
	if (NULL == psAirport)
	{
		processError ("airportLandPlane", ERROR_INVALID_AIRPORT);
	}
	if (NULL == fuelRemainingBuffer)
	{
		processError ("airportLandPlane", ERROR_NULL_AIRPORT_PTR);
	}
	if (airportLandingQueueIsEmpty (psAirport))
	{
		processError ("airportLandPlane", ERROR_EMPTY_LANDING_Q);
	}

	pqueueDequeue (&psAirport->sLandingQueue, &sPlaneBuffer,
								 sizeof (sPlaneBuffer), fuelRemainingBuffer);
	waitTime = currentTime - sPlaneBuffer.timeAdded + MINIMUM_WAIT;

	return waitTime;
}

/*************************************************************************
 Function: 	 	airportTakeoffPlane

 Description: Removes a plane from the front of the airports takeoff queue

 Parameters:	psAirport - pointer to the airport to takeoff a plane from
 	 	 	 	 	 	 	currentTime - an integer that contains the current time

 Returned:	 	int - the amount of time the plane had to wait before taking
 	 	 	 	 	 	 				off
 ************************************************************************/

int airportTakeoffPlane (AirportPtr psAirport, int currentTime)
{
	Airplane sPlaneBuffer;
	int waitTime;

	//Error Checking
	if (NULL == psAirport)
	{
		processError ("airportTakeoffPlane", ERROR_INVALID_AIRPORT);
	}
	if (airportTakeoffQueueIsEmpty (psAirport))
	{
		processError ("airportTakeoffPlane", ERROR_EMPTY_TAKEOFF_Q);
	}

	queueDequeue (&psAirport->sTakeoffQueue, &sPlaneBuffer,
								 sizeof (sPlaneBuffer));
	waitTime = currentTime - sPlaneBuffer.timeAdded + MINIMUM_WAIT;

	return waitTime;
}

/**************************************************************************
*												Checking fuel amount
**************************************************************************/
/*************************************************************************
 Function: 	 	airportLowestFuelAmount

 Description: Returns the lowest amount of fuel in a given airports landing
 	 	 	 	 	 	 	queue

 Parameters:	psAirport - pointer to the airport to check for the lowest
 	 	 	 	 	 	 	 	 	 	 	 	 	fuel amount in

 Returned:	 	int - the lowest fuel amount in the airports landing queue
 ************************************************************************/
int airportLowestFuelAmount (AirportPtr psAirport)
{
	Airplane sPlaneBuffer;
	int fuelAmount;

	//Error Checking
	if (NULL == psAirport)
	{
		processError ("airportLowestFuelAmount", ERROR_INVALID_AIRPORT);
	}

	pqueuePeek (&psAirport->sLandingQueue, &sPlaneBuffer,
							sizeof (sPlaneBuffer), &fuelAmount);

	return fuelAmount;
}

/**************************************************************************
*												Decrementing fuel amount
**************************************************************************/
/*************************************************************************
 Function: 	 	airportDecrementFuel

 Description: Decreases the amount of fuel in each of the planes in an
 	 	 	 	 	 	 	airport by the specified amount

 Parameters:	psAirport - pointer to the airport to decrement fuel of
 	 	 	 	 	 	 	amount - the amount of fuel to decrement from each plane

 Returned:	 	None
 ************************************************************************/
void airportDecrementFuel (AirportPtr psAirport, int amount)
{
	//Error Checking
	if (NULL == psAirport)
	{
		processError ("airportDecrementFuel", ERROR_INVALID_AIRPORT);
	}

	pqueueChangePriority (&psAirport->sLandingQueue, -amount);

	return;
}

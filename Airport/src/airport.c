/***************************************************************************
File name:  airport.c
Author:     Damon Holland
Date:       Oct 27, 2019
Class:      CS300
Assignment: Airport
Purpose:    Implement functions in airport.h
***************************************************************************/

#include "../include/airport.h"

#define MINIMUM_WAIT 1

void airportLoadErrorMessages ()
{
	queueLoadErrorMessages ();
	return;
}

void airportCreate (AirportPtr psAirport)
{
	queueCreate (&psAirport->sTakeoffQueue);
	pqueueCreate (&psAirport->sLandingQueue);
	return;
}

void airportTerminate (AirportPtr psAirport)
{
	queueTerminate (&psAirport->sTakeoffQueue);
	pqueueTerminate (&psAirport->sLandingQueue);
	return;
}

bool airportIsEmpty (AirportPtr psAirport)
{
	bool bIsEmpty = false;
	if (pqueueIsEmpty (&psAirport->sLandingQueue) &&
		  queueIsEmpty (&psAirport->sTakeoffQueue))
	{
		bIsEmpty = true;
	}

	return bIsEmpty;
}

int airportLengthOfLandingQueue (AirportPtr psAirport)
{
	return pqueueSize (&psAirport->sLandingQueue);
}

int airportLengthOfTakeoffQueue (AirportPtr psAirport)
{
	return queueSize (&psAirport->sTakeoffQueue);
}

int airportLowestFuelAmount (AirportPtr psAirport)
{
	Airplane planeBuffer;
	int fuelAmount;

	pqueuePeek (&psAirport->sLandingQueue, &planeBuffer, sizeof (planeBuffer),
							&fuelAmount);

	return fuelAmount;
}


void airportAddTakeoffPlane (AirportPtr psAirport, int currentTime)
{
	Airplane sNewPlane;
	sNewPlane.timeAdded = currentTime;

	queueEnqueue (&psAirport->sTakeoffQueue, &sNewPlane, sizeof(sNewPlane));

	return;
}


void airportAddLandingPlane (AirportPtr psAirport, int currentTime, int fuel)
{
	Airplane sNewPlane;
	sNewPlane.timeAdded = currentTime;

	pqueueEnqueue (&psAirport->sLandingQueue, &sNewPlane, sizeof(sNewPlane),
								 fuel);

	return;
}


int airportLandPlane (AirportPtr psAirport, int currentTime, int *fuelRemainingBuffer)
{
	Airplane planeBuffer;
	int fuelAmount, waitTime;

	pqueueDequeue (&psAirport->sLandingQueue, &planeBuffer,
								 sizeof (planeBuffer), &fuelAmount);

	waitTime = currentTime - planeBuffer.timeAdded + MINIMUM_WAIT;

	*fuelRemainingBuffer = fuelAmount;

	return waitTime;
}

int airportTakeoffPlane (AirportPtr psAirport, int currentTime)
{
	Airplane planeBuffer;
	int waitTime;

	queueDequeue (&psAirport->sTakeoffQueue, &planeBuffer,
								 sizeof (planeBuffer));

	waitTime = currentTime - planeBuffer.timeAdded + MINIMUM_WAIT;

	return waitTime;
}

void airportDecrementFuel (AirportPtr psAirport, int amount)
{
	pqueueChangePriority (&psAirport->sLandingQueue, amount);
	return;
}

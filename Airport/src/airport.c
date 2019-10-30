/***************************************************************************
File name:  airport.c
Author:     Damon Holland
Date:       Oct 27, 2019
Class:      CS300
Assignment: Airport
Purpose:    Implement functions in airport.h
***************************************************************************/

#include "../include/airport.h"

#define NO_FUEL 0

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


void airportAddTakeoffPlane (AirportPtr psAirport)
{
	Airplane sNewPlane;

	queueEnqueue (&psAirport->sTakeoffQueue, &sNewPlane, sizeof(sNewPlane));

	return;
}


void airportAddLandingPlane (AirportPtr psAirport, int fuel)
{
	Airplane sNewPlane;

	pqueueEnqueue (&psAirport->sLandingQueue, &sNewPlane, sizeof(sNewPlane),
								 fuel);

	return;
}


void airportLandPlane (AirportPtr psAirport)
{
	Airplane planeBuffer;
	int fuelAmount;

	pqueueDequeue (&psAirport->sLandingQueue, &planeBuffer,
								 sizeof (planeBuffer), &fuelAmount);

	return;
}

void airportTakeoffPlane (AirportPtr psAirport)
{
	Airplane planeBuffer;
	queueDequeue (&psAirport->sTakeoffQueue, &planeBuffer,
								 sizeof (planeBuffer));
	return;
}

void airportDecrementFuel (AirportPtr psAirport, int amount)
{
	pqueueChangePriority (&psAirport->sLandingQueue, -amount);
	return;
}

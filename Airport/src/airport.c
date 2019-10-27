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
#define FUEL_DECREMENT -1

void airportAddTakeoffPlane (AirportPtr psAirport)
{
	Airplane sNewPlane;

	queueEnqueue (&psAirport->sTakeOffQueue, &sNewPlane, sizeof(sNewPlane));

	return;
}

extern void airportAddLandingPlane (AirportPtr psAirport, int fuel)
{
	Airplane sNewPlane;

	pqueueEnqueue (&psAirport->sLandingQueue, &sNewPlane, sizeof(sNewPlane),
								 fuel);

	return;
}

extern void airportDecrementFuel (AirportPtr psAirport)
{
	pqueueChangePriority (&psAirport->sLandingQueue, FUEL_DECREMENT);
	return;
}

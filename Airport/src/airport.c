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


void airportAddTakeoffPlane (AirportPtr psAirport)
{
	Airplane sNewPlane;
	createPlane (&sNewPlane, NO_FUEL);

	queueEnqueue (&psAirport->sTakeOffQueue, &sNewPlane, sizeof(sNewPlane));

	return;
}

void createPlane (AirplanePtr psPlane, int fuel)
{
	psPlane->fuel = fuel;
	return;
}

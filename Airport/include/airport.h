/***************************************************************************
File name:  airport.h
Author:     Damon Holland
Date:       Oct 27, 2019
Class:      CS300
Assignment: Airport
Purpose:    Header file for airport
***************************************************************************/

#ifndef AIRPORT_H_
#define AIRPORT_H_

#include "../../GenericDynamicQ/include/queue.h"
#include "../../GenericDynamicPriorityQ/include/pqueue.h"

//*************************************************************************
// User-defined types
//*************************************************************************

typedef struct Airplane *AirplanePtr;
typedef struct Airplane
{
		int timeAdded;
} Airplane;

typedef struct Airport *AirportPtr;
typedef struct Airport
{
		Queue sTakeoffQueue;
		PriorityQueue sLandingQueue;
} Airport;

extern void airportLoadErrorMessages ();

extern void airportCreate (AirportPtr psAirport);

extern void airportTerminate (AirportPtr psAirport);

extern bool airportIsEmpty (AirportPtr psAirport);

extern int airportLengthOfLandingQueue (AirportPtr psAirport);

extern int airportLengthOfTakeoffQueue (AirportPtr psAirport);

extern int airportLowestFuelAmount (AirportPtr psAirport);

extern void airportAddTakeoffPlane (AirportPtr psAirport, int timeAdded);

extern void airportAddLandingPlane (AirportPtr psAirport, int timeAdded, int fuel);

extern int airportLandPlane (AirportPtr psAirport, int currentTime, int *fuelRemainingBuffer);

extern int airportTakeoffPlane (AirportPtr psAirport, int currentTime);

extern void airportDecrementFuel (AirportPtr psAirport, int amount);




#endif /* AIRPORT_H_ */

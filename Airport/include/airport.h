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
		//No need to store fuel value because priority is used instead
} Airplane;

typedef struct Airport *AirportPtr;
typedef struct Airport
{
		Queue sTakeOffQueue;
		PriorityQueue sLandingQueue;
} Airport;


extern void airportAddTakeoffPlane (AirportPtr psAirport);

extern void airportAddLandingPlane (AirportPtr psAirport, int fuel);

extern void airportDecrementFuel (AirportPtr psAirport);







#endif /* AIRPORT_H_ */

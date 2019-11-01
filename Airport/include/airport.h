/**************************************************************************
File name:  airport.h
Author:     Damon Holland
Date:       Oct 27, 2019
Class:      CS300
Assignment: Airport
Purpose:    This file defines the constants, data structures, and
            function prototypes for implementing an airport structure
**************************************************************************/

#ifndef AIRPORT_H_
#define AIRPORT_H_

#include "../../GenericDynamicQ/include/queue.h"
#include "../../GenericDynamicPriorityQ/include/pqueue.h"

//*************************************************************************
// Constants
//*************************************************************************
#define MAX_ERROR_AIRPORT_CHARS 64

enum {NO_AIRPORT_ERROR = 0,
			ERROR_NO_AIRPORT_CREATE,
			ERROR_NO_AIRPORT_TERMINATE,
			ERROR_INVALID_AIRPORT,
			ERROR_NULL_AIRPORT_PTR,
			ERROR_EMPTY_TAKEOFF_Q,
			ERROR_EMPTY_LANDING_Q}; // If this error name changes, change below
#define NUMBER_OF_AIRPORT_ERRORS ERROR_EMPTY_LANDING_Q -\
				NO_AIRPORT_ERROR + 1


//*************************************************************************
// Error Messages
//*************************************************************************
#define LOAD_AIRPORT_ERRORS strcpy(gszAirportErrors[NO_AIRPORT_ERROR],\
																	 "No Error.");\
strcpy(gszAirportErrors[ERROR_NO_AIRPORT_CREATE],\
		   "Error: No Airport Create.");\
strcpy(gszAirportErrors[ERROR_NO_AIRPORT_TERMINATE],\
			 "Error: No Airport Terminate.");\
strcpy(gszAirportErrors[ERROR_INVALID_AIRPORT],\
			 "Error: Invalid Airport.");\
strcpy(gszAirportErrors[ERROR_NULL_AIRPORT_PTR], "Error: NULL Pointer.");\
strcpy(gszAirportErrors[ERROR_EMPTY_TAKEOFF_Q],\
			 "Error: Empty Takeoff Queue."),\
strcpy(gszAirportErrors[ERROR_EMPTY_LANDING_Q],\
			 "Error: Empty Landing Queue.");

//*************************************************************************
// User-defined types
//*************************************************************************
typedef struct Airplane *AirplanePtr;
typedef struct Airplane
{
	//No need for a fuel variable, this is stored as priority in queues
	int timeAdded;
} Airplane;

typedef struct Airport *AirportPtr;
typedef struct Airport
{
	Queue sTakeoffQueue;
	PriorityQueue sLandingQueue;
} Airport;

/**************************************************************************
*										Allocation and Deallocation
**************************************************************************/
extern void airportCreate (AirportPtr psAirport);

extern void airportTerminate (AirportPtr psAirport);

extern void airportLoadErrorMessages ();

/**************************************************************************
*									Checking number of planes in queues
**************************************************************************/
extern bool airportIsEmpty (AirportPtr psAirport);

extern bool airportLandingQueueIsEmpty (AirportPtr psAirport);

extern bool airportTakeoffQueueIsEmpty (AirportPtr psAirport);

extern int airportLengthOfLandingQueue (AirportPtr psAirport);

extern int airportLengthOfTakeoffQueue (AirportPtr psAirport);

/**************************************************************************
*												Add planes to queues
**************************************************************************/
extern void airportAddTakeoffPlane (AirportPtr psAirport, int timeAdded);

extern void airportAddLandingPlane (AirportPtr psAirport, int timeAdded,
																		int fuel);

/**************************************************************************
*												Remove planes to queues
**************************************************************************/
extern int airportLandPlane (AirportPtr psAirport, int currentTime,
														 int *fuelRemainingBuffer);

extern int airportTakeoffPlane (AirportPtr psAirport, int currentTime);

/**************************************************************************
*												Checking fuel amount
**************************************************************************/
extern int airportLowestFuelAmount (AirportPtr psAirport);

/**************************************************************************
*												Decrementing fuel amount
**************************************************************************/
extern void airportDecrementFuel (AirportPtr psAirport, int amount);

#endif /* AIRPORT_H_ */

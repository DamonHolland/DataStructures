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
typedef struct Airport *AirportPtr;
typedef struct Airport
{
		Queue sTakeOffQueue;
		PriorityQueue sLandingQueue;
} Airport;

#endif /* AIRPORT_H_ */

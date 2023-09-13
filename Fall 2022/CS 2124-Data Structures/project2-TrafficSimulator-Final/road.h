#ifndef _road_h
#define _road_h
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "car.h"
#include "queue.h"

typedef struct RoadData
{
    /* TODO - Add data associated with road.  Some suggested data: */
    /* length of this road */
    int length;
    bool fromIntersection;
    /* information used to record/update whether the light at the end of this road is green or red */
    int cycleStep;
    int gOn; //step to turn light green 
    int gOff; //step to turn light red
    int cycleReset; //step to turn cycleStep to 0
    bool green; // true == green, false == red 
    /* intersections this road starts from and moves to */
    int startVertex;
    int endVertex;
    /* Each road should have an array to track cars currently driving on them.  The type of this array can be either `Car**` 
     * (array of car pointers) or `Car*` (array of cars) but the former may be easier to use since locations on the road can 
     * be set to `NULL` if no car is present.
     */
    Car **carsOnRoad;
    /* For each road it is recommended to have a `queue` of cars waiting to enter the simulated road system (see `queue.h` for 
     * the queues functions which have already been implemented for you).  Cars will be put into this queue only when an add 
     * car event occurs for this road.
     */
    Queue *carsWaiting;
}  RoadData;

void printCar();

RoadData initializeRoad( int length, int cycleStep, int gOn, int gOff, int cycleReset, int startVertex, int endVertex);

#endif


#include "road.h"

/* Suggested TODO - Write a function to create road.
 */
RoadData initializeRoad( int length, int cycleStep, int gOn, int gOff, int cycleReset, int startVertex, int endVertex)
{
	RoadData road;
	int i;
	road.length = length;
	road.cycleStep = cycleStep;
	road.gOn = gOn;
	road.gOff = gOff;
	road.cycleReset = cycleReset;
	road.startVertex = startVertex;
	road.endVertex = endVertex;
	road.fromIntersection = false;

	road.carsWaiting = createQueue();
	road.carsOnRoad = (Car**)malloc(length * sizeof(Car*));
	for (i = 0; i < length; i++)
	    road.carsOnRoad[i] = NULL;

	return road;

}
/* Suggested TODO - Write a function to free a road.
 */

/* Suggested TODO - Write a function that attempts to move the cars on a given road forward (if space ahead of them was empty).
 */

/* Suggested TODO - Write a function to attempt to move the car at the first position on a given road
 * to the last position of a another given road.
 */

/* Suggested TODO - Write a function to attempt to move a car from the add car queue onto the end of this road.
 */

/* Suggested TODO - Write a function to update the current state of the traffic light based on the current cycle.
 */

/* Suggested TODO - Write a function to print the destinations of the cars on the road
 */
 //printf("Cars on the road from %d to %d: \n", ????, ????);



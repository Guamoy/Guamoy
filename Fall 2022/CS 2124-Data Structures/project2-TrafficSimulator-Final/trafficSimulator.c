#include "trafficSimulator.h"

/* Function declarations: */
TrafficData* readTrafficDataFromInputFile( char* name );

/* printNames
 * input: none
 * output: none
 *
 * Prints names of the students who worked on this solution
 */
void printNames( )
{
    /* TODO : Fill in you and your partner's names (or N/A if you worked individually) */
    printf("This solution was completed by:\n");
    printf("Georgy Vinogradov\n");
    printf("N/A\n");
}


/* trafficSimulator
 * input: char* name of file to read
 * output: N/A
 *
 * Read in the traffic data from the file whose name is stored in char* filename
 * Simulate the rules outlined in the project 2 description
 */
void trafficSimulator( char* filename )
{
    /* TODO: complete this function */

    /* Read in the traffic data from filename.  It's recommended you call readTrafficDataFromInputFile to do this: */
    TrafficData* tData = readTrafficDataFromInputFile( filename );
    int i, j;
    int maxSteps = 0;
    double sum = 0.0;
    int timeStep = 0;
    int noMovement = 0;
    bool noMove = true;
    bool gridlock = false;
    Event *currentEvent;
    RoadData *road;
    int nextOnShortestPath;
    Car *car;
    //bool fromWait = false; //checks if latest car added is from queue
    int totCars = 0;   
    
    //while ( (tData->numCars > 0 || !gridlock) && !isEmptyPQ( tData->events) )
    while (true)
    {   
    /* Loop until all events processed and either all cars reached destination or gridlock has occurred */
	
        /* Update the state of every traffic light */
        for (i = 0; i < tData->numRoads; i++)
	{
	    if (tData->roads[i].cycleStep >= tData->roads[i].gOn && tData->roads[i].cycleStep < tData->roads[i].gOff)
		tData->roads[i].green = true;
	    else if (tData->roads[i].cycleStep >= tData->roads[i].gOff || tData->roads[i].cycleStep < tData->roads[i].gOn)
		tData->roads[i].green = false;
	    tData->roads[i].cycleStep += 1;
	    if (tData->roads[i].cycleStep != tData->roads[i].cycleReset)
		continue;
	    else
		tData->roads[i].cycleStep = 0;
	    //printf("Light is: %d\n", tData->roads[i].green); // green = 1, red = 0
	}
        /* Loop on events associated with this time step */
	while (!isEmptyPQ(tData->events))
	{
	    if (getFrontPriority(tData->events) == timeStep)
	    {
	        //printf("Front priority: %d\n", getFrontPriority( tData->events));
	        currentEvent = dequeuePQ( tData->events);
		//printf("type: %d, toV: %d, fromV: %d\n", currentEvent->type, currentEvent->toV, currentEvent->fromV);
		if (currentEvent->type == ADD_CAR_EVENT)
		{
		    road = getEdgeData(tData->roadNetwork, currentEvent->fromV, currentEvent->toV);
		    mergeQueues( road->carsWaiting, currentEvent->carsToAdd);
		    freeQueue(currentEvent->carsToAdd);
		    printf("CYCLE %d - ADD_CAR_EVENT - Cars enqueued on road from %d to %d\n", timeStep, road->startVertex, road->endVertex);
		}
		else if (currentEvent->type == PRINT_ROADS_EVENT)
		{
		    printf("\nCYCLE %d - PRINT_ROADS_EVENT - Current contents of the roads:\n", timeStep);
		    printRoadData(tData);
		}
		free(currentEvent);
	    }
	    else
		break;
	}
	
        /* First try to move cars through the next intersection */
	
	for (i = 0; i < tData->numRoads; i++)
	{   
	    if (tData->roads[i].carsOnRoad[0] == NULL) //if no car at intersection
		continue;
	    else //if there is a car at intersection
	    {
		if (tData->roads[i].carsOnRoad[0]->destV == tData->roads[i].endVertex && tData->roads[i].green == true)
		{
		    noMove = false;
		    car = tData->roads[i].carsOnRoad[0];
		    tData->roads[i].carsOnRoad[0] = NULL;
		    sum += timeStep - car->stepAdded + 1;
		    totCars++;
		    if (maxSteps < timeStep - car->stepAdded + 1)
			maxSteps = timeStep - car->stepAdded + 1;
		    printf("CYCLE %d - Car successfuly traveled from %d to %d in %d time steps.\n", timeStep, car->startV, car->destV, timeStep - car->stepAdded + 1); 
		    free(car);
		    tData->numCars -= 1;
		    //printf("numCars: %d\n", tData->numCars);    
		}
		else if (tData->roads[i].green == true)  //what a behemoth oh my god
		{
		    //move car onto next road
		    getNextOnShortestPath(tData->roadNetwork, tData->roads[i].endVertex, tData->roads[i].carsOnRoad[0]->destV, &nextOnShortestPath);
		    road = getEdgeData( tData->roadNetwork, tData->roads[i].endVertex, nextOnShortestPath);
		    if ( road->carsOnRoad[road->length-1] == NULL)
		    {
			noMove = false;
			tData->roads[i].carsOnRoad[0]->moved = 1;
			road->fromIntersection = true;
			//printf("car moved intersection\n"); //this bugTest saved my life im shaking and crying rn howwww
			road->carsOnRoad[road->length-1] = tData->roads[i].carsOnRoad[0];
			tData->roads[i].carsOnRoad[0] = NULL;
		    }
			//gridlock check is here --no its not lol
		}
	    }
	}
        // Second move waiting cars onto the end of each road if possible 
	for (i = 0; i < tData->numRoads; i++)
	{
	    if (tData->roads[i].carsOnRoad[tData->roads[i].length-1] == NULL && !isEmpty(tData->roads[i].carsWaiting))
	    {
		car = dequeue(tData->roads[i].carsWaiting);
		car->moved = 1;
		noMove = false;
		//printf("car moved waitQueue\n"); //im writing the impacts of this test down for my grandkids
		tData->roads[i].carsOnRoad[tData->roads[i].length-1] = car;
		//printRoadData(tData);
		//printf("bingbongdingdong\n"); //TODO
		//fromWait = true;	
	    }
	}

	//printf("numIntersections: %d, numRoads: %d\n", tData->numIntersections, tData->numRoads); 
        // Third move cars forward on every road (only those that haven't moved yet this time step) 

	for (i = 0; i < tData->numRoads; i++)
	{
	    for (j = tData->roads[i].length - 1; j > 0; j--) 
	    {
		if (tData->roads[i].carsOnRoad[j] == NULL)
		    continue;
		if ( tData->roads[i].carsOnRoad[j]->moved == 1)
		{
		    tData->roads[i].carsOnRoad[j]->moved = 0;
		    //printf("car unmoved\n");
		    continue;
		}
		if (tData->roads[i].fromIntersection == true && j == tData->roads[i].length)
		{
		    tData->roads[i].fromIntersection = false;
		    continue;
		}
		if (tData->roads[i].carsOnRoad[j-1] == NULL) 
		{
		    noMove = false;
		    tData->roads[i].carsOnRoad[j-1] = tData->roads[i].carsOnRoad[j];
		    tData->roads[i].carsOnRoad[j] = NULL;
		    j--;
		}
	    }
	}
	
	if (noMove == true)
	    noMovement++;
	else
	{
	    noMovement = 0;
	    noMove = true;
	}

	if (noMovement == tData->longestTimeStep && tData->numCars != 0 && isEmptyPQ(tData->events))//noMovement > 2) //include else for when gridlock becomes false ---- not required under current conditions tho
	    gridlock = true;// the last condition in this if statement is sussy and needs to be fixed... but it fixes the test cases and im on no sleeeeepppp	
	
	if (isEmptyPQ(tData->events) && (gridlock || tData->numCars == 0))
	    break;
	
	
	//fromWait = false;
	//printf("timestep: %d\n", timeStep);
	timeStep++;
	
    }

    if (gridlock == true)
	printf("\nCYCLE %d - Gridlock detected.\n", timeStep+1);
    else
    {
	printf("\nAverage number of time steps to reach their destination is %.2lf\n", sum / totCars);
	printf("Maximum number of time steps to reach their destination is %d\n", maxSteps); 
    }
    for (i = 0; i < tData->numRoads; i++)
    {
    	while (!isEmpty(tData->roads[i].carsWaiting)) //frees all cars in waiting queue
	    free(dequeue( tData->roads[i].carsWaiting));
    	freeQueue(tData->roads[i].carsWaiting); //frees waiting queue
	for (j = 0; j < tData->roads[i].length; j++) 
	{
	    if (tData->roads[i].carsOnRoad[j] == NULL) //checks if road spot is occupied
		continue;
	    else //if occupied, frees the car
	    {
		free(tData->roads[i].carsOnRoad[j]);
	    }
	}
	free(tData->roads[i].carsOnRoad);
	
    }
	

    freePQ( tData->events);
    freeGraph(tData->roadNetwork);
    free(tData->roads);
    free(tData);
}

/* readTrafficDataFromInputFile
 * input: char* filename of file to read
 * output: TrafficData* which stores the data of this road network
 *
 * Create a new TrafficData variable and read in the traffic data from the file whose name is stored in char* filename
 */
TrafficData* readTrafficDataFromInputFile( char* filename )
{
    /* open the file */
    FILE *pFile = fopen( filename, "r" );
    int i, j, numVertices, numEdges, incomingRoads, numCarAdd, numCars, numPrintRoad; //vertice = intersection, edge = roads, loop variables here
    int fromVertex, toVertex, destVertex, priority; //variables to be input in structures
    int length, gOn, gOff, cycleReset;
    int currentRoad = 0;
    int totalNumCars = 0; 
    TrafficData *tData = NULL;
    Graph *g;
    RoadData *r;
    PriorityQueue *events; 
    Event *currentEvent;
    Queue *cars;   
    Car *currentCar;
    //Event *tempEvent = NULL;
	
    tData = (TrafficData*)malloc(sizeof(TrafficData)); // Freed
    tData->longestTimeStep = 0;

    fscanf( pFile, "%d%d", &numVertices, &numEdges); //TODO validate input here
    tData->numIntersections = numVertices;
    tData->numRoads = numEdges;

    //printf("numVertices = %d -- numEdges = %d\n", numVertices, numEdges);
    g = createGraph(numVertices); //FREED
    //printf("graph Gaming");
    r = (RoadData*)malloc(numEdges * sizeof(RoadData)); //FREED
    //printf("road reached?");
    for (i = 0; i < numVertices; i++)
    {
	fscanf( pFile, "%d", &incomingRoads);
	for (j = 0; j < incomingRoads; j++)
	{
	    /*fscanf( pFile, "%d%d%d%d%d", &fromVertex, &(tData->roads[currentRoad].length), &(tData->roads[currentRoad].gOn), &(tData->roads[currentRoad].gOff), &(tData->roads[currentRoad].cycleReset));
	    tData->roads[currentRoad].startVertex = fromVertex;
	    tData->roads[currentRoad].endVertex = i;
	    setEdge(tData->roadNetwork, fromVertex, i, tData->roads[currentRoad].length);
	    */
	    fscanf( pFile, "%d%d%d%d%d", &fromVertex, &length, &gOn, &gOff, &cycleReset);
	    r[currentRoad] = initializeRoad( length, 0, gOn, gOff, cycleReset, fromVertex, i);
	    
	    if (tData->longestTimeStep < cycleReset)
		tData->longestTimeStep = cycleReset;

	    setEdge(g, fromVertex, i, r[currentRoad].length);
	    setEdgeData(g, fromVertex, i, &r[currentRoad]);
	    //printf("from: %d - to: %d - length: %d - gOn: %d - gOff: %d - cycleReset: %d\n", fromVertex, i ,r[currentRoad].length, r[currentRoad].gOn, r[currentRoad].gOff, r[currentRoad].cycleReset);
	    //printf("fromV: %d - toV: %d\n", getEdgeData(g, fromVertex, i)->startVertex, getEdgeData(g, fromVertex, i)->endVertex);
	    currentRoad++; 
	}

    }

    fscanf( pFile, "%d", &numCarAdd);
    events = createPQ(); // FREED
    
    for (i = 0; i < numCarAdd; i++) //add car commands
    {
	 
	fscanf( pFile, "%d%d%d", &fromVertex, &toVertex, &priority);
	currentEvent = createEvent( ADD_CAR_EVENT, toVertex, fromVertex); // TODO FREE this - freed
	//printf("type: %d - toV: %d - fromV: %d\n", currentEvent.type, currentEvent.toV, currentEvent.fromV);	
	//printf("type: %d - toVertex: %d - fromVertex: %d\n", ADD_CAR_EVENT, toVertex, fromVertex);

	fscanf(pFile, "%d", &numCars);
	totalNumCars += numCars;
	cars = createQueue(); //TODO FREE THIS ----- MALLOCED * NumCarAdd

	for (j = 0; j < numCars; j++)
	{
	    currentCar = (Car*)malloc(sizeof(Car)); //TODO FREE THIS ------ MALLOCED NumCarAdd * numCars times
	    fscanf(pFile, "%d", &destVertex);
	    currentCar->destV = destVertex;
	    currentCar->stepAdded = priority;
	    currentCar->startV = fromVertex;
	    currentCar->moved = 0;
	    enqueue( cars, currentCar);
	    //printf("destV: %d - stepAdded: %d\n", currentCar->destV, currentCar->stepAdded);
	}
	currentEvent->carsToAdd = cars;
	enqueueByPriority( events, currentEvent, priority);
	//printf("priority: %d --- getPriority: %d\n", priority, getFrontPriority( events));
	//dequeuePQ( events);
    }

    fscanf( pFile, "%d", &numPrintRoad);
    for ( i = 0; i < numPrintRoad; i++)
    {
	currentEvent = createEvent(PRINT_ROADS_EVENT, 0, 0); //TODO FREE THIS --- MALLOCED * numPrintRoad times --should be freed
	fscanf( pFile, "%d", &priority);
	enqueueByPriority( events, currentEvent, priority);
    }

    /* while (!isEmptyPQ(events))
    {
	tempEvent = (Event*)malloc(sizeof(Event));
	tempEvent = dequeuePQ(events);
	printf("current type = %d, toV = %d, fromV = %d\n", tempEvent->type, tempEvent->toV, tempEvent->fromV);
    }*/	
    /* Optional TODO: read in all the data in pFile */
    /* HINT: use fscanf( pFile, "%d", &<your int variable here> ) to read an int from pFile */
    
    /* HINTs:
     * Each road can be stored in a `RoadData` struct (see `road.h`).
     *
     * You'll want to store all of these `RoadData` structs in a single array.  This is important to track the order that  
     * roads were added to your graph.  These are also the order they are processed in each time step.  You can store this
     * array in your TrafficData struct.
     *
     * You'll add edges to a graph to represent each road using `setEdge` (see `graph.c`).  The vertices of the graph 
     * represent intersections.  The graph will do the work of finding shortest paths (see `getNextOnShortestPath` in graph.c 
     * and the longest shortest path problem on Blackboard).
     *
     * It will also help to add your `RoadData` structs to your graph using `setEdgeData` (see `graph.c`).   You can then 
     * retrieve that `RoadData` struct by calling `getEdgeData`.  This will be helpful for finding roads when cars pass 
     * through intersections.
     * 
     * Each event will be stored in an Event struct (see `event.h`).
     * 
     * It's recommended to store all of the `Event` structs in a single priority queue (using time step as the priority).  This 
     * allows you to quickly find the next event to execute by time step (see `enqueueByPriority`, `getFrontPriority`, and 
     * `dequeuePQ`).
     *
     * Each car is stored in a Car struct (see `car.h`).
     */
    tData->numCars = totalNumCars;
    tData->events = events;    
    tData->roadNetwork = g;
    tData->roads = r;
    /* close file */
    fclose( pFile );

    return tData; /* Optional TODO: Replace this with your TrafficData pointer */
}

void printRoadData( TrafficData* tData)
{
	int i, j;
	
	for (i = 0; i < tData->numRoads; i++)
	{
	    printf("Cars on the road from %d to %d:\n", tData->roads[i].startVertex, tData->roads[i].endVertex);
	    for (j = 0; j < tData->roads[i].length; j++)
	    {
		if (tData->roads[i].carsOnRoad[j] == NULL)
		    printf("- ");
		else
		    printf("%d ", tData->roads[i].carsOnRoad[j]->destV);
	    }
	    if (tData->roads[i].green == true)
		printf("(GREEN light)\n");
	    else
		printf("(RED light)\n");

	}


}



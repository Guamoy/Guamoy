#include "graph.h"
#include "graphPathAlg.h"


/* printName
 * input: none
 * output: none
 *
 * Prints the name of the student who worked on this solution
 */
void printName( )
{
    /* TODO : Fill in your names */
    printf("This solution was completed by:\n");
    printf("Georgy Vinogradov\n");
}

/* OPTIONAL HELPER FUNCTION
 * buildGraph
 *
 * IMPORTANT NOTE: This is an entirely optional helper function which is only called by student implemented functions.
 * Creates a new graph to represent the given maze.  
 */
Graph* buildGraph( array2D* maze, Point2D *start, Point2D *finish, bool tunnel, int *numF /* and other parameters you find helpful */  )
{
    //OPTIONAL TODO: Translate the given maze into a graph.  'X' represents impassable locations.  Only moves of up, down, left, and right are allowed. 
    /* With the right parameters this can be used by all three functions below to build the graph representing their different maze problems. */
    /* HINT 1: To solve this, my solution used the functions createGraph and setEdge from graph.c */
    /* HINT 2: My solution also used createPoint from point2D.c */
    int i; // rows ---- y
    int j; // columns - x
    int k; 
    int xMove[4] = {0, 1, -1, 0};
    int yMove[4] = {1, 0, 0, -1};
    Point2D current;
    Point2D neighbor;
    Graph* g = createGraph( maze->length * maze->width);

    for (i = 0; i < maze->length; i++)
    {
	for (j = 0; j < maze->width; j++)
	{
	    if (tunnel == false)
		if (maze->array2D[i][j] == 'X')
		    continue;

	    if (maze->array2D[i][j] == 'S')
		*start = createPoint(j, i);
	
	    if (maze->array2D[i][j] == 'F')
	    {
		finish[*numF] = createPoint(j, i); //only relevant when there is only one F in maze
	    	*numF = *numF + 1;
		//printf("Finish %d x: %d, y: %d\n", numF-1, finish[numF-1].x, finish[numF-1].y); 
	    }
	    current = createPoint(j, i);
	    //printf("currPoints: x = %d, y = %d\n", current.x, current.y);
	    for (k = 0; k < 4; k++) //yeah this would be faster as a directed graph... ughhhhh
	    {
		if (i + yMove[k] >= 0 && i + yMove[k] <= maze->length - 1 && j + xMove[k] >= 0 && j + xMove[k] <= maze->width - 1) //bounds check -- since this function goes through the 2d array from left to right, then down a row, I can remove the checks for left and up
// but like it works and the deadline is really close so for later~~~~
		{
		    if (tunnel == true)
		    {
			neighbor = createPoint(j+xMove[k], i+yMove[k]);
			if (maze->array2D[i+yMove[k]][j+xMove[k]] == 'X') //Caroline Oliver is my hero for how to set these Edge Values
		    	    setEdge(g, current, neighbor, 1);
			else 
			    setEdge(g, current, neighbor, 0);
		    }
		    else if (maze->array2D[i+yMove[k]][j+xMove[k]] != 'X') //redundant else if, can just be else
		    {
			neighbor = createPoint(j+xMove[k], i+yMove[k]);
			//printf("curr: x = %d, y = %d || neighbor: x = %d, y = %d\n", current.x, current.y, neighbor.x, neighbor.y);
			setEdge(g, current, neighbor, 1);
		    }
		}
	    }
	}
    }

    //printf("numVertices = %d\n", g->numVertices);
    return g; /* TODO: Replace with your graph representing maze */
}

/* hasPath
 * input: an array2D pointer to a maze
 * output: pathResult
 *
 * Detects whether a path exists from 'S' to 'F' in the graph. 'X' marks impassable regions.
 */
pathResult hasPath( array2D *maze )
{
    //TODO: Complete this function
    /* HINT 1: To solve this, my solution used the functions createGraph, freeGraph, setEdge, dijkstrasAlg, getDistance from graph.c */
    /* HINT 2: My solution also used createPoint from point2D.c */
    /* HINT 3: You might also consider using the new helper function buildGraph to build the graph representing maze. */
    Point2D start;
    Point2D finish[50]; //I should have made this dynamic, but also i am on the brink of insanity already
    int numF = 0;
    Graph *g = buildGraph(maze, &start, finish, false, &numF);
    //printf("x = %d, y = %d\n", start.x, start.y);
    //printf("x = %d, y = %d\n", finish.x, finish.y);
    //printf("numVertices = %d\n", g->numVertices);
    dijkstrasAlg(g, start);
    
    if (getDistance(g, start, finish[0]) == INT_MAX)
    {
	freeGraph(g);
	return PATH_IMPOSSIBLE;
    }
    else
    {
	freeGraph(g);
	return PATH_FOUND;
    }
    freeGraph(g);
    return PATH_UNKNOWN; /* TODO: Replace with PATH_FOUND or PATH_IMPOSSIBLE based on whether a path exists */
}

/* findNearestFinish
 * input: an array2D pointer to a maze, a pointer to an int
 * output: pathResult
 *
 * The maze contains one 'S' and multiple 'F's (1 or more).  'X' marks impassable regions.
 * Find the length of the shortest path to any 'F' from 'S' and return it in spDist.
 * If no 'F' is reachable set spDist to INT_MAX.
 */
pathResult findNearestFinish( array2D *maze, int *spDist )
{
    //TODO: Complete this function
    /* HINT 1: To solve this, my solution used the functions createGraph, freeGraph, setEdge, dijkstrasAlg, getDistance from graph.c */
    /* HINT 2: My solution also used createPoint from point2D.c */
    /* HINT 3: You might also consider using the new helper function buildGraph to build the graph representing maze. */
    Point2D start;    
    Point2D finish[50];
    int numF = 0;
    int min = INT_MAX;
    int currDist;
    int i;
    Graph *g = buildGraph(maze, &start, finish, false, &numF);
    //printf("numF = %d\n", numF);
    dijkstrasAlg(g, start);    
        
    for (i = 0; i < numF; i++)
    {
	currDist = getDistance(g, start, finish[i]);
	if (min > currDist)
	    min = currDist;
    }

    (*spDist) = min; /* TODO: This returns your shortest path distance to any 'F' from the 'S'.  Set it to INT_MAX if no path exists. */
    freeGraph(g);
    if (*spDist == INT_MAX)
        return PATH_IMPOSSIBLE;
    else
	return PATH_FOUND;	 /* TODO: Replace with PATH_FOUND or PATH_IMPOSSIBLE based on whether a path exists */
}

/* findTunnelRoute
 * input: an array2D pointer to a maze, an int representing the number X's you can travel through
 * output: pathResult
 *
 * Detects whether a path exists from 'S' to 'F' in the graph where you pass through at most k 'X' symbols.
 */
pathResult findTunnelRoute( array2D *maze, int k )
{
    //TODO: Complete this function
    /* HINT 1: To solve this, my solution used the functions createGraph, freeGraph, setEdge, dijkstrasAlg, getDistance from graph.c */
    /* HINT 2: My solution also used createPoint from point2D.c */
    /* HINT 3: You might also consider using the new helper function buildGraph to build the graph representing maze. */
    Point2D start; 
    Point2D finish[50];
    int i;
    int numF = 0;
    Graph *g = buildGraph(maze, &start, finish, true, &numF);    
    dijkstrasAlg(g, start);
    
    if (getDistance(g, start, finish[0]) > k)
    {	
	freeGraph(g);
	return PATH_IMPOSSIBLE;
    }
    else
    {
	freeGraph(g);
	return PATH_FOUND;
    }
    freeGraph(g);
    return PATH_UNKNOWN; /* TODO: Replace with PATH_FOUND or PATH_IMPOSSIBLE based on whether a path exists */
}

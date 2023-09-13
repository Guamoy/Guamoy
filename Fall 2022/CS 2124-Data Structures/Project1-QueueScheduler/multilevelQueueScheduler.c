#include <stdlib.h>

#include "multilevelQueueScheduler.h"

void attemptPromote( schedule *ps );
int min( int x, int y );

static const int STEPS_TO_PROMOTION = 50;
static const int FOREGROUND_QUEUE_STEPS = 5;

/* printNames
 * input: none
 * output: none
 *
 * Prints names of the students who worked on this solution
 */
void printNames( )
{

    printf("\nThis solution was completed by:\n");
    printf("Georgy Vinogradov\n");
    printf("N/A\n\n");
}

/* createSchedule
 * input: none
 * output: a schedule
 *
 * Creates and return a schedule struct.
 */
schedule* createSchedule( ) {
	
    schedule *schedPointer = NULL;
    schedPointer = (schedule*)malloc(sizeof(schedule));
    schedPointer->foreQueue = createQueue(); 
    schedPointer->backQueue = createQueue();
    schedPointer->currentStep = 0; 
    return schedPointer; 
}

/* isScheduleUnfinished
 * input: a schedule
 * output: bool (true or false)
 *
 * Check if there are any processes still in the queues.
 * Return TRUE if there is.  Otherwise false.
 */
bool isScheduleUnfinished( schedule *ps ) {

    if (isEmpty(ps->foreQueue) == true && isEmpty(ps->backQueue) == true)
        return false;
    
    return true; 
}

/* addNewProcessToSchedule
 * input: a schedule, a string, a priority
 * output: void
 *
 * Create a new process with the provided name and priority.
 * Add that process to the appropriate queue
 */
void addNewProcessToSchedule( schedule *ps, char *processName, priority p ) {

    process *temp = (process*)malloc(sizeof(process)); //Freed in next functions
    temp->processName = processName; //FREED in next function
    
    temp->data = initializeProcessData(processName); //malloc in here - FREED in next function
    temp->stepAdded = ps->currentStep;

    if (p == FOREGROUND){
		temp->stepsRemaining = FOREGROUND_QUEUE_STEPS;
		enqueue(ps->foreQueue, temp);  
    }
    else if (p == BACKGROUND){
		temp->stepsRemaining = STEPS_TO_PROMOTION;
		enqueue(ps->backQueue, temp);
    }
    else{
		printf("Priority Error?");
		return;
	}
}

/* runNextProcessInSchedule
 * input: a schedule
 * output: a string
 *
 * Use the schedule to determine the next process to run and for how many time steps.
 * Call "runProcess" to attempt to run the process.  You do not need to print anything.
 * You should return the string received from "runProcess".  You do not need to use/modify this string in any way.
 */
char* runNextProcessInSchedule( schedule *ps ) {

    char *ret = NULL;
    int numSteps;
    process *theProcess = NULL; // I really want a THEprocess variable name, but its just bad practice. Best name would've been temp but that's boring
    bool b;
    attemptPromote( ps ); 

    if (isEmpty(ps->foreQueue) == false){
		if (isEmpty(ps->backQueue) == false){
			numSteps = min(getNext(ps->foreQueue)->stepsRemaining, getNext(ps->backQueue)->stepAdded + STEPS_TO_PROMOTION - ps->currentStep);
	    //printf("%d\n", getNext(ps->backQueue)->stepAdded + STEPS_TO_PROMOTION - ps->currentStep);

		}
		else
			numSteps = getNext(ps->foreQueue)->stepsRemaining;
    }
    else{ //forequeue is empty
		numSteps = getNext(ps->backQueue)->stepAdded + STEPS_TO_PROMOTION - ps->currentStep;

    }
       
    //Seeing the infinite loop message in my console felt like passing a trail by fire --- so satisfying 
    //^^Oh how I look upon my past celebrations, unaware of the horrors ahead
	
    if( !isEmpty(ps->foreQueue) ){ //checks Foreground
        theProcess = getNext(ps->foreQueue); //grabs front node of queue
		loadProcessData( theProcess->data); //prints nothing if already loaded
		b = runProcess( theProcess->processName, &ret, &numSteps); 
		ps->currentStep += numSteps;
		
		if (b == true){
			//printf("Foreground free here \n");
			dequeue(ps->foreQueue);   
			freeProcessData();
			free(theProcess->processName);
			free(theProcess);
		}
		
		else if (b == false){ 
			if (theProcess->stepsRemaining - numSteps > 0) //checks if process did 5 (FOREGROUND_QUEUE_STEPS) steps	    
				theProcess->stepsRemaining = FOREGROUND_QUEUE_STEPS - numSteps;
			else{
				theProcess->stepsRemaining = FOREGROUND_QUEUE_STEPS;
				dequeue(ps->foreQueue);
				enqueue(ps->foreQueue, theProcess);
			}
		}
    }
    else if( !isEmpty(ps->backQueue) ){ //checks background
        theProcess = getNext(ps->backQueue);
		loadProcessData( theProcess->data);
		b = runProcess( theProcess->processName, &ret, &numSteps);
		ps->currentStep += numSteps;
    	
		if (b == true){
			//printf("background free here \n"); //delete
			dequeue(ps->backQueue);
			freeProcessData();
			free(theProcess->processName);
			free(theProcess);
		}
		
		else if (b == false){
	    ; //My favorite line of code I've written, ever
		}
    }
  
    return ret; /* This will be the char* that runProcess stores in ret when called. */
}

/* attemptPromote
 * input: a schedule
 * output: none
 *
 * Promote every background process that has been waiting for 50 time steps.
 * This function might be tricky so you might save it for last.
 */
void attemptPromote( schedule *ps ) {
    process *temp = NULL;

    if (isEmpty(ps->backQueue) == false){
		temp = getNext(ps->backQueue);
    }
    else
		return;

    while (temp->stepAdded + STEPS_TO_PROMOTION - ps->currentStep == 0 && isEmpty(ps->backQueue) == false ){
		promoteProcess(temp->processName, temp->data);
		temp->stepsRemaining = FOREGROUND_QUEUE_STEPS;
		dequeue(ps->backQueue);
		enqueue(ps->foreQueue, temp);
		
		if (isEmpty(ps->backQueue) == false)
			temp = getNext(ps->backQueue);
    }
}

/* freeSchedule
 * input: a schedule
 * output: none
 *
 * Free all of the memory associated with the schedule.
 */
void freeSchedule( schedule *ps ) {
    freeQueue(ps->foreQueue);
    freeQueue(ps->backQueue);
    free(ps); // I was initially using "freeSchedule()" on this line initially because I thought it 
              // was a provided function like min or runProcess.
              // Valgrind was showing 8 allocs and 512,000 frees
              // I thought the error was with the freeQueue function lmao
              // I'm such a smart lil cookie and want to cry ughhhh
}

/* PROVIDED FUNCTION
 * freeSchedule
 * input: two ints
 * output: the smaller of the 2 ints
 */
int min( int x, int y ){
    if( x<y )
        return x;
    return y;
}

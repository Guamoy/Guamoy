#include "event.h"

/* File for any functions you want to create for events.  I didn't use this in my solution to project 2 but added in case you want the option. */

Event* createEvent( int type, int toV, int fromV)
{
	Event *event = (Event*)malloc(sizeof(Event));
	event->type = type;
	event->toV = toV;
	event->fromV = fromV;
	
	return event;
}

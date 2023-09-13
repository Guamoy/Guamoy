#include <stdio.h>
#include <stdlib.h>

#include "champion.h"

/*
	Function: createChampion
	------------------------
	This function dynamically allocates a new Champion struct object 
		No parameters
	Returns : Pointer to the champion struct object created which will later be used to 
	insert into a linked list. 
*/

Champion* createChampion()
{
	Champion *n = ( Champion* )malloc( sizeof( Champion ) );
	n->role = rand() % 4;
	switch( n->role )
	{
		case 0:
			n->level = rand() % 4 + 5;
			break;
		case 1:
			n->level = rand() % 4 + 1;
			break;
		case 2:
			n->level = rand() % 4 + 3;
			break;
		case 3:
			n->level = rand() % 8 + 1;
			break;
	}
	return n;	

}

/*
	Function: addChampion
	----------------------
	This function adds a new Champion struct object to the linked list that head is pointing at. 
	It is assumed that a new Champion struct object is being passed into this function as parameter c. 
	This function will add the new node in descending (decreasing) order of the champion’s “level” 
	value regardless of the “role”.
		Champion* head - head node of the linked list to be added to
		Champion* c - node to add to the linked list
	Returns: A pointer to the new head of the linked list
*/

Champion* addChampion( Champion *head, Champion *c )
{
	Champion* cur = head;
	Champion* prev = NULL;

	while (cur != NULL && cur->level >= c->level)
	{
		prev = cur;
		cur = cur->nextNodePtr;
	}
	if (prev == NULL){
		c->nextNodePtr = cur;
		return c;
	}
	else
	{
		prev->nextNodePtr = c;
		c->nextNodePtr = cur;
	}
	return head;

}

/*
	Function: buildChampionList
	----------------------------
	This function builds a list of champions using a linked list. The parameter n determines 
	how many champions are created. It will use createChampion() and addChampion() to create 
	and return the head of the new linked list.
		int n - number of champions to create
	Returns: A pointer to the new head of the linked list
*/

Champion* buildChampionList( int n )
{
	int i;
	Champion *cur = NULL;
	Champion *head = NULL;

	head = createChampion();

	for ( i = 1; i < n; i++ )
	{
		cur = createChampion();		
		head = addChampion( head, cur );
	}
	return head;
}

/*
	Function:  printChampionList
	----------------------------
	Prints the entire linked list (list of champions) pointed to by the head passed in as a parameter
		Champion* head- head of the linked list
	Returns: Nothing
*/


void printChampionList( Champion *head )
{
	Champion *t = head;
	while ( t != NULL )
	{
		switch ( t->role )
		{
			case 0:
				printf("M%d ", t->level);
				break;
			case 1:
				printf("F%d ", t->level);
				break;
			case 2:
				printf("S%d ", t->level);
				break;
			case 3:
				printf("T%d ", t->level);
				break;
		}
		t = t->nextNodePtr;
	}
	printf("\n");
}

/*
	Function: removeChampion
	------------------------
	Removes and deallocates the first node in the linked list that the head is pointing at
		Champion* head - head of the linked list
	Returns: A pointer to the new head of the linked list
*/ 


Champion* removeChampion( Champion *head )
{
	if ( head == NULL )
		return NULL;

	Champion *t = head;
	head = t->nextNodePtr;
	free(t);
	return head;
}

/*
	Function: destroyChampionList
	-----------------------------
	This function is the destructor for a linked list that head is pointing at. 
	It will remove all the champions from the player’s list and return NULL.
		Champion *head - head of the linked list
	Returns: The NULL value
*/

Champion* destroyChampionList( Champion *head )
{
	while ( head != NULL )
	{
		Champion *t = head;
		head = head->nextNodePtr;
		free( t );
	}
	return NULL;
}

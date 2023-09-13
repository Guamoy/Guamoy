/*
	champion.h
	Project 3
	Georgy Vinogradov

	This file contains the enumerator type declaration "ChampionRole", the struct declaration "Champion", 
	and 6 function declarations to be utilized in project 3's dueling game.

*/

#ifndef CHAMPION_H
#define CHAMPION_H

typedef enum ChampionRole{ MAGE, FIGHTER, SUPPORT, TANK }ChampionRole;

typedef struct Champion
{
	ChampionRole role;
	int level;
	struct Champion* nextNodePtr;
} Champion;

/*
	Function: createChampion
	------------------------
	This function dynamically allocates a new Champion struct object 
		No parameters
	Returns : Pointer to the champion struct object created which will later be used to 
	insert into a linked list. 
*/

Champion* createChampion();

/*
	Function: addChampion
	----------------------
	This function adds a new Champion struct object to the linked list that head is pointing at. 
	It is assumed that a new Champion struct object is being passed into this function as parameter c. 
	This function will add the new node in descending (decreasing) order of the champion’s “level” 
	value regardless of the “role”.
		Champion* - head node of the linked list to be added to
		Champion* - node to add to the linked list
	Returns: A pointer to the new head of the linked list
*/

Champion* addChampion( Champion*, Champion* );

/*
	Function: buildChampionList
	----------------------------
	This function builds a list of champions using a linked list. The parameter n determines 
	how many champions are created. It will use createChampion() and addChampion() to create 
	and return the head of the new linked list.
		int - number of champions to create
	Returns: A pointer to the new head of the linked list
*/

Champion* buildChampionList( int );

/*
	Function:  printChampionList
	----------------------------
	Prints the entire linked list (list of champions) pointed to by the head passed in as a parameter
		Champion* - head of the linked list
	Returns: Nothing
*/

void printChampionList( Champion* );

/*
	Function: removeChampion
	------------------------
	Removes and deallocates the first node in the linked list that the head is pointing at
		Champion* - head of the linked list
	Returns: A pointer to the new head of the linked list
*/ 

Champion* removeChampion( Champion* );

/*
	Function: destroyChampionList
	-----------------------------
	This function is the destructor for a linked list that head is pointing at. 
	It will remove all the champions from the player’s list and return NULL.
		Champion* - head of the linked list
	Returns: The NULL value
*/

Champion* destroyChampionList( Champion* ); 

#endif

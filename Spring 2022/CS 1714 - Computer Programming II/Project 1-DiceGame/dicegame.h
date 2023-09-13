/*
	dicegame.h
	Project 1
	Georgy Vinogradov
	
	This file contains all the five functions declaration utilized in project 1's dicegame 
	along with enumerator declaration of type ROUNDTYPE.

*/

#ifndef DICEGAME_H
#define DICEGAME_H

enum ROUNDTYPE {BONUS, DOUBLE, REGULAR};

/* 
	Function: getRandomNumber
	----------------------
	Gets a random number from min to max inclusive
		parameter 1: Integer value that determines lower bound of random number
		parameter 2: Integer value that determines upper bound of random number

	Returns: A random integer from min to max
*/

int getRandomNumber( int, int );

/*
	Function: getRoundType()
	----------------------
	Calculates a random number using getRandomNumber() from 0-2 and chooses a roundtype
	based on the rnadom number. 20% for BONUS, 30% for DOUBLE, and 50% for Regular.
	
	Returns: Randomly picked Roundtype enumerator

*/

enum ROUNDTYPE getRoundType();

/*
	Function: getRoundPoints()
	--------------------------
	Uses getRandomNumber to choose a random number from 10-100, then modifies number by parameter roundtype 
	to determine the number of points associated with a round.

		enum ROUNDTYPE: A value that could be BONUS, DOUBLE, REGULAR, and determines the modifier to
		be applied to initially calculated round points.

	Returns: Integer containing the number of points associated with a round.

*/

int getRoundPoints( enum ROUNDTYPE );

/*
	Function: printPlayerPoints()
	-----------------------------
	Prints formatted player points
		parameter 1: Integer that represents points held by first player
		parameter 2: Integer that represents points held by second player
	Returns: Void function

*/

void printPlayerPoints( int, int );

/*
	Function: printRoundInfo()
	---------------------------
	Prints formmated round information
		parameter 1: refers to the current roundtype to be printed
		parameter 2: Value that represents the dice number rolled for a round
		parameter 3: Value holding the number of points to be won or lost in a round
	Returns: Void function

*/

void printRoundInfo( enum ROUNDTYPE, int, int );

#endif

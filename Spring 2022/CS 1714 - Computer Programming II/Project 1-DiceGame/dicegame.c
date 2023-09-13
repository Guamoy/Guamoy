/*
	dicegame.c
	Project 1
	Georgy Vinogradov
	
	This file contains all the five functions utilized for project 1's dice game.

*/
#include <stdlib.h>
#include <stdio.h>
#include "dicegame.h"

/* 
	Function: getRandomNumber
	----------------------
	Gets a random number from min to max inclusive
		int min: Integer value that determines lower bound of random number
		int max: Integer value that determines upper bound of random number

	Returns: A random integer from min to max
*/

int getRandomNumber ( int min, int max ) 
{
  int randomNum = ( rand() % ( max - min + 1 ) ) + min;
  return randomNum;
}

/*
	Function: getRoundType()
	----------------------
	Calculates a random number using getRandomNumber() from 0-9 and chooses a roundtype
	based on the random number. 20% for BONUS, 30% for DOUBLE, and 50% for Regular.
	
	Returns: Randomly picked Roundtype enumerator

*/

enum ROUNDTYPE getRoundType()
{
  int randomRoundValue;
  enum ROUNDTYPE roundType;
  randomRoundValue = getRandomNumber( 0, 9 );

  if( randomRoundValue >= 0 && randomRoundValue < 2 )
  {
    roundType = BONUS;
  }
  else if( randomRoundValue >= 2 && randomRoundValue < 5 )
  {
    roundType = DOUBLE;
  }
  else
  {
    roundType = REGULAR;
  }

  return roundType;
}

/*
	Function: getRoundPoints()
	--------------------------
	Uses getRandomNumber to choose a random number from 10-100, then modifies number by parameter roundtype 
	to determine the number of points associated with a round.

		enum ROUNDTYPE roundType: A value that could be BONUS, DOUBLE, REGULAR, and determines the modifier to
		be applied to initially calculated round points.

	Returns: Integer containing the number of points associated with a round.

*/
int getRoundPoints( enum ROUNDTYPE roundType ) 
{
  int points = getRandomNumber( 1, 10 ) * 10;
  switch(roundType)
  {
    case BONUS:
      points = 200;
      break;
    case DOUBLE:
      points = points * 2;
      break;
    case REGULAR:
      //do nothing
      break;
    default:
      printf("Error: GetRoundPoints invalid ROUNDTYPE");
      break;
  }
  return points;
}

/*
	Function: printPlayerPoints()
	-----------------------------
	Prints formatted player points
		int p1: Integer that represents points held by first player
		int p2: Integer that represents points held by second player
	Returns: Void function

*/

void printPlayerPoints( int p1, int p2 ) 
{
  printf("P1\t: %d\nP2\t: %d\n\n", p1, p2);
  return; 
}

/*
	Function: printRoundInfo()
	---------------------------
	Prints formmated round information
		ROUNDTYPE t: refers to the current roundtype to be printed
		int dice: Value that represents the dice number rolled for a round
		int points: Value holding the number of points to be won or lost in a round
	Returns: Void function

*/

void printRoundInfo( enum ROUNDTYPE t, int dice, int points ) //prints formatted round info
{
  switch (t)
  {
    case BONUS:
      printf("TYPE\t: BONUS\nDICE\t: %d\nPOINTS\t: %d\n", dice, points);
      break;
    case DOUBLE:
      printf("TYPE\t: DOUBLE\nDICE\t: %d\nPOINTS\t: %d\n", dice, points);
      break;
    case REGULAR:
      printf("TYPE\t: REGULAR\nDICE\t: %d\nPOINTS\t: %d\n", dice, points);
      break;
  }
  return;
}

/*
	main.c
	Project 1
	Georgy Vinogradov
	
	Main function for project 1's dicegame which receives user input, calls all functions utilized
	in the game, and contains the logic of game progression and game winners.

*/

#include <stdio.h>
#include <stdlib.h>
#include "dicegame.h"
#include <time.h>

int main ( int argc, char *argv[] )
{
	// Initialize the srand() to start the random generator
	
	srand( (int)time( 0 ) ); //seeds random gen with time in seconds since Jan 1, 1970
	int p1Points = 0; 
	int p2Points = 0;
	int rounds;
	int currentRound;
	int currentPlayer;
	int diceRoll;
	int roundPoints;
	enum ROUNDTYPE type;
	currentPlayer = getRandomNumber( 1, 2 ); //randomly chooses the first player


	printf("Enter the number of rounds: "); //prompts user for number of rounds to play
	scanf("%d", &rounds);
	printPlayerPoints( p1Points, p2Points ); //prints formatted player scores
	
	for( currentRound = 1; currentRound <= rounds; currentRound++ ) //iterates through number of rounds specified by player
	{
		type = getRoundType(); //determines current round type
		diceRoll = getRandomNumber( 1, 6 ); // determines dice roll for given round
		roundPoints = getRoundPoints( type ); //determines number of points associated with a round based on roundtype

		printf("ROUND %d\n--------\n", currentRound); // Print round number
		printf("Player\t: %d\n", currentPlayer); // Print current player
		printRoundInfo( type, diceRoll, roundPoints ); // prints the round information
	
		switch( currentPlayer )
		// MAIN GAME LOGIC
		{
			case (1):
				if ( diceRoll % 2 != 1 ) // p1 loss
				{
					p1Points -= roundPoints;
					currentPlayer = 2;
				}
				else //p1 win
				{
					p1Points += roundPoints;
				}
				break;
			case ( 2 ): 
				if ( diceRoll % 2 != 0 ) //p2 loss
				{
					p2Points -= roundPoints;
					currentPlayer = 1;
				}
				else //p2 win
				{
					p2Points += roundPoints;
				}
				break;
		}
			// Current player incurs penalty of the same number of points, based on the type of the round (see above). In the next round, the current player is changed to the other player.
		printPlayerPoints( p1Points, p2Points );
	}
	printf("GAME OVER!!\n"); //indicates all rounds have been iterated through and game has ended
	if ( p1Points > p2Points ) //p1 wins
		printf("P1 Dumpstered P2!\n");
	else if ( p1Points < p2Points ) //p2 wins
		printf("P2 has completely and utterly annihilated P1!\n");
	else
		printf("Somehow, there was a TIE!"); //indicates tie

	return 0;
}

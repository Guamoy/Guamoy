/*
	main.c
	Project 3
	Georgy Vinogradov

	Main function for project 3's dueling game, contains the seed for rand(), command line input validation,
	logic for champion duels, and calls all functions related to the game.

*/

#include <stdio.h>
#include <stdlib.h>

#include "champion.h"

int main ( int argc, char* argv[] )
{
	int loopCon = 0;
	int round = 1;
	char *a = argv[1];
	int numInput = atoi(a);
	Champion *p1Head = NULL;
	Champion *p2Head = NULL;
	Champion *new = NULL;
	srand(time(0)); //seeds rand function

	if ( argc != 2 || numInput < 1) //checks for correct num of command line arguments
	{
		printf("ERROR: No ARGS\n");
		return 1;
	}

	if ( numInput < 1 ) //checks for proper input
	{
		printf("ERROR: Input must be greater than 0\n");
		return 1;
	}	

	p1Head = buildChampionList( numInput );
	p2Head = buildChampionList( numInput );	

	printf("============= PLAYER 1 V PLAYER 2 SHOWDOWN ============\n");
	
	while ( loopCon == 0 ) //infinite loop
	{
		printf("\n----- ROUND %d -----\n", round);
		printf("Player 1: ");
		printChampionList( p1Head );
		printf("Player 2: ");
		printChampionList( p2Head );
		
		//print player champions logic

		switch ( p1Head->role ) // 16 permutations of champion duels
		//as a reminder, here is the champion enumerator declaration
		//typedef enum ChampionRole{ MAGE, FIGHTER, SUPPORT, TANK }ChampionRole;
		{
			case 0:
				switch ( p2Head->role )
				{
					case 0:
						printf("Player 1 is a MAGE and Player 2 is a MAGE\n");
						if ( p1Head->level > p2Head->level )
						{
							printf("Player 1 (MAGE) wins and gains a new champion.\n");
							printf("Player 2 (MAGE) loses one champion.\n");

							p1Head = removeChampion( p1Head ); 
							p2Head = removeChampion( p2Head );

							new = createChampion();
							p1Head = addChampion( p1Head, new );
							p2Head = removeChampion( p2Head );

						}
						else if ( p1Head->level < p2Head->level )
						{
							printf("Player 1 (MAGE) loses one champion.\n");
							printf("Player 2 (MAGE) wins and gains a new champion.\n");

							p1Head = removeChampion( p1Head ); 
							p2Head = removeChampion( p2Head );

							new = createChampion();
							p2Head = addChampion( p2Head, new );
							p1Head = removeChampion( p1Head );
						}
						else
						{
							printf("Neither player won, nothing happens.\n");
							p1Head = removeChampion( p1Head ); 
							p2Head = removeChampion( p2Head );
						}
						break;
					case 1:
						printf("Player 1 is a MAGE and Player 2 is a FIGHTER\n");
						if ( p1Head->level > p2Head->level )
						{
							printf("Player 1 (MAGE) wins and gains a new champion.\n");
							printf("Player 2 (FIGHTER) loses but with no penalty.\n");

							p1Head = removeChampion( p1Head ); 
							p2Head = removeChampion( p2Head );

							new = createChampion();
							p1Head = addChampion( p1Head, new );

						}
						else if ( p1Head->level < p2Head->level )
						{
							printf("Player 1 (MAGE) loses one champion.\n");
							printf("Player 2 (FIGHTER) wins but with no reward.\n");

							p1Head = removeChampion( p1Head ); 
							p2Head = removeChampion( p2Head );

							p1Head = removeChampion( p1Head ); 
						}
						else
						{
							printf("Neither player won, nothing happens.\n");
							p1Head = removeChampion( p1Head ); 
							p2Head = removeChampion( p2Head );
						}
						break;
					case 2:
						printf("Player 1 is a MAGE and Player 2 is a SUPPORT\n");
						if ( p1Head->level > p2Head->level )
						{
							printf("Player 1 (MAGE) wins and gains a new champion.\n");
							printf("Player 2 (SUPPORT) loses two champions.\n");

							p1Head = removeChampion( p1Head ); 
							p2Head = removeChampion( p2Head );

							new = createChampion();
							p1Head = addChampion( p1Head, new );
							p2Head = removeChampion( p2Head ); 
							p2Head = removeChampion( p2Head );

						}
						else if ( p1Head->level < p2Head->level )
						{
							printf("Player 1 (MAGE) loses one champion.\n");
							printf("Player 2 (SUPPORT) wins and gains two new champions.\n");

							p1Head = removeChampion( p1Head ); 
							p2Head = removeChampion( p2Head );

							new = createChampion();
							p2Head = addChampion( p2Head, new );
							new = createChampion();
							p2Head = addChampion( p2Head, new );
							p1Head = removeChampion( p1Head ); 
						}
						else
						{
							printf("Neither player won, nothing happens.\n");
							p1Head = removeChampion( p1Head ); 
							p2Head = removeChampion( p2Head );
						}
						break;
					case 3:
						printf("Player 1 is a MAGE and Player 2 is a TANK\n");
						printf("Player 1 (MAGE) gains one new champion.\n");
						printf("Player 2 (TANK) loses one champion.\n");

						p1Head = removeChampion( p1Head ); 
						p2Head = removeChampion( p2Head );

						new = createChampion();
						p1Head = addChampion( p1Head, new );
						p2Head = removeChampion( p2Head );

						break;
				}
				break;
			case 1:
				switch ( p2Head->role )
				{
					case 0:
						printf("Player 1 is a FIGHTER and Player 2 is a MAGE\n");
						if ( p1Head->level < p2Head->level )
						{
							printf("Player 1 (FIGHTER) loses but with no penalty.\n");
							printf("Player 2 (MAGE) wins and gains a new champion.\n");

							p1Head = removeChampion( p1Head ); 
							p2Head = removeChampion( p2Head );

							new = createChampion();
							p2Head = addChampion( p2Head, new );

						}
						else if ( p1Head->level > p2Head->level )
						{
							printf("Player 1 (FIGHTER) wins but with no reward.\n");
							printf("Player 2 (MAGE) loses one champion.\n");

							p1Head = removeChampion( p1Head ); 
							p2Head = removeChampion( p2Head );

							p2Head = removeChampion( p2Head );
						}
						else
						{
							printf("Neither player won, nothing happens.\n");
							p1Head = removeChampion( p1Head ); 
							p2Head = removeChampion( p2Head );
						}
						break;
					case 1:
						printf("Player 1 is a FIGHTER and Player 2 is a FIGHTER\n");
						printf("Player 1 (FIGHTER) gains a new champion.\n");
						printf("Player 2 (FIGHTER) gains a new champion.\n");
						
						p1Head = removeChampion( p1Head ); 
						p2Head = removeChampion( p2Head );

						new = createChampion();
						p1Head = addChampion( p1Head, new );
						new = createChampion();
						p2Head = addChampion( p2Head, new );

						break;
					case 2:
						printf("Player 1 is a FIGHTER and Player 2 is a SUPPORT\n");
						if ( p1Head->level > p2Head->level )
						{
							printf("Player 1 (FIGHTER) wins but gains no reward.\n");
							printf("Player 2 (SUPPORT) loses one champion.\n");

							p1Head = removeChampion( p1Head ); 
							p2Head = removeChampion( p2Head );

							p2Head = removeChampion( p2Head );

						}
						else if ( p1Head->level < p2Head->level )
						{
							printf("Player 1 (FIGHTER) loses with no penalty.\n");
							printf("Player 2 (SUPPORT) wins and gains one new champion.\n");

							p1Head = removeChampion( p1Head ); 
							p2Head = removeChampion( p2Head );

							new = createChampion();
							p2Head = addChampion( p2Head, new );
						}
						else
						{
							printf("Neither player won, nothing happens.\n");
							p1Head = removeChampion( p1Head ); 
							p2Head = removeChampion( p2Head );
						}
						break;
					case 3:
						printf("Player 1 is a FIGHTER and Player 2 is a TANK\n");
						printf("Player 1 (FIGHTER) wins and gains one new champion.\n");
						printf("Player 2 (TANK) loses but with no penalty.\n");

						p1Head = removeChampion( p1Head ); 
						p2Head = removeChampion( p2Head );

						new = createChampion();
						p1Head = addChampion( p1Head, new );

						break;
				}
				break;
			case 2:
				switch ( p2Head->role )
				{
					case 0:
						printf("Player 1 is a SUPPORT and Player 2 is a MAGE\n");
						if ( p1Head->level < p2Head->level )
						{
							printf("Player 1 (SUPPORT) loses two champions.\n");
							printf("Player 2 (MAGE) wins and gains a new champion.\n");

							p1Head = removeChampion( p1Head ); 
							p2Head = removeChampion( p2Head );

							new = createChampion();
							p2Head = addChampion( p2Head, new );
							p1Head = removeChampion( p1Head );
							p1Head = removeChampion( p1Head );

						}
						else if ( p1Head->level > p2Head->level )
						{
							printf("Player 1 (SUPPORT) wins and gains two new champions.\n");
							printf("Player 2 (MAGE) loses one champion.\n");

							p1Head = removeChampion( p1Head ); 
							p2Head = removeChampion( p2Head );

							new = createChampion();
							p1Head = addChampion( p1Head, new );
							new = createChampion();
							p1Head = addChampion( p1Head, new );
							p2Head = removeChampion( p2Head );
						}
						else
						{
							printf("Neither player won, nothing happens.\n");
							p1Head = removeChampion( p1Head ); 
							p2Head = removeChampion( p2Head );
						}
						break;
					case 1:
						printf("Player 1 is a SUPPORT and Player 2 is a FIGHTER\n");
						if ( p1Head->level < p2Head->level )
						{
							printf("Player 1 (SUPPORT) loses one champion.\n");
							printf("Player 2 (FIGHTER) wins but gains no reward.\n");

							p1Head = removeChampion( p1Head ); 
							p2Head = removeChampion( p2Head );

							p1Head = removeChampion( p1Head );

						}
						else if ( p1Head->level > p2Head->level )
						{
							printf("Player 1 (SUPPORT) wins and gains one new champion.\n");
							printf("Player 2 (FIGHTER) loses with no penalty.\n");

							p1Head = removeChampion( p1Head ); 
							p2Head = removeChampion( p2Head );

							new = createChampion();
							p1Head = addChampion( p1Head, new );
						}
						else
						{
							printf("Neither player won, nothing happens.\n");
							p1Head = removeChampion( p1Head ); 
							p2Head = removeChampion( p2Head );
						}
						break;
					case 2:
						printf("Player 1 is a SUPPORT and Player 2 is a SUPPORT\n");
						printf("Player 1 loses a champion.\n");
						printf("Player 2 loses a champion.\n");
							
						p1Head = removeChampion( p1Head ); 
						p2Head = removeChampion( p2Head );

						p1Head = removeChampion( p1Head ); 
						p2Head = removeChampion( p2Head );
						
						break;
					case 3:
						printf("Player 1 is a SUPPORT and Player 2 is a TANK\n");

						printf("Player 1 (SUPPORT) loses but with no penalty.\n");
						printf("Player 2 (TANK) wins and gets a new champion.\n");

						p1Head = removeChampion( p1Head ); 
						p2Head = removeChampion( p2Head );

						new = createChampion();
						p2Head = addChampion( p2Head, new );

						break;
				}
				break;
			case 3:
				switch ( p2Head->role )
				{
					case 0:
						printf("Player 1 is a TANK and Player 2 is a MAGE\n");
						printf("Player 1 (TANK) loses one champion.\n");
						printf("Player 2 (MAGE) gains one new champion.\n");

						p1Head = removeChampion( p1Head ); 
						p2Head = removeChampion( p2Head );

						new = createChampion();
						p2Head = addChampion( p2Head, new );
						p1Head = removeChampion( p1Head );

						break;
					case 1:
						printf("Player 1 is a TANK and Player 2 is a FIGHTER\n");
						printf("Player 1 (TANK) loses but with no penalty.\n");
						printf("Player 2 (FIGHTER) wins and gains one new champion.\n");

						p1Head = removeChampion( p1Head ); 
						p2Head = removeChampion( p2Head );

						new = createChampion();
						p2Head = addChampion( p2Head, new );

						break;
					case 2:
						printf("Player 1 is a TANK and Player 2 is a SUPPORT\n");

						printf("Player 1 (TANK) wins and gets a new champion.\n");
						printf("Player 2 (SUPPORT) loses but with no penalty.\n");

						p1Head = removeChampion( p1Head ); 
						p2Head = removeChampion( p2Head );

						new = createChampion();
						p1Head = addChampion( p1Head, new );

						break;
					case 3:
						printf("Player 1 is a TANK and Player 2 is a TANK\n");

						printf("Nothing happens - no penalty or reward.\n");
						
						p1Head = removeChampion( p1Head ); 
						p2Head = removeChampion( p2Head );
				
						break;
				}
				break;

		}

		//sleep(5); //ooOOOooooo the game is fun now
		if ( p1Head == NULL || p2Head == NULL ) //end loop when either player has no champions
			loopCon = 1;

		round++;
	}

	printf("\n============ GAME OVER  =============\n\n");
	printf("Player 1 ending champion list: ");
	printChampionList( p1Head );
	printf("Player 2 ending champion list: ");
	printChampionList( p2Head );
	printf("\n");

	if ( p1Head == NULL && p2Head == NULL ) 
		printf("TIE -- both players ran out of champions.\n");
	else if ( p1Head != NULL && p2Head == NULL )
	{
		destroyChampionList( p1Head );
		printf("Player 2 ran out of champions. Player 1 wins.\n");
	}
	else if ( p1Head == NULL && p2Head != NULL )
	{
		destroyChampionList( p2Head );	
		printf("Player 1 ran out of champions. Player 2 wins.\n");
	}
	else
		printf("Its broke bruh ughhhhhhhh");

	return 0;
}

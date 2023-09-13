/*
	route-records.c
	Project 2
	Georgy Vinogradov
	This file contains all four functions utilized for project 2's csv analysis.

*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "route-records.h"

/*
	Function: createRecords
	------------------------
	Counts the number of lines in the input file and dynamically allocates a struct array of type RouteRecord based on line count
		File* fileIn - pointer to input file
	
	returns: pointer to RouteRecord array
*/

RouteRecord* createRecords( FILE* fileIn )
{
	RouteRecord* routeRecords = NULL;
	int count = 0;
	int i;
	int j;
	char garbo[50]; //stores line read from file, whose ultimate fate is to disappear into obscurity

	while (!feof(fileIn))
	{
		fgets( garbo, 50, fileIn );
		count++;
	}
	
	routeRecords = (RouteRecord*)malloc(count * sizeof(RouteRecord));
	//printf("Count: %d\n", count);
	for ( i = 0; i < count; i++)
	{
		for ( j = 0; j < 6; j++ )
		{ 
			routeRecords[i].passengers[j] = 0;
		}
	}	
	rewind(fileIn);
	
	return routeRecords;
}

/*
	Function: fillRecords
	-----------------------
	Processes the csv file and enters the parsed values into an array of type RouteRecord
		RouteRecord* r - pointer to RouteRecord array
		FILE* fileIn - pointer to input file
	
	returns: int number of unique entries in RouteRecord array to be used as length in array traversals
*/

int fillRecords( RouteRecord* r, FILE* fileIn )
{
	int index;
	char typeGarbo[50];
	int inputMonth;
	char inputOrigin[4];
	char inputDest[4];
	char inputAirline[3];
	int currPass;
	int count = 0;

	fgets( typeGarbo, 50, fileIn ); //dumps first line of file

	while(!feof( fileIn ))
	{
		fscanf( fileIn, "%d,%3s,%3s,%2s,%10s,%d", &inputMonth, inputOrigin, inputDest, inputAirline, typeGarbo, &currPass );
		index = findAirlineRoute( r, count, inputOrigin, inputDest, inputAirline, 0 );
		if ( index == -1 )
		{
			r[count].passengers[inputMonth-1] += currPass;
			strcpy( r[count].origin, inputOrigin );
			strcpy( r[count].destination, inputDest );
			strcpy( r[count].airline, inputAirline );
			count++; //only iterates when a new record is added
		}
		else if ( index != -1 ) //staying safe for sake of readability
		{
			r[index].passengers[inputMonth-1] = r[index].passengers[inputMonth-1] + currPass;
		}
		
	}
	return count;
}

/*
	findAirlineRoute
	------------------
	Traverses the RouteRecord array recursively to check if three parameter strings (keys) are present in array
		RouteRecord* r - pointer to RouteRecord array
		int length - Working size of array to be used
		const char* origin - string to search for in array
		const char* destination - string to search for in array
		const char* airline - string to search for in array
	
	returns: Index of position of 3 keys in array if founnd, -1 if not found
*/

int findAirlineRoute( RouteRecord* r, int length, const char* origin, const char* destination, const char* airline, int curIdx )
{
	if ( curIdx >= length ) //base case
	{
		//printf("base case 1\n");
		return -1;
	
	}
	if ( strcmp( r[curIdx].origin, origin ) == 0 && strcmp( r[curIdx].destination, destination ) == 0 && strcmp( r[curIdx].airline, airline) == 0)
	{
		//printf("Base case 2\n");
		return curIdx; //base case 2
	
	}
	else //recursion
	{
		//printf("Recursion!!!!\n"); //lol what is this line
		findAirlineRoute( r, length, origin, destination, airline, curIdx + 1 );
	}
}

/*
	searchRecords
	---------------
	Traverses the RouteRecords array and gathers passenger data based on key
		RouteRecord *r - pointer to RouteRecord array
		int length - size of array to be traversed
		const char* key1 - string keyword to search for in array
		const char* key2 - string keyword to search for in array, used exclusively for destination
		SearchType st - specifies what type of information the key contains 

	returns: Void
*/

void searchRecords( RouteRecord* r, int length, const char* key1, const char* key2, SearchType st )
{
	int i;
	int totalPass;
	int totPassM1 = 0;
	int totPassM2 = 0;
	int totPassM3 = 0;
	int totPassM4 = 0;
	int totPassM5 = 0;
	int totPassM6 = 0;
	int matches = 0;
	switch ( st )
	{
		case ROUTE:
			for (i = 0; i < length; i++)
			{
				if ( strcmp( r[i].origin, key1 ) == 0 && strcmp( r[i].destination, key2 ) == 0)
				{
			 		printf("%s (%s-%s) ", r[i].airline, r[i].origin, r[i].destination);
					totPassM1 += r[i].passengers[0];
					totPassM2 += r[i].passengers[1];
					totPassM3 += r[i].passengers[2];
					totPassM4 += r[i].passengers[3];
					totPassM5 += r[i].passengers[4];
					totPassM6 += r[i].passengers[5];
					matches++;
				}
			}
			totalPass = totPassM1 + totPassM2 + totPassM3 + totPassM4 + totPassM5 + totPassM6;
			printf("\n%d matches were found.\n", matches);
			if ( matches == 0 )
				return;
			printf("\nStatistics\nTotal Passengers\t%d\nTotal Passengers in Month 1:\t%d\n", totalPass, totPassM1);
			printf("Total Passengers in Month 2:\t%d\n", totPassM2);
			printf("Total Passengers in Month 3:\t%d\n", totPassM3);
			printf("Total Passengers in Month 4:\t%d\n", totPassM4);
			printf("Total Passengers in Month 5:\t%d\n", totPassM5);
			printf("Total Passengers in Month 6:\t%d\n", totPassM6);
			printf("\nAverage Passengers per Month:\t%d\n", totalPass / 6);
			break;

		case ORIGIN:
			for (i = 0; i < length; i++)
			{
				if ( strcmp( r[i].origin, key1 ) == 0 )
				{
			 		printf("%s (%s-%s) ", r[i].airline, r[i].origin, r[i].destination);
					totPassM1 += r[i].passengers[0];
					totPassM2 += r[i].passengers[1];
					totPassM3 += r[i].passengers[2];
					totPassM4 += r[i].passengers[3];
					totPassM5 += r[i].passengers[4];
					totPassM6 += r[i].passengers[5];
					matches++;
				}
			}
			totalPass = totPassM1 + totPassM2 + totPassM3 + totPassM4 + totPassM5 + totPassM6;
			printf("\n%d matches were found.\n", matches);
			if ( matches == 0 )
				return;
			printf("\nStatistics\nTotal Passengers\t%d\nTotal Passengers in Month 1:\t%d\n", totalPass, totPassM1);
			printf("Total Passengers in Month 2:\t%d\n", totPassM2);
			printf("Total Passengers in Month 3:\t%d\n", totPassM3);
			printf("Total Passengers in Month 4:\t%d\n", totPassM4);
			printf("Total Passengers in Month 5:\t%d\n", totPassM5);
			printf("Total Passengers in Month 6:\t%d\n", totPassM6);
			printf("\nAverage Passengers per Month:\t%d\n", totalPass / 6);
			break;

		case DESTINATION:
			for (i = 0; i < length; i++)
			{
				if ( strcmp( r[i].destination, key2 ) == 0 )
				{
			 		printf("%s (%s-%s) ", r[i].airline, r[i].origin, r[i].destination);
					totPassM1 += r[i].passengers[0];
					totPassM2 += r[i].passengers[1];
					totPassM3 += r[i].passengers[2];
					totPassM4 += r[i].passengers[3];
					totPassM5 += r[i].passengers[4];
					totPassM6 += r[i].passengers[5];
					matches++;
				}
			}
			totalPass = totPassM1 + totPassM2 + totPassM3 + totPassM4 + totPassM5 + totPassM6;
			printf("\n%d matches were found.\n", matches);
			if ( matches == 0 )
				return;
			printf("\nStatistics\nTotal Passengers\t%d\nTotal Passengers in Month 1:\t%d\n", totalPass, totPassM1);
			printf("Total Passengers in Month 2:\t%d\n", totPassM2);
			printf("Total Passengers in Month 3:\t%d\n", totPassM3);
			printf("Total Passengers in Month 4:\t%d\n", totPassM4);
			printf("Total Passengers in Month 5:\t%d\n", totPassM5);
			printf("Total Passengers in Month 6:\t%d\n", totPassM6);
			printf("\nAverage Passengers per Month:\t%d\n", totalPass / 6);
			break;

		case AIRLINE:
			for (i = 0; i < length; i++)
			{
				if ( strcmp( r[i].airline, key1 ) == 0 )
				{
			 		printf("%s (%s-%s) ", r[i].airline, r[i].origin, r[i].destination);
					totPassM1 += r[i].passengers[0];
					totPassM2 += r[i].passengers[1];
					totPassM3 += r[i].passengers[2];
					totPassM4 += r[i].passengers[3];
					totPassM5 += r[i].passengers[4];
					totPassM6 += r[i].passengers[5];
					matches++;
				}
			}
			totalPass = totPassM1 + totPassM2 + totPassM3 + totPassM4 + totPassM5 + totPassM6;
			printf("\n%d matches were found.\n", matches);
			if ( matches == 0 )
				return;
			printf("\nStatistics\nTotal Passengers\t%d\nTotal Passengers in Month 1:\t%d\n", totalPass, totPassM1);
			printf("Total Passengers in Month 2:\t%d\n", totPassM2);
			printf("Total Passengers in Month 3:\t%d\n", totPassM3);
			printf("Total Passengers in Month 4:\t%d\n", totPassM4);
			printf("Total Passengers in Month 5:\t%d\n", totPassM5);
			printf("Total Passengers in Month 6:\t%d\n", totPassM6);
			printf("\nAverage Passengers per Month:\t%d\n", totalPass / 6);
			break;

	}
}

/*
	printMenu
	----------
	Prints menu to prompt user interaction
		No parameters
	
	returns: void
*/

void printMenu()
{	
	
	printf("\n\n######### Airline Route Records Database MENU #########\n" );
	printf( "1. Search by Route\n" );
	printf( "2. Search by Origin Airport\n" );
	printf( "3. Search by Destination Airport\n" );
	printf( "4. Search by Airline\n" );
	printf( "5. Quit\n" );
	printf( "Enter your selection: " );
	
}

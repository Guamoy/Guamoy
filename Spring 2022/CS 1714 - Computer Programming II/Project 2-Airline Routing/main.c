/*
	main.c
	Project 2
	Georgy Vinogradov

	Main function for project 2's CSV file analysis which reads file name from terminal, opens the file and 
	calls functions to process files. Then prompts user for keys to gather statistics on file.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "route-records.h"

int main( int argc, char *argv[] )
{
	FILE* inFile = NULL;
	char fileName[100];
	RouteRecord* routeRecordPtr = NULL;
	int uniqueRecords;
	int loopCon = 0;
	int input;
	char origin[4];
	char destination[4];
	int numRead;

	if (argc != 2) //checks for proper console input
	{
		printf("ERROR: Missing File Name\n");
		return 1;		
	}    

    
	strcpy(fileName, argv[1]); //saves file name
	printf("Opening %s...\n", fileName); 
	inFile = fopen(fileName, "r"); //tries to open file
    
	if (inFile == NULL) //checks if file opened successfully
	{
		printf("ERROR: Could not open file\n");
		return -1;
	}    

	routeRecordPtr = createRecords( inFile ); //creates array of type RouteRecord
    		

	uniqueRecords = fillRecords( routeRecordPtr, inFile ); 
	printf("Unique routes operated by airlines: %d\n", uniqueRecords);
	
	fclose( inFile ); //closes the file

	while (loopCon != 1) // infinity loop
	{
		printMenu(); //scare user with confrontation
		numRead = scanf("%d", &input); //steal user number
		
		if ( numRead != 1 ) //handles incorrect user input
		{
			printf("Error: Invalid Input\n");
			while( getchar() != '\n' );
			continue;
		}

		if (input > 0 && input < 6)
		{
			switch ( input ) //does a thing
			{
			case 1 :
				printf("Enter Origin: \n");
				scanf("%s", origin);
				printf("Enter Destination: \n");
				scanf("%s", destination);
				printf("Searching by route...\n");
				searchRecords( routeRecordPtr, uniqueRecords, origin, destination, ROUTE );
				break;
			case 2 :
				printf("Enter Origin: \n");
				scanf("%s", origin);
				printf("Searching by origin...\n");
				searchRecords( routeRecordPtr, uniqueRecords, origin, destination, ORIGIN );
				break;
			case 3 :
				printf("Enter Destination: \n");
				scanf("%s", destination);
				printf("Searching by destination...\n");
				searchRecords( routeRecordPtr, uniqueRecords, origin, destination, DESTINATION );
				break;
			case 4 :
				printf("Enter airline: \n");
				scanf("%s", origin); //no need to create a new value
				printf("Searching by airline...\n");
				searchRecords( routeRecordPtr, uniqueRecords, origin, destination, AIRLINE );
				break;
			case 5 :
				free( routeRecordPtr ); //frees memory allocated to RouteRecord array
				printf("Good-bye!\n");
				exit(0); //quits the program
			}	
		}
		else
		{
		printf("Invalid Choice.\n"); //ruins user's life
		}

	}
    
    return 0; //this shouldnt ever be reached theoretically
}

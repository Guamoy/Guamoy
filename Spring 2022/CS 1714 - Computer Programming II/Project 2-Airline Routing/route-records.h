/*
	route-records.h
	Project 2
	Georgy Vinogradov

	The file contains the struct declaration "RouteRecord", enumerator declaration 
	of type SearchType, and five function declarations to be utilized in project 2's 
	CSV file analysis.

*/

#ifndef ROUTE_RECORDS_H
#define ROUTE_RECORDS_H

typedef struct RouteRecord_struct {
	char origin[4];
	char destination[4];
	char airline[3];
	int passengers[6];
} RouteRecord;

typedef enum SearchType { ROUTE, ORIGIN, DESTINATION, AIRLINE 
} SearchType;

/*
	Function: createRecords
	------------------------
	Counts the number of lines in the input file and dynamically allocates a struct array of type RouteRecord based on line count
		File* - pointer to input file
	
	returns: pointer to RouteRecord array
*/

RouteRecord* createRecords( FILE* );

/*
	Function: fillRecords
	-----------------------
	Processes the csv file and enters the parsed values into an array of type RouteRecord
		RouteRecord* - pointer to RouteRecord array
		FILE* - pointer to input file
	
	returns: int number of unique entries in RouteRecord array to be used as length in array traversals
*/

int fillRecords( RouteRecord*, FILE* );

/*
	findAirlineRoute
	------------------
	Traverses the RouteRecord array recursively to check if three parameter strings (keys) are present in array
		RouteRecord* - pointer to RouteRecord array
		int - Working size of array to be used
		const char* - string to search for in array
		const char* - string to search for in array
		const char* - string to search for in array
	
	returns: Index of position of 3 keys in array if founnd, -1 if not found
*/

int findAirlineRoute( RouteRecord*, int, const char*, const char*, const char*, int );

/*
	searchRecords
	---------------
	Traverses the RouteRecords array and gathers passenger data based on key
		RouteRecord* - pointer to RouteRecord array
		int - size of array to be traversed
		const char* - string keyword to search for in array
		const char* - string keyword to search for in array, used exclusively for destination
		SearchType - specifies what type of information the key contains 

	returns: Void
*/

void searchRecords( RouteRecord*, int, const char*, const char*, SearchType );

/*
	printMenu
	----------
	Prints menu to prompt user interaction
		No parameters
	
	returns: void
*/

void printMenu();

#endif




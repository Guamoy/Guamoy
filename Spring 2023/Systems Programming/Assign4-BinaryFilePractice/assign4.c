#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>
#include <stdint.h>
#include "assign4.h"

FILE *coursesFile;
#define FILE_PATH "courses.dat"

int main(int argc, char argv[]) 
{
	char inputOpt = 'x';
	int iScanfCount;
	char inBuffer[101];

	while (1) //include ctrl-d exit
	{
		printf("\n");
		printf("Enter one of the following actions or press CTRL-D to exit.\n");
		printf("C - create a new course record\n");
		printf("U - update an existing course record\n");
		printf("R - read an existing course record\n");
		printf("D - delete an existing course record\n");
		printf("\n");
		
		//inputOpt = getchar();

		if (fgets(inBuffer, 100, stdin) == NULL)
		{
			printf("Ending Program\n");
			return 0;
		}
		iScanfCount = sscanf(inBuffer, " %c", &inputOpt);
		if (iScanfCount != 1) //I dont think this can be triggered, as only the first char is always read anyways
		{
			printf("Error: Only 1 input character accepted, Received %d. Found %s\n", iScanfCount, inBuffer);
			continue;
		}
		switch (inputOpt)
		{
			case 'c':
			case 'C':
				//printf("C reached\n");
				createCourse();
				break;
			case 'u':
			case 'U':
				//update
				//printf("U reached\n");
				updateCourse();
				break;
			case 'r':	
			case 'R':
				//read
				//printf("R reached\n");
				readCourse();
				break;
			case 'd':
			case 'D':
				//delete
				//printf("D reached\n");
				deleteCourse();
				break;
			default: 
				printf("Error: Invalid character entered, input must be: [C, U, R, D] or CTRL-D\n");
		}
	}
}

int createCourse()
{
	FILE *tempReadFile; //temp file should be simplified into just coursesFile
	char inBuffer[101];
	int iScanfCount;
	COURSE course;
	COURSE temp;
	//int inputLines = 0;
	int courseNumber;
	//int iFdWr;
	int iNumRecRead;

	printf("Enter the Course number: \n");
	fgets(inBuffer, 100, stdin);
	if (sscanf(inBuffer, "%d\n", &courseNumber) != 1)
	{
		printf("error\n"); //obviously complete these TODO
		return -1;
	}

	printf("Enter the Course name: \n");
	fgets(inBuffer, 100, stdin);
	if (sscanf(inBuffer, "%[^\n]", course.course_Name) != 1)
	{
		printf("error\n"); //obviously complete these TODO
		return -1;
	}

	printf("Enter the Course Schedule: \n");
	fgets(inBuffer, 100, stdin);
	if (sscanf(inBuffer, "%3s\n", course.course_Sched) != 1)
	{
		printf("error\n"); //obviously complete these TODO
		return -1;
	}

	printf("Enter the Course hours: \n");
	fgets(inBuffer, 100, stdin);
	if (sscanf(inBuffer, "%u\n", &course.course_Hours) != 1)
	{
		printf("error\n"); //obviously complete these TODO
		return -1;
	}

	printf("Enter the Course size: \n");
	fgets(inBuffer, 100, stdin);
	if (sscanf(inBuffer, "%u\n", &course.course_Size) != 1)
	{
		printf("error\n"); //obviously complete these TODO
		return -1;
	}

	tempReadFile = fopen(FILE_PATH, "rb");
	if (!tempReadFile)
	{
		printf("Error: Unable to open read file\n");
		return -1;
	}

	fseek(tempReadFile, sizeof(COURSE) * courseNumber, SEEK_SET);
	iNumRecRead = fread(&temp, sizeof(COURSE), 1L, tempReadFile);
	//printf("NumRecRead: %d, Hours: %u\n", iNumRecRead, temp.course_Hours);
	if (iNumRecRead != 0)
	{
		if (temp.course_Hours != 0)
		{
			printf("ERROR: Course already exists\n");
			fclose(tempReadFile);
			return -1;
		}
	}

	coursesFile = fopen(FILE_PATH, "rb+");
	if (!coursesFile)
	{
		printf("Error: Unable to open file\n");
		return -1;
	}

	fseek(coursesFile, sizeof(COURSE) * courseNumber, SEEK_SET); //include error checking 
	fwrite(&course, sizeof(COURSE), 1L, coursesFile);
	fclose(coursesFile);
	return 0;
}

int updateCourse()
{
	FILE *tempCourseFile; //temp file should be simplified into coursesFile
	COURSE course;
	COURSE oldCourse;
	COURSE newCourse;
	char inBuffer[101];
	int iScanfCount;
	int iNumRecRead;
	int courseNumber;
	int iNumRecWrote;
	int courseNameCheck = 0;
	int courseSchedCheck = 0;
	int courseHoursCheck = 0;
	int courseSizeCheck = 0;

	printf("Enter the Course number: \n");
	fgets(inBuffer, 100, stdin);
	if (sscanf(inBuffer, "%d\n", &courseNumber) != 1)
	{
		printf("Error: Course Number cannot be blank\n"); 
		return -1;
	}

	printf("Enter the Course name: \n");
	fgets(inBuffer, 100, stdin);
	if (strcmp(inBuffer, "\n") == 0)
		courseNameCheck = 1;
	sscanf(inBuffer, "%[^\n]", course.course_Name);/** != 1)
	{
		printf("error\n"); //obviously complete these TODO
		return -1;
	}**/

	printf("Enter the Course Schedule: \n");
	fgets(inBuffer, 100, stdin);
	if (strcmp(inBuffer, "\n") == 0)
		courseSchedCheck = 1;
	sscanf(inBuffer, "%3s\n", course.course_Sched);/** != 1)
	{
		printf("error\n"); //obviously complete these TODO
		return -1;
	}**/

	printf("Enter the Course hours: \n");
	fgets(inBuffer, 100, stdin);
	if (strcmp(inBuffer, "\n") == 0)
		courseHoursCheck = 1;
	sscanf(inBuffer, "%u\n", &course.course_Hours);/** != 1)
	{
		printf("error\n"); //obviously complete these TODO
		return -1;
	}**/

	printf("Enter the Course size: \n");
	fgets(inBuffer, 100, stdin);
	if (strcmp(inBuffer, "\n") == 0)
		courseSizeCheck = 1;
	sscanf(inBuffer, "%u\n", &course.course_Size);/** != 1)
	{
		printf("error\n"); //obviously complete these TODO
		return -1;
	}**/

	tempCourseFile = fopen(FILE_PATH, "rb");
	if (!tempCourseFile)
	{
		printf("Error: File not opened\n");
		return -1;
	}

	fseek(tempCourseFile, sizeof(COURSE) * courseNumber, SEEK_SET);
	iNumRecRead = fread(&oldCourse, sizeof(COURSE), 1L, tempCourseFile);
	if (iNumRecRead == 0 || oldCourse.course_Hours == 0)
	{
		printf("ERROR: course not found\n");
		fclose(tempCourseFile);
		return -1;
	}
	fclose(tempCourseFile);

	//this function is literally a million if statements im going insane
	if (courseNameCheck == 1)
	{
		//printf("no input name\n");
		strncpy(newCourse.course_Name, oldCourse.course_Name, sizeof(newCourse.course_Name));
	}
	else
	{
		//printf("yes input name\n");
		strncpy(newCourse.course_Name,  course.course_Name, sizeof(newCourse.course_Name));
	}
	/**
		replace every usage of strncpy with strlcpy or something safer 
	**/

	if (courseSchedCheck == 1)
	{
		//printf("no input sched\n");
		strncpy(newCourse.course_Sched, oldCourse.course_Sched, sizeof(newCourse.course_Sched));
	}
	else
	{
		//printf("yes input sched\n");
		strncpy(newCourse.course_Sched, course.course_Sched, sizeof(newCourse.course_Sched));
	}
	
	if (courseHoursCheck == 1)
	{
		//printf("no input hours\n");
		newCourse.course_Hours = oldCourse.course_Hours;
	}
	else
	{
		//printf("yes input hours\n");
		newCourse.course_Hours = course.course_Hours;
	}
	
	if (courseSizeCheck == 1)
	{
		//printf("no input size\n");
		newCourse.course_Size = oldCourse.course_Size;
	}
	else
	{
		//printf("yes input size\n");
		newCourse.course_Size = course.course_Size;
	}
	coursesFile = fopen(FILE_PATH, "rb+");
	fseek(coursesFile, sizeof(COURSE) * courseNumber, SEEK_SET); //resets fread movement
	iNumRecWrote = fwrite(&newCourse, sizeof(COURSE), 1L, coursesFile);

	if (iNumRecWrote != 1)
	{
		printf("Error writing record to file\n");
		fclose(coursesFile);
		return -1;
	}
	
	printf("Course %d successfully updated\n", courseNumber);
	fclose(coursesFile);
	return 0;
}

int readCourse()
{
	char inBuffer[101];
	int iScanfCount;
	int courseNumber;
	COURSE course;
	int iNumRecRead;

	printf("Enter the Course number: \n");
	fgets(inBuffer, 100, stdin);
	if (sscanf(inBuffer, "%d\n", &courseNumber) != 1)
	{
		printf("Error: Invalid input\n"); //make error message more robust TODO
		return -1;
	}

	coursesFile = fopen(FILE_PATH, "rb");
	if (!coursesFile)
	{
		printf("ERROR: Could not open file\n");
		return -1;
	}

	fseek(coursesFile, sizeof(COURSE) * courseNumber, SEEK_SET); //include error checking
	iNumRecRead = fread(&course, sizeof(COURSE), 1L, coursesFile);
	if (iNumRecRead != 1 || course.course_Hours == 0)
	{
		printf("Error: Course not found\n");
		fclose(coursesFile);
		return -1;
	}
	printf("Course number: %d\nCourse name: %s\nScheduled days: %s\nCredit Hours: %u\nEnrolled Students: %u\n", 
		courseNumber, course.course_Name, course.course_Sched, course.course_Hours, course.course_Size);
	fclose(coursesFile);
	return 0;
}

int deleteCourse()
{
	int courseNumber;
	char inBuffer[101];
	int iScanfCount;
	int iNumRecRead;
	int iNumRecWrote;
	COURSE course;
	FILE *tempReadFile;
	
	printf("Enter the course number: \n");
	fgets(inBuffer, 100, stdin);
	iScanfCount = sscanf(inBuffer, "%d\n", &courseNumber);
	if (iScanfCount != 1)
	{
		printf("Error: Invalid Input\n");
		return -1;
	}

	tempReadFile = fopen(FILE_PATH, "rb"); //since rb+ is used, tempFile can be simplified into just coursesFile
	if (!tempReadFile)
	{
		printf("ERROR: File not opened\n");
		return -1;
	}
	fseek(tempReadFile, sizeof(COURSE) * courseNumber, SEEK_SET);
	iNumRecRead = fread(&course, sizeof(COURSE), 1L, tempReadFile);
	//printf("Course hours: %u\n", course.course_Hours); 
	if (iNumRecRead != 1 || course.course_Hours == 0)
	{
		printf("ERROR: Course not found\n");
		fclose(tempReadFile);
		return -1;
	}
	fclose(tempReadFile);

	coursesFile = fopen(FILE_PATH, "rb+");
	fseek(coursesFile, sizeof(COURSE) * courseNumber, SEEK_SET);
	course.course_Hours = 0;
	iNumRecWrote = fwrite(&course, sizeof(COURSE), 1L, coursesFile);
	if (iNumRecWrote == 0)
	{
		printf("Error writing to file\n");
		fclose(coursesFile);
		return -1;
	}
	printf("Course %d was successfully deleted\n", courseNumber);
	fclose(coursesFile);
	return 0;
}

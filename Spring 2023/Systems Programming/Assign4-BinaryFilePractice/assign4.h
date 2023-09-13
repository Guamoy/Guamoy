#ifndef ASSIGN4_H
#define ASSIGN4_H

typedef struct {
	char course_Name[84];
	char course_Sched[4];
	unsigned course_Size;
	unsigned course_Hours;
} COURSE;

int createCourse();

int updateCourse();

int readCourse();

int deleteCourse();

#endif

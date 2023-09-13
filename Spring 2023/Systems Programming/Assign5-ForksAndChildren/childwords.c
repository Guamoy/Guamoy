#include <stdio.h>
#include <string.h>
#include <unistd.h>
//#include <errno.h>
#include <stdlib.h>

int countWords(char*);

int main(int argc, char *argv[])
{
	int numWords;
	int numErrors = 0;
	int exitStatus = 0;
	//int forkNum = 0;
	//pid_t lForkPid;
	//pid_t lWaitPid;
	//int iExitStatus;
	//pid_t iExit;
	
	for (int i = 1; i < argc; i++) 
	{
		if (fork() == 0)
		{
			//printf("Child pid %d from Parent pid %d\n", getpid(), getppid());
			numWords = countWords(argv[i]);
			if (numWords >= 0)
			{
				printf("Child process for %s: word count is %d\n", argv[i], numWords);
				exit(0);
			}
			else //file opening error
			{
				printf("Child process for %s: %s not opened\n", argv[i], argv[i]);
				return -1;
			}
		}
	}

	while (exitStatus = wait(NULL) > 0); 
	/**{
		printf("Exit status: %d\n", exitStatus);
		if (exitStatus == -1) 
		{
			numErrors++;
		}
	}**/
	printf("%d of %d files counted successfully\n", argc - 1 - numErrors, argc - 1); //this Line does not display unsuccessful files, is broken
	
	/**if (lForkPid = fork())
		printf("lForkPid is: %d\n", lForkPid);
	else if (lForkPid = fork())
		printf("lForkPid is: %d\n", lForkPid);
	

	switch (lForkPid) 
	{
		case -1:
			printf("Fork failed: %s", strerror(errno));
			return -1;
			break;
		case 0: //child
			printf("Child Process: PID=%ld, PPID=%ld\n", getpid(), getppid());
			break;
		default:
			printf("I am the parent: PID=%ld, PPID=%ld\n", getpid(), getppid());
			while (wait(NULL) > 0);
			if (lWaitPid == -1)
			{
				printf("Wait error: %s", strerror(errno));
				return -1;
			}
	}**/

	//printf("I'm %d, forkPid is %d\n", getpid(), lForkPid);
	//printf("My parent id is %d\n", getppid());
	//numWords = countWords(argv[1]);
	//printf("NumWords: %d\n", numWords);
	return 0;
}

int countWords(char *fileName)
{
	FILE *file = NULL;
	int numWords = 0;
	char inBuffer[65536];
	const char *delimiter = " \t\n";

	file = fopen(fileName, "r");

	if (file == NULL) {
		//printf("Error Opening File\n");
		return -1;
	}

	while (fgets(inBuffer, 65535, file)) 
	{
		if (strtok(inBuffer, delimiter)) {
			numWords++;
		
			while (strtok(NULL, delimiter)) {
				numWords++;
			}
		}
	}
	fclose(file);
	return numWords;
}

/*
@author Wahhaj Javed, muj975, 11135711
@date 2024-10-31
*/

#include <stdio.h>
#include <os.h>
#include <standards.h>

#include <Monitor.h>
#include <best_fit_monitor.h>


#define MAXALLOCATION 1000


PROCESS thread1(void* args) {
	int maxSleepTime, maxAllocation, freeProbability, numberOfIterations;
	int* a = (int*)args;
	maxSleepTime = a[0];
	maxAllocation = a[1];
	freeProbability = a[2];
	numberOfIterations = a[3];
	
	printf(
		"maxSleepTime = %d, "
		"maxAllocation = %d, "
		"freeProbability = %d, "
		"numberOfIterations = %d, ",
		maxSleepTime,
		maxAllocation,
		freeProbability,
		numberOfIterations
	);
	
}






void printUsage() {
		printf("Usage: ./best_fit <maxSleepTime>, <maxAllocation>, "
				"<freeProbability>, <numberOfIterations>\n");
		printf("maxSleepTime: 0 - 10\n");
		printf("maxAllocation: 0 - %d\n", MAXALLOCATION);
		printf("freeProbability: 0 - 100\n");
		printf("numberOfIterations: 1 - 10\n");
}

int mainp(int argc, char* argv[]) {
	int maxSleepTime, maxAllocation, freeProbability, numberOfIterations;
	int* args;
	if(argc != 5) {
		printUsage();
	}

	maxSleepTime = atoi(argv[1]);
	maxAllocation = atoi(argv[2]);
	freeProbability = atoi(argv[3]);
	numberOfIterations = atoi(argv[4]);
	
	if(maxSleepTime < 0 || maxSleepTime > 10) {
		printf("Max sleep time must be between 0 and 10.\n");
		printUsage();
		return 1;
	}
	if(maxAllocation < 0 || maxAllocation > MAXALLOCATION) {
		printf("Max allocation must be between 0 and %d.\n", MAXALLOCATION);
		printUsage();
		return 1;
	}
	if(freeProbability < 0 || freeProbability > 100) {
		printf("Free probability must be between 0 and 100.\n");
		printUsage();
		return 1;
	}
	if(numberOfIterations < 0 || numberOfIterations > 10) {
		printf("Number of iterations must be between 0 and 10.\n");
		printUsage();
		return 1;
	}
	
	if((args = malloc(4 * sizeof(int))) == NULL){
		perror("Error with malloc");
		return 1;
	}

	args[0] = maxSleepTime;
	args[1] = maxAllocation;
	args[2] = freeProbability;
	args[3] = numberOfIterations;
	
	Create( 
		(void(*)()) thread1,
		65536,
		"thread1",
		(void *) args,
		NORM,
		USR
	);


	
	
	return 0;
}
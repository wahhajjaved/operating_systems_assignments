/*
@author Wahhaj Javed, muj975, 11135711
@date 2024-10-31
*/

#include <best_fit_monitor.h>
#include <Monitor.h>

#define MAXALLOCATION 1000

void printUsage() {
		printf("Usage: ./best_fit <maxSleepTime>, <maxAllocation>, "
				"<freeProbability>, <numberOfIterations>\n");
		printf("maxSleepTime: 0 - 10\n");
		printf("maxAllocation: 0 - %d\n", MAXALLOCATION);
		printf("freeProbability: 0 - 100\n");
		printf("numberOfIterations: 1 - 10\n");
}

int main(int argc, char* argv[]) {
	int maxSleepTime, maxAllocation, freeProbability, numberOfIterations;
				 
	if(argc != 5) {
		printUsage();
	}
	
	maxSleepTime = atoi(argv[0]);
	maxAllocation = atoi(argv[1]);
	freeProbability = atoi(argv[2]);
	numberOfIterations = atoi(argv[3]);
	
	if(maxSleepTime < 0 || maxSleepTime > 10) {
		printf("Max sleep time must be between 0 and 10.\n");
		printUsage();
		exit(1);
	}
	if(maxAllocation < 0 || maxAllocation > MAXALLOCATION) {
		printf("Max allocation must be between 0 and %d.\n", MAXALLOCATION);
		printUsage();
		exit(1);
	}
	if(freeProbability < 0 || freeProbability > 100) {
		printf("Free probability must be between 0 and 100.\n");
		printUsage();
		exit(1);
	}
	if(numberOfIterations < 0 || numberOfIterations > 10) {
		printf("Number of iterations must be between 0 and 10.\n");
		printUsage();
		exit(1);
	}
	
	return 0;
}
/*
* @author Wahhaj Javed, muj975, 11135711
* @author Nakhba Mubashir, epl482, 11317060
* @date 2024-09-21
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*UBC pthreads headers*/
#include <kernel.h>

#include "square.h"

#define CHILD_STACK_SIZE 4000000

int getIndex() {
	PID pid;
	char *name, *p;
	PNODE *pd;
	int index;
	pid = MyPid();
	pd = getPcbFromPid(pid);
	name = GetPname(pd);
	index = strtol(name, &p, 10);
	return index;
}


PROCESS childThreadFunction(void* threadParams){
	int32_t n, index;
	int32_t* params;
	uint64_t elapsedTime;
	struct timespec startTime, endTime;
	
	params = (int*)threadParams;
	index = params[0];
	n = params[1];
	
	clock_gettime(CLOCK_MONOTONIC, &startTime);
	Square(n);
	clock_gettime(CLOCK_MONOTONIC, &endTime);
	elapsedTime = 1000000000L * (endTime.tv_sec - startTime.tv_sec) + 
        endTime.tv_nsec - startTime.tv_nsec;
	elapsedTime = elapsedTime / 1000;
	
	printf("Thread %d finished. "
        "Square called %d times. "
        "Thread ran for %lu microseconds.\n",
		index, pSquareCount[index], elapsedTime);
		
	return;
}
	
PROCESS parentThreadFunction(void* params){
	int32_t threads, size, deadline, *args, sleepTicks;
	int i;
	int32_t** threadParams;
	PID* threadIDs;
	char name[15];
	
	args = (int32_t*) params;
	threads = args[0];
	deadline = args[1];
	size = args[2];
	
	threadIDs = (PID *)malloc(sizeof(PID) * threads);
	pSquareCount = (int32_t *)calloc(threads, sizeof(int32_t));
	pStartTime = (int64_t *)calloc(threads, sizeof(int64_t));
	threadParams = malloc(threads * sizeof(int32_t*));
	
	for(i=0; i<threads; i++){
		PID id;
		threadParams[i] = malloc(sizeof(int32_t) * 2);
		threadParams[i][0] = i;
		threadParams[i][1] = size;
		
		snprintf(name, 15, "%d", i);
		id = Create( (void(*)()) childThreadFunction,
			CHILD_STACK_SIZE,
			name,
			threadParams[i],
			NORM,
			USR 
			);
		
		if (id == PNUL){
			printf("Failed to create thread %d.\n", i);
			return;
		}
		threadIDs[i] = id;
	}
	
	sleepTicks = deadline*1000000/TICKINTERVAL;
	printf("Main thread sleeping for %d ticks. \n", sleepTicks);
	
	/* Sleep doesn't work properly yet. 
		The main thread is supposed to use Kill() to kill child threads but 
		not enough time to implement that yet.
	*/
	
	while(sleepTicks > 0xffff) {
		Sleep(0xffff);
		sleepTicks -= 0xffff;
	}
	if(sleepTicks > 0) {
		Sleep(sleepTicks);
	}
	printf("Main thread woken up.\n");
	stopSquare = 1;
	Sleep(200);
}


void mainp(int argc, char* argv[]) {
	int32_t *args, parentStackSize;

	args = parseArgs(argc, argv);
    if(args == NULL) {
        return;
    }

	parentStackSize = CHILD_STACK_SIZE * args[0] + CHILD_STACK_SIZE;
	Create( (void(*)()) parentThreadFunction,
		parentStackSize,
		"a",
		(void *) args,
		NORM,
		USR
	);

	
}
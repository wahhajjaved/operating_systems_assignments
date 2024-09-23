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
	params = (int*)threadParams;
	index = params[0];
	n = params[1];
	
	Square(n);
	printf("Thread %d finished. Square called %d times. \n",
		index, pSquareCount[index]);
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
			16000,
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

	while(sleepTicks > 0xffff) {
		Sleep(0xffff);
		sleepTicks -= 0xffff;
	}
	if(sleepTicks > 0) {
		Sleep(sleepTicks);
	}
	printf("Main thread woken up.\n");
	stopSquare = 1;
	Sleep(100);
}



void mainp(int argc, char* argv[]) {
	int32_t *args;

	args = parseArgs(argc, argv);
    if (args == NULL){
        return;
    }
	
	 Create( (void(*)()) parentThreadFunction,
		16000,
		"a",
		(void *) args,
		NORM,
		USR
	);

	
}
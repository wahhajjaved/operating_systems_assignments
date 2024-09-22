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
	
	square(n);
	printf("Thread %d finished. Square called %d times. \n",
		index, pSquareCount[index]);
	return;
}
	
PROCESS parentThreadFunction(void* params){
	int32_t threads, size, deadline, *args;
	int i;
	int32_t** threadParams;
	PID* threadIDs;
	char name[15];
	
	args = (int32_t*) params;
	threads = args[0];
	deadline = args[1];
	size = args[2];
	
	printf("parentThreadFunction: threads %d, deadline %d, size %d\n", threads, deadline, size);

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
	
}



void mainp(int argc, char* argv[]) {
	char *p;
	int32_t threads, size, deadline;
	int32_t* threadParams;

	if (argc != 4) {
		printf("Invalid number of arguments.\n");
		printf("Usage: ./partA1 threads deadline size.\n");
		return;
	}
	
	threads = strtol(argv[1], &p, 10);
	deadline = strtol(argv[2], &p, 10);
	size = strtol(argv[3], &p, 10);
	
	threadParams = calloc(3, sizeof(int32_t));
	threadParams[0] = threads;
	threadParams[1] = deadline;
	threadParams[2] = size;
	
	if (threads < 1){
		printf("Invalid value %d for number of threads. Must be at least 1.\n",
			threads
		);
		return;
	}
	if (deadline <= 0){
		printf("Invalid value %d for deadline . Must be greater than 0\n",
			deadline
		 );
		return;
	}
	if (size < 0){
		printf("Invalid value %d for size. Must be at least 0\n", size);
		return;
	}
	
	printf("threads %d, deadline %d, size %d\n", threads, deadline, size);
	
	 Create( (void(*)()) parentThreadFunction,
		16000,
		"a",
		(void *) threadParams,
		NORM,
		USR
	);

	
}
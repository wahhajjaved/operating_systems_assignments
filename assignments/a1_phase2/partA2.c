/*
* @author Wahhaj Javed, muj975, 11135711
* @author Nakhba Mubashir, epl482, 11317060
* @date 2024-09-21
*/

#include <stdio.h>
#include <stdlib.h>

#include "square.h"

int main(int argc, char* argv[]) {
	char *p;
	int32_t threads, size;
	double deadline;
	HANDLE *threadHandles;
	DWORD *threadIDs;
	int i;
	int32_t** threadParams;

	if (argc != 4) {
		printf("Invalid number of arguments.\n");
		printf("Usage: ./partA1 threads deadline size.\n");
		return 1;
	}
	
	threads = strtol(argv[1], &p, 10);
	deadline = strtod(argv[2], &p);
	size = strtol(argv[3], &p, 10);
	
	if (threads < 1){
		printf("Invalid value %d for number of threads. Must be at least 1.\n",
			threads
		);
		return 1;
	}
	if (deadline <= 0){
		printf("Invalid value %.2f for deadline . Must be greater than 0\n",
			deadline
		 );
		return 1;
	}
	if (size < 0){
		printf("Invalid value %d for size. Must be at least 0\n", size);
		return 1;
	}

	
	printf("threads %d, deadline %.2f, size %d\n", threads, deadline, size);
}
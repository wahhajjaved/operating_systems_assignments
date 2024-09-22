/*
* @author Wahhaj Javed, muj975, 11135711
* @author Nakhba Mubashir, epl482, 11317060
* @date 2024-09-14
*/

#include "square.h"
#include <stdio.h>
#include <stdlib.h>



int32_t *pSquareCount;
int64_t *pStartTime;
int stopSquare = 0;

int64_t square(int n) {
	int index;
	if (n < 0){
		printf("Invalid value %d for n. Must be at least 0\n", n);
		return -1;
	}
    if (n == 0 || stopSquare != 0){
		return 0;
	}
	index = getIndex();
	pSquareCount[index]++;
	return (square(n - 1) + n + n - 1);
}



/* Parse the command line arguments

	Parameters:
		int argc: Number of arguments
		char* argv[]: Array of arguments
	
	Return
		int32_t* arr = {threads, deadline, size}
		NULL if arguments are invalid. 
		arr is dynamically allocated.
*/
int32_t* parseArgs(int argc, char* argv[]) {
	int32_t* r;
	int32_t threads, size, deadline;

	if (argc != 4) {
		printf("Invalid number of arguments.\n");
		printf("Usage: ./partA1 threads deadline size.\n");
		return NULL;
	}
	
	threads = strtol(argv[1], NULL, 10);
	deadline = strtod(argv[2], NULL);
	size = strtol(argv[3], NULL, 10);
	
	if (threads < 1){
		printf("Invalid value %d for number of threads. Must be at least 1.\n",
			threads
		);
		return NULL;
	}
	if (deadline <= 0){
		printf("Invalid value %d for deadline . Must be greater than 0.\n",
			deadline
		 );
		return NULL;
	}
	if (size < 0){
		printf("Invalid value %d for size. Must be at least 0.\n", size);
		return NULL;
	}
	
	printf("threads %d, deadline %d, size %d\n", threads, deadline, size);
	
	r = malloc(3 * sizeof(int32_t));
	r[0] = threads;
	r[1] = deadline;
	r[2] = size;
	
	return r;

}
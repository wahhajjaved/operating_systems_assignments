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

int64_t Square(int n) {
	int64_t r;
	while(n >= 0){
		r = square(n);
		if (r < 0) {
			return -1;
		}
		n--;
	}
	return 0;
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
	char* endptr;


	if (argc != 4) {
		printf("Invalid number of arguments.\n");
		printf("Usage: ./partA1 threads deadline size.\n");
		return NULL;
	}
	
	threads = strtol(argv[1], &endptr, 10);
	if (*endptr != '\0' || threads < 1){
		printf("Invalid value %s for number of threads. "
			"Must be an integer greater than 0.\n",
			argv[1]
		);
		return NULL;
	}
	
	
	deadline = strtol(argv[2], &endptr, 10);
	if (*endptr != '\0' || deadline <= 0){
		printf("Invalid value %s for deadline. "
			"Must be an integer greater than 0.\n",
			argv[2]
		 );
		return NULL;
	}
	
	size = strtol(argv[3], &endptr, 10);
	if (*endptr != '\0' || size < 0 || size > MAN_SIZE){
		printf("Invalid value %s for size. "
			"Must be non-negative integer between 0 and %d.\n",
			argv[3],
			MAN_SIZE
		);
		return NULL;
	}
	
	printf("threads %d, deadline %d, size %d\n\n", threads, deadline, size);
	
	r = malloc(3 * sizeof(int32_t));
	r[0] = threads;
	r[1] = deadline;
	r[2] = size;
	
	return r;

}
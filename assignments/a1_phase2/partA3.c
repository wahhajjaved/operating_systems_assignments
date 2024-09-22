/*
* @author Wahhaj Javed, muj975, 11135711
* @author Nakhba Mubashir, epl482, 11317060
* @date 2024-09-22
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

#include "square.h"
pthread_key_t tlsKey;

int getIndex() {
	int index;
	index = *(int*)pthread_getspecific(tlsKey);
	return index;
}

/* Entry point of the thread
	
	Parameters
		LPVOID lpParam: Array of ints. lpParam[0] is index of pSquareCount at
			which Square()'s call count is stored. lpParam[0] is the value
			passed to Square() when it is called
	
	Return
		0. Return value doesn't mean anything. It only exists to conform with
		the windows api
*/
void* tmain(void* lpParam) {
	int32_t n, index;
	int32_t* params;
	
	params = (int32_t*)lpParam;
	index = params[0];
	n = params[1];
    
	printf("tmain: index %d, n %d\n", index, n);
	pthread_setspecific(tlsKey, (void*)&index);

	square(n);

	printf("Thread %d finished. Square called %d times. \n",
		index, pSquareCount[index]);
	
	return 0;

}


int main(int argc, char* argv[]) {
	char *p;
	int32_t threads, size, deadline;
	pthread_t *threadIDs;
	int i;
	int32_t** threadParams;

	if (argc != 4) {
		printf("Invalid number of arguments.\n");
		printf("Usage: ./partA1 threads deadline size.\n");
		return 1;
	}
	
	threads = strtol(argv[1], &p, 10);
	deadline = strtol(argv[2], &p, 10);
	size = strtol(argv[3], &p, 10);
	
	if (threads < 1){
		printf("Invalid value %d for number of threads. Must be at least 1.\n",
			threads
		);
		return 1;
	}
	if (deadline <= 0){
		printf("Invalid value %d for deadline . Must be greater than 0\n",
			deadline
		 );
		return 1;
	}
	if (size < 0){
		printf("Invalid value %d for size. Must be at least 0\n", size);
		return 1;
	}

	
	printf("threads %d, deadline %d, size %d\n", threads, deadline, size);


	pthread_key_create(&tlsKey, NULL);
    /*
	if (tlsIndex == TLS_OUT_OF_INDEXES) {
        printf("Failed to allocate TLS index\n");
        return 1;
    }*/
	
	threadIDs = malloc(sizeof(pthread_t) * threads);
	pSquareCount = (int32_t *)calloc(threads, sizeof(int32_t));
	pStartTime = (int64_t *)calloc(threads, sizeof(int64_t));
	
	
	threadParams = malloc(threads * sizeof(int32_t*));
	for(i=0; i<threads; i++) {
		int r;
		threadParams[i] = malloc(sizeof(int32_t) * 2);
		threadParams[i][0] = i;
		threadParams[i][1] = size;
		
		r = pthread_create(
			&threadIDs[i],
			NULL,
			tmain,
			threadParams[i]
		);

		if (r != 0) {
			printf("pthread_create failed. Error: %u\n", r);
			return 1;
		}
	}


	sleep(deadline);
	stopSquare = 1;
	
	/*potential segfault if child threads don't stop fast enough before the
	arrays are freed. A small delay before freeing shoudl prevent this.*/
	sleep(1);


	free(threadIDs);
	free(pSquareCount);
	free(pStartTime);

	return 0;
}
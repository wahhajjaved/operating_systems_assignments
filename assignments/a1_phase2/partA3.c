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
    
	printf("tmain: index %d, n: %d\n", index, n);
	pthread_setspecific(tlsKey, (void*)&index);

	Square(n);

	printf("Thread %d finished. Square called %d times. \n",
		index, pSquareCount[index]);
	
	return 0;

}


int main(int argc, char* argv[]) {
	int32_t threads, size, deadline, *args;
	pthread_t *threadIDs;
	int i;
	int32_t** threadParams;

	args = parseArgs(argc, argv);
    if (args == NULL){
        return 1;
    }
    threads = args[0];
	deadline = args[1];
	size = args[2];

	pthread_key_create(&tlsKey, NULL);
	
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
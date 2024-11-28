/*
 * # @author Wahhaj Javed, muj975, 11135711
 * @author Nakhba Mubashir, epl482, 11317060
 * */

#include <mem-management.h>

#define STKSIZE 262144
/* Limits of the simulation */
#define MAX_THREADS    9
#define MAX_ITERATIONS 10000

/* Parameters */
#define ALLOC_MEAN  0x20000    /* 128 KiB */
#define ALLOC_STDEV 0xC000     /* 48 KiB */
#define SLEEP_MEAN  10000     /* 10 ms */

int allocSizes[MAX_THREADS][MAX_ITERATIONS];
int sleepTimes[MAX_THREADS][MAX_ITERATIONS];
bool doFree[MAX_THREADS][MAX_ITERATIONS];


typedef struct _params {
	int threadNo;
	int algNo;
} PARAMS;

int numIterations;
int numThreads;

RTTTHREAD MallocTest(void *arg);

void *MyMalloc(size_t size, int algNo) {
	if (algNo == 0)return FfMalloc(size);
	else if (algNo == 1)return BfMalloc(size);
	else
		errx(1, "MyMalloc: invalid algNo");
}

void MyFree(void *ptr, int algNo) {
	if (algNo == 0)FfFree(ptr);
	else if (algNo == 1)BfFree(ptr);
	else
		errx(1, "MyFree: invalid algNo");
}

int mainp(int argc, char* argv[]) {
	int i, j, temp;
    double u, x;

	RttSchAttr attr;
	RttThreadId pid[NUM_ALGS][MAX_THREADS];
	PARAMS* params;

	attr.startingtime = RTTZEROTIME;
	attr.priority = RTTNORM;
	attr.deadline = RTTNODEADLINE;

	setbuf(stdout, 0);

	/* check the command line arguments numThreads*/

    if (argc != 3)
		errx(1, "ERROR: expected 2 args, got %d", argc-1);

	numThreads = atoi(argv[1]);
    numIterations = atoi(argv[2]);
	if (numThreads < 1 || numThreads > MAX_THREADS)
		errx(1, "Erroe :numThreads must be between 1 and %d, but got %d\n",
         MAX_THREADS,numThreads );

	if (numIterations < 1 || numIterations > MAX_ITERATIONS)
		errx(1, "ERROR: numIterations must be between 1 and %d, but got %d\n", 
    MAX_ITERATIONS, numIterations);

	srand48(time(NULL));

	/* initialize the random numbersequences */
	for (i = 0; i < numThreads; i++) {
		for (j = 0; j < numIterations; j++) {
			/*normal distribution for allocation sizes */
			for (;;) {
				u = drand48();
				x = -log(u);
				if (drand48() < exp(-(x-1)*(x-1)/2))
					break;
			}
			if (drand48() > 0.5)
				allocSizes[i][j] = ALLOC_MEAN + ALLOC_STDEV * x;
			else {
				allocSizes[i][j] = ALLOC_MEAN - ALLOC_STDEV * x;
                /* make sure allocation is positive */
				if (allocSizes[i][j] <= 0)  
					allocSizes[i][j] = 1;
			}

			/*exponential distribution for sleep times */
			u = drand48();
			sleepTimes[i][j] = - SLEEP_MEAN * log(u);

			/* random binary value for free */
			doFree[i][j] = drand48() > 0.5;
		}
	}	

	Initialize(numThreads);  /* initialize the monitor */
	/* Create the threads for each algorithm */
	for (j = 0; j < numThreads; j++) {
		for (i = 0; i < NUM_ALGS; i++) {
			params = malloc(sizeof(PARAMS));
			params->threadNo = j;
			params->algNo = i;

			temp = RttCreate(&pid[i][j], (void(*)()) MallocTest, STKSIZE, NULL, 
				 	params, attr, RTTUSR);
			if (temp == RTTFAILED) {
				perror("RttCreate");
				exit(1);
			}
		}
	} 

	return 0;
}



RTTTHREAD MallocTest(void *arg) {
	int i;
	int algNo, threadNo;
	void *allocatedAddrs[MAX_ITERATIONS];

	threadNo = ((PARAMS*) arg)->threadNo;
	algNo = ((PARAMS*) arg)->algNo;
	free(arg);
	printf("threadNo=%d, algNo=%d\n", threadNo, algNo); 

	/* Initialize the allocated address array to all 0s (NULL) */
	for (i = 0; i < numIterations; i++) allocatedAddrs[i] = NULL;

	/* Main simulation loop */
	for (i = 0; i < numIterations; i++) {
/*		printf("%d-%d: attempting to allocate %u bytes\n", algNo, threadNo,
				allocSizes[threadNo][i]); 
*/
		/* Allocate a block of memory */
		allocatedAddrs[i] = MyMalloc(allocSizes[threadNo][i], algNo);
/*		printf("%d-%d: allocated block: %p to %p\n", algNo, threadNo, 
				(void*) allocatedAddrs[i], 
				(void*) ((long) allocatedAddrs[i] + allocSizes[threadNo][i] 
				- 1)); 
*/
		/* Sleep for some time */
		RttUSleep(sleepTimes[threadNo][i]);
/*		printf("%d-%d: slept for %d ticks\n", algNo, threadNo,
				sleepTimes[threadNo][i]); 
*/
		/* If freeing memory this iteration... */
		if (doFree[threadNo][i]) {
			int freeIndex;
			
			/* Determine a random addr to free from the random alloc size */
			freeIndex = allocSizes[threadNo][i] % (i + 1);

			/* Linear probing if address has already been freed */
			while (allocatedAddrs[freeIndex] == NULL)
				freeIndex = (freeIndex + 1) % (i + 1);	

			MyFree(allocatedAddrs[freeIndex], algNo);
/*	printf("%d-%d: freed block of allocated memory at 0x%lx\n", 
				algNo, threadNo, (long) allocatedAddrs[freeIndex]); 
			allocatedAddrs[freeIndex] = NULL;
*/	}
	}

	Threadend(algNo);  /* Prints results if this is the last thread */
}


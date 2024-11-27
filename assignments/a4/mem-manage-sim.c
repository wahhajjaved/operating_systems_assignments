/*
 * # @author Wahhaj Javed, muj975, 11135711
 * @author Nakhba Mubashir, epl482, 11317060
 * */

#include <mem-management.h>

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
 
	return 0;
}

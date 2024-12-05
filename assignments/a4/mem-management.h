/*
 * author Wahhaj Javed, muj975, 11135711
 * author Nakhba Mubashir, epl482, 11317060
 * */



#include <stdio.h>
#include <stdbool.h>
#include <err.h>
#include <time.h>
#include <math.h>
#include <list.h>
#include <rtthreads.h>
#include <RttCommon.h>
#include <monitor.h>

#define MEM_AVAILABLE  0x80000000l  /* 8 GiB */
#define MEM_BASE       0x80000000l
#define NUM_ALGS       2

/* store all stats for a single algorithm */
typedef struct {
	unsigned long numAllocations;
	unsigned long numDeallocations;
	unsigned long numSearchedNodesAllocation;
	unsigned long numSearchedNodesDeallocation;
	unsigned long numAllocatedSegments;
	unsigned long numUnallocatedSegments; /*number of holes*/
	unsigned long* allocatedSegmentsSizes; /*array of allocated segments*/
	unsigned long* unallocatedSegmentsSizes; /*array of free segments*/

} Stats;

typedef struct {
	char *start;
	size_t size;
} MemorySpace;


/* typedef struct {
	long int start;
	size_t size;
} MemorySpace;
 */


void Initialize(int numThreads);
void *FfMalloc(size_t size);
void *BfMalloc(size_t size);
void FfFree(void *ptr);
void BfFree(void *ptr);
void Threadend(int alg);
void MyMemStats(int algNo, void* statistics);


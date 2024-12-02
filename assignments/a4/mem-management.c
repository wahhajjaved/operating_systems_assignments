/*
 * # @author Wahhaj Javed, muj975, 11135711
 * @author Nakhba Mubashir, epl482, 11317060
 * */

#include <mem-management.h>

#define numConds 2
#define FFMemAvail 0
#define BFMemAvail 1

int threadsLeft[NUM_ALGS];

struct _FF{
    LIST *freeMem;
    LIST *allocateMem;
    Stats stat;
}FF;

struct _BF{
    LIST *freeMem;
    LIST *allocateMem;
    Stats stat;
}BF;


void *FfMalloc(size_t size) {
    MemorySpace *firstFit=NULL;
    MemorySpace *freeBlock, *allocaBlock;

    int wait= 0; /*wait flag*/

    if (size == 0) return NULL;
    RttMonEnter(); /* critical section*/
    /*find first free memory space */
    /*printf("size:%d\n", FF.freeMem->size);*/
    freeBlock = ListFirst(FF.freeMem);
    FF.stat.numSearchedNodesAllocation++;

    while (freeBlock != NULL) {
        /* check if the size is large wnough*/
        if (freeBlock->size >= size) {
            firstFit = freeBlock;
            break;
        }
        /*move to the next block*/
        freeBlock = ListNext(FF.freeMem);
        FF.stat.numSearchedNodesAllocation++;
    }
    /* no fit found, wait until Free() and then try again */
    while (firstFit == NULL) {
        errx(1, "FfMalloc: no freea block\n");
        wait = 1;
        RttMonWait(FFMemAvail);

        freeBlock = ListFirst(FF.freeMem);
        FF.stat.numSearchedNodesAllocation++;

        while (freeBlock != NULL) {
            if (freeBlock->size >= size) {
                firstFit = freeBlock;
                break;
            }
            freeBlock = ListNext(FF.freeMem);
            FF.stat.numSearchedNodesAllocation++;
        }
    /* If still no fit was found, signal the next waiting thread */
		if (firstFit == NULL)
			RttMonSignal(FFMemAvail);
           /* RttMonLeave();*/
            /*return NULL;*/
    }

    /* allocate and initialize the MemorySpace struct for
        allocated memory */
    allocaBlock = malloc(sizeof(MemorySpace));
    allocaBlock->start = firstFit->start;
    allocaBlock->size = size;
    ListAppend(FF.allocateMem, allocaBlock);

    /* If the free block equals size, remove it; otherwise, shrink it */
    if (firstFit->size == size) {
        ListRemove(FF.freeMem);
        free(firstFit);
    } else {
        firstFit->start += size;
        firstFit->size -= size;
    }

    if (wait)
        RttMonSignal(FFMemAvail);

    RttMonLeave();

    return allocaBlock->start;
}


void *BfMalloc(size_t size) {
    MemorySpace *bestFit, *freeBlock, *allocaBlock;

    int wait= 0; /*wait flag*/

    if (size == 0) return NULL;
    RttMonEnter(); /* critical section*/

    /*find Best free memory space */
    bestFit = NULL;
    freeBlock = ListFirst(BF.freeMem);
    BF.stat.numSearchedNodesAllocation++;

    while (freeBlock != NULL) {
        if ((freeBlock->size >= size) &&
            (bestFit == NULL || (freeBlock->size) < (bestFit->size)))
            bestFit = freeBlock;

        freeBlock = ListNext(BF.freeMem);
        BF.stat.numSearchedNodesAllocation++;
    }

    /* no fit found, wait until Free() and then try again */
    while (bestFit == NULL) {
        errx(1, "BFMalloc: no free block\n");
        wait = 1;
        RttMonWait(BFMemAvail);

        freeBlock = ListFirst(BF.freeMem);
        BF.stat.numSearchedNodesAllocation++;

        while (freeBlock != NULL) {
            if (freeBlock->size >= size) {
                bestFit = freeBlock;
                break;
            }

            freeBlock = ListNext(BF.freeMem);
            BF.stat.numSearchedNodesAllocation++;
        }
        /* If no fit was found, signal the next waiting */
        if (bestFit != NULL)
            RttMonSignal(BFMemAvail);
    }
    /* allocate and initialize the MemorySpace struct for the memory */
    allocaBlock = malloc(sizeof(MemorySpace));
    allocaBlock->start = bestFit->start;
    allocaBlock->size = size;
    ListAppend(BF.allocateMem, allocaBlock);


    /* if the free block equals size, remove it */
    if (bestFit->size == size) {
        /* refind the block since the pointer is at the end of the list */
        MemorySpace *memBlock = ListFirst(BF.freeMem);
        BF.stat.numSearchedNodesAllocation++;
        while (memBlock != bestFit){
            memBlock = ListNext(BF.freeMem);
            BF.stat.numSearchedNodesAllocation++;
        }
        ListRemove(BF.freeMem);
        free(bestFit);
    } else {
        bestFit->start += size;
        bestFit->size -= size;
    }

    if (wait) RttMonSignal(BFMemAvail);

    RttMonLeave();

    return allocaBlock->start;
}

void FfFree(void *ptr) {
	MemorySpace *mem, *freeMemBefore, *freeMemAfter;
	char *start;
	start = ptr;

	RttMonEnter();

	/* find the allocated memory block with the given address*/
	mem = ListFirst(FF.allocateMem);
	while (mem != NULL && mem ->start != start) {
		mem = ListNext(FF.allocateMem);}

	/*  remove the allocated memory block*/
	if (mem == NULL) {
		printf("FfFree:no allocated memory block with the address %p found\n",
            start);
		exit(1);
	}

	ListRemove(FF.allocateMem);

	/*find the memory blocks before and after the allocated block */
	freeMemAfter = ListFirst(FF.freeMem);
	FF.stat.numSearchedNodesDeallocation++;
	while ((freeMemAfter != NULL) && ((freeMemAfter->start)<start)){
		freeMemAfter = ListNext(FF.freeMem);
		FF.stat.numSearchedNodesDeallocation++;
	}

	if (freeMemAfter == NULL)
		freeMemBefore = ListLast(FF.freeMem);
	else
		freeMemBefore = ListPrev(FF.freeMem);

	/* If free block before is adjacent to block, combine them */
	if (freeMemBefore == NULL) {
		ListPrepend(FF.freeMem, mem);
	} else if (freeMemBefore->start + freeMemBefore->size == start) {
		freeMemBefore->size += mem->size;
		free(mem);
		mem = freeMemBefore;
	} else {  /* Otherwise, add block to the list b/w before and after */
		ListAdd(FF.freeMem, mem);
	}

	/* If free block after is adjacent to block, combine them */
	if (freeMemAfter != NULL &&
			mem->start + mem->size == freeMemAfter->start) {
		mem->size += freeMemAfter->size;
		ListNext(FF.freeMem);
		free(ListRemove(FF.freeMem));
	}

	RttMonSignal(FFMemAvail);
	RttMonLeave();
}
void BfFree(void *ptr) {
    MemorySpace *mem, *freeMemBefore, *freeMemAfter;
    char *start;
    start = ptr;

    RttMonEnter();

    /* find the allocated memory block with the given address*/
    mem = ListFirst(BF.allocateMem);
    while (mem != NULL && mem ->start != start) {
        mem = ListNext(BF.allocateMem);}

    /*  remove the allocated memory block*/
    if (mem == NULL) {
        printf("BfFree:no allocated memory block with the address %p found\n",
            start);
        exit(1);
    }

    ListRemove(BF.allocateMem);

    /*find the memory blocks before and after the allocated block */
    freeMemAfter = ListFirst(BF.freeMem);
    BF.stat.numSearchedNodesDeallocation++;
    while ((freeMemAfter != NULL) && ((freeMemAfter->start)<start)){
        freeMemAfter = ListNext(BF.freeMem);
        BF.stat.numSearchedNodesDeallocation++;
    }

    if (freeMemAfter == NULL)
        freeMemBefore = ListLast(BF.freeMem);
    else
        freeMemBefore = ListPrev(BF.freeMem);

    /* If free block before is adjacent to block, combine them */
    if (freeMemBefore == NULL) {
        ListPrepend(BF.freeMem, mem);
    } else if (freeMemBefore->start + freeMemBefore->size == start) {
        freeMemBefore->size += mem->size;
        free(mem);
        mem = freeMemBefore;
    } else {  /* Otherwise, add block to the list b/w before and after */
        ListAdd(BF.freeMem, mem);
    }
    /* If free block after is adjacent to block, combine them */
    if (freeMemAfter != NULL &&
            mem->start + mem->size == freeMemAfter->start) {
        mem->size += freeMemAfter->size;
        ListNext(BF.freeMem);
        free(ListRemove(BF.freeMem));
    }

    RttMonSignal(BFMemAvail);
    RttMonLeave();

}

void InitStats(Stats *stats) {
	stats->numAllocations = 0;
	stats->numDeallocations = 0;
	stats->numSearchedNodesAllocation = 0;
	stats->numSearchedNodesDeallocation = 0;
	stats->numAllocatedSegments = 0;
	stats->numUnallocatedSegments = 0;
}

/* Monitor Procedures */
void Initialize(int numThreads) {
	MemorySpace *freeMem;

	/*FF */
	FF.freeMem = ListCreate();
	FF.allocateMem = ListCreate();
    if (FF.freeMem == NULL || FF.allocateMem == NULL) {
        printf("Error: Failed to create lists for FF\n");
        exit(EXIT_FAILURE);
    }

	threadsLeft[0] = numThreads;
	InitStats(&FF.stat);

	freeMem = malloc(sizeof(MemorySpace));
    /*freeMem = (MemorySpace *)malloc(sizeof(MemorySpace));*/
    if (freeMem == NULL) {
        printf("Error: Failed to allocate memory for FF\n");
        exit(EXIT_FAILURE);
    }
    freeMem->start = (char*) MEM_BASE;

	freeMem->size = MEM_AVAILABLE;
    if (ListPrepend(FF.freeMem, freeMem)== -1) {
        printf( "Error: Failed to prepend to FF freeMem\n");
        exit(EXIT_FAILURE);
    }
	/* BF  */
	BF.freeMem = ListCreate();
	BF.allocateMem = ListCreate();
    if (BF.freeMem == NULL || BF.allocateMem == NULL) {
        printf("Error: Failed to create lists for BF\n");
        exit(EXIT_FAILURE);
    }

	threadsLeft[1] = numThreads;
	InitStats(&BF.stat);

	freeMem = malloc(sizeof(MemorySpace));
    /*freeMem = (MemorySpace *)malloc(sizeof(MemorySpace));*/
	freeMem->start = (char*) MEM_BASE;
	freeMem->size = MEM_AVAILABLE;
	if (ListPrepend(BF.freeMem, freeMem) == -1) {
        fprintf(stderr, "Error: Failed to prepend to BF freeMem\n");
        exit(EXIT_FAILURE);
    }

	RttMonInit(numConds);
        /* Debug prints to verify initialization*/
    printf("FF initialized: Free memory start=%p, size=%lu\n",
    freeMem->start, freeMem->size);
    printf("BF initialized: Free memory start=%p, size=%lu\n",
    freeMem->start, freeMem->size);
}

void Threadend(int alg, void* statistics) {
	RttMonEnter();
	threadsLeft[alg]--;
	if (threadsLeft[alg] == 0)
		MyMemStats(alg, statistics);
	RttMonLeave();
}

size_t* getSizes(LIST* list) {
    size_t* sizes;
    MemorySpace* m;
    int i = 0;
    sizes = malloc(sizeof(size_t) * ListCount(list));
    if(sizes == NULL) {
        errx(1,"getSizes(): malloc() returned NULL.\n");
    }

    m = ListFirst(list);
	i = 0;
    while(m != NULL) {
		sizes[i] = m->size;
		m = ListNext(list);
		i++;
    }
	return sizes;
}

void MyMemStats(int algNo, void* statistics) {
	Stats *stats;
    stats = (Stats*) statistics;

	if (algNo < 0 || algNo > 1)
		errx(1, "algNo must be between 0 and 1");
    if (algNo == 0) {
        stats->numAllocations = FF.stat.numAllocations;
        stats->numDeallocations = FF.stat.numDeallocations;
        stats->numSearchedNodesAllocation = FF.stat.numSearchedNodesAllocation;
        stats->numSearchedNodesDeallocation=FF.stat.numSearchedNodesDeallocation;
        stats->numAllocatedSegments = ListCount(FF.allocateMem);
        stats->numUnallocatedSegments = ListCount(FF.freeMem);
        stats->allocatedSegmentsSizes = getSizes(FF.allocateMem);
        stats->unallocatedSegmentsSizes = getSizes(FF.freeMem);
	}
	else if (algNo == 1) {
        stats->numAllocations = BF.stat.numAllocations;
        stats->numDeallocations = BF.stat.numDeallocations;
        stats->numSearchedNodesAllocation = BF.stat.numSearchedNodesAllocation;
        stats->numSearchedNodesDeallocation=BF.stat.numSearchedNodesDeallocation;
        stats->numAllocatedSegments = ListCount(BF.allocateMem);
        stats->numUnallocatedSegments = ListCount(BF.freeMem);
        stats->allocatedSegmentsSizes = getSizes(BF.allocateMem);
        stats->unallocatedSegmentsSizes = getSizes(BF.freeMem);
	}


/*
	printf(
            "%d: "
            "numSearchedNodesAllocation = %d, "
            "numFreeMem = %d, "
            "totalAlloMem = %ld, "
            "extFrag = %ld, "
            "intFrag = %ld\n",
            algNo,
            stats->numSearchedNodesAllocation,
			stats->numFreeMem,
            stats->totalAlloMem,
			stats->extFrag,
            stats->intFrag
        );
		*/
}


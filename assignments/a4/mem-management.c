/*
 * # @author Wahhaj Javed, muj975, 11135711
 * @author Nakhba Mubashir, epl482, 11317060
 * */

void *FfMalloc(size_t size) {
    MemorySpace *firstFit;
    MemorySpace *freeBlock;
    MemorySpace *allocaBlock;

    int wait= 0; /*wait flag*/

    if (size == 0) return NULL;
    MonEnter(); /* critical section*/

    /*find first free memory space */
    firstFit = NULL;
    freeBlock = ListFirst(FF.freeMem);
    FF.stats.nodesSearched++;

    while (freeBlock != NULL) {
        /* check if the size is large wnough*/
        if (freeBlock->size >= size) {
            firstFit = freeBlock;
            break;
        }
        /*move to the next block*/
        freeBlock = ListNext(FF.freeMem);
        FF.stats.nodesSearched++;
    }

    /* no fit found, wait until Free() and then try again */
    while (firstFit == NULL) {
        errx(1, "FfMalloc: no freea block\n");
        wait = 1;
        MonWait(FFMemAvail);
        freeBlock = ListFirst(FF.freeMem);
        FF.stats.nodesSearched++;
        while (freeBlock != NULL) {
            if (freeBlock->size >= size) {
                firstFit = freeBlock;
                break;
            }
            freeBlock = ListNext(FF.freeMem);
            FF.stats.nodesSearched++;
        }
        
    }

    /* allocate and initialize the MemorySpace struct for 
        allocated memory */
    allocaBlock = malloc(sizeof(MemorySpace));
    allocaBlock->start = firstFit->start;
    allocaBlock->size = size;
    ListAppend(FF.allocateMem, allocBlock);

    /* If the free block equals size, remove it; otherwise, shrink it */
    if (firstFit->size == size) {
        ListRemove(FF.freeMem);
        free(firstFit);
    } else {
        firstFit->start += size;
        firstFit->size -= size;
    }
    FF.stats.totalAlloMem +=size;
    FF.stats.numFreeMem -listCount(FF.freeMem);
    if (firstFit != ListLast(FF.freeMem))
		FF.stats.extFrag -= size;

    if (wait)
        MonSignal(FFMemAvail);

    MonLeave();

    return allocaBlock->start;
}


void *BfMalloc(size_t size) {
    MemorySpace *BestFit;
    MemorySpace *freeBlock;
    MemorySpace *allocaBlock;

    int wait= 0; /*wait flag*/

    if (size == 0) return NULL;
    MonEnter(); /* critical section*/

    /*find Best free memory space */
    BestFit = NULL;
    freeBlock = ListFirst(BF.freeMem);
    BF.numAlloc++;

    while (freeBlock != NULL) {
        if ((freeBlock->size >= size) && 
            (bestFit == NULL || freeBlock->size < bestFit->size))
            bestFit = freeBlock;
        freeBlock = ListNext(BF.freeMem);
    }
    /* no fit found, wait until Free() and then try again */
    while (bestFit == NULL) {
        errx(1, "BFMalloc: no free block\n");
        wait = 1;
        MonWait(BFMemAvail);

        freeBlock = ListFirst(BF.freeMem);

        while (freeBlock != NULL) {
            if (freeBlock->size >= size) {
                bestFit = freeBlock;
                break;
            }

            freeBlock = ListNext(BF.freeMem);
        }
        /* If no fit was found, signal the next waiting */
        if (bestFit != NULL)
            MonSignal(BFMemAvail);
    }
    /* allocate and initialize the MemorySpace struct for the memory */
    allocaBlock = malloc(sizeof(MemorySpace));
    allocaBlock->start = bestFit->start;
    allocaBlock->size = size;
    ListAppend(BF.allocateMem, allocaBlock);

    /* update memory */
    BF.totalAllocateMem += size;
    BF.totalFreeMem -= size;

    /* if the free block equals size, remove it */
    if (bestFit->size == size) {
        /* refind the block since the pointer is at the end of the list */
        MemorySpace *memBlock = ListFirst(BF.freeMem);
        while (memBlock != bestFit) 
            memBlock = ListNext(BF.freeMem);
        
        ListRemove(BF.freeMem);
        free(bestFit);
    } else {
        bestFit->start += size;
        bestFit->size -= size;
    }

    BF.numAlloc++; // Increment allocation count
    if (bestFit != ListLast(BF.freeMem))
        BF.totalFreeMem -= size;

    if (waitFlag)
        MonSignal(BFMemAvail);

    MonLeave();

    return allocBlock->start;
}

void FfFree(void *ptr) {
	MemorySpace *mem, *freeMemBefore, *freeMemAfter;
	char *start;
	int size;

	start = ptr;

	MonEnter();

	/* find the allocated memory block with the given address*/
	mem = ListFirst(FF.allocateMem);
	while (mem != NULL && mem ->start != start) {
		mem = ListNext(FF.allocateMem);}

	/*  remove the allocated memory block*/
	if (memBlock == NULL) {
		printf("FfFree:no allocated memory block with the address %p found\n",
            start);
		exit(1);
	}

	ListRemove(FF.allocateMem);
	size = mem->size;

	/*find the memory blocks before and after the allocated block */
	freeMemAfter = ListFirst(FF.freeMem);
	FF.stat.nodesSearched++;
	while ((freeMemAfter != NULL) && ((freeMemAfter->start)<start)){
		freeMemAfter = ListNext(FF.freeMemBlocks);
		FF.stats.nodesSearched++;
	}
	
	if (freeMemAfter == NULL)
		freeMemBefore = ListLast(FF.freeMem);
	else
		freeMemBefore = ListPrev(FF.freeMem);
	
	/* If free block before is adjacent to block, combine them */
	if (freeMemBefore == NULL) {
		ListPrepend(FF.freeMemBlocks, memBlock);
	} else if (freeBlockBefore->start + freeBlockBefore->size == start) {
		freeBlockBefore->size += memBlock->size;
		free(memBlock);
		memBlock = freeBlockBefore;
	} else {  /* Otherwise, add block to the list b/w before and after */
		ListAdd(FF.freeMemBlocks, memBlock);
	}

	MonSignal(FFMemAvail);

	MonLeave();
}


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
    FF.numAlloc++;

    while (freeBlock != NULL) {
        /* check if the size is large wnough*/
        if (freeBlock->size >= size) {
            firstFit = freeBlock;
            break;
        }
        /*move to the next block*/
        freeBlock = ListNext(FF.freeMem);
    }

    /* no fit found, wait until Free() and then try again */
    while (firstFit == NULL) {
        errx(1, "FfMalloc: no freea block\n");
        wait = 1;
        MonWait(FFMemAvail);
        freeBlock = ListFirst(FF.freeMem);
        while (freeBlock != NULL) {
            if (freeBlock->size >= size) {
                firstFit = freeBlock;
                break;
            }
            freeBlock = ListNext(FF.freeMem);
        }
        
    }

    /* allocate and initialize the MemorySpace struct for 
        allocated memory */
    allocaBlock = malloc(sizeof(MemorySpace));
    allocaBlock->start = firstFit->start;
    allocaBlock->size = size;
    ListAppend(FF.allocateMem, allocBlock);

    /* update the memory  */
    FF.totalAllocateMem += size;
    FF.totalFreeMem -= size;

    /* If the free block equals size, remove it; otherwise, shrink it */
    if (firstFit->size == size) {
        ListRemove(FF.freeMem);
        free(firstFit);
    } else {
        firstFit->start += size;
        firstFit->size -= size;
    }

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
    

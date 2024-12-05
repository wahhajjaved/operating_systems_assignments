/*
 * # @author Wahhaj Javed, muj975, 11135711
 * @author Nakhba Mubashir, epl482, 11317060
 * */

#include <mem-management.h>

#define numConds 2
#define FFMemAvail 0
#define BFMemAvail 1

int threadsLeft[NUM_ALGS];

LIST *ffFreeMem;
LIST *ffAllocateMem;
Stats ffStat;

void printMemory(LIST* memory) {
	MemorySpace* m;
	m = ListFirst(memory);
	if (m == NULL) {
		printf("\tList Empty\n");
		return;
	}
	do{
		printf(
			"\tstart = %lx, "
			"size = %-lx \n"
			,m->start
			,m->size
		);
	} while((m = ListNext(memory)) != NULL);
}

void printMemories(int algNo) {
	printf("------------------------------------\n");
	if (algNo == 0) {
		printf("ffFreeMem\n");
		printMemory(ffFreeMem);
		printf("ffAllocateMem\n");
		printMemory(ffAllocateMem);
	}
	printf("------------------------------------\n");
}


/* Checks if the addresses of two MemorySpace structs is equal */
int memorySpaceAddressComparator(void* memSpace, void* start) {
	MemorySpace *a;
	long int *b;
	a = (MemorySpace*)memSpace;
	b = (long int*)start;
	return a->start == *b;
}

/*
* Moves the current block from the free list to the usedList. The freeList
* cursor must be at the block to be moved. If size is equal to the current
* block is equal to the parameter size, then the item is moved as is to the
* usedList. Otherwise, a new MemorySpace is malloc()ed, and added to the
* usedList and the size of the current block in the freeList is reduced.
*/
MemorySpace* moveBlockFreeToAllocated(LIST* freeList, LIST* usedList, size_t size) {
	MemorySpace *curBlock, *allocaBlock;

	/* Everything inside the lists is dynamically allocated so this won't
	* go out of scope when returned */
	curBlock = ListCurr(freeList);

	if (curBlock->size == size) {
		ListRemove(freeList);
		if(ListPrepend(usedList, curBlock) == -1)
			exit(1);
		return curBlock;
	}
	else {
		allocaBlock = malloc(sizeof(MemorySpace));
		if(allocaBlock == NULL) {
			perror("moveBlockFreeToAllocated(): malloc failed \n");
		}
		allocaBlock->start = curBlock->start;
		allocaBlock->size = size;
		curBlock->start += size;
		curBlock->size -= size;
		if(ListPrepend(usedList, allocaBlock) == -1)
			exit(1);
		return allocaBlock;
	}
}


/* Adds a MemorySpace in the free list, merging adjacents segments if needed.
* mem should have already been removed from the used list.
*/
void mergeMemory(LIST* freeList, MemorySpace* mem, Stats* stat) {
	MemorySpace *freeMemBefore, *freeMemAfter;
	long int start;
	int size;
	start = mem->start;
	size = mem->size;

	freeMemAfter = ListFirst(freeList);
	stat->nodesSearched++;
	while ((freeMemAfter != NULL) && ((freeMemAfter->start)<start)){
		freeMemAfter = ListNext(freeList);
		stat->nodesSearched++;
	}
	if (freeMemAfter == NULL)
		freeMemBefore = ListLast(freeList);
	else
		freeMemBefore = ListPrev(freeList);
	/*cursor is on freeMemBefore after this point*/

	/*
	If both freeMemAfter and freeMemBefore are NULL that means the list is
	empty and mem can simply be added in
	*/
	if (freeMemAfter == NULL && freeMemBefore == NULL) {
		if(ListPrepend(freeList, mem) == -1)
			exit(1);
	}

	/*
	If freeMemAfter is NULL but freeMemBefore is not NULL, that means mem has
	the highest address in the list so it must be placed at the end of the
	list. It may need to be merged with freeMemBefore
	*/
	else if (freeMemAfter == NULL && freeMemBefore != NULL) {
		/*merge with freeMemBefore*/
		if (freeMemBefore->start + freeMemBefore->size == mem->start) {
			freeMemBefore->size += mem->size;
			free(mem);
			mem = freeMemBefore;
		}
		else {
			if(ListAppend(freeList, mem) == -1)
				exit(1);
		}
	}

	/*
	- If freeMemAfter is not NULL but freeMemBefore is NULL, that means that
	mem will need to be inserted at the beginning of the list and may
	potentially need to be merged with freeMemAfter
	*/
	else if (freeMemAfter != NULL && freeMemBefore == NULL) {
		/*merge with freeMemAfter*/
		if (mem->start + mem->size == freeMemAfter->start) {
			freeMemAfter->start = mem->start;
			freeMemAfter->size += mem->size;
			free(mem);
			mem = freeMemAfter;
		}
		else {
			if(ListPrepend(freeList, mem) == -1)
				exit(1);
		}
	}

	/*
	If both freeMemAfter and freeMemBefore are not NULL, then mem is inserted
	between them and may possibly need to be merged with one or both
	*/
	else {
		/* merge mem with freeMemBefore and freeMemAfter*/
		if (
			freeMemBefore->start + freeMemBefore->size == mem->start &&
			mem->start + mem->size == freeMemAfter->start
			) {

			freeMemBefore->size += mem->size + freeMemAfter->size;
			ListNext(freeList); /*move cursor onto freeMemAfter*/
			if(ListRemove(freeList) != freeMemAfter) {
				printf(
					"mergeMemory(): freeMemAfter was not removed from "
					"freeList when merging mem with freeMemBefore and "
					"freeMemAfter \n"
				);
				exit(1);
			}
			free(mem);
			free(freeMemAfter);
			mem = freeMemBefore;
		}

		/* merg mem with freeMemBefore only*/
		else if (freeMemBefore->start + freeMemBefore->size == mem->start) {
			freeMemBefore->size += mem->size;
			free(mem);
			mem = freeMemBefore;
		}

		/*merge with freeMemAfter only*/
		else if (mem->start + mem->size == freeMemAfter->start) {
			freeMemAfter->start = mem->start;
			freeMemAfter->size += mem->size;
			free(mem);
			mem = freeMemAfter;
		}

		/*insert mem in between freeMemBefore and freeMemAfter*/
		else {
			if(ListAdd(freeList, mem) == -1)
				exit(1);
		}
	}

	stat->totalAlloMem -= size;
	stat->numFreeMem = ListCount(freeList);
	stat->extFrag += size;
}

MemorySpace* findFfFreeBlock(size_t size) {
	MemorySpace *freeBlock, *firstFit;
	firstFit = NULL;

	freeBlock = ListFirst(ffFreeMem);
	ffStat.nodesSearched++;
	while (freeBlock != NULL) {
		if (freeBlock->size >= size) {
			firstFit = freeBlock;
			break;
		}
		freeBlock = ListNext(ffFreeMem);
		ffStat.nodesSearched++;
	}
	return firstFit;
}


void *FfMalloc(size_t size) {
	MemorySpace *allocaBlock;
	MemorySpace *firstFit=NULL;

	if (size == 0) return NULL;

	RttMonEnter(); /* critical section*/
	printf("FfMalloc(): Start. Allocating %lx\n", size);
	printMemories(0);

	/*printf("size:%d\n", FF.freeMem->size);*/
	firstFit = findFfFreeBlock(size);

	/* no fit found, wait until Free() and then try again */
	while (firstFit == NULL) {
		errx(1, "FfMalloc: no freea block\n");
		RttMonWait(FFMemAvail);
		firstFit = findFfFreeBlock(size);

		/* If still no fit was found, signal the next waiting thread */
		if (firstFit == NULL)
			RttMonSignal(FFMemAvail);
	}

	/*allocate memory*/
	allocaBlock = moveBlockFreeToAllocated(ffFreeMem, ffAllocateMem, size);

	ffStat.totalAlloMem +=size;
	ffStat.numFreeMem = ListCount(ffFreeMem);
	if (firstFit != ListLast(ffFreeMem))
		ffStat.extFrag -= size;

	printf("FfMalloc(): End. Done Allocating %lx\n", size);
	printMemories(0);
	printf("\n");

	RttMonLeave();

	return &(allocaBlock->start);
}




void FfFree(void *ptr) {
	MemorySpace *mem;
	long int start;
	start = *((long int*)ptr);

	RttMonEnter();

	printf("FfFree(): Start. Freeing %lx\n", start);
	printMemories(0);

	/* find the allocated memory block with the given address*/
	ListFirst(ffAllocateMem);
	mem = ListSearch(ffAllocateMem, memorySpaceAddressComparator, &start);
	if (mem == NULL) {
		printf("FfFree:no allocated memory block with the address %lx found\n",
			start);
		exit(1);
	}

	ListRemove(ffAllocateMem);
	mergeMemory(ffFreeMem, mem, &ffStat);

	printf("FfFree(): End. Done freeing %lx\n", start);
	printMemories(0);
	printf("\n");

	RttMonSignal(FFMemAvail);
	RttMonLeave();
}

void *BfMalloc(size_t size) {
	printf("BfMalloc not implemented/\n");
	return NULL;
}

void BfFree(void *ptr) {
	printf("BfFree not implemented/\n");
}

void InitStats(Stats *stats) {
	stats->nodesSearched = 0;
	stats->numFreeMem = 1;
	stats->totalAlloMem = 0;
	stats->extFrag = 0;
	stats->intFrag = 0;
}

/* Monitor Procedures */
void Initialize(int numThreads) {
	MemorySpace *freeMem;

	/*FF */
	ffFreeMem = ListCreate();
	ffAllocateMem = ListCreate();
    if (ffFreeMem == NULL || ffAllocateMem == NULL) {
        printf("Error: Failed to create lists for FF\n");
        exit(EXIT_FAILURE);
    }

	threadsLeft[0] = numThreads;
	InitStats(&ffStat);

	freeMem = malloc(sizeof(MemorySpace));
    /*freeMem = (MemorySpace *)malloc(sizeof(MemorySpace));*/
    if (freeMem == NULL) {
        printf("Error: Failed to allocate memory for FF\n");
        exit(EXIT_FAILURE);
    }
    freeMem->start = MEM_BASE;

	freeMem->size = MEM_AVAILABLE;
    if (ListPrepend(ffFreeMem, freeMem) == -1) {
        printf( "Error: Failed to prepend to FF freeMem\n");
        exit(EXIT_FAILURE);
    }

	RttMonInit(numConds);
        /* Debug prints to verify initialization*/
    printf("FF initialized: ");
	printMemory(ffFreeMem);
}

void Threadend(int alg) {
	RttMonEnter();
	threadsLeft[alg]--;
	if (threadsLeft[alg] == 0)
		MyMemStats(alg);
	RttMonLeave();
}

void MyMemStats(int algNo) {
	Stats *stats;

	if (algNo < 0 || algNo > 1)
		errx(1, "algNo must be between 0 and 1");

	if (algNo == 0)
		stats = &ffStat;
	/*else if (algNo == 1)
		stats = &BF.stat;*/

	printf("%d: %d, %d, %ld, %ld, %ld\n", algNo, stats->nodesSearched,
			stats->numFreeMem, stats->totalAlloMem,
			stats->extFrag, stats->intFrag);
}


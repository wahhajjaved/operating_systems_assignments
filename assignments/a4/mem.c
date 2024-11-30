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

/* Checks if the addresses of two MemorySpace structs is equal */
int memorySpaceAddressComparator(void* memSpace, void* start) {
	MemorySpace *a;
	char *b;
	a = (MemorySpace*)memSpace;
	b = (char*)start;
	return a->start == b;
}

/*
* Moves the current block from the free list to the usedList. The freeList 
* cursor must be at the block to be moved. If size is equal to the current 
* block is equal to the parameter size, then the item is moved as is to the 
* usedList. Otherwise, a new MemorySpace is malloc()ed, and added to the 
* usedList and the size of the current block in the freeList is reduced.
*/
MemorySpace* moveBlockFreeToAllocated(LIST* freeList, LIST* usedList, size_t size) {
	MemorySpace* curBlock, allocaBlock;
	
	/* Everything inside the lists is dynamically allocated so this won't 
	* go out of scope when returned */
	curBlock = ListCurr(freeList);
	
	if (curBlock->size == size) {
		ListRemove(freeList);
		ListPrepend(usedList, curBlock);
		return curBlock; 
	}
	else {
		allocaBlock = malloc(sizeof(MemorySpace));
		if(allocaBlock == NULL) {
			perror(1, "moveBlockFreeToAllocated(): malloc failed \n");
		}
		allocaBlock->start = curBlock->start;
		allocaBlock->size = size;
		curBlock->start += size;
		curBlock->size -= size;
		ListPrepend(usedList, allocaBlock);
		return allocaBlock;
	}
}

/* Adds a MemorySpace the free list, merging adjacents segments if needed. 
* mem should have already been removed from the used list. stat.nodesSearched
* is updated while iterating over the free list.
*/
void mergeMemory(LIST* freeList, MemorySpace* mem, Stats* stat) {
	MemorySpace *freeMemBefore, *freeMemAfter;
	char *start;
	start = mem->start;
	
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
	
	
	/* 
	- If both freeMemAfter and freeMemBefore are NULL that means the list is
	empty and mem can simply be added in
	
	- if freeMemAfter is NULL but freeMemBefore is not NULL, that means mem has
	the highest address in the list so it must be placed at the end of the 
	list. It may need to be merged with freeMemBefore
	
	- If freeMemAfter is not NULL but freeMemBefore is NULL, that means that mem
	will need to be inserted at the beginning of the list and may potentially
	need to be merged with freeMemAfter
	
	- If both freeMemAfter and freeMemBefore are not NULL, then mem is inserted
	between them and may possibly need to be merged with one or both
	*/
	
	if (freeMemBefore == NULL) {
		ListPrepend(freeList, mem);
	} else if (freeMemBefore->start + freeMemBefore->size == start) {
		freeMemBefore->size += mem->size;
		free(mem);
		mem = freeMemBefore;
	} else {
		ListAdd(freeList, mem);
	}

	if (freeMemAfter != NULL &&
			mem->start + mem->size == freeMemAfter->start) {
		mem->size += freeMemAfter->size;
		ListNext(freeList);
		free(ListRemove(freeList));
	}
	stat->totalAlloMem -= size;
	stat->numFreeMem = ListCount(freeList);
	stat->extFrag += size;
}

MemorySpace* findFfFreeBlock(size_t size) {
	MemorySpace *freeBlock, firstFit;
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
	MemorySpace *freeBlock, *allocaBlock;
	MemorySpace *firstFit=NULL;

	int wait= 0; /*wait flag*/
	if (size == 0) return NULL;
	
	RttMonEnter(); /* critical section*/
	
	/*printf("size:%d\n", FF.freeMem->size);*/
	firstFit = findFfFreeBlock(size)
	
	/* no fit found, wait until Free() and then try again */
	while (firstFit == NULL) {
		errx(1, "FfMalloc: no freea block\n");
		wait = 1;
		RttMonWait(FFMemAvail);
		firstFit = findFfFreeBlock(size)

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
	
	RttMonLeave();

	return allocaBlock->start;
}




void FfFree(void *ptr) {
	MemorySpace *mem, *freeMemBefore, *freeMemAfter;
	char *start;
	int size;
    int coalescedToEnd = 0;
	start = ptr;

	RttMonEnter();

	/* find the allocated memory block with the given address*/
	ListFirst(ffAllocateMem);
	mem = ListSearch(ffAllocateMem, memorySpaceAddressComparator, start);
	if (mem == NULL) {
		printf("FfFree:no allocated memory block with the address %p found\n",
			start);
		exit(1);
	}
	
	ListRemove(ffAllocateMem);
	mergeMemory(ffFreeMem, mem, ffStat);

	RttMonSignal(FFMemAvail);
	RttMonLeave();
}

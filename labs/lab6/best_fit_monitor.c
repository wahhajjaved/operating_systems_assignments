/*
@author Wahhaj Javed, muj975, 11135711
@date 2024-10-31
*/

#include <list.h>
#include <Monitor.h>
#include <best_fit_monitor.h>

#define TOTALMEMORY 50

LIST* memory;


int compareMemory(void* a, void* b) {
	return a == b;
}

int findAddress(void* a, void* b) {
	return &(((MemoryBlock*)a)->startAddress) == (int*) b;
}

void printMemory() {
	MemoryBlock* m;
	
	m = ListFirst(memory);
	do{
		printf(
			"startAddress = %-5d "
			"endAddress = %-5d "
			"size = %-5d "
			"inUse = %-5d \n"
			,m->startAddress
			,m->endAddress
			,m->size
			,m->inUse
		);
	} while((m = ListNext(memory)) != NULL);
}

void init() {
	MemoryBlock* m;
	m = malloc(sizeof(MemoryBlock));
	m->startAddress = 0;
	m->endAddress = TOTALMEMORY-1;
	m->size = TOTALMEMORY;
	m->inUse = 0;
	
	memory = ListCreate();
	ListAppend(memory, m);
	
	MonInit(1);
	printf("best fit monitor initialized. List size %d\n", ListCount(memory));
}

MemoryBlock* bestFit(int size) {
	MemoryBlock *m, *bestChunk, *best;
	int bestSize;
	bestSize = TOTALMEMORY+1;
	
	/*find the best chunk of free memory*/
	if((m = ListFirst(memory)) == NULL) {
		fprintf(stderr, "Error: No memory in memory list.\n");
		exit(1);
	}
	do {
		int diff;
		if(m->inUse) continue;

		diff = m->size - size;
		if(diff >= 0 && diff < bestSize){
			bestSize = diff;
			bestChunk = m;
		}
	} while((m = ListNext(memory)) != NULL);
	if(bestSize == TOTALMEMORY+1){
		printf("Allocating Memory: No memory available.\n");
		return NULL;
	}
	
	/*split up the best chunk into the exact size needed*/
	best = malloc(sizeof(MemoryBlock));
	ListFirst(memory);
	ListSearch(memory, compareMemory, bestChunk);
	ListInsert(memory, best);
	best->startAddress = bestChunk->startAddress;
	best->endAddress = bestChunk->startAddress + size - 1;
	best->size = size;
	best->inUse = 1;
	
	bestChunk->startAddress = best->endAddress + 1;
	bestChunk->size = bestChunk->endAddress - bestChunk->startAddress + 1;

	return best;
	
}

int* BFAllocate(int size){
	MemoryBlock* m;
	
	MonEnter();
	
	printf("\n");
	printf("\n------------------------------------------------------------\n");
	printf("Allocating %d Memory: Current Memory Layout\n", size);
	printMemory();
	
	while((m = bestFit(size)) == NULL){
		MonWait(0);
	}
	
	printf("------\n");
	printf("Allocated %d Memory: New Memory Layout\n", size);
	printMemory();
	printf("------------------------------------------------------------\n");
	
	MonLeave();
	return &m->startAddress;
}

void BFFree(int* address){
	MemoryBlock *m, *prevChunk, *nextChunk;
	
	MonEnter();
	
	printf("\n");
	printf("\n------------------------------------------------------------\n");
	printf("Freeing Memory at %d: Current Memory Layout\n", *address);
	printMemory();
	
	/*find the block to free*/
	if((m = ListFirst(memory)) == NULL) {
		fprintf(stderr, "Error: No memory in memory list.\n");
		exit(1);
	}
	m = ListSearch(memory, findAddress, address);
	if(m == NULL){
		fprintf(stderr, "Error: Address %d not found.\n", *address);
		exit(1);
	}
	
	m->inUse = 0;
	
	/*combine prev chunk with current chunk*/
	prevChunk = ListPrev(memory);
	if(prevChunk != NULL && prevChunk->inUse == 0){
		m->startAddress = prevChunk->startAddress;
		m->size = m->endAddress - m->startAddress + 1;
		ListRemove(memory);
		free(prevChunk);
	}
	else if(prevChunk != NULL) {
		m = ListNext(memory);
	}
	
	/*combine next chunk with current chunk*/
	nextChunk = ListNext(memory);
	if(nextChunk != NULL && nextChunk->inUse == 0){
		m->endAddress = nextChunk->endAddress;
		m->size = m->endAddress - m->startAddress + 1;
		ListRemove(memory);
		free(nextChunk);
	}
	
	printf("------\n");
	printf("Freed Memory at %d: New Memory Layout\n", *address);
	printMemory();
	printf("------------------------------------------------------------\n");

	MonLeave();
	MonSignal(0);
}
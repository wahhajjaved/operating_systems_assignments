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
	MemoryBlock *m, *bestChunk, *best, *nextChunk;
	int bestSize;
	bestSize = TOTALMEMORY+1;
	
	/*find the best chunk of free memory*/
	if((m = ListFirst(memory)) == NULL) {
		fprintf(stderr, "Error: No memory in memory list.\n");
		return NULL;
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
	best->startAddress = bestChunk->startAddress;
	best->endAddress = bestChunk->startAddress + size - 1;
	best->size = size;
	best->inUse = 1;
	
	nextChunk = malloc(sizeof(MemoryBlock));
	nextChunk->startAddress = best->endAddress + 1;
	nextChunk->endAddress = bestChunk->endAddress;
	nextChunk->size = nextChunk->endAddress - nextChunk->startAddress + 1;
	nextChunk->inUse = 0;
	
	ListFirst(memory);
	ListSearch(memory, compareMemory, bestChunk);
	ListRemove(memory);
	ListAdd(memory, best);
	ListAdd(memory, nextChunk);
	
	
	return best;
	
}

int* BFAllocate(int size){
	MemoryBlock* m;
	
	printf("\n");
	printf("\n------------------------------------------------------------\n");
	printf("Allocating %d Memory: Current Memory Layout\n", size);
	printMemory();
	
	m = bestFit(size);
	
	printf("------\n");
	printf("Allocated %d Memory: New Memory Layout\n", size);
	printMemory();
	printf("------------------------------------------------------------\n");
	
	return &m->startAddress;
}

void BFFree(int* address){
	
}
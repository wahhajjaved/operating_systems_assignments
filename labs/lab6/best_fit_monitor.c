/*
@author Wahhaj Javed, muj975, 11135711
@date 2024-10-31
*/

#include <list.h>
#include <Monitor.h>
#include <best_fit_monitor.h>

#define TOTALMEMORY 1000

LIST* memory;

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

int* BFAllocate(int size){
	MemoryBlock* m = ListFirst(memory);
	return &m->startAddress;
}

void BFFree(int* address){
	
}
/*
@author Wahhaj Javed, muj975, 11135711
@date 2024-10-31
*/

typedef struct memoryBlock {
	int startAddress;
	int endAddress;
	int size;
	int inUse;
} MemoryBlock;

void init();
int* BFAllocate(int size);
void BFFree(int* address);
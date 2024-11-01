/* Nakhba Mubashir, epl482, 11317060 */

#include <BestFitMonitor.h>

MemoryBlock Memory;

static int allocationCheck=0;
static int freeCheck=0;

void BF_init(void){
    Memory.size= MEM_SIZE ;
    Memory.startAddressIndex= 1;
    Memory.endAddressIndex= MEM_SIZE -1;
    Memory.startAddressBlock= (int *) malloc (MAX_MEM_ALLOCATION* sizeof(int));
    Memory.endAddressBlock= (int *) malloc (MAX_MEM_ALLOCATION* sizeof(int));
    Memory.blockNum=0;
    MonInit(num);

}

void BF_allocation(int size){
    int i,spaceNeeded, freeIndex;
    freeIndex=-1; /* -1 is invalid index*/
    MonEnter();
    if (allocationCheck || freeCheck ){
        MonWait(1); /* 1 so allocate*/
    }
    allocationCheck=1;
    
    /* find the space that can fit the requested size*/
    for (i=0; i<Memory.blockNum-1 ;i++){
        spaceNeeded=Memory.startAddressBlock[i+1]-Memory.endAddressBlock[i+1];
        /*check if space in middle*/
        if (spaceNeeded >= size && spaceNeeded < (Memory.size-1)){
            freeIndex= i;
        }
    }
    if (freeIndex ==-1){ /*if no free block then wait*/
        MonWait(2);
    } else{
        Memory.startAddressBlock[freeIndex+1]=
            Memory.endAddressBlock[freeIndex]+1;
        for (i=Memory.blockNum; i>freeIndex+1; i--){
            Memory.startAddressBlock[i]=Memory.startAddressBlock[i+1];
            Memory.endAddressBlock[i]=Memory.endAddressBlock[i+1];
        }
    }

    Memory.blockNum++;
    printf("Allocation of size: %d\n", size );
    allocationCheck=0;
    MonSignal(0);
    MonLeave();
}

void BF_free(int address){
    int i,j;
    MonEnter();
    if (allocationCheck){
        MonWait(0); /* 0 so deallocate*/
    }
    freeCheck++;
    /* find and free memory */
    for (i=0; i< Memory.blockNum; i++){
        if (Memory.startAddressBlock[i] == address){
            for (j=i; j<Memory.blockNum-1 ;j++){
                Memory.startAddressBlock[j]= Memory.startAddressBlock[j+1];
                Memory.endAddressBlock[j]= Memory.endAddressBlock[j+1];
            }
            Memory.blockNum--;
            break;
        }
    }
    freeCheck++;
    if (freeCheck ==0){
        MonSignal(0);
    }
    MonLeave();
}

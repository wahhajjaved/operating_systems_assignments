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
    MonEnter();
    
    if (Memory.blockNum ==0){
        
    }
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

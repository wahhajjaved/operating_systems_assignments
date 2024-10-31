/* Nakhba Mubashir, epl482, 11317060 */

#include <BestFitMonitor.h>

MemoryBlock Memory;

static int allocationCheck=0;
static int freeCheck=0

BF-init(void){
    Memory.size= MEM_SIZE ;
    Memory.startAddressIndex= 1;
    Memory.endAddressIndex= MEM_SIZE -1;
    startAddressBlock= (int *) malloc (MAX_MEM_ALLOCATION* sizeof(int));
    endAddressBlock= (int *) malloc (MAX_MEM_ALLOCATION* sizeof(int));
    Memory.blockNum=0;
    MonInit(num);

}

void BF-allocation(int size){
    MonEnter();
    
    if (Memory.blockNum ==0){
        Memory.b
    }
}

void BF-free(int address){
    int i;
    MonEnter();
    if (allocationCheck){
        MonWait(0); /* 0 so deallocate*/
    }
    freeCheck++;
    if (i=0; i< Memory.blockNum; i++){
    
    }


}

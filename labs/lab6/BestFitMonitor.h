/* @author Nakhba Mubashir, epl482, 11317060 */

#include <Monitor.h>
typedef struct memBlock{
    int size;
    int startAddressIndex;
    int endAddressIndex;
    int *startAddressBlock;
    int *endAddressBlock;
    int blockNum;
}MemoryBlock;

#define MEM_SIZE 5000000 
#define num 2
#define MAX_MEM_ALLOCATION 20
#define MAX_THREAD_ITEM 5


void BF_init(void);
void BF_allocation(int size);
void BF_free(int address);

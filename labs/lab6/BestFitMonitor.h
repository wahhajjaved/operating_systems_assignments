/* @author Nakhba Mubashir, epl482, 11317060 */

typedef struct memBlock{
    int size;
    int startAddressIndex;
    int endAddressIndex;
    int *startAddressBlock;
    int *endAddressBlock;
    int blockNum;
}MemoryBlock;

#define MEM_SIZE 4000000 /**/
#define num 2
#define MAX_MEM_ALLOCATION 20
#define MAX_THREAD_ITEM 5


void BF-init(void);
void BF-allocation(int size);
void BF-free(int address);

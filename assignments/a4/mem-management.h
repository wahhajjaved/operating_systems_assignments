/*
 * author Wahhaj Javed, muj975, 11135711
 * author Nakhba Mubashir, epl482, 11317060
 * */

typedef struct {
	char *start;
	size_t size;
} MemorySpace;

struct _FF{
    LIST *freeMem;         
    LIST *allocateMem;     
    int totalFreeMem;      
    int totalAllocateMem;  
    int numAlloc;          
}FF;

struct _BF{
    LIST *freeMem;         
    LIST *allocateMem;     
    int totalFreeMem;      
    int totalAllocateMem;  
    int numAlloc;          
}BF;


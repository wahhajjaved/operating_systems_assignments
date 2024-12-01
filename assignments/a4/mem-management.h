/*
 * author Wahhaj Javed, muj975, 11135711
 * author Nakhba Mubashir, epl482, 11317060
 * */

/* store all stats for a single algorithm */
typedef struct {
	unsigned nodesSearched; /*how many block have been searched*/
	unsigned numFreeMem; 
	unsigned long totalAlloMem; /*total memory allocated*/
	unsigned long extFrag;  /* memory holes, not counting last*/
	unsigned long intFrag; /* allocated memory is larger then 
                                    allocated space */
} Stats;

typedef struct {
	char *start;
	size_t size;
} MemorySpace;

struct _FF{
    LIST *freeMem;         
    LIST *allocateMem;     
    Stats stat;          
}FF;

struct _BF{
    LIST *freeMem;         
    LIST *allocateMem;     
    Stats stat;      
}BF;


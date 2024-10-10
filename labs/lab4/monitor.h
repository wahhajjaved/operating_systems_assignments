

/*
 * *@author Nakhba Mubashir, epl482, 11317060
 */
#ifndef MONITOR
#define MONITOR


#include <stdio.h>
#include <list.h>
#include <rtthreads.h> 
#include <err.h>
#include <string.h>

/* the size of data*/
typedef struct msg{
    char data[];
    unt condVar; /* conditional variable*/
} MSG;

void RttMonInit(int numConds);
void RttMonEnter();
void RttMonLeave(); 

void RttMonWait(int CV);
void RttMonSignal(int CV);
void MonServer() ;


#endif

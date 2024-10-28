/*
 *@author Wahhaj Javed, muj975, 11135711
 *@author Nakhba Mubashir, epl482, 11317060
 */

#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"
#include "user/uthread.h"

#define buffSizeVal 5
#define buffMaxVal 6

static int mtx, buffMax, buffSize, empty, full;

void prod(void){
    printf("Producer created\n");
    thread_yield();
    /*run till all are produced*/
    for (;;){
        if (buffSize <= buffMax){
                P(empty);
                P(mtx); /* locks the critical section*/
                buffSize++;
                printf("Producer: added to the buffer: %d / %d \n",buffSize,
            buffMax );
        }
        V(mtx);
        V(full);
        thread_yield();
    }
}

void con(void){
    printf("Consumer created\n");
    thread_yield();
    /*run till all are produced*/
    for (;;){
        if (buffSize <= buffMax){
                P(full);
                P(mtx); /* locks the critical section*/
                buffSize--;
                printf("Consumer:removed from the buffer:%d / %d \n",buffSize,
            buffMax );
        }
        V(mtx);
        V(empty);
        thread_yield();
    }
}

int main(int argc, char *argv[]){
    /*initialize the mutex */
    mtx= mtx_create(0);
    buffSize=buffSizeVal;
    buffMax=buffMaxVal;

    /*checking for invalid */
    if (buffMax < 1){
        printf("prod-con-mtx: bufferMax cant not be less than 1\n");
        exit(1);
    }
    if (buffSize <0 || buffSize >buffMax){
        printf("prod-con-mtx: bufferSize cant not be less than 0\n" 
                " or more than buffermax\n");
        exit(1);
    }

    /* create producer and consumer threads*/
    thread_init(); 
    thread_create(prod);
    thread_create(con);
    thread_schedule();

    exit(0);
    

}




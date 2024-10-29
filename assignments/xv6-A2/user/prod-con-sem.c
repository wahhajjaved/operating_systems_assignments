/*
 *@author Wahhaj Javed, muj975, 11135711
 *@author Nakhba Mubashir, epl482, 11317060
 */

#include "user/sem.h"

#define buffSizeVal 6
#define buffMaxVal 6

static int mtx, buffMax, buffSize, empty, full;

void prod(void){
    int i;
    printf("Producer created\n");
    thread_yield();
    /*run till all are produced*/
    for (i=0;i<buffMax;i++){
        P(empty);
        P(mtx); /* locks the critical section*/
            thread_yield();
        buffSize++;
        printf("Producer: added to the buffer: %d / %d \n",i+1,
            buffMax );
        V(mtx);
        V(full);
        sleep(10); /*to slow it down*/
        thread_yield();
    }
}


void con(void){
    int i;
    printf("Consumer created\n");
    thread_yield();
    /*run till all are produced: buffer size*/
    for (i=0;i<buffMax;i++){
        P(full);
        P(mtx); /* locks the critical section*/
        thread_yield();
        buffSize--;
        printf("Consumer:removed from the buffer:%d / %d \n",i+1,
            buffMax );
        V(mtx);
        V(empty);
        thread_yield();
    }
}
int main(int argc, char *argv[]){
    /*initialize*/
    buffSize = 0;
    buffMax = buffMaxVal;
    mtx = sem_create(1);
    full = sem_create(0);
    empty = sem_create(buffMaxVal);
    mtx= sem_create(1);
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




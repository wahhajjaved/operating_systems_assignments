/*
 *@author Wahhaj Javed, muj975, 11135711
 *@author Nakhba Mubashir, epl482, 11317060
 */

#include "user/sem.h"

#define buffSizeVal 6
#define buffMaxVal 6

static int mtx, buffMax, buffSize, empty, full;

void prod(void){
    printf("Producer created\n");
    thread_yield();
    /*run till all are produced*/
    for (;;){
        P(empty);
        P(mtx); /* locks the critical section*/
            thread_yield();
        buffSize++;
        printf("Producer: added to the buffer: %d / %d \n",buffSize,
            buffMax );
        V(mtx);
        V(full);
        sleep(10); /*to slow it down*/
        thread_yield();
    }
}

void con1(void){
    printf("Consumer created\n");
    thread_yield();
    /*run till all are produced*/
    for (;;){
        P(full);
        P(mtx); /* locks the critical section*/
        thread_yield();
        buffSize--;
        printf("Consumer:removed from the buffer:%d / %d \n",buffSize,
            buffMax );
        V(mtx);
        V(empty);
        thread_yield();
    }
}

void con2(void){
    printf("Consumer created\n");
    thread_yield();
    /*run till all are produced*/
    for (;;){
        P(full);
        P(mtx); /* locks the critical section*/
        buffSize--;
        printf("Consumer:removed from the buffer:%d / %d \n",buffSize,
            buffMax );
        V(mtx);
        V(empty);
        thread_yield();
    }
}
int main(int argc, char *argv[]){
    /*initialize the mutex */
    buffSize=buffSizeVal;
    buffMax=buffMaxVal;
    full= sem_create(buffSize);
    empty=sem_create(buffMax-buffSize);
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
    thread_create(con1);
    thread_schedule();

    exit(0);
}




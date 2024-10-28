
/*
 *@author Wahhaj Javed, muj975, 11135711
 *@author Nakhba Mubashir, epl482, 11317060
 */

#include "user/mtx.h"
#include "user/uthread.h"

#define buffSizeVal 5
#define buffMaxVal 6
static int mtx, buffMax, buffSize;

void prod(void){
    printf("Producer created\n");
    thread_yield();

    for (;;){
        mtx_lock(mtx);
        if (buffSize < buffMax){
                thread_yield();
                buffSize++;
                printf("Producer: added to the buffer: %d / %d \n",buffSize,
            buffMax );
                mtx_unlocked(mtx);
        }else{
        mtx_unlocked(mtx);
        thread_yield();
        }
    }
}

void con(void){
    printf("Consumer created\n");
    thread_yield();
    for (;;){
        mtx_lock(mtx);
        if (buffSize > 1){
                thread_yield();
                buffSize--;
                printf("Producer: removed from the buffer: %d / %d \n",
                    buffSize, buffMax );
                mtx_unlocked(mtx);
        }else{
        mtx_unlocked(mtx);
        thread_yield();
        }
    }
}

int main(int argc, char *argv[]){
    /*initialize the mutex */
    mtx= mtx_create(0);
    buffSize=buffSizeVal;
    buffMax=buffMaxVal;

    if (buffMax < 1){
        printf("prod-con-mtx: bufferMax cant not be less than 1\n");
        exit(1);
    }
    if (buffSize <0 || buffSize >buffMax){
        printf("prod-con-mtx: bufferSize cant not be less than 0\n" 
                " or more than buffermax\n");
        exit(1);
    }

    thread_init(); 
    thread_create(prod);
    thread_create(con);
    thread_schedule();

    exit(0);
    

}


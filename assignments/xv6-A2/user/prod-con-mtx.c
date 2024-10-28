
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
        if (buffSize > 0){
                thread_yield();
                buffSize--;
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
    thread_init(); 
    thread_create(prod);
    thread_create(con);
    thread_schedule();

    exit(0);
    

}



/*
 *@author Wahhaj Javed, muj975, 11135711
 *@author Nakhba Mubashir, epl482, 11317060
 */

#include "user/mtx.h"

#define buffSize 5
#define buffMax 6
static int mutex;

void prod(void){
    printf("Producer created\n");
    thread_yeild();
    for (;;;){
        mtx_lock(mutex);
        if (buffSize < buffMax){
                thread_yeild();
                buffSize++;
                mtx_unlocked(mtx);
        }else{
        mtx_unlocked(mtx);
        thread_yeild();
        }
    }
}

void con(void){
    printf("Consumer created\n");
    thread_yeild();
    for (;;;){
        mtx_lock(mutex);
        if (buffSize > 0){
                thread_yeild();
                buffSize--;
                mtx_unlocked(mtx);
        }else{
        mtx_unlocked(mtx);
        thread_yeild();
        }
    }
}

int main(int argc, char *argv[]){
    /*initialize the mutex */
    mutex= mtx_mtx_create(0);

    thread_init(); 
    thread_create(prod);
    thread_create(con);
    thread_scedule();

    exit(0);
    

}


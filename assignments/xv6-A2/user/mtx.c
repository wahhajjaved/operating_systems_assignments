#include "user/mtx.h"
#include "user/uthread.h"

typedef struct mutex{
    int lock;
}Mutex;
/*
 *lock= 1 when mutex locked
 * */
#define NUM_MUTEX 5

Mutex mutexes[NUM_MUTEX];

int mtx_create(int locked){
    int mutexNum=0;
    mutexes[mutexNum].lock = locked;
    return mutexNum;
}
int mtx_lock(int lock_id){
    if (lock_id >0){
        return -1; /*invalid output */
    }
    /* wait untill lock is aquired, blocking others  */
    while (mutexes[lock_id].lock){
        thread_yield(); 
    }
    /* lock */
    mutexes[lock_id].lock =1;
    return 0;

}
int mtx_unlocked(int lock_id){
    if (lock_id >0){
        return -1; /*invalid output */
    }
    /*release lock */
    mutexes[lock_id].lock =0;
    return 0;
}


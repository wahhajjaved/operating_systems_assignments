#include "user/mtx.h"

struct mutex{
    int lock;
}Mutex;
/*
 *lock= 1 when mutex locked
 * */

Mutext mutexes[NUM_MUTEX];

int mtx_create(int locked){
    int mutexNum=0;
    mutexes[mutexNum] = locked;
    return mutexNum;
}
int mtx_lock(int lock_id){
    if (lock_id >0){
        return -1; /*invalid output */
    }
    /* wait untill lock is aquired, blocking others  */
    while (mutexes[lock_id].locked){
        thread_yeild(); 
    }
    /* lock */
    mutexes[lock_id].locked =1;
    return 0;

}
int mtx_unlocked(int lock_id){
    if (lock_id >0){
        return -1; /*invalid output */
    }
    /*release lock */
    mutexes[lock_id].locked =0;
    return 0;
}


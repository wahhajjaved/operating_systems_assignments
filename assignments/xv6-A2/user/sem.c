/*
 *@author Wahhaj Javed, muj975, 11135711
 *@author Nakhba Mubashir, epl482, 11317060
*/
#include "user/sem.h"

typedef struct _semaphore{
    int value;
}Semaphore;

#define NUM_SEM 5

Semaphore sem[NUM_SEM];
static int mtx;

int sem_create(int val){
    int i;
    mtx= mtx_create(1);
    for (i=0; i<NUM_SEM; i++){
        sem[i].value= val;
    }
    mtx_unlocked(mtx);
    return i;
}

int P(int semVal){
    mtx_lock(mtx);
    sem[semVal].value--;
    mtx_unlocked(mtx);
    return 0;

}
int V(int semVal){
    mtx_lock(mtx);
    sem[semVal].value++;
    mtx_unlocked(mtx);
    return 0;
}


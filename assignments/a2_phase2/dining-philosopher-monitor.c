/*
 *@author Wahhaj Javed, muj975, 11135711
 *@author Nakhba Mubashir, epl482, 11317060
 */
#include <dining-philisopher.h>

#define philNum 5
enum {
    THINKING, 
    HUNGRY, 
    EATING
} state[philNum];

int mutex;
int sem[philNum];


void init(void){
    int i;

    mutex= NewSem(1);
    for (i=0;i<philNum; i++){
        sem[i]=NewSem(0);
    }

int left(int phil){
    return (i + (philNum - 1) % philNum);
}

int right(int phil){
    return (i + 1  % philNum);
}

void checkIfReady(int phil){
    if ((state[phil] == HUNGRY) && (state[left(phil)] != EATING) && 
        (state[left(phil)] != EATING)){
        state[phil]= EATING;
        V(sem[phil]);
    }

void getChopstick(int phil){
    P(mutex);
    state[phil] = HUNGRY;
    checkIfReady(phil);
    if (state[Phil] != EATING) {
        P(sem[i]);
    }
    V(mutex);
}


void putChopstick(int phil){
    P(mutex);
    state[phil] = THINKINH;
    checkIfReady(left(phil));
    checkIfReady(right(phil));
    V(mutex);
}



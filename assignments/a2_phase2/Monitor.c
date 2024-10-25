/*
 *@author Wahhaj Javed, muj975, 11135711
 *@author Nakhba Mubashir, epl482, 11317060
 */

int mutex, urgent, urgentNum;
int *monList, *sem;


#include "Monitor.h"
void MonInit(int numConds){
    int i:

    mutex= NewSem(1);
    urgent= NewSem(0);
    urgentNum=0;

    sem= (int *) malloc(numConds * sizeof(int));
    if (sem== NULL) {
        printf("Sem: memory allocated Fail\n");
    }
    for (i=0 ; i<numConds; i++) {
        sem[i]=NewSem(0); 
    }


    monList= (int *) malloc(numConds * sizeof(int));
    if (monList== NULL) {
        printf("monList: memory allocate Fail\n");
    }
    for (i=0 ; i<numConds; i++) {
        monList[i]= 0;
    }
}

void MonEnter(void) {
    P(mutex);
}

void MonLeave(void) {
    if (urgentNum > 0){
        V(urgent);
    }else {
        V(mutex);
    }
}

void MonWait(int signal) {}

void MonSignal(int signal) {}

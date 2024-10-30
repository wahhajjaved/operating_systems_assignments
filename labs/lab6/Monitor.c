/*
 *@author Wahhaj Javed, muj975, 11135711
 *@author Nakhba Mubashir, epl482, 11317060
 */
#include <os.h>
#include <standards.h>
#include <Monitor.h>


int mutex, urgent, urgentNum;
int *monList, *sem;
LIST **condVar;

#define OKtoWrite 1
#define OKtoRead  0


void MonInit(int numConds){
    int i;
    mutex= NewSem(1); /*for entry and exit */
    urgent= NewSem(0); 
    urgentNum=0;

    /*memory allocation and initilizing */
    sem= (int *) malloc(numConds * sizeof(int));
    if (sem== NULL) {
        printf("Sem: memory allocated Fail\n");
        return;
    }
    for (i=0 ; i<numConds; i++) {
        sem[i]=NewSem(0); 
    }


    monList= (int *) malloc(numConds * sizeof(int));
    if (monList== NULL) {
        printf("monList: memory allocate Fail\n");
        return;
    }
    for (i=0 ; i<numConds; i++) {
        monList[i]= 0;
    }

    condVar = (LIST **)malloc(numConds * sizeof(LIST *));
    if (condVar == NULL) {
        printf("condVars: memory allocation failed\n");
    }
    for (i = 0; i < numConds; i++) {
        condVar[i] = ListCreate();
    }
}

void MonEnter(void) {
    P(mutex);     /* wait and get  mutex   */
}

void MonLeave(void) {
    if (urgentNum > 0){
        V(urgent);   /* if urgent is waiting then leave urgent*/
    }else {
        V(mutex);    /* leave mutex*/
    }
}

void MonWait(int CV) {
    /*
    PID myPid= MyPid();
    P(mutex);
    */
    ListAppend(condVar[CV], (void *) MyPid() );
    monList[CV] ++;

     if (urgentNum > 0){
        V(urgent);
    }else {
        V(mutex);
    }

    P(sem[CV]);
    ListRemove(condVar[CV]);
    monList[CV] --;

}

void MonSignal(int CV) {
    if (monList[CV] > 0) {
        urgentNum++;  
        ListRemove(condVar[CV]);     
        V(sem[CV]);        
         
        P(urgent);                    
        urgentNum--;                  
    }
}

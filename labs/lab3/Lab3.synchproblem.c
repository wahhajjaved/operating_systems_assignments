/*
 *NAKHBA MUBASHIR
 * EPL482
 * 11317060
 */

#include <stdio.h>
#include <stdlib.h>
#include <os.h>
#include <standards.h>


int elfTex,mutex, santaSem, reindeerSem;

int elveNum;
int reindeerNum;

void getHelp(void){
    printf("getting help\n");
    Sleep(100);
}

void helpElves(void){
    printf("helpping elves\n");
    Sleep(100);
}

void prepareSleigh(void){
    printf("preparing sleigh \n");
    Sleep(100);
}
void getHitched(void){
    printf(" getiing hitched \n");
    Sleep(50);
}


PROCESS elves(void){
    P(elfTex);
    P(mutex);
    elveNum++;
    if (elveNum == 3) V(santaSem);
    else V(elfTex);
    V(mutex);

    getHelp();

    P(mutex);
    elveNum--;
    if (elveNum == 0) V(elfTex);
    V(mutex);
}

PROCESS santa(void){
    int i;
    while(1){
        P(santaSem);
        P(mutex);
        if (reindeerNum >= 9){
            prepareSleigh();
            for (i=0; i<9; i++){
                V(reindeerSem);
                reindeerNum--;
            }
        } else if (elveNum == 3){
            helpElves();
        }
        V(mutex);
        }
}

PROCESS reindeer(void){
    P(mutex);
    reindeerNum++;
    if (reindeerNum == 9) V(santaSem);
    V(mutex);
    V(reindeerSem);
    getHitched();
}

void initialize(void){
    elveNum=0;
    reindeerNum=0;
    mutex=NewSem(1);  /* mutex */
    elfTex=NewSem(0); /* allow one elf  to enter*/
    santaSem= NewSem(1); 
    reindeerSem=NewSem(1);
}


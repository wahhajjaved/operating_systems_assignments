/*
 *NAKHBA MUBASHIR
 * EPL482
 * 11317060
 */

#include <stdio.h>
#include <stdlib.h>
#include <standards.h>
#include <os.h>

int elfTex,mutex, santaSem, reindeerSem;

int elveNum, reindeerNum;

void getHelp(void){
    printf("getting help\n");
}

void helpElves(void){
    printf("helpping elves\n");
}

void prepareSleigh(void){
    printf("preparing sleigh \n");
}
void getHitched(void){
    printf("getiing hitched \n");
}


PROCESS elves(void){
    P(elfTex);
    P(mutex);

    elveNum++;
    if (eleveNum == 3) V(santaSem);
    else V(elfTex);
    V(mutex);

    getHelp();

    P(mutex);
    elveNum--;
    if (eleveNum == 0) V(elfTex);
    V(mutex);
}

PROCESS santa(void){
    int i;

    P(santaSem);
    P(mutex);

    if (reindeerNum >= 9){
        prepareSleigh();
        for (i=0; i<=9; i++){
            V(reindeerSem);
            reindeerNum--;
        }
    } else if (eleveNum == 3){
        helpElves();
    }
    V(mutex);
}

PROCESS reindeer(void){
    P(mutex);
    reindeerNum++;
    if (reindeerNum == 9) V(santaSem);
    V(mutex);

    V(reindeerSem);
    getHitcth();
}



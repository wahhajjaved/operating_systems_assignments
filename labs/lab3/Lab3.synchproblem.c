/*
 *NAKHBA MUBASHIR
 * EPL482
 * 11317060
 */

#include <stdio.h>
#include <stdlib.h>
#include <standards.h>
#include <os.h>

int elfTex,mutex, santaSem;

int elveNum, reindeerNum;

void getHelp(){
    printf("getting help");
}




PROCESS Elves(void){
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




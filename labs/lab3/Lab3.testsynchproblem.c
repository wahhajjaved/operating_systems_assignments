/*
 *NAKHBA MUBASHIR
 * EPL482
 * 11317060
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <os.h>

#include <standards.h>


PROCESS elves(void);
PROCESS santa(void);
PROCESS reindeer(void);
void initialize(void);

int main (void){
    int i;
    initialize();
    /* santa wakes up for elve*/
    for (i = 0; i  <10; i++) {
        reindeer();
    }
    santa();
    for (i = 0; i < 4; i++) {
        elves();
    }
    return 0;

}

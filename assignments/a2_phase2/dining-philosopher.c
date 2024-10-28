/*
 *@author Wahhaj Javed, muj975, 11135711
 *@author Nakhba Mubashir, epl482, 11317060
 */

#include <dining-philosopher.h>

#define SLEEPMAX 20

#define philNum 5


PROCESS Philosopher(void *arg)
{
  long myId;
  
  myId = (long) arg;
  
  for(;;)
    {
      printf("%ld Philosopher is thinding \n", myId);
      Sleep((int) (rand() % SLEEPMAX*6));
      printf("%ld Philosopher is hungry \n", myId);
      getChopstick(myId %1000);
      printf("%ld Philosopher is eating \n", myId);
      Sleep((int) (rand() % SLEEPMAX));
      putChopstick(myId %1000);  
      printf("%ld philosopher is done\n", myId);
    }
}


int mainp()
{
    unsigned long i;
    void *ptr;
    PID tempPid[philNum];
    setbuf(stdout, 0);

    srand(71);

    init();

    for (i=0; i < philNum; i++){
        ptr= (void *) (1000+i);
        tempPid[i] = Create((void(*)()) Philosopher, 16000, (char*) (&i),
            ptr ,NORM, USR );
        if (tempPid[i] == PNUL) perror("Create");
    }
    printf("philosopher processes created\n");

    return(0);
}




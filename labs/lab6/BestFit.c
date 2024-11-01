/* Nakhba Mubashir, epl482, 11317060 */

#include <BestFitMonitor.h>

PROCESS BestFit(void *arg)
{
  long myId;
  myId = (long) arg;
  
  for(i=0;i<MAX_THREAD_ITEM;i++)
    {
      printf("%ld Allocate\n", myId);
      BF-allocation(rand() % (MEM_SIZE));
      Sleep((int) (rand() % SLEEPMAX*5));
      printf("%ld FINISH allocaation\n", myId);
      Sleep((int) (rand() % SLEEPMAX*6));
    }
    printf("*****%ld DONE ******\n", myId);
  
}

int mainp()
{
    PID tempPid, temp2, temp3,temp4;
    setbuf(stdout, 0);

    srand(71);
    BF-init();

    tempPid = Create((void(*)()) BestFit, 16000, "T1", NULL, NORM, USR );
    if (tempPid == PNUL) perror("Create");
    temp2 = Create(  (void(*)()) BestFit, 16000, "T2", NULL, NORM, USR );
    if (temp2 == PNUL) perror("Create");
    temp3 = Create(  (void(*)()) BestFit, 16000, "T3",  NULL, NORM, USR );
    if (temp3 == PNUL) perror("Create");
    temp4 = Create(  (void(*)()) BestFit, 16000, "T4",  NULL, NORM, USR );
    if (temp4 == PNUL) perror("Create");
    printf("ALL threads created\n");

    return(0);
}



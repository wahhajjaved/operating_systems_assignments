/*
 *@author Wahhaj Javed, muj975, 11135711
 *@author Nakhba Mubashir, epl482, 11317060
*/
/*
#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"
*/
#include "user/uthread.h"
#include "user/mtx.h"

int sem_create(int val);
int P(int semVal);
int V(int semVal);

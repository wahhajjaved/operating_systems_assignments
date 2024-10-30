/*
 *@author Wahhaj Javed, muj975, 11135711
 *@author Nakhba Mubashir, epl482, 11317060
 */
#ifndef MONITOR
#define MONITOR

#include <stdio.h>
#include <stdlib.h>
#include <list.h>


void MonInit(int num);
void MonEnter(void);

void MonLeave(void);

void MonWait(int CV);

void MonSignal(int CV);

#endif

/*
 *@author Wahhaj Javed, muj975, 11135711
 *@author Nakhba Mubashir, epl482, 11317060
 *@date 2024-10-08
 */

#ifndef READER-WRITER-MONITOR
#define READER-WRITER-MONITOR

#include <stdio.h>
#include <monitor.h>
#include <os.h>
#include <standards.h>

void StartRead();
void StopRead();
void StopWrite();
PID reader(void *arg);
PID writer(void *arg);


#endif

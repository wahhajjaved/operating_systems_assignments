/*
 *@author Wahhaj Javed, muj975, 11135711
 *@author Nakhba Mubashir, epl482, 11317060
 *@date 2024-10-08
 */

#ifndef READER_WRITER_MONITOR
#define READER_WRITER_MONITOR

#include <stdio.h>
/*#include <os.h>*/
#include <standards.h>

void StartRead(void);
void StopRead(void);
void StopWrite(void);
void StartWrite(void);
/*
PROCESS reader(void *arg);
PROCESS writer(void *arg);
*/

#endif

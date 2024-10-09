/*
 *@author Wahhaj Javed, muj975, 11135711
 *@author Nakhba Mubashir, epl482, 11317060
 *@date 2024-10-08
 */


#include <stdio.h>

#include <rtthreads.h>
#include <RttCommon.h>

#define STKSIZE 65536

RTTTHREAD server() {
	printf("server not yet implemented.\n");
	
}
RTTTHREAD consoleIn() {
	printf("consoleIn not yet implemented.\n");
	
}
RTTTHREAD consoleOut() {
	printf("consoleOut not yet implemented.\n");
	
}
RTTTHREAD networkIn() {
	printf("networkIn not yet implemented.\n");
	
}
RTTTHREAD networkOut() {
	printf("networkOut not yet implemented.\n");
	
}

int mainp()
{
	
	int temp;
	
	RttThreadId serverTid;
	RttThreadId	consoleInTid;
	RttThreadId consoleOutTid;
	RttThreadId networkInTid;
	RttThreadId networkOutTid;
	
	RttSchAttr 	attr;
	attr.startingtime = RTTZEROTIME;
	attr.priority = RTTNORM;
	attr.deadline = RTTNODEADLINE;

	printf("s-chat starting.\n");
	setbuf(stdout, 0);
	
	temp = RttCreate(
		&serverTid, 
		(void(*)()) server,
		STKSIZE,
		"server",
		NULL,
		attr,
		RTTSYS
	);
	if (temp == RTTFAILED) perror("Failed to create server thread.");

	temp = RttCreate(
		&consoleInTid, 
		(void(*)()) consoleIn,
		STKSIZE,
		"consoleIn",
		NULL,
		attr,
		RTTSYS
	);
	if (temp == RTTFAILED) perror("Failed to create consoleIn thread.");

	temp = RttCreate(
		&consoleOutTid, 
		(void(*)()) consoleOut,
		STKSIZE,
		"consoleOut",
		NULL,
		attr,
		RTTSYS
	);
	if (temp == RTTFAILED) perror("Failed to create consoleOut thread.");

	temp = RttCreate(
		&networkInTid, 
		(void(*)()) networkIn,
		STKSIZE,
		"networkIn",
		NULL,
		attr,
		RTTSYS
	);
	if (temp == RTTFAILED) perror("Failed to create networkIn thread.");

	temp = RttCreate(
		&networkOutTid, 
		(void(*)()) networkOut,
		STKSIZE,
		"networkOut",
		NULL,
		attr,
		RTTSYS
	);
	if (temp == RTTFAILED) perror("Failed to create networkOut thread.");
	
	
	printf("s-chat exiting.\n");
	
	return(0);

}
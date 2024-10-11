/*
@author Wahhaj Javed, muj975, 11135711
@date 2024-10-10
*/

#include <stdio.h>
#include <monitor.h>
#include <list.h>
#include <rtthreads.h>
#include <RttCommon.h>
#include <RttMutex.h>

#define STKSIZE 65536


unsigned long monMessagesMutex; /*1 is unlocked, 0 is locked*/
LIST* monMessages;

LIST* cvLists;
LIST* enterq;
LIST* urgentq;


typedef enum action {
	ENTER, LEAVE, WAIT, SIGNAL
} ACTION;

typedef struct message {
	RttThreadId tid;
	ACTION action;
	int cv;
} Message;

void RttMonInit(int numConds){
	int temp;
	RttSchAttr 	attr;
	RttThreadId	serverTid;

	
	RttNewMutex(&monMessagesMutex);
	monMessages = ListCreate();
	cvLists = ListCreate();
	while(numConds > 0) {
		ListAdd(cvLists, ListCreate());
		numConds--;
	}
	enterq = ListCreate();
	urgentq = ListCreate();
	
	
	attr.startingtime = RTTZEROTIME;
	attr.priority = RTTHIGH;
	attr.deadline = RTTNODEADLINE;
	temp = RttCreate(&serverTid, 
		(void(*)()) MonServer, 
		STKSIZE,"R1", 
		(void *) 1000, 
		attr, 
		RTTSYS
	);
	if (temp == RTTFAILED) perror("RttMonInit");
	
	printf("RttMonInit - Lists created and server started.\n");
}

void RttMonEnter() {
	Message* message;
	message = malloc(sizeof(Message));
	message->tid = RttMyThreadId();
	message->action = ENTER;
	message->cv = -1;
	
	printf("Sending enter message.\n");
	
	RttMutexLock(monMessagesMutex);
	ListAppend(monMessages, message);
	RttMutexUnlock(monMessagesMutex);
	RttSuspend();
	
	
}

void RttMonLeave(){
	Message* message;
	message = malloc(sizeof(Message));
	message->tid = RttMyThreadId();
	message->action = LEAVE;
	message->cv = -1;
	
	printf("Sending leave message.\n");
	RttMutexLock(monMessagesMutex);
	ListAppend(monMessages, message);
	RttMutexUnlock(monMessagesMutex);
	RttSuspend();
}

void RttMonWait(int CV){
	printf("RttMonWait not implemented.\n");
	/*
	Message* message;
	message = malloc(sizeof(Message));
	message->tid = RttMyThreadId();
	message->action = WAIT;
	message->cv = CV;
	
	RttMutexLock(monMessagesMutex);
	ListAppend(monMessages, message);
	RttMutexUnlock(monMessagesMutex);
	RttSuspend();
	*/
}

void RttMonSignal(int CV){
	printf("RttMonSignal not implemented.\n");
	/*Message* message;
	message = malloc(sizeof(Message));
	message->tid = RttMyThreadId();
	message->action = SIGNAL;
	message->cv = CV;
	
	RttMutexLock(monMessagesMutex);
	ListAppend(monMessages, message);
	RttMutexUnlock(monMessagesMutex);
	RttSuspend();*/
}

void MonServer(){
	Message* message;
	int isOccupied;
	isOccupied = 0;
	
	printf("Starting server loop.\n");
	while(1){
		if (!isOccupied && ListCount(urgentq)) {
			ListFirst(urgentq);
			message = (Message*) ListRemove(urgentq);
		}
		else if (!isOccupied && ListCount(enterq)) {
			ListFirst(enterq);
			message = (Message*) ListRemove(enterq);
		}
		else{
			RttMutexLock(monMessagesMutex);
			ListFirst(monMessages);
			message = (Message*) ListRemove(monMessages);
			RttMutexUnlock(monMessagesMutex);
		}
		if(!message) {
			printf("No message dequeued.\n");
			RttUSleep(1000);
			continue;
		}
		switch (message->action) {
			case ENTER:
				if (isOccupied) {
					ListAppend(enterq, message);
				}
				else {
					isOccupied = 1;
					RttResume(message->tid);
					free(message);
				}
				break;
			
			case LEAVE:
				isOccupied = 0;
				RttResume(message->tid);
				free(message);
				break;
			
			case WAIT:
				printf("Wait not handled in server.\n");
				break;
			
			case SIGNAL:
				printf("Wait not handled in server.\n");
				break;
			
			default:
				printf("ERROR - Unrecognized message.\n");
				break;
		}
	}
}

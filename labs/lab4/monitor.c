/*
@author Wahhaj Javed, muj975, 11135711
@date 2024-10-10
*/

#include <stdio.h>
#include <monitor.h>
#include <list.h>
#include <rtthreads.h>
#include <RttCommon.h>


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
	RttNewMutex(&monMessagesMutex);
	monMessages = ListCreate();
	
	cvLists = ListCreate();
	for(numConds; numConds > 0; numConds--) {
		ListAdd(cvLists, ListCreate());
	}
	enterq = ListCreate();
	urgentq = ListCreate();
	MonServer();
	printf("RttMonInit - Lists created and server started.\n");
}

void RttMonEnter() {
	Message* message;
	
	message = malloc(sizeof(message));
	message->tid = RttMyThreadId();
	message->action = ENTER;
	message->cv = -1;
	
	RttMutexLock(monMessagesMutex);
	ListAppend(monMessages, message);
	RttMutexUnlock(monMessagesMutex);
	
	
}

void RttMonLeave(){
	Message* message;
	message = malloc(sizeof(message));
	message->tid = RttMyThreadId();
	message->action = LEAVE;
	message->cv = -1;
	RttMutexLock(monMessagesMutex);
	ListAppend(monMessages, message);
	RttMutexUnlock(monMessagesMutex);
}

void RttMonWait(int CV){
	Message* message;
	message = malloc(sizeof(message));
	message->tid = RttMyThreadId();
	message->action = WAIT;
	message->cv = CV;
	RttMutexLock(monMessagesMutex);
	ListAppend(monMessages, message);
	RttMutexUnlock(monMessagesMutex);
	
}

void RttMonSignal(int CV){
	Message* message;
	message = malloc(sizeof(message));
	message->tid = RttMyThreadId();
	message->action = SIGNAL;
	message->cv = CV;
	RttMutexLock(monMessagesMutex);
	ListAppend(monMessages, message);
	RttMutexUnlock(monMessagesMutex);
}

void MonServer(){
	int isOccupied;

	isOccupied = 0;
	
	while(1){
		
	}
}

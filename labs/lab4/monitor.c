/*
@author Wahhaj Javed, muj975, 11135711
@date 2024-10-10
*/

#include <stdio.h>
#include <monitor.h>
#include <list.h>



LIST* cvLists;
LIST* enterq;
LIST* urgentq;


void RttMonInit(int numConds){
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
	printf("RttMonEnter not implemented\n");
}

void RttMonLeave(){
	printf("RttMonLeave not implemented\n");
}

void RttMonWait(int CV){
	printf("RttMonWait not implemented\n");
}

void RttMonSignal(int CV){
	printf("RttMonSignal not implemented\n");
}

void MonServer(){
	printf("MonServer not implemented\n");
}

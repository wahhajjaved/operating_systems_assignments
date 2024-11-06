/*
@author Wahhaj Javed, muj975, 11135711
@date 2024-11-06
*/

/*
BarberShop
*/


#include <stdio.h>
#include <os.h>
#include <Lab3.synchproblem.h>

#define TOTALCUSTOMERS 50
#define MAXSLEEPTIME 75
int total_customers;
int shopOpen;
void print_usage() {
	printf(
		"Usage ./Lab3.testsynchproblem.c <total_customers>\n"
		"total_customers is the total number of threads to spawn for a run. \n"
		"total_customers must be between 1 and 100. \n"
	);
}
void customerMaker() {
	int i;
	PID pids[TOTALCUSTOMERS];
	for(i = 0; i < total_customers; i++) {
		Sleep(rand() & MAXSLEEPTIME);
		pids[i] = Create( 
			customerThread,
			4096,
			"customerThread",
			NULL,
			NORM,
			USR
		);
	}
	while(1) {
		int j, runningThreads;
		runningThreads = 0;
		for(j = 0; j < total_customers; j++) {
			if(PExists(pids[j])) {
				runningThreads++;
			}
		}
		if(runningThreads == 0)
			break;
		Sleep(100);
	}
	printf("Closing shop.\n");
	shopOpen = 0;
	Sleep(100);
	for(i = 0; i < TOTALCUSTOMERS; i++) {
		Kill(pids[i]);
	}
}
int mainp(int argc, char* argv[]) {
	
	if(argc != 2) {
		print_usage();
		return 1;
	}
	
	total_customers = atoi(argv[1]);
	if(total_customers <= 0 || total_customers > TOTALCUSTOMERS) {
		print_usage();
		return 1;
	}
	
	if(init() == 1) {
		return 1;
	}
	srandom(2);
	shopOpen = 1;
	Create( 
		barberThread,
		4096,
		"barber",
		NULL,
		NORM,
		USR
	);
	Create( 
		customerMaker,
		65536,
		"customerMaker",
		NULL,
		NORM,
		USR
	);
	
	return 0;

}
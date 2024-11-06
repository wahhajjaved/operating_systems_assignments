/*
@author Wahhaj Javed, muj975, 11135711
@date 2024-10-16
*/

/*
BarberShop
*/


#include <stdio.h>
#include <os.h>
#include <Lab3.synchproblem.h>

#define TOTALCUSTOMERS 50

void print_usage() {
	printf(
		"Usage ./Lab3.testsynchproblem.c <total_customers>\n"
		"total_customers is the total number of threads to spawn for a run. \n"
		"total_customers must be between 1 and 100. \n"
	);
}

int main(int argc, char* argv[]) {
	int total_customers, i;
	if(argc != 2) {
		print_usage();
		return 1;
	}
	
	total_customers = atoi(argv[1]);
	if(total_customers < 0 || total_customers > TOTALCUSTOMERS) {
		print_usage();
		return 1;
	}
	
	if(init() == 1) {
		return 1;
	}
	
	Create( 
		barberThread,
		65536,
		"barber",
		NULL,
		NORM,
		USR
	);

	for(i = 0; i < total_customers; i++) {
		Create( 
			customerThread,
			65536,
			"customerThread",
			NULL,
			NORM,
			USR
		);
	}
}
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

#define MAXCUSTOMERS 5

int customers = 0;
int mutex, customer, barber, customerDone, barberDone; 

void customerThread() {
	P(mutex);
	printf("New customer arrived.\n");
	
	/*If no chairs, then release the lock and return*/
	if(customers >= MAXCUSTOMERS) {
		printf("No chair available.\n");
		V(mutex);
		return;
	}
	/*otherwise wait in the chair*/
	customers++;
	V(mutex);
	
	V(customer);
	P(barber);
	
	printf(
		"Customer getting hair cut. \n"
		"Total number of current customers = %d\n"
		,customers
	);
	
	
	V(customerDone);
	P(barberDone);
	
	P(mutex);
	customers--;
	printf("Customer leaving.\n");
	V(mutex);
}

void barberThread() {
	printf("Barber thread starting.\n");
	while(shopOpen) {
		P(customer);
		V(barber);
		
		printf(
			"Barber cutting hair. \n"
			"Total number of current customers = %d\n"
			,customers
		);
		Sleep(50);
		
		P(customerDone);
		V(barberDone);
	}
	printf("Barber thread ending.\n");
}
int init() {
	
	if((mutex = NewSem(1)) == -1){
		perror("Could not create mutex semaphore.");
		return 1;
	}
	if((customer = NewSem(0)) == -1){
		perror("Could not create customer semaphore.");
		return 1;
	}
	if((barber = NewSem(0)) == -1){
		perror("Could not create barber semaphore.");
		return 1;
	}
	if((customerDone = NewSem(0)) == -1){
		perror("Could not create custormerDone semaphore.");
		return 1;
	}
	if((barberDone = NewSem(0)) == -1){
		perror("Could not create barberDone semaphore.");
		return 1;
	}
	return 0;
}
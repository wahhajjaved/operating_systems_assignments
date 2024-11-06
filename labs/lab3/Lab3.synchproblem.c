/*
@author Wahhaj Javed, muj975, 11135711
@date 2024-10-16
*/

/*
BarberShop
*/

#include <os.h>

#define MAXCUSTOMERS 5

int customers = 0;
int mutex, customer, barber, customerDone, barberDone; 

void customerThread() {
	P(customer);
	
	/*If no chairs, then release the lock and return*/
	if(customers == MAXCUSTOMERS) {
		V(customer);
		return;
	}
	/*otherwise wait in the chair*/
	customers++;
	
	V(customer);
	P(barber);
	
	printf(
		"Customer getting hair cut. \n"
		"Total number of current customers = %d\n"
		,customers
	);
	
	
	V(customerDone);
	P(barberDone);
	
	P(customer);
	customers--;
	V(customer);
}

void barberThread() {
	P(customer);
	V(barber);
	
	printf(
		"Barber cutting hair. \n"
		"Total number of current customers = %d\n"
		,customers
	);
	
	P(customerDone);
	V(barberDone);
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
	if((custormerDone = NewSem(0)) == -1){
		perror("Could not create custormerDone semaphore.");
		return 1;
	}
	if((barberDone = NewSem(0)) == -1){
		perror("Could not create barberDone semaphore.");
		return 1;
	}
}
/*
@author Wahhaj Javed, muj975, 11135711
@date 2024-10-16
*/

/*
BarberShop
*/

#include <semaphore.h>

#define MAXCUSTOMERS 5

int customers = 0;
sem_t mutex, customer, barber, customerDone, barberDone; 

void customerThread() {
	sem_wait(&customer);
	
	/*If no chairs, then release the lock and return*/
	if(customers == MAXCUSTOMERS) {
		sem_post(&customer);
		return;
	}
	/*otherwise wait in the chair*/
	customers++;
	
	sem_post(&customer);
	sem_wait(&barber);
	
	getHairCut();
	
	sem_post(&customerDone);
	sem_wait(&barberDone);
	
	sem_wait(&customer);
	customers--;
	sem_post(&customer);
}

void barberThread() {
	sem_wait(&customer);
	sem_post(&barber);
	
	cutHair();
	
	sem_wait(&customerDone);
	sem_post(&barberDone);
}
int main() {
	
	if(sem_init(&mutex, 0, 1) == -1){
		perror("Could not create mutex semaphore.");
		return 1;
	}
	if(sem_init(&customer, 0, 0) == -1){
		perror("Could not create customer semaphore.");
		return 1;
	}
	if(sem_init(&barber, 0, 0) == -1){
		perror("Could not create barber semaphore.");
		return 1;
	}
	if(sem_init(&custormerDone, 0, 0) == -1){
		perror("Could not create custormerDone semaphore.");
		return 1;
	}
	if(sem_init(&barberDone, 0, 0) == -1){
		perror("Could not create barberDone semaphore.");
		return 1;
	}
	
	
	
	
	
}
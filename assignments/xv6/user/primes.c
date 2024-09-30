/*
* @author Wahhaj Javed, muj975, 11135711
* @author Nakhba Mubashir, epl482, 11317060
* @date 2024-09-30
*/

#include "kernel/types.h"
#include "user/user.h"

int pipe1[2];
int pipe2[2];

void prime() {
	int nextInt;
	
	if (read(pipe1[0], &nextInt, 4) != 4) {
		printf("Error when reading nextInt.\n");
		return;
	}
	printf("%d read in prime.\n", nextInt);
}

int main(int argc, char* argv[]) {
	int childPid, nextInt;
	nextInt = 2;
	
	if (pipe(pipe1) == -1) {
		printf("Could not create pipe1 pipe.\n");
		return 1;
	}
	if (pipe(pipe2) == -1) {
		printf("Could not create pipe2 pipe.\n");
		return 1;
	}

	childPid = fork();
	if (childPid == -1) {
		printf("fork failed in main.\n");
		return 1;
	}
	else if (childPid == 0) {
		prime();
	}
	else {
		printf("Writing to child\n");
		if (write(pipe1[1], &nextInt, 4) != 4) {
			printf("Error when writing nextInt.\n");
			return 1;
		}
	}
	
	return 0;
	
}
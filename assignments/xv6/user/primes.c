/*
* @author Wahhaj Javed, muj975, 11135711
* @author Nakhba Mubashir, epl482, 11317060
* @date 2024-09-30
*/

#include "kernel/types.h"
#include "user/user.h"

#define MAX_INT 5

int pipe1[2]; //incoming
int pipe2[2]; //outgoing
int incoming = -1;
int outgoing = -1;

int createProcess() {
	int childPid;
	if (pipe2[0] != -1 && pipe2[1] != -1) {
		printf("%d: Can not create process as pipe2 is already initialized\n", getpid());
		return -1;
	}
	
	if (pipe(pipe2) == -1) {
		printf("%d: Could not create pipe2 pipe.\n", getpid());
		return -1;
	}

	childPid = fork();
	if (childPid == -1) {
		printf("%d: fork failed in createProcess().\n", getpid());
		return -1;
	}
	else if (childPid == 0) {
		incoming = pipe2[0];
		outgoing = -1;
		if(close(pipe1[0]) != 0) {
			printf("%d: Error in createProcess. Could not close pipe1[0]\n", getpid());
			return -1;
		}
		pipe1[0] = -1;
		
		if(close(pipe2[1]) != 0) {
			printf("%d: Error in createProcess. Could not close pipe2[1]\n", getpid());
			return -1;
		}
		pipe2[1] = -1;
	}
	else {
		outgoing = pipe2[1];
		if(close(pipe2[0]) != 0) {
			printf("%d: Error in createProcess. Could not close pipe2[0]\n", getpid());
			return -1;
		}
		pipe2[0] = -1;
	}
	return childPid;
	
}

void prime() {
	int divisor, nextInt, bytesRead;
	// int childPid, divisor, nextInt, outgoing, incoming;
	divisor = -1;
	while(1) {
		bytesRead = read(incoming, &nextInt, 4);
		if (bytesRead == 0) {
			printf("%d: 0 bytes read in prime(). Incoming pipe close in prime().\n", getpid());
			break;
		}
		else if (bytesRead != 4) {
			printf("%d: Error when reading nextInt.\n", getpid());
			break;
		}
		printf("%d: %d read in prime.\n", getpid(), nextInt);
		if (divisor == -1) {
			divisor = nextInt;
			continue;
		}
		if (nextInt % divisor != 0) {
			printf("%d: nextInt = %d, divisor = %d, remainder = %d.\n", getpid(), nextInt, divisor, nextInt%divisor);
			// if (outgoing == -1) {
			// 	childPid = createProcess(&incoming, &outgoing);
			// 	if (childPid == -1) {
			// 		printf("Could not create new process in prime().\n");
			// 		return;
			// 	}
			// 	else if (childPid == 0) {
			// 		continue;
			// 	}
			// }

			// if (write(outgoing, &nextInt, 4) != 4) {
			// 	printf("Error when writing nextInt.\n");
			// 	return;
			// }
		}
	}
	printf("%d: Loop finished in prime(). Now exiting program.\n", getpid());
	return;
}

void parent(int outgoing) {
	int nextInt, bytesWritten;
	nextInt = 1;
	while (nextInt++ <= MAX_INT) {	
		printf("\n");
		printf("%d: Writing %d to child.\n", getpid(), nextInt);
		if ((bytesWritten = write(outgoing, &nextInt, 4)) != 4) {
			printf("%d: Error when writing nextInt.\n", getpid());
			printf("%d: Expected to write 4 bytes but instead wrote %d.\n", getpid(), bytesWritten);
			return;
		}
		sleep(1);
		
	}
	printf("\n");
	if (close(outgoing) != 0) {
		printf("%d: Error in main. Could not close outgoing.\n", getpid());
		return;
	}
	
}

int main(int argc, char* argv[]) {
	int childPid, status, closedPid;
	
	pipe2[0] = -1;
	pipe2[1] = -1;
	if (pipe(pipe1) == -1) {
		printf("%d: Could not create pipe1 pipe.\n", getpid());
		return 1;
	}
	childPid = createProcess();
	if (childPid == -1) {
		printf("%d: Could not create new process. Exiting program.\n", getpid());
		return 1;
	}
	else if (childPid == 0) {
		prime();
		printf("%d: Returned from prime().\n", getpid());
	}
	else {
		parent(outgoing);
		while((closedPid = wait(&status) != childPid)) {
			printf("%d: Process %d closed\n", getpid(), closedPid);
		}
		
	}
	
	printf("%d: Exiting program.\n", getpid());
	return 0;
}
/*
* @author Wahhaj Javed, muj975, 11135711
* @author Nakhba Mubashir, epl482, 11317060
* @date 2024-09-30
*/

#include "kernel/types.h"
#include "user/user.h"

#define MAX_INT 35

int pipe1[2]; //incoming
int pipe2[2]; //outgoing
int incoming = -1;
int outgoing = -1;

void print_state() {
	printf("%d: pipe 1 = {%d, %d}, pipe 2 = {%d, %d}, "
		"incoming = %d, outgoing = %d\n", 
		getpid(), pipe1[0], pipe1[1], pipe2[0], pipe2[1], incoming, outgoing
	);
	
}

int createProcess() {
	int childPid;
	
	// printf("%d: createProcess() called.\n", getpid());
	if (pipe2[0] != -1 && pipe2[1] != -1) {
		printf("%d: Can not create process as pipe2 is already initialized.\n", 
			getpid()
		);
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
		if(close(pipe1[0]) != 0) {
			printf("%d: Error in createProcess. Could not close pipe1[0]\n", 
				getpid()
			);
			return -1;
		}
		if(close(pipe2[1]) != 0) {
			printf("%d: Error in createProcess. Could not close pipe2[1]\n", 
				getpid()
			);
			return -1;
		}
		
		pipe1[0] = pipe2[0];
		pipe2[0] = -1;
		pipe2[1] = -1;
	}
	else {
		if(close(pipe2[0]) != 0) {
			printf("%d: Error in createProcess. Could not close pipe2[0]\n", 
				getpid()
			);
			return -1;
		}
		pipe2[0] = -1;
	}
	
	incoming = pipe1[0];
	outgoing = pipe2[1];
	return childPid;
	
}

void prime() {
	// int divisor, nextInt, bytesRead;
	int childPid, divisor, number, bytesRead, bytesWritten, closedPid, status;
	childPid = -1;
	divisor = -1;
	
	while(1) {
		bytesRead = read(incoming, &number, 4);
		if (bytesRead == 0) {
			break;
		}
		else if (bytesRead != 4) {
			printf("%d: Error when reading number.\n", getpid());
			break;
		}
		if (divisor == -1) {
			printf("%d: prime %d\n", getpid(),number);
			divisor = number;
			continue;
		}

		//if remainder is 0, not a prime so drop the integer
		if (number % divisor == 0) {
			continue;
		}

		if (outgoing == -1) {
			childPid = createProcess(&incoming, &outgoing);
			if (childPid == -1) {
				printf("%d: Could not create new process in prime().\n",
					getpid()
				);
				return;
			}
			else if (childPid == 0) {
				divisor = -1;
				continue;
			}
		}
		bytesWritten = write(outgoing, &number, 4);
		if ( bytesWritten != 4) {
			if (bytesWritten == -1)
				printf("%d: Downstream pipe closed.\n", getpid());
			else
				printf("%d: Error when writing number.\n", getpid());
			return;
		}
		
	}
	
	if (outgoing != -1 && close(outgoing) != 0) {
		printf("%d: Error in prime. Could not close outgoing.\n", getpid());
		return;
	}
	if((closedPid = wait(&status) != childPid)) {
			printf("%d: Process %d closed\n", getpid(), closedPid);
	}
	return;
}

void parent(int outgoing) {
	int nextInt, bytesWritten;
	nextInt = 1;
	while (nextInt++ <= MAX_INT) {
		if ((bytesWritten = write(outgoing, &nextInt, 4)) != 4) {
			if (bytesWritten == -1)
				printf("%d: Downstream pipe closed.\n", getpid());
			else {
				printf("%d: Error when writing nextInt.\n", getpid());
				printf("%d: Expected to write 4 bytes but instead wrote %d.\n", getpid(), bytesWritten);
			}
			return;
		}
	}

	if (close(outgoing) != 0) {
		printf("%d: Error in main. Could not close outgoing.\n", getpid());
		return;
	}
	outgoing = -1;
}

int main(int argc, char* argv[]) {
	int childPid, status, closedPid;
	
	pipe1[0] = -1;
	pipe1[1] = -1;
	pipe2[0] = -1;
	pipe2[1] = -1;
	if (pipe(pipe1) == -1) {
		printf("%d: Could not create pipe1 pipe.\n", getpid());
		return 1;
	}
	if(close(pipe1[1]) != 0) {
		printf("%d: Error in main. Could not close pipe1[1]\n", 
			getpid()
		);
		return -1;
	}
	pipe1[1] = -1;

	childPid = createProcess();
	if (childPid == -1) {
		printf("%d: Could not create new process. Exiting program.\n", 
			getpid()
		);
		return 1;
	}
	else if (childPid == 0) {
		prime();
	}
	else {
		parent(outgoing);
		while((closedPid = wait(&status) != childPid)) {
			printf("%d: Process %d closed\n", getpid(), closedPid);
		}
		sleep(1); //so shell prompt doesn't end up as part of program output
	}
	return 0;
}
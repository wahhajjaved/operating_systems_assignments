/*
* @author Wahhaj Javed, muj975, 11135711
* @author Nakhba Mubashir, epl482, 11317060
* @date 2024-09-30
*/

#include "kernel/types.h"
#include "user/user.h"

#define MAX_INT 3

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
	
	printf("%d: CreateProcess() start.\n", getpid());
	print_state();
	
	
	sleep(1);
	if (pipe2[0] != -1 && pipe2[1] != -1) {
		printf("%d: Can not create process as pipe2 is already initialized.\n", 
			getpid()
		);
		return -1;
	}
	
	sleep(1);
	if (pipe(pipe2) == -1) {
		printf("%d: Could not create pipe2 pipe.\n", getpid());
		return -1;
	}
	
	printf("%d: pipe2 created in createProcess().\n", getpid());
	print_state();
	printf("\n");
	sleep(1);

	childPid = fork();
	sleep(1);
	if (childPid == -1) {
		printf("%d: fork failed in createProcess().\n", getpid());
		return -1;
	}
	else if (childPid == 0) {
		// close pipe1 because it connects to the parent's parent
		sleep(3);
		printf("\n");
		printf("%d: createProcess() in child after fork.\n", getpid());
		print_state();
		
		if(close(pipe1[0]) != 0) {
			printf("%d: Error in createProcess. Could not close pipe1[0]\n", 
				getpid()
			);
			return -1;
		}
		// if(close(pipe1[1]) != 0) {
		// 	printf("%d: Error in createProcess. Could not close pipe1[1]\n", 
		// 		getpid()
		// 	);
		// 	return -1;
		// }

		sleep(3);
		if(close(pipe2[1]) != 0) {
			printf("%d: Error in createProcess. Could not close pipe2[1]\n", 
				getpid()
			);
			return -1;
		}
		
		pipe1[0] = pipe2[0];
		// pipe1[1] = -1;
		pipe2[0] = -1;
		pipe2[1] = -1;
		sleep(3);
		printf("%d: createProcess() in child end.\n", getpid());
		print_state();
		sleep(3);
	}
	else {
		sleep(1);
		printf("%d: createProcess() after fork in parent.\n", getpid());
		print_state();
		
		// pipe1 = [3, 4]
		// pipe2 = [5, 6]
		
		// if(close(pipe1[1]) != 0) {
		// 	printf("%d: Error in createProcess. Could not close pipe1[1]\n", 
		// 		getpid()
		// 	);
		// 	return -1;
		// }
		if(close(pipe2[0]) != 0) {
			printf("%d: Error in createProcess. Could not close pipe2[0]\n", 
				getpid()
			);
			return -1;
		}
		
		// pipe1[1] = -1;
		pipe2[0] = -1;
		
		sleep(1);
		printf("%d: createProcess() in parent end.\n", getpid());
		print_state();
	}
	
	sleep(2);
	incoming = pipe1[0];
	outgoing = pipe2[1];
	printf("%d: createProcess() end.\n", getpid());
	print_state();
	return childPid;
	
}

void prime() {
	// int divisor, nextInt, bytesRead;
	int childPid, divisor, number, bytesRead;
	childPid = -1;
	divisor = -1;
	
	while(1) {
		sleep(5);
		bytesRead = read(incoming, &number, 4);
		if (bytesRead == 0) {
			printf("%d: 0 bytes read in prime(). Incoming pipe close in "
				"prime().\n", getpid()
			);
			// write(outgoing, &bytesRead, 4);
			break;
		}
		else if (bytesRead != 4) {
			printf("%d: Error when reading number.\n", getpid());
			break;
		}
		printf("%d: %d read in prime.\n", getpid(), number);
		if (divisor == -1) {
			divisor = number;
			continue;
		}

		//if remainder is 0, not a prime so drop the integer
		if (number % divisor == 0) {
			printf("%d: %d is a factor of %d\n", 
				getpid(),
				number,
				divisor
			);
			continue;
		}
		
		printf("%d: %d is not divisible by %d.\n", 
			getpid(), 
			number,
			divisor
		);
		
		if (outgoing == -1) {
			printf("%d: No process next in line to handle %d. "
				"Creating a new process.\n", 
				getpid(),
				number
			);
			childPid = createProcess(&incoming, &outgoing);
			sleep(5);
			if (childPid == -1) {
				printf("%d: Could not create new process in prime().\n",
					getpid()
				);
				return;
			}
			else if (childPid == 0) {
		sleep(1);
				
				printf("Prime %d\n", number);
				divisor = -1;
				continue;
			}
		}

		sleep(5);
		if (write(outgoing, &number, 4) != 4) {
			printf("Error when writing number.\n");
			return;
		}
		
	}
	sleep(5);
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
		sleep(30);
		
	}
	printf("\n");
	if (close(outgoing) != 0) {
		printf("%d: Error in main. Could not close outgoing.\n", getpid());
		return;
	}
	
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
		printf("%d: Returned from prime().\n", getpid());
	}
	else {
		sleep(5);
		
		parent(outgoing);
		while((closedPid = wait(&status) != childPid)) {
			printf("%d: Process %d closed\n", getpid(), closedPid);
		}
	}
	sleep(10);
	printf("%d: Exiting program.\n", getpid());
	return 0;
}
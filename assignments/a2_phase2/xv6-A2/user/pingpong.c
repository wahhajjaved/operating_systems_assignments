/*
* @author Wahhaj Javed, muj975, 11135711
* @author Nakhba Mubashir, epl482, 11317060
* @date 2024-09-22
*/

#include "kernel/types.h"
#include "user/user.h"

int pToC[2];
int cToP[2];
char b = 'p';

int child() {
	char buffer;
	int bytesRead, bytesWritten;
	bytesRead = read(pToC[0], &buffer, 1);
	if (bytesRead == -1) {
		printf("Error when reading byte from parent\n");
		return 1;
	}
	else if (bytesRead != 1) {
		printf("Error in child: Expected to read 1 byte but instead read %d"
			"\n",
			bytesRead
		);
		return 1;
	}
	
	if(buffer == b) {
		printf("%d: received ping\n", getpid());
	}
	else {
		printf("Error in child. Expecting %d but got %d\n", b, buffer);
		return 1;
	}
	
	bytesWritten = write(cToP[1], &b, 1);
	if (bytesWritten == -1) {
		printf("Error when sending byte to child\n");
	}
	else if (bytesWritten != 1) {
		printf("Error in parent: Expected to write 1 byte but instead wrote %d"
			"\n",
			bytesWritten
		);
	}
	
	return 0;
}

int parent() {
	char buffer;
	int bytesRead, bytesWritten;
	bytesWritten = write(pToC[1], &b, 1);
	if (bytesWritten == -1) {
		printf("Error when sending byte to child\n");
	}
	else if (bytesWritten != 1) {
		printf("Error in parent: Expected to write 1 byte but instead wrote %d"
			"\n",
			bytesWritten
		);
	}
	
	bytesRead = read(cToP[0], &buffer, 1);
	if (bytesRead == -1) {
		printf("Error when reading byte from child\n");
		return 1;
	}
	else if (bytesRead != 1) {
		printf("Error in parent: Expected to read 1 byte but instead read %d"
			"\n",
			bytesRead
		);
		return 1;
	}
	
	if(buffer == b) {
		printf("%d: received pong\n", getpid());
	}
	else {
		printf("Error in parent. Expecting %d but got %d\n", b, buffer);
		return 1;
	}
	
	return 0;
}

int main(int argc, char* argv[]) {
	int childPid;
	if (pipe(pToC) == -1) {
		printf("Could not create pipe pToC\n");
		return 1;
	}
	if (pipe(cToP) == -1) {
		printf("Could not create pipe cToP\n");
		return 1;
	}
	
	childPid = fork();
	if (childPid == -1) {
		printf("fork failed\n");
		return 1;
	}
	else if (childPid == 0) {
		child();
	}
	else {
		parent();
	}
	return 0;
	
}
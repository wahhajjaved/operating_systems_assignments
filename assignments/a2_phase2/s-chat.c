/*
 *@author Wahhaj Javed, muj975, 11135711
 *@author Nakhba Mubashir, epl482, 11317060
 *@date 2024-10-24
 */


#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <fcntl.h>

#include <rtthreads.h>
#include <RttCommon.h>

#define STKSIZE 65536
#define BUFSIZE 100


RTTTHREAD server() {
	printf("server not yet implemented.\n");
	
}
RTTTHREAD consoleIn() {
	char inputBuffer[BUFSIZE];
	int bytesRead;
	for(;;) {
		printf("consoleIn(): Reading from stdin. \n");
		bytesRead = read(0, inputBuffer, BUFSIZE);
		if(bytesRead == -1 && errno != EAGAIN && errno != EWOULDBLOCK) {
			perror("consoleIn(): Error encountered when reading from stdin.");
			break;
		}
		else if (bytesRead == 0) {
			printf("consoleIn(): EOF detected on stdin.\n");
		}
		else {
			printf("consoleIn(): No data to read on stdin.\n");
		}
		printf("consoleIn(): Sleeping for 1000 us. \n");
		RttUSleep(1000);
	}
	printf("consoleIn(): exiting.\n");
	
}
RTTTHREAD consoleOut() {
	printf("consoleOut not yet implemented.\n");
	
}
RTTTHREAD networkIn() {
	printf("networkIn not yet implemented.\n");
	
}
RTTTHREAD networkOut() {
	printf("networkOut not yet implemented.\n");
	
}

void parseArguments(
	int argc,
	char* argv[],
	uint32_t* src_port,
	uint32_t* dst_ip,
	uint32_t* dst_port
) {
	int status;
	struct addrinfo hints, *res;
	struct sockaddr_in *ipv4;

	if (argc != 4) {
		printf("Incorrect number of arguments.\n");
		printf("Usage: s-chat <src_port> <dst_host_name> <dst_port>\n");
		exit(EXIT_FAILURE);
	}
	
	*src_port = atoi(argv[1]);
	*dst_port = atoi(argv[3]);
	
	
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	status = getaddrinfo(argv[2], NULL, &hints, &res);
	if (status != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
		exit(EXIT_FAILURE);
	}
	ipv4 = (struct sockaddr_in *)res->ai_addr;
	*dst_ip = ipv4->sin_addr.s_addr;
	freeaddrinfo(res);
}

int mainp(int argc, char* argv[])
{
	int temp;
	uint32_t src_port, dst_ip, dst_port;
	RttThreadId serverTid, consoleInTid, consoleOutTid, networkInTid;
	/* RttThreadId networkOutTid; */
	RttSchAttr attr;
	
	/* setbuf(stdout, 0); */
	parseArguments(argc, argv, &src_port, &dst_ip, &dst_port);
	printf("Starting s-chat. src port: %u, dst ip: %u, dst port: %u.\n",
		src_port, 
		dst_ip, 
		dst_port
	);
	
	/*Configure stdin to be non blocking*/
	temp = fcntl(0, F_SETFL, O_NONBLOCK);
	if(temp == -1) {
		perror("main(): Could not set std in to be non-blocking.\n");
		return 1;
	}

	/*Thread creations*/
	attr.startingtime = RTTZEROTIME;
	attr.priority = RTTNORM;
	attr.deadline = RTTNODEADLINE;
	
	/* 
	temp = RttCreate(
		&serverTid, 
		(void(*)()) server,
		STKSIZE,
		"server",
		NULL,
		attr,
		RTTSYS
	);
	if (temp == RTTFAILED) perror("Failed to create server thread.");
 */
	temp = RttCreate(
		&consoleInTid, 
		(void(*)()) consoleIn,
		STKSIZE,
		"consoleIn",
		NULL,
		attr,
		RTTSYS
	);
	if (temp == RTTFAILED) {
		perror("Failed to create consoleIn thread.");
		return 1;
	}
		

/* 	temp = RttCreate(
		&consoleOutTid, 
		(void(*)()) consoleOut,
		STKSIZE,
		"consoleOut",
		NULL,
		attr,
		RTTSYS
	);
	if (temp == RTTFAILED) perror("Failed to create consoleOut thread.");
 */
/* 	temp = RttCreate(
		&networkInTid, 
		(void(*)()) networkIn,
		STKSIZE,
		"networkIn",
		NULL,
		attr,
		RTTSYS
	);
	if (temp == RTTFAILED) perror("Failed to create networkIn thread.");
 */
/* 	temp = RttCreate(
		&networkOutTid, 
		(void(*)()) networkOut,
		STKSIZE,
		"networkOut",
		NULL,
		attr,
		RTTSYS
	);
	if (temp == RTTFAILED) perror("Failed to create networkOut thread.");
 */	
	
	printf("s-chat exiting.\n");
	
	return(0);

}
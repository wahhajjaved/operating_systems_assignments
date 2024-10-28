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
#include <list.h>

#define STKSIZE 65536
#define QUEUESIZE 20
#define BUFSIZE 100
#define SUCCESS 1
#define FAILURE 0


typedef struct message {
	char message[BUFSIZE];
	u_int size;
} Message;

RttThreadId serverTid, consoleInTid, consoleOutTid, networkInTid;
RttThreadId networkOutTid;
struct addrinfo *localAddrInfo, *remoteAddrInfo;
int localSockFd;
u_int exitFlag = 0;

int getSockets(
	char* src_port, 
	char* dst_ip,
	char* dst_port
) {
	int r;
	struct addrinfo hints;
	
	
	/*Local*/
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE;
	
	r = getaddrinfo(NULL, src_port, &hints, &localAddrInfo);
	if(r != 0) {
		perror("getSockets: Error getting addr info for local socket.\n");
		freeaddrinfo(localAddrInfo);
		return 0;
	}
	
	localSockFd = socket(
		(localAddrInfo)->ai_family,
		(localAddrInfo)->ai_socktype | SOCK_NONBLOCK,
		(localAddrInfo)->ai_protocol
	);
	if(localSockFd == -1) {
		perror("getSockets: Could not create socket.\n");
		return 0;
	}
	
	r = bind(localSockFd, (localAddrInfo)->ai_addr, (localAddrInfo)->ai_addrlen);
	if(r != 0) {
		perror("getSockets: Error binding local socket.\n");
		close(localSockFd);
		return 0;
	}
	
	
	/*Remote*/
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	
	r = getaddrinfo(dst_ip, dst_port, &hints, &remoteAddrInfo);
	if(r != 0) {
		close(localSockFd);
		perror("getSockets: Error getting addr info for remote socket.\n");
		freeaddrinfo(remoteAddrInfo);
		return 0;
	}
	
	return 1;
}



int configureLists(
	LIST** consoleOutFreeList,
	LIST** consoleOutQueue,
	LIST** networkOutFreeList, 
	LIST** networkOutQueue
) {
	int i;

	*consoleOutQueue = ListCreate();
	*consoleOutFreeList = ListCreate();
	if(*consoleOutQueue == NULL) {
		fprintf(stderr, "Error: consoleOutQueue not created.\n");
		return 0;
	}
	if(*consoleOutFreeList == NULL) {
		fprintf(stderr, "Error: consoleOutFreeList not created.\n");
		return 0;
	}
	for(i = 0; i < QUEUESIZE; i++) {
		Message* message = malloc(sizeof(Message));
		if(message == NULL) {
			perror("configureLists(): malloc returned NULL.");
			return 0;
		}
		message->size = 0;
		message->message[0] = '\0';
		if(ListAppend(*consoleOutFreeList, message) == -1) {
			fprintf(stderr, "Error: ListAppend to consoleOutFreeList failed.\n");
			return 0;
		}
	}
	
	*networkOutQueue = ListCreate();
	*networkOutFreeList = ListCreate();
	if(*networkOutQueue == NULL) {
		fprintf(stderr, "Error: networkOutQueue not created.\n");
		return 0;
	}
	if(*networkOutFreeList == NULL) {
		fprintf(stderr, "Error: networkOutFreeList not created.\n");
		return 0;
	}
	
	for(i = 0; i < QUEUESIZE; i++) {
		Message* message = malloc(sizeof(Message));
		if(message == NULL) {
			perror("configureLists(): malloc returned NULL.");
			return 0;
		}
		message->size = 0;
		message->message[0] = '\0';
		if(ListAppend(*networkOutFreeList, message) == -1) {
			fprintf(stderr, "Error: ListAppend to networkOutFreeList failed.\n");
			return 0;
		}
	}
	return 1;
}

RTTTHREAD server() {
	int r, reply, newMessage;
	RttThreadId from;
	char data[BUFSIZE+1];
	u_int len, replyLen;
	u_int consoleOutReady, networkOutReady;
	Message *consoleOutCurMessage, *networkOutCurMessage;
	LIST *consoleOutFreeList, *consoleOutQueue;
	LIST *networkOutFreeList, *networkOutQueue;
	
	r = configureLists (
			&consoleOutFreeList,
			&consoleOutQueue,
			&networkOutFreeList,
			&networkOutQueue
		);
	if(r != 1) {
		fprintf(stderr, "Error: configureLists() did not return 1.\n");
		exitFlag = 1;
	}
	
	/*special case to handle first response from consoleOut*/
	consoleOutCurMessage = ListFirst(consoleOutFreeList);
	networkOutCurMessage = ListFirst(networkOutFreeList);
	
	consoleOutReady = 0;
	networkOutReady = 0;
	replyLen = 1;
	
	printf("Starting server main loop\n");
	while(exitFlag != 1) {
		/*Allow other threads to run*/
		RttUSleep(10);
		newMessage = 0;
		len = BUFSIZE;
		/*Get a message if there are any waiting*/
		if(RttMsgWaits()) {
			r = RttReceive(&from, data, &len);
			if (r == RTTFAILED) {
				perror("server(): RttReceive() failed.\n");
				continue;
			}
			newMessage = 1;
			printf("server(): %u bytes recieved.\n", len);
		}
		
		/*empty message indicates EOF so exit all threads*/
		if(newMessage && len == 0) {
			exitFlag = 1;
			
			RttReply(consoleInTid, NULL, 0);
			if(consoleOutReady) {
				RttReply(consoleOutTid, NULL, 0);
			}
			if(networkOutReady) {
				RttReply(networkOutTid, NULL, 0);
			}
			break;
		}

		/*process message from consoleIn */
		if (newMessage && RTTTHREADEQUAL(from, consoleInTid) ) {
			if (ListCount(consoleOutFreeList) == 0) {
				fprintf(stderr, "server: Cannot buffer any more messages from "
					"consoleIn.\n"
				);
				
			}
			else {
				/*
				Message* message = ListTrim(consoleOutFreeList);
				printf("server(): message from consoleIn.\n");
				message->size = len;
				memcpy(message->message, data, message->size);
				ListPrepend(consoleOutQueue, message);
				reply = SUCCESS;
				RttReply(from, &reply, replyLen);
				*/

				Message* message = ListTrim(networkOutFreeList);
				printf("server(): message from networkOut.\n");
				message->size = len;
				memcpy(message->message, data, message->size);
				ListPrepend(networkOutQueue, message);
				reply = SUCCESS;
				RttReply(from, &reply, replyLen);

			}
		}

		/*Process message from consoleOut*/
		if (newMessage && RTTTHREADEQUAL(from, consoleOutTid) ) {
			if (consoleOutCurMessage == NULL) {
				fprintf(stderr, "server: consoleOutCurMessage is NULL.\n");
			}
			else { 
			consoleOutCurMessage->message[0] = '\0';
			consoleOutCurMessage->size = 0;
			ListAppend(consoleOutFreeList, consoleOutCurMessage);
			consoleOutReady = 1;
			}
		}
		
		/*Process message from networkOut*/
		if (newMessage && RTTTHREADEQUAL(from, networkOutTid) ) {
			if (networkOutCurMessage == NULL) {
				fprintf(stderr, "server: networkOutCurMessage is NULL.\n");
			}
			else { 
			networkOutCurMessage->message[0] = '\0';
			networkOutCurMessage->size = 0;
			ListAppend(networkOutFreeList, networkOutCurMessage);
			networkOutReady = 1;
			}
		}
		
		
		/*Send message to consoleOut if its ready*/
		if(consoleOutReady == 1 && ListCount(consoleOutQueue) > 0) {
			printf("server(): sending message to consoleOut.\n");
			consoleOutCurMessage = ListTrim(consoleOutQueue);
			if(consoleOutCurMessage != NULL) {
				printf("server(): Sending %u bytes to consoleOut.\n", consoleOutCurMessage->size);
				consoleOutReady = 0;
				RttReply(
					consoleOutTid, 
					consoleOutCurMessage->message,
					consoleOutCurMessage->size
				);
			}
		}
		
		/*Send message to networkOut if its ready*/
		if(networkOutReady == 1 && ListCount(networkOutQueue) > 0) {
			printf("server(): sending message to networkOut.\n");
			networkOutCurMessage = ListTrim(networkOutQueue);
			if(networkOutCurMessage != NULL) {
				printf("server(): Sending %u bytes to networkOut.\n", networkOutCurMessage->size);
				networkOutReady = 0;
				RttReply(
					networkOutTid, 
					networkOutCurMessage->message,
					networkOutCurMessage->size
				);
			}
		}
	}

	printf("server(): exiting.\n");
}

RTTTHREAD consoleIn(void) {
	char inputBuffer[BUFSIZE];
	int bytesRead;
	int reply;
	u_int replyLen = 1;
	int r;
	
	printf("consoleIn(): starting. \n");
	while(exitFlag != 1) {
		/*Allow other threads to run*/
		RttUSleep(10);
		replyLen = 1;
		bytesRead = read(0, inputBuffer, BUFSIZE);
		if(bytesRead == -1 && errno != EAGAIN && errno != EWOULDBLOCK) {
			perror("consoleIn(): Error encountered when reading from stdin.");
			break;
		}

		else if (bytesRead == 0) {
			printf("consoleIn(): EOF detected on stdin.\n");
			exitFlag = 1;
			RttSend(serverTid, inputBuffer, bytesRead, &reply, &replyLen);
			break;
		}

		else if(bytesRead > 0) {
			printf("consoleIn(): %d bytes read.\n", bytesRead);
			r = RttSend(serverTid, inputBuffer, bytesRead, &reply, &replyLen);
			if(r != RTTOK) {
				printf("Could not send message from consoleIn to server.\n");
			}
		}
	}
	printf("consoleIn(): exiting.\n");
}

RTTTHREAD consoleOut(void) {
	int r, sentMsg;
	char message[BUFSIZE+1];
	u_int messageLen=BUFSIZE;
	sentMsg = SUCCESS;
	printf("consoleOut(): starting.\n");
	while(exitFlag != 1) {
		messageLen=BUFSIZE;
		r = RttSend(serverTid, &sentMsg, 1, &message, &messageLen);
		if(r != RTTOK) {
			printf("Could not get message from server.\n");
		}
		printf("consoleOut: %u bytes recieved.\n", messageLen);
		message[messageLen] = '\0';
		printf("consoleOut: %s\n", message);

	}
	printf("consoleOut(): exiting.\n");
	
	
}

RTTTHREAD networkIn() {
	printf("networkIn not yet implemented.\n");
	
}

RTTTHREAD networkOut() {
	int r, sentMsg;
	char message[BUFSIZE];
	u_int messageLen=BUFSIZE;
	sentMsg = SUCCESS;
	
	printf("networkOut(): starting.\n");
	while(exitFlag != 1) {
		messageLen=BUFSIZE;
		r = RttSend(serverTid, &sentMsg, 1, &message, &messageLen);
		if(r != RTTOK) {
			printf("Could not get message from server.\n");
		}
		printf("networkOut: %u bytes recieved.\n", messageLen);
		
		r = sendto(localSockFd, message, messageLen, 0, remoteAddrInfo->ai_addr, remoteAddrInfo->ai_addrlen );
		if(r == -1) {
			perror("sendto failed.\n");
			continue;
		}
		printf("sendto: %d bytes sent.\n", r);
	}
	printf("networkOut(): exiting.\n");
	
}

void exitFunction() {
	int temp, curFlags;
	printf("s-chat exiting.\n");
	/*Configure stdin to be blocking*/
	curFlags = fcntl(0, F_GETFL, 0);
	if(curFlags == -1) {
		perror("Error getting curFlags for stdin.\n");
		return;
	}
	curFlags &= ~O_NONBLOCK;
	temp = fcntl(0, F_SETFL, curFlags);
	if(temp == -1) {
		perror("main(): Could not set std in to be blocking.\n");
	}
}


int mainp(int argc, char* argv[])
{
	int r;
	char *src_port, *dst_ip, *dst_port;
	
	RttSchAttr attr;
	
	setbuf(stdout, 0);
	if (argc != 4) {
		printf("Incorrect number of arguments.\n");
		printf("Usage: s-chat <src_port> <dst_host_name> <dst_port>\n");
		exit(EXIT_FAILURE);
	}
	src_port = argv[1];
	dst_ip = argv[2];
	dst_port = argv[3];
	printf("Starting s-chat. src port: %s, dst ip: %s, dst port: %s.\n",
		src_port, 
		dst_ip, 
		dst_port
	);
	
	/*Configure stdin to be non blocking*/
	r = fcntl(0, F_SETFL, O_NONBLOCK);
	if(r == -1) {
		perror("main(): Could not set std in to be non-blocking.\n");
		return 1;
	}
	
	r = getSockets(
		src_port, 
		dst_ip,
		dst_port
	);
	if(r != 1) {
		return 1;
	}
	
	/*Socket send test*/
	/*
	r = sendto(localSockFd, "Hello nc", 9, 0, remoteAddrInfo->ai_addr, remoteAddrInfo->ai_addrlen );
	if(r == -1) {
		perror("sendto failed.\n");
		return 1;
	}
	printf("sendto: %d bytes sent.\n", r);
	return 0;
	*/
	
	
	
	
	RttRegisterExitRoutine(&exitFunction);
	
	/*Thread creations*/
	attr.startingtime = RTTZEROTIME;
	attr.priority = RTTNORM;
	attr.deadline = RTTNODEADLINE;
	r = RttCreate(
		&serverTid, 
		(void(*)()) server,
		STKSIZE,
		"server",
		NULL,
		attr,
		RTTUSR
	);
	if (r == RTTFAILED) perror("Failed to create server thread.");
	printf("server thread created.\n");

	r = RttCreate(
		&consoleInTid, 
		(void(*)()) consoleIn,
		STKSIZE,
		"consoleIn",
		NULL,
		attr,
		RTTUSR
	);
	if (r == RTTFAILED) {
		perror("Failed to create consoleIn thread.");
		return 1;
	}
	printf("ConsoleIn thread created.\n");
	
 	r = RttCreate(
		&consoleOutTid, 
		(void(*)()) consoleOut,
		STKSIZE,
		"consoleOut",
		NULL,
		attr,
		RTTUSR
	);
	if (r != RTTOK) {
		perror("Failed to create consoleOut thread.");
		return 1;
	}
	printf("ConsoleOut thread created.\n");

/* 	r = RttCreate(
		&networkInTid, 
		(void(*)()) networkIn,
		STKSIZE,
		"networkIn",
		NULL,
		attr,
		RTTUSR
	);
	if (r == RTTFAILED) perror("Failed to create networkIn thread.");
 */
	r = RttCreate(
		&networkOutTid, 
		(void(*)()) networkOut,
		STKSIZE,
		"networkOut",
		NULL,
		attr,
		RTTUSR
	);
	if (r == RTTFAILED) perror("Failed to create networkOut thread.");

	RttSleep(1);
	return(0);
}
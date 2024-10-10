/* @author Nakhba Mubashir, epl482, 11317060 */

#include <monitor.h>

/* global variables */

LIST *CVList
LIST *enterQueue, *UrgentQueue;
MSG *sendMsg;

unsigned int sendLen, recieveLen;
MSG *receiveMsg;
RttThreadId RTTPid;


/* functions */
void RttMonInit(){

}
void RttMonEnter(){
    
    int temp;
    char Mess[] = "enter";
    
    /* memory allocation*/
    sendMsg= (MSG *) malloc(sizeof(MSG));
    if (sendMmsg ==NULL) errx(1, "Memory allocation failed");

    strcpy(sendMsg->data, Mess);
    
    /*int RttSend(RttThreadId, void *, unsigned int, void *, unsigned int *)*/ 
    temp= RttSend(RTTPid, msg,*sendLen, receiveMsg,recieveLen); 

}

    /*
 *
 *int RttSend(RttThreadId, void *, unsigned int, void *, unsigned int *);
int RttMsgWaits();
int RttReceive(RttThreadId *, void *, unsigned int *);
int RttReply(RttThreadId, void *, unsigned int);
 *int RttCreate(RttThreadId *, void(*)(), size_t, char *, void *, RttSchAttr, int);
int RttP(RttSem);
int RttV(RttSem);
 * */

void RttMonLeave(){

    int temp;
    char Mess[] = "leave";

    /* memory allocation*/
    sendMsg= (MSG *) malloc(sizeof(MSG));
    if (sendMmsg ==NULL) errx(1, "Memory allocation failed");

    strcpy(sendMsg->data, Mess);

    /*int RttSend(RttThreadId, void *, unsigned int, void *, unsigned int *)*/
    temp= RttSend(RTTPid, msg,*sendLen, receiveMsg,recieveLen);    
}

void RttMonWait(int CV){

    int temp;
    char Mess[] = "wait";

    /* memory allocation*/
    sendMsg= (MSG *) malloc(sizeof(MSG));
    if (sendMmsg ==NULL) errx(1, "Memory allocation failed");

    strcpy(sendMsg->data, Mess);

    /*int RttSend(RttThreadId, void *, unsigned int, void *, unsigned int *)*/
    temp= RttSend(RTTPid, msg, *sendLen, receiveMsg,recieveLen);    


}
void RttMonSignal(int CV){

    int temp;
    char Mess[] = "signal";

    /* memory allocation*/
    sendMsg= (MSG *) malloc(sizeof(MSG));
    if (sendMmsg ==NULL) errx(1, "Memory allocation failed");

    strcpy(sendMsg->data, Mess);

    /*int RttSend(RttThreadId, void *, unsigned int, void *, unsigned int *)*/
    temp= RttSend(RTTPid, msg, *sendLen, receiveMsg,recieveLen);
}
void MonServer() 

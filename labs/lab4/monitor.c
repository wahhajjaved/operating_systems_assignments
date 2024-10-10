/* @author Nakhba Mubashir, epl482, 11317060 */

#include <monitor.h>

/* global variables */

LIST *CVList
LIST *enterQueue, *urgentQueue;
MSG *sendMsg, msg;

unsigned int sendLen, recieveLen;
MSG *receiveMsg;
RttThreadId RTTPid, senderPid, takeOffPid;


/* functions */
void RttMonInit(){

}
void RttMonEnter(){
    
    int temp;
    char Mess[] = "enter";
    
    /* memory allocation*/
    sendMsg= (MSG *) malloc(sizeof(MSG));
    if (sendMsg ==NULL) errx(1, "Memory allocation failed");

    strcpy(sendMsg->data, Mess);
    
    /*int RttSend(RttThreadId, void *, unsigned int, void *, unsigned int *)*/ 
    temp= RttSend(RTTPid, msg,*sendLen, receiveMsg,recieveLen); 

}

void RttMonLeave(){

    int temp;
    char Mess[] = "leave";

    /* memory allocation*/
    sendMsg= (MSG *) malloc(sizeof(MSG));
    if (sendMsg ==NULL) errx(1, "Memory allocation failed");

    strcpy(sendMsg->data, Mess);

    /*int RttSend(RttThreadId, void *, unsigned int, void *, unsigned int *)*/
    temp= RttSend(RTTPid, msg,*sendLen, receiveMsg,recieveLen);    
}

void RttMonWait(int CV){

    int temp;
    char Mess[] = "wait";

    /* memory allocation*/
    sendMsg= (MSG *) malloc(sizeof(MSG));
    if (sendMsg ==NULL) errx(1, "Memory allocation failed");

    strcpy(sendMsg->data, Mess);

    /*int RttSend(RttThreadId, void *, unsigned int, void *, unsigned int *)*/
    temp= RttSend(RTTPid, msg, *sendLen, receiveMsg,recieveLen);    


}
void RttMonSignal(int CV){

    int temp;
    char Mess[] = "signal";

    /* memory allocation*/
    sendMsg= (MSG *) malloc(sizeof(MSG));
    if (sendMsg ==NULL) errx(1, "Memory allocation failed");

    strcpy(sendMsg->data, Mess);

    /*int RttSend(RttThreadId, void *, unsigned int, void *, unsigned int *)*/
    temp= RttSend(RTTPid, msg, *sendLen, receiveMsg,recieveLen);
}

void MonServer() {

    int message, monBusy, reply;
    char replyMess[] = "server";

    /* memory allocation*/
    msg= (MSG *) malloc(sizeof(MSG));
    if (msg ==NULL) errx(1, "Memory allocation failed");
    
    monBusy=0;
    
    while (1){
        /* memory allocation*/
        senderPid=(RttThreadId *) malloc(sizeof(RttThreadId)); 
        if (senderPid==NULL) errx(1, "Memory allocation failed for senderPid");
    
        /* recieve message*/
        message=  RttReceive(senderPid, msg, recieveLen);
        if (message != 0) errx(1, "ERROR: RttRecieve");

        /*Enter */

        if (strcmp(msg ->data , "enter") ==0){
            if (monOccu){
                ListInsert(enterQueue, senderPid);
            } else {
                monOccu =1;
                RttReply (*senderPid, replyMess,*recieveLen );
                free (senderPid);
            }

        } else if (strcmp(msg ->data , "leave") ==0){
            /* reply for every case that they have reached server*/
            RttReply (*senderPid, replyMess,*recieveLen );
            free (senderPid);

            if (ListCount(urgentQueue) !=0) {
                takeOffPid= (RttThreadId *) ListTrim(urgentQueue);
                RttReply (*takeOffPid, replyMess,*recieveLen );
                free (takeOffPid);
            } else if (ListCount(enterQueue) !=0) {
                takeOffPid= (RttThreadId *) ListTrim(enterQueue);
                RttReply (*takeOffPid, replyMess,*recieveLen );
                free (takeOffPid);
            } else {
                monBusy =0;
            }
            
        }else if (strcmp(msg ->data , "wait") ==0){

        } else if (strcmp(msg ->data , "signal") ==0){

        }

    }
}



    /*
 *for my refrence

int RttSend(RttThreadId, void *, unsigned int, void *, unsigned int *);
int RttMsgWaits();
int RttReceive(RttThreadId *, void *, unsigned int *);
int RttReply(RttThreadId, void *, unsigned int);
int RttCreate(RttThreadId*,void(*)(),size_t, char *,void *,RttSchAttr, int);
int RttP(RttSem);
int RttV(RttSem);
 */

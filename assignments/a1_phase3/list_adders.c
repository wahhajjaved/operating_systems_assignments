/*
 *@author Wahhaj Javed, muj975, 11135711
 *@author Nakhba Mubashir, epl482, 11317060
 *@date 2024-09-16
 */


#include "list.h"
int nodesNum=0;
int listNum=0;
LIST *listDict= NULL; /* dict of lists*/
NODE *nodeDict= NULL; /* dict of all the nodes*/
LIST *aviableList=NULL;
NODE *aviableNode=NULL;


void Increse_node_Memory(){
    NODE *newNodeDict;
    int i;
    Num =MIN_NODE*2;
    newNodeDict=realloc(nodeDict, (Num * sizeof(LIST)));
    nodeDict=newNodeDict;
    /* initialize the new list*/

    for (i=MIN_NODE; i< Num; i++){
        nodeDict[i].next= &nodeDict[i+1];
        if (i==MIN_NODE){
            nodeDict[i].prev=NULL;
        }
        else {
            nodeDict[i].prev= &nodeDict[i-1];
        }

    
    }
    nodeDict[MIN_NODE-1].next= NULL;
}


LIST *ListCreate(){
    LIST *newList;
    if (listDict == NULL){
        int i;
        /* Allocating memory */
        listDict= (LIST*) malloc ((MIN_LIST) * sizeof(LIST));
        if (listDict ==NULL) errx(1, "ERROR: MEMORY ALLOCATION FAILED");
    
        nodeDict= (NODE*) malloc ((MIN_NODE) * sizeof(NODE));
        if (nodeDict ==NULL) errx(1, "ERROR: MEMORY ALLOCATION FAILED ");
    
        /* initialization */
        aviableList=&listDict[0];
        aviableNode=&nodeDict[0];

        for ( i=0; i<(MIN_LIST); i++){
            listDict[i].size=0;
            listDict[i].nextfreeList= &listDict[i+1];
         }
   
        listDict[i].nextfreeList= NULL; /*last*/

    for ( i=0; i<(MIN_NODE-1); i++){
        nodeDict[i].next= &nodeDict[i+1];
        if (i==0) nodeDict[i].prev= NULL;
        else {
             nodeDict[i].prev= &nodeDict[i-1];
        }
    }
    nodeDict[i].next= NULL; /*last*/
    }
    if (aviableList==NULL) {
        printf("ERROR:no aviableList\n");
        return NULL;}

    /*get new list and initilize it */
    newList= aviableList;
    aviableList= newList-> nextfreeList;
    newList-> nextfreeList= NULL;
    
    newList -> head= NULL;
    newList -> tail= NULL;
    newList -> curser= NULL;
    newList -> size= 0;

    return newList;
}


int ListAdd(LIST *list,void *item){
    NODE *newNode;
/*    
  if the List struct pointer is not right*/
    if (list == NULL) {
        printf("ERROR: list is NULL \n");
        return -1;
    }
    if (item == NULL){
        printf("ERROR: item is NULL");
        return -1;   }
    if (nodeNums == MIN_NODE){
        Increse_node_Memory();
    }

    /*get an unused node  */
    newNode = aviableNode;
    aviableNode = aviableNode-> next; 
    nodesNum++;   
    
    /*initialize and add to list*/
    newNode-> item = item;
    newNode-> next = NULL;
    newNode-> prev = NULL;
    
    if (list->size==0){ /* if list is empty */
        newNode-> next =NULL;
        list-> head = newNode;
        list-> tail = newNode;
        list-> curser = newNode;
    }
    else if (list->curser ==list->tail){ /*curser at tail */
        newNode->prev =list->tail;
        list->tail->next =newNode;
        list->tail=newNode;
        }
    else if (list->curser!=NULL&&list->curser->next!=NULL)
       { newNode->prev = list->curser;
        newNode->next = list->curser->next;
        list->curser->next->prev=newNode;
        list->curser->next=newNode;
        }
    else { printf("ERROR: wrong curser\n");
    }
    list->curser=newNode;
    list->size++;

    return 0;

}
int ListInsert(LIST *list,void *item){
    NODE *newNode;
     /* if the List struct pointer is not right*/
    if (list == NULL) {
        printf("ERROR: list is NULL \n");
        return -1;
    }
    if (item == NULL){
        printf("ERROR: item is NULL");
        return -1;
    }
    if (nodeNums == MIN_NODE){
        Increse_node_Memory();
    }

    /*get an unused node  */
    newNode = aviableNode;
    aviableNode = aviableNode-> next;    
    nodesNum++;

    /*initialize and add to list*/
    newNode-> item=item;
    newNode-> next=NULL;

    if (list->size==0){ /* if list is empty */
        newNode-> next =NULL;
        list-> head= newNode;
        list-> tail= newNode;
    }
    else if (list->curser ==list->head){ /*curser at head */
        newNode->next =list->head;
        list->head->prev =newNode;
        list->head=newNode;
        }
    else{
        newNode->prev=list->curser->prev;
        newNode->next=list->curser;
        list->curser->prev->next=newNode;
        list->curser->prev=newNode;
        }
    list->curser = newNode;
    list->size++;

    return 0;
}

int ListAppend(LIST *list, void *item){
    NODE *newNode; 
    /* if the List struct pointer is not right*/
    if (list == NULL) {
        printf("ERROR: list is NULL \n");
        return -1;
    }
    if (item == NULL){
        printf("ERROR: item is NULL");
        return -1;
    }
        if (nodeNums == MIN_NODE){
        Increse_node_Memory();
    }

    /*get an unused node  */
    newNode = aviableNode;
    aviableNode = aviableNode-> next;    
    nodesNum++;

    /*initialize and add to list*/
    newNode-> item = item;
    newNode-> next = NULL;

    if (list->size==0){ /* if list is empty */
        newNode-> prev = NULL;
        list-> head= newNode;
        list-> tail= newNode;
    }
    else { /* list not empty */
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail=newNode;
        }
    list->curser=newNode;
    list->size++;

    return 0;


}
int ListPrepend(LIST *list,void *item){
    NODE *newNode;
     /* if the List struct pointer is not right*/
    if (list == NULL) {
        printf("ERROR: list is NULL \n");
        return -1;
    }
    if (item == NULL){
        printf("ERROR: item is NULL");
        return -1;
    }
        if (nodeNums == MIN_NODE){
        Increse_node_Memory();
    }
        /*get an unused node  */
    newNode = aviableNode;
    aviableNode = aviableNode-> next;    
    nodesNum++;

    /*initialize and add to list*/
    newNode-> item=item;
    newNode-> next=NULL;

    if (list->size==0){ /* if list is empty */
        newNode-> next =NULL;
        list-> head= newNode;
        list-> tail= newNode;
    }
    else { /* list not empty */
        newNode->next =list->head;
        list->head->prev =newNode;
        list->head=newNode;
        }
    list->curser=newNode;
    list->size++;

    return 0;
}

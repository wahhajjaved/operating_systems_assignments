/*
 *@author Wahhaj Javed, muj975, 11135711
 *@author Nakhba Mubashir, epl482, 11317060
 *@date 2024-09-16
 */


#include "list.h"
int nodeNum=0;
int listNum=0;

LIST *listDict= NULL; /* dict of lists*/
NODE *nodeDict= NULL; /* dict of all the nodes*/
LIST *aviableList=NULL;
NODE *aviableNode=NULL;


void Increse_node_Memory(){
    NODE *newNodeDict;
    int i, Num;
    Num = MIN_NODES *2;

    newNodeDict=realloc(nodeDict, (Num * sizeof(NODE)));
    if (newNodeDict ==NULL){
            errx(1, "ERROR: MEMORY ALLOCATION FAILED\n");
            return ;
    }
    nodeDict=newNodeDict;
    /* initialize the new list*/

    for (i=MIN_NODES; i< Num; i++){
        nodeDict[i].next= &nodeDict[i+1];
        if (i==MIN_NODES){
            nodeDict[i].prev=NULL;
        }
        else {
            nodeDict[i].prev= &nodeDict[i-1];
        }
    }
    nodeDict[MIN_NODES-1].next= NULL;
    aviableNode =&nodeDict[MIN_NODES];
}


LIST *ListCreate(){
    LIST *newList;
    
    if (listDict == NULL){
        int i;
        /* Allocating memory */
        listDict= (LIST*) malloc ((MIN_LISTS) * sizeof(LIST));
        if (listDict ==NULL) {
            errx(1, "ERROR: MEMORY ALLOCATION FAILED\n");
            return NULL;}
        nodeDict= (NODE*) malloc ((MIN_NODES) * sizeof(NODE));
        if (nodeDict ==NULL) {
            errx(1, "ERROR: MEMORY ALLOCATION FAILED\n ");
            return NULL;
        }
        /* initialization */
        aviableList=&listDict[0];
        aviableNode=&nodeDict[0];

        for ( i=0; i<(MIN_LISTS); i++){
            listDict[i].size=0;
 
            if (i == MIN_LISTS - 1) {
                listDict[i].nextfreeList = NULL;
            } else {
                listDict[i].nextfreeList = &listDict[i + 1];
                }
         }
        for ( i=0; i<(MIN_NODES-1); i++){
            nodeDict[i].next= &nodeDict[i+1];
            
            if (i==0){
                 nodeDict[i].prev= NULL;
            }
            else {
             nodeDict[i].prev= &nodeDict[i-1];
            }
        }
        nodeDict[MIN_NODES-1].next= NULL; /*last*/
    }

    if (aviableList==NULL) {
        int i, Num;

        LIST *newListDict;
        Num= MIN_LISTS*2;

            /* doubling the memory  */
        newListDict =(LIST*) realloc(listDict,Num * sizeof(LIST));
        if (newListDict ==NULL) {
            errx(1, "ERROR: MEMORY ALLOCATION FAILED increasing memory \n");  
                          return NULL;
            }
        listDict=newListDict;

            /*INITIALIZE ALL NEW LISTS*/
         for ( i=MIN_LISTS; i<(Num); i++){
              listDict[i].size=0;
              listDict[i].nextfreeList= aviableList;
              aviableList= &listDict[i];
            }
    }

    if (aviableList==NULL) {
        /*printf("ERROR: no aviable list \n");*/
        return NULL;
    }
    /*get new list and initilize it */
    newList= aviableList;
    aviableList= newList-> nextfreeList;
    newList-> nextfreeList= NULL;
    
    newList -> head= NULL;
    newList -> tail= NULL;
    newList -> curser= NULL;
    newList -> size= 0;

    listNum++;
    return newList;

}

int ListAdd(LIST *list,void *item){
    NODE *newNode;
/*    
  if the List struct pointer is not right*/
    if (list == NULL) {
      /*  printf("ERROR: list is NULL \n");*/
        return -1;
    }
    if (item == NULL){
        /*printf("ERROR: item is NULL");*/
        return -1;   
    }
    if (aviableNode ==NULL){
        /*printf("ERROR: no aviabkle node");*/
        return -1;   }

    if (nodeNum == MIN_NODES){
        Increse_node_Memory();
    }
    /*get an unused node  */
    newNode = aviableNode;
    aviableNode = aviableNode-> next; 
    nodeNum++;   
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
       /* printf("ERROR: list is NULL \n");*/
        return -1;
    }
    if (item == NULL){
        /*printf("ERROR: item is NULL");*/
        return -1;
    }
    if (nodeNum == MIN_NODES){
        Increse_node_Memory();
    }

    /*get an unused node  */
    newNode = aviableNode;
    aviableNode = aviableNode-> next;    
    nodeNum++;

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
        /*printf("ERROR: list is NULL \n");*/
        return -1;
    }
    if (item == NULL){
       /* printf("ERROR: item is NULL");*/
        return -1;
    }
    if (nodeNum == MIN_NODES){
        Increse_node_Memory();
    }

    /*get an unused node  */
    newNode = aviableNode;
    aviableNode = aviableNode-> next;    
    nodeNum++;

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
        /*printf("ERROR: list is NULL \n");*/
        return -1;
    }
    if (item == NULL){
        /*printf("ERROR: item is NULL");*/
        return -1;
    }
    if (nodeNum == MIN_NODES){
        Increse_node_Memory();
    }
        /*get an unused node  */
    newNode = aviableNode;
    aviableNode = aviableNode-> next;    
    nodeNum++;

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

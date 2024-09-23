/*
 *@author Wahhaj Javed, muj975, 11135711
 *@author Nakhba Mubashir, epl482, 11317060
 *@date 2024-09-16
 */


#include "list.h"
int nodesNum;
int listNum;
LIST *listDict= NULL; /* dict of lists*/
NODE *nodeDict= NULL; /* dict of all the nodes*/
LIST *aviableList=NULL;
NODE *aviableNode=NULL;

/*
 *Allocatingand initializing  memory for list
 */
void listInit(void){
    int i;

    /* Allocating memory */
    listDict= (LIST*) malloc ((MIN_LIST) * sizeof(LIST));
    if (listDict ==NULL) errx(1, "ERROR: MEMORY ALLOCATION FAILED"); 

    nodeDict= (NODE*) malloc ((MIN_NODE) * sizeof(NODE));
    if (nodeDict ==NULL) errx(1, "ERROR: MEMORY ALLOCATION FAILED "); 

    /* initialization */
     aviableList=&listDict[0];
     aviableNode=&nodeDict[0];
    
    for ( i=0; i<(MIN_LIST-1); i++){
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


void Increse_List_Memory(){
    LIST newListDict;
    int i;
    listNum *=2;
    
    newListDict= realloc(listDict,(listNum*2 * sizeof(LIST));

    /* initialize the new list*/

    for (i=(listNum/2); i<listNum; i++){
        listDict[i].size=0;
    }
    
}

void Increse_node_Memory(){
    int i;
    nodeNum *=2;
    nodeDict= (LIST*) malloc ((listNum*2) * sizeof(LIST));

    /* initialize the new list*/

    aviableNode= NULL;
    for (i=nodeDict-1; i>= nodeDict; i--){
        nodeDict[i].next= aviableNode;
        aviableNode= &nodeDict[i];
    }
    
}

NODE *new_node(){
    NODE *newNode;


    newNode= aviableNode;
    aviableNode= aviableNode-> next;
    return newNode;

}

LIST *new_list(){
    LIST *newList;
    
    if (aviableList==NULL) Increse_List_Memory();

    newList= aviableList;
    aviableList= newList-> nextfreeList;
    newList-> nextfreeList= NULL;
    return newList;

}


LIST *ListCreate(){

    LIST *newList;

    if (listDict == NULL){
        listInit(); 
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
    /* check if the list size is less than max, or node is less than max
    if (list-> size <MAX_LIST_SIZE || nodesNum > MAX_NODE ){
        printf("ERROR: list is full or max number of nodes have been reached");
        return -1;

    }*/
    if (item == NULL){
        printf("ERROR: item is NULL");
        return -1;   }

    /*get an unused node  */
    newNode =new_node();
    if (newNode ==NULL) return -1;
    
    /*initialize and add to list*/
    newNode-> item=item;
    newNode-> next=NULL;
    newNode-> prev=NULL;
    
    if (list->size==0){ /* if list is empty */
        newNode-> next =NULL;
        list-> head= newNode;
        list-> tail= newNode;
        list-> curser= newNode;
    }
    else if (list->curser ==list->tail){ /*curser at tail */
        newNode->prev =list->tail;
        list->tail->next =newNode;
        list->tail=newNode;
        }
    else if (list->curser!=NULL&&list->curser->next!=NULL)
       { newNode->prev=list->curser;
        newNode->next=list->curser->next;
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
    /* check if the list size is less than max, or node is less than max
    if (list-> size <MAX_LIST_SIZE || nodesNum > MAX_NODE ){
        printf("ERROR: list is full or max number of nodes have been reached");
        return -1;
    }*/
    if (item == NULL){
        printf("ERROR: item is NULL");
        return -1;
    }

    /*get an unused node  */
    newNode=new_node();
    if (newNode ==NULL) return -1;

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
    list->curser=newNode;
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
    /* check if the list size is less than max, or node is less than max
    if (list-> size <MAX_LIST_SIZE || nodesNum > MAX_NODE ){
        printf("ERROR: list is full or max number of nodes have been reached");
        return -1;
    }*/
    if (item == NULL){
        printf("ERROR: item is NULL");
        return -1;
    }

    /*get an unused node  */
    newNode=new_node();
    if (newNode ==NULL) return -1;

    /*initialize and add to list*/
    newNode-> item=item;
    newNode-> next=NULL;

    if (list->size==0){ /* if list is empty */
        newNode-> prev =NULL;
        list-> head= newNode;
        list-> tail= newNode;
    }
    else { /* list not empty */
        newNode->prev =list->tail;
        list->tail->next =newNode;
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
    /* check if the list size is less than max, or node is less than max
    if (list-> size <MAX_LIST_SIZE || nodesNum > MAX_NODE ){
        printf("ERROR: list is full or max number of nodes have been reached");
        return -1;
    }*/
    if (item == NULL){
        printf("ERROR: item is NULL");
        return -1;
    }
        /*get an unused node  */
    newNode=new_node();
    if (newNode ==NULL) return -1;

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

void ListConcat(LIST *list1, LIST *list2){
     /* if the List struct pointer is not right*/
    if (list1 == NULL || list2== NULL) {
        printf("ERROR: list1 OR list2 is NULL \n");
        return ;
    }
   /*TODO */
}

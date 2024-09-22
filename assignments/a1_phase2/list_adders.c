/*
 *@author Wahhaj Javed, muj975, 11135711
 *@author Nakhba Mubashir, epl482, 11317060
 *@date 2024-09-16
 */


#include "list.h"
int nodesNum;
int listNum;
LIST *listDict= NULL; /* dict of lists*/
NODE *NodeDict= NULL; /* dict of all the nodes*/
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

    NodeDict= (NODE*) malloc ((MIN_NODE) * sizeof(NODE));
    if (listNode ==NULL) errx(1, "ERROR: MEMORY ALLOCATION FAILED "); 

    /* initialization */
     aviableList=&listDict[0];
     aviableNode=&nodeDict[0];
    
    for ( i=0; i<(MIN_LIST-1); i++){
        listDict[i].size=0;
        listDict[i].nextfreeList= &listDict[i+1];
    }
    listdict[i].nextfreeList= NULL; //last

    for ( i=0; i<(MIN_NODE-1); i++){
        listNode[i].next= &listNode[i+1];
        if (i==0) listNode[i].prev= NULL;
        else {
             listNode[i].prev= &listNode[i-1];
        }
    }
    listNode[i].next= NULL; //last
}


void Increse_List_Memory(){
    int i;
    listnum *=2
    listDict= (LIST*) malloc ((listnum*2) * sizeof(LIST));

    /* initialize the new list*/

    for (i=(listNum/2); i<listNum; i++){
        listDict[i].size=0;
    }
    
}


NODE *new_node(){
    NODE newNode;

    newNode= avaiableNode-> next;
    avaiableNode= avaiableNode-> next;
    return newNode;

}

LIST *new_list(){
    LIST newList;
    
    if (aviable_list==NULL) Increse_List_Memory();

    newList= avaiableList-> next;
    avaiableList= avaiableList-> nextfreeList;
    newList-> nextfreeList= NULL;
    return newList;

}


LIST *ListCreate(){
    /*TODO */
    LIST *newList;

    if (list_dict == NULL){
        listInit(); 
    }
    
    /*get new list and initilize it */
    newlist= aviable_list;
    aviable_list= newList-> nextfreeList;
    newList-> nextfreeList= NULL;
    
    newList -> head= NULL;
    newList -> tail= NULL;
    newList -> curser= NULL;
    newList -> size= 0;

    return newList;
}


int ListAdd(LIST *list,void *item){
     /* if the List struct pointer is not right*/
    if (list == NULL) {
        printf("ERROR: list is NULL \n");
        return -1;
    }
    /* check if the list size is less than max, or node is less than max*/
    if (list-> size <MAX_LIST_SIZE || nodes_num > MAX_NODE ){
        printf("ERROR: list is full or max number of nodes have been reached");
        return -1;

}    if (item == NULL){
        printf("ERROR: item is NULL");
        return -1;
    }

    newNode= avaiableNode-> next;
    avaiableNode= avaiableNode-> next;
    newNode-> item=item;
    newNode-> next=null;
    return -1;

}
int ListInsert(LIST *list,void *item){
     /* if the List struct pointer is not right*/
    if (list == NULL) {
        printf("ERROR: list is NULL \n");
        return -1;
    }
    /* check if the list size is less than max, or node is less than max*/
    if (list-> size <MAX_LIST_SIZE || nodes_num > MAX_NODE ){
        printf("ERROR: list is full or max number of nodes have been reached");
        return -1;
}
    if (item == NULL){
        printf("ERROR: item is NULL");
        return -1;
    }

   /*TODO */
    return -1;

}

int ListAppend(LIST *list, void *item){
     /* if the List struct pointer is not right*/
    if (list == NULL) {
        printf("ERROR: list is NULL \n");
        return -1;
    }
    /* check if the list size is less than max, or node is less than max*/
    if (list-> size <MAX_LIST_SIZE || nodes_num > MAX_NODE ){
        printf("ERROR: list is full or max number of nodes have been reached");
        return -1;
  }
  if (item == NULL){
        printf("ERROR: item is NULL");
        return -1;
    }

   /*TODO */
    return -1;

}
int ListPrepend(LIST *list,void *item){
     /* if the List struct pointer is not right*/
    if (list == NULL) {
        printf("ERROR: list is NULL \n");
        return -1;
    }
    /* check if the list size is less than max, or node is less than max*/
    if (list-> size <MAX_LIST_SIZE || nodes_num > MAX_NODE ){
        printf("ERROR: list is full or max number of nodes have been reached");
        return -1;
}
    if (item == NULL){
        printf("ERROR: item is NULL");
        return -1;
    }

   /*TODO */
    return -1;
}

void ListConcat(LIST *list1, LIST *list2){
     /* if the List struct pointer is not right*/
    if (list1 == NULL || list2== NULL) {
        printf("ERROR: list1 OR list2 is NULL \n");
        return ;
    }
   /*TODO */
}

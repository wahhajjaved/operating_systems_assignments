/*
 *@author Wahhaj Javed, muj975, 11135711
 *@author Nakhba Mubashir, epl482, 11317060
 *@date 2024-09-16
 */


#include "list.h"

int ListCount(LIST *list){
    /* if the List struct pointer is not right*/
    if (list == NULL) {
        printf("ERROR: list is NULL \n");
        return 0;
    }

    if (list-> count <0){
        printf("ERROR: list count cannot be negative");
    }
    /*TODO */
    return list->size;
}

void *ListFirst(LIST *list){
    /*TODO */
    /* if the List struct pointer is not right*/
    if (list == NULL) {
        printf("ERROR: list is NULL \n");
        return NULL;
    }
    /* check if the list is empty or not*/
    if (list-> count ==0){
        printf("ERROR: list empty");
        return NULL;
    }
    list->curser= list->head;
    return list->curser->item;
}


void *ListLast(LIST *list){
    /* if the List struct pointer is not right*/
    if (list == NULL) {
        printf("ERROR: list is NULL \n");
        return NULL;
    }
    /* check if the list is empty or not*/
    if (list-> count ==0){
        printf("ERROR: list empty");
        return NULL;
    } 
    list->curser=list->curser->tail;
    return list->curser->item;
}


void *ListNext(LIST *list){
    /* if the List struct pointer is not right*/
    if (list == NULL) {
        printf("ERROR: list is NULL \n");
        return NULL;
    }
    /* check if the list is empty or not*/
    if (list-> count ==0){
        printf("ERROR: list empty");
        return NULL;
    }

    /* check if the curser is not list last*/
    if (list -> curser == list -> tail) {
        printf("ERROR: curser is list tail");
        return NULL;
    }
    list->curser=list->curser->next;
    return list->curser->item;

}

void *ListPrev(LIST *list){
    /* if the List struct pointer is not right
    */
    if (list == NULL) {
        printf("ERROR: list is NULL \n");
        return NULL;
    }
    /* check if the list is empty or not*/
    if (list-> count ==0){
        printf("ERROR: list empty");
        return NULL;
    }
    
    /* check if the curser is not list head*/
    if (list -> curser == list -> head) {         
        printf("ERROR: curser is list tail");
        return NULL;
    }
    list->curser=list->curser->prev;
    return list->curser->item;

}

void *ListCurr(LIST *list){
    /* if the List struct pointer is not right*/
    if (list == NULL) {
        printf("ERROR: list is NULL \n");
        return NULL;
    }
    /* check if the list is not empty */
    if (list-> count ==0){
        printf("ERROR: list empty");
        return NULL;
    }
    return list->curser->item;

}

void *ListSearch(LIST *list,COMPARATOR *comparator,void *comparisonArg){
    /* if the List struct pointer is not right*/
    if (list == NULL||comparator ==NULL || comparisonArg == NULL ) {
        printf("ERROR: one of the arguments is NULL \n");
        return NULL;
    }
    /* check if the list is empty or not*/
    if (list-> count ==0){
        printf("ERROR: list empty");
        return NULL;
    }    


    /*TODO */
    return NULL;
}


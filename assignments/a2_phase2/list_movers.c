/*
 *@author Wahhaj Javed, muj975, 11135711
 *@author Nakhba Mubashir, epl482, 11317060
 *@date 2024-09-16
 *@editted 
 */


#include "list.h"

int ListCount(LIST *list){
    /* if the List struct pointer is not right*/
    if (list == NULL) {
        errx(1,"ERROR: list is NULL \n");
        return 0;
    }

    if (list-> size <0){
        err(1,"ERROR: list count cannot be negative\n");
    }
    return list->size;
}

void *ListFirst(LIST *list){
    /* if the List struct pointer is not right*/
    if (list == NULL) {
      /*  printf("ERROR: list is NULL \n");*/
        return NULL;
    }
    /* check if the list is empty or not*/
    if (list-> size ==0){
        return NULL;
    }
    list->curser= list->head;
    return list->curser->item;
}


void *ListLast(LIST *list){
    /* if the List struct pointer is not right*/
    if (list == NULL) {
       /* printf("ERROR: list is NULL \n");*/
        return NULL;
    }
    /* check if the list is empty or not*/
    if (list-> size ==0){
        return NULL;
    } 
    list->curser=list->tail;
    return list->curser->item;
}


void *ListNext(LIST *list){
    /* if the List struct pointer is not right*/
    if (list == NULL) {
       /* printf("ERROR: list is NULL \n");*/
        return NULL;
    }
    /* check if the list is empty or not*/
    if (list-> size ==0){
        return NULL;
    }

    /* check if the curser is not list last*/
    if (list -> curser == list -> tail) {
        /*printf("ERROR: curser is list tail\n");*/
        return NULL;
    }
    list->curser=list->curser->next;
    return list->curser->item;
}

void *ListPrev(LIST *list){
    /* if the List struct pointer is not right
    */
    if (list == NULL) {
       /* printf("ERROR: list is NULL \n");*/
        return NULL;
    }
    /* check if the list is empty or not*/
    if (list-> size ==0){
        return NULL;
    }
    
    /* check if the curser is not list head*/
    if (list -> curser == list -> head) {         
       /* printf("ERROR: curser is list tail\n");*/
        return NULL;
    }
    list->curser=list->curser->prev;
    return list->curser->item;

}

void *ListCurr(LIST *list){
    /* if the List struct pointer is not right*/
    if (list == NULL) {
       /* printf("ERROR: list is NULL \n");*/
        return NULL;
    }
    /* check if the list is not empty */
    if (list-> size ==0){
        /*printf("ERROR: list empty\n");*/
        return NULL;
    }
    return list->curser->item;

}

void *ListSearch(LIST *list,COMPARATOR comparator,void *comparisonArg){
    /* if the List struct pointer is not right*/
    if (list == NULL||comparator ==NULL || comparisonArg == NULL ) {
        /*printf("ERROR: one of the arguments is NULL \n");*/
        return NULL;
    }
    /* check if the list is empty or not*/
    if (list-> size ==0){
       /* printf("ERROR: list empty\n");*/
        return NULL;
    }    

    while (1){
        if ((*comparator)(list->curser->item, comparisonArg)==1) {
            return list->curser->item;
            }
        
        if (list->curser ==list->tail){
            return NULL;
            }
        
        list-> curser= list->curser->next;
    }
}


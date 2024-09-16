/* Authors
 *Wahhaj Javed, muj975, 11135711
 *Nakhba Mubashir, epl482, 11317060
 *
 */

#include "list.h"
LIST *ListCreate(){
    /*TODO */
    return NULL;
}

int ListCount(LIST *list){
    // if the List struct pointer is not right
    if (list == NULL) {
        printf("ERROR: list is NULL \n");
        return NULL;
    }

    if (list-> count <0){
        printf("ERROR: list count cannot be negative");
    }
    /*TODO */
    return 0;
}

void *ListFirst(LIST *list){
    /*TODO */
    // if the List struct pointer is not right
    if (list == NULL) {
        printf("ERROR: list is NULL \n");
        return NULL;
    }
    // check if the list is empty or not
    if (list-> count ==0){
        printf("ERROR: list empty");
        return NULL;
    }

    return NULL;
}


void *ListLast(LIST *list){
    // if the List struct pointer is not right
    if (list == NULL) {
        printf("ERROR: list is NULL \n");
        return NULL;
    }
    // check if the list is empty or not
    if (list-> count ==0){
        printf("ERROR: list empty");
        return NULL;
    } 

   /*TODO */
    return NULL;
}


void *ListNext(LIST *list){
    // if the List struct pointer is not right
    if (list == NULL) {
        printf("ERROR: list is NULL \n");
        return NULL;
    }
    // check if the list is empty or not
    if (list-> count ==0){
        printf("ERROR: list empty");
        return NULL;
    }

    // check if the curser is not list last
    if (list -> curser == list -> tail) {
        printf("ERROR: curser is list tail");
        return NULL;
    }
    /*TODO */
    return NULL;
}

void *ListPrev(LIST *list){
    // if the List struct pointer is not right
    if (list == NULL) {
        printf("ERROR: list is NULL \n");
        return NULL;
    }
    // check if the list is empty or not
    if (list-> count ==0){
        printf("ERROR: list empty");
        return NULL;
    }
    
    // check if the curser is not list head
    if (list -> curser == list -> head) {         
        printf("ERROR: curser is list tail");
        return NULL;
    }
    /*TODO */
    return NULL;
}

void *ListCurr(LIST *list){
    // if the List struct pointer is not right
    if (list == NULL) {
        printf("ERROR: list is NULL \n");
        return NULL;
    }
    // check if the list is not empty 
    if (list-> count ==0){
        printf("ERROR: list empty");
        return NULL;
    }

    /*TODO */
    return NULL;
}

void *ListSearch(LIST *list,COMPARATOR *comparator,void *comparisonArg){
    // if the List struct pointer is not right
    if (list == NULL||comparator ==NULL || comparisonArg == NULL ) {
        printf("ERROR: one of the arguments is NULL \n");
        return NULL;
    }
    // check if the list is empty or not
    if (list-> count ==0){
        printf("ERROR: list empty");
        return NULL;
    }    


    /*TODO */
    return NULL;
}


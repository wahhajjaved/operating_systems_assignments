/*
 *@author Wahhaj Javed, muj975, 11135711
 *@author Nakhba Mubashir, epl482, 11317060
 *@date 2024-09-16
 */

#include "list.h"

extern LIST *aviableList;
extern NODE *aviableNode;

void *ListRemove(LIST *list){
    NODE *curr_node;
    void *curr_item;

    /* if the List struct pointer is not right */
    if (list == NULL) { errx(1, "ERROR: list is NULL \n");}

    /* check if the list is empty or not */
    if (list-> size ==0){ errx(1, "ERROR: list empty");}

    removeNode= list->curser;
    curr_item= list->curser->item;
    if (list->curser == list->tail){
        if (list->size == 1){
            list->head = NULL;
            list->tail = NULL;
            list->curser = NULL;
        } 
        else {
            list->tail = list->curser->prev;
            list->curser->curser = NULL;
            list->tail->next = NULL;
            list->curser =list->tail;
        }
    }
    else if (list->curser == list->head){
        
    }
    else {
        list->curser->prev->next = list->curser->next;
        list->curser->next->prev = list->curser->prev;
        list->curser= list->curser->next;
        removeNode->next= NULL;
        removeNode->next= NULL;
    }
    list->size--;
    listnum--;

    removeNode->next= avaiableNode;
    avaiableNode = removeNode;
    return curr_item;
}

void ListFree(LIST *list, ITEMFREE *itemFree){

    /* if the List struct pointer is not right
    */
    if (list == NULL || itemFree == NULL) {
        printf("ERROR: list or itemfree is NULL \n");
        return ;
    }

    /* check if the list is empty or not
    */
    if (list-> size ==0){
        printf("ERROR: list empty");
        return ;
    }

   /*TODO */
}


void *ListTrim(LIST *list){

    /* if the List struct pointer is not right*/
    if (list == NULL) {
        printf("ERROR: list is NULL \n");
        return NULL;
    }

    /* check if the list is empty or not*/
    if (list-> size ==0){
        printf("ERROR: list empty");
        return NULL;
    }


    return NULL;
}


void ListConcat(LIST *list1, LIST *list2){
     /* if the List struct pointer is not right*/
    if (list1 == NULL || list2== NULL) {
        printf("ERROR: list1 OR list2 is NULL \n");
        return ;
    }
    if (list1 == list2) {
        errx(1, "ERROR: IN listConcat, both list are same");
    }

    /*list1 is empty and list2 not empty 
    * concatenate to an empty list */
    if (list1->size == 0 && list2->size !=0){
        list1->head = list2->head;
        list1->tail = list2->tail;
        list1->curser = list2->curser;
        list1->size = list2->size;
    }

    /* both  list1 and list2 are non empty*/
    if (list1->size !=0 && list2->size !=0){
        list1->tail->next = list2->head;
        list2->head->prev = list1->tail;
        list1->tail = list2->tail;
        list2->size += list2->size;
    }

    list2->size = 0;
    list2->head = NULL;
    list2->tail = NULL;
    list2->curser = NULL;

    listNum--;

    list2->nextfreeList = aviableList;
    aviableList = list2;
}


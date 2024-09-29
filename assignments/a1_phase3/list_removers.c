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
   /*TODO */
    return NULL;
}



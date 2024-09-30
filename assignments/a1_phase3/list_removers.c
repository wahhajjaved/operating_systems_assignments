/*
 *@author Wahhaj Javed, muj975, 11135711
 *@author Nakhba Mubashir, epl482, 11317060
 *@date 2024-09-16
 */

#include "list.h"

extern LIST *aviableList;
extern NODE *aviableNode;
extern int listNum;
extern int nodeNum;

void *ListRemove(LIST *list){
    NODE *removeNode;
    void *currItem;

    /* if the List struct pointer is not right */
    if (list == NULL) { errx(1, "ERROR: list is NULL \n");}

    /* check if the list is empty or not */
    if (list-> size ==0){ errx(1, "ERROR: list empty");}

    removeNode= list->curser;
    currItem= list->curser->item;
    if (list->curser == list->tail){
        if (list->size == 1){
            list->head = NULL;
            list->tail = NULL;
            list->curser = NULL;
        } 
        else {
            list->tail = list->curser->prev;
            removeNode->prev = NULL;
            list->tail->next = NULL;
            list->curser =list->tail;
        }
    }
    else if (list->curser == list->head){
        if (list->size == 1){
            list->head = NULL;
            list->tail = NULL;
            list->curser = NULL;
        } 
        else {
            list->tail = list->curser->prev;
            list->head->prev = NULL;
            removeNode->next = NULL;
            list->curser =list->head;
        }
    }
    else {
        list->curser->prev->next = list->curser->next;
        list->curser->next->prev = list->curser->prev;
        list->curser= list->curser->next;
        removeNode->next= NULL;
        removeNode->next= NULL;
    }
    list->size--;
    listNum--;

    removeNode->next= aviableNode;
    aviableNode = removeNode;
    return currItem;
}

void ListFree(LIST *list, ITEMFREE *itemFree){
    NODE *node;
    /* if the List struct pointer is not right
    */
    if (list == NULL || itemFree == NULL) {
        errx(1,"ERROR: list or itemfree is NULL \n");
    }

    /* check if the list is empty or not
    */
    if (list-> size ==0){
        printf("ERROR: list empty");
        return ;
    }

    while (node != NULL){
    node = node->next;
    (*itemFree)(node->item);
    nodeNum--;
    node->next = aviableNode;
    aviableNode = node;
    }

    list->head = NULL;
    list->tail = NULL;
    list->curser = NULL;
    list->size=0;
    nodeNum--;


}


void *ListTrim(LIST *list){
    NODE *removeNode;
    void *lastItem;

    /* if the List struct pointer is not right */
    if (list == NULL) { errx(1, "ERROR: list is NULL \n");}

    /* check if the list is empty or not */
    if (list-> size ==0){ errx(1, "ERROR: list empty");}

    removeNode = list->tail;
    lastItem = list->tail->item;
    
    if (list->size == 1){
        list->head = NULL;
        list->tail = NULL;
        list->curser = NULL;
    }
    else {
        list->tail = list->tail->prev;
        removeNode->prev = NULL;
        list->tail->next = NULL;
        list->curser =list->tail;
        
    }
    list->size--;
    listNum--;

    removeNode->next= aviableNode;
    aviableNode = removeNode;
    return lastItem;

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


/* Authors
 *Wahhaj Javed, muj975, 11135711
 *Nakhba Mubashir, epl482, 11317060
 *
 */

#include "list.h"
void *ListRemove(LIST *list){

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

void ListFree(LIST *list, ITEMFREE *itemFree){

    // if the List struct pointer is not right
    if (list == NULL || itemfree == NULL) {
        printf("ERROR: list or itemfree is NULL \n");
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


void *ListTrim(LIST *list){

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

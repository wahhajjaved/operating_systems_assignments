/*
 *@author Wahhaj Javed, muj975, 11135711
 *@author Nakhba Mubashir, epl482, 11317060
 *@date 2024-09-16
 */

#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <err.h>


#define MIN_LISTS 50
#define MIN_NODES 5000
/*
 * comparator pointer for the parameter for ListSearch()
 */
typedef int (COMPARATOR)(void *, void *);

/*
 * itemfree pointer used for the parameter to ListFree()
 */
typedef void (ITEMFREE)(void *);

/*int nodes_num;
*/
/*
 * STRUCT
 */
typedef struct node {
    void *item;
    struct node *next;
    struct node *prev;

} NODE;

typedef struct list {
    NODE *head;
    NODE *tail;
    NODE *curser;
    int size;
    struct list *nextfreeList;
} LIST;


/*
 * creates a new empty list and return its reference or Null if fails
 *
 * Parameter: none
 *
 * return :  refrence of empty list or NULL if fails
 */
LIST *ListCreate();

/*
 * it returns the number of items in the list
 *
 * Parameter: none
 *
 * Return: int size
 *
 */
int ListCount(LIST *list);

/*
 * returns a pointer to the first item in list and makes the first
 * item the current item.
 *
 * Parameter: List list:    struct List
 *
 * Return:
 *
 */
void *ListFirst(LIST *list);

/*
 * returns a pointer to the last item in list and makes the last item the
 * current one.
 *
 * Parameter: List list:    struct List
 *
 * Return:
 *
 */
void *ListLast(LIST *list);

/*
 * advances the list's current node by one, and returns a pointer to the new
 * current item. If this operation attempts to advances the current item
 * beyond the end of the list, a NULL pointer is returned.
 *
 * Parameter: List list:    struct List
 *
 * Return:
 *
 */
void *ListNext(LIST *list);

/*
 * backs up the list's current node by one, and returns a pointer to the new
 * current item.
 *
 * Parameter: List list:    struct List
 *
 * Return:
 *
 */
void *ListPrev(LIST *list);

/*
 * returns a pointer to the current item in list
 *
 * Parameter: List list:    struct List
 *
 * Return:
 *
 */
void *ListCurr(LIST *list);

/*
 * adds the new item to list directly after the current item,
 * and makes the new item the current item. If the current pointer is at the
 * end of the list, the item is added at the end.
 *
 * Parameter: List list:    struct List
 *            item:         item to be added
 *
 * Return: Returns 0 on success, -1 on failure.
 *
 */
int ListAdd(LIST *list,void *item);

/*
 * adds item to list directly before the current item, and makes the new item
 * the current one.
 *
 * Parameter: List list:    struct List
 *            item:         item to be added
 *
 * Return: Returns 0 on success, -1 on failure
 *
 */
int ListInsert(LIST *list,void *item);

/*
 * adds item to the end of list, and makes the new item the current
 * one. Returns 0 on success, -1 on failure.
 *
 * Parameter: List list:    struct List
 *            item:         item to be added
 *
 * Return:   Returns 0 on success, -1 on failure
 *
 */
int ListAppend(LIST *list, void *item);

/*
 * adds item to the start of list, and makes the new item the current
 * one. Returns 0 on success, -1 on failure.
 *
 * Parameter: LIST list: struct List
 *            item:      pointer to the item to be added
 *
 * Return:   Returns 0 on success, -1 on failure
 *
 */
int ListPrepend(LIST *list,void *item);

/*
 * Return current item and take it out of list. Make the next item
 * the current one.
 *
 * Parameter: LIST list: struct List
 *
 * Return:
 *
 */
void *ListRemove(LIST *list);

/*
 * add l2 to the end of l1, current pointer is current pointer of l2
 *
 * Parameter: List list1: struct List
 *            List list2: struct List
 *
 * Return:
 *
 */
void ListConcat(LIST *list1, LIST *list2);

/*
 * Delete list
 *
 * Parameter: LIST list:             struct List
 *            ITEMFREE itemFree:     item to be freed
 *
 * Return:
 *
 */
void ListFree(LIST *list, ITEMFREE itemFree);

/*
 * Return last item and take it out of list. The current pointer shall
 * be the new last item in the list.
 *
 * Parameter: LIST list:    struct List
 *
 * Return:
 *
 */
void *ListTrim(LIST *list);

/*
 * searches list starting at the current item until the end is reached
 * or a match is found.
 *
 * Parameter:  LIST List:                   struct list
 *             COMPARATOR *comparator:      to match
 *             *comparisonArg :             match with
 *
 * Return:
 *
 */
void *ListSearch(LIST *list,COMPARATOR comparator,void *comparisonArg);


#endif

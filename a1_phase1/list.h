/*
 *Authors
 *Wahhaj Javed, muj975, 11135711
 *Nakhba Mubashir, epl482, 11317060
 *
 */

#ifndef LIST_H
#define LIST_H

#include <stdlib.h> 


/*
 * Comparator pointer for the parameter for ListSearch() 
 */
typedef int (*COMPARATOR)(void *, void *);

/*
 * Itemfree pointer used for the parameter to ListFree()
 */
typedef void (*ITEMFREE)(void *);

struct LIST dictionary[MAX_LIST]

/*
 * STRUCT
 */
typedef struct node {
    void *value;
    Node *next;
    Node *prev;
} Node;

typedef struct list {
    Node *head;
    Node *tail
    Node storage;
    int size;
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
int ListCount(list);

/*
 * returns a pointer to the first item in list and makes the first
 * item the current item.
 *
 * Parameter: struct List
 *
 * Return: pointer to first item
 *
 */
void *ListFirst(list);

/*
 *
 * Parameter: struct List
 *
 * Return: 
 *
 */
void *ListLast(list);

/*
 *
 * Parameter: struct List
 *
 * Return: 
 *
 */
void *ListNext(list);

/*
 *
 * Parameter: struct List
 *
 * Return: 
 *
 */
void *ListPrev(list);

/*
 *
 * Parameter: struct List
 *
 * Return: 
 *
 */
void *ListCurr(list);

/*
 *
 * Parameter: struct List
 *
 * Return: 
 *
 */
int ListAdd(list, item);

/*
 *
 * Parameter: struct List
 *            item to be added
 *
 * Return: 
 *
 */
int ListInsert(list, item);

/*
 *
 * Parameter: struct List
 *            item to be added
 *
 * Return: 
 *
 */
int ListAppend(list, item);

/*
 *
 * Parameter: struct List
 *            item to be added
 *
 * Return: 
 *
 */
int ListPrepend(list, item);

/*
 *
 * Parameter: struct List
 *            item to be added
 *
 * Return: 
 *
 */
void *ListRemove(list);

/*
 *
 * Parameter: struct List
 *
 * Return: 
 *
 */
void ListConcat(list1, list2);

/*
 *
 * Parameter:struct List
 *            ITEMFREE itemFree: item to be freed
 *
 * Return: 
 *
 */
void ListFree(list, itemFree);

/*
 *
 * Parameter: struct List
 *
 * Return: 
 *
 */
void *ListTrim(list);

/*
 *
 * Parameter:  struct List
 *
 * Return: 
 *
 */
void *ListSearch(list, comparator, comparisonArg);


#endif

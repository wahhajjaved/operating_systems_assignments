/*
 *Authors
 *Wahhaj Javed, muj975, 11135711
 *Nakhba Mubashir, epl482, 11317060
 *
 */

#ifndef LIST_H
#define LIST_H

struct LIST dictionary[MAX_LIST]
typedef struct node {
    Node *value;
    Node *next;
    Node *prev;
} Node;

typedef struct list {
    Node *head;
    Node *tail
    Node storage;
    int size;
} LIST;

LIST *ListCreate();
int ListCount(list);
void *ListFirst(list);
void *ListLast(list);
void *ListNext(list);
void *ListPrev(list);
void *ListCurr(list);
int ListAdd(list, item);
int ListInsert(list, item);
int ListAppend(list, item);
int ListPrepend(list, item);
void *ListRemove(list);
void ListConcat(list1, list2);
void ListFree(list, itemFree);
void *ListTrim(list);
void *ListSearch(list, comparator, comparisonArg);


endif

/*
 *@author Wahhaj Javed, muj975, 11135711
 *@author Nakhba Mubashir, epl482, 11317060
 *@date 2024-09-16
 */

#include"list.h"


/* print list for testing*/
void Print_List(LIST *list);
void testItemFree(void *item);
int testComp(void *item1,void *item2 );


int main(void){
    LIST *L1, *L2, *L3, *L4, *LTest, *L5;
    int *I1, *I2, *I4, *I5, *Itemcheck, *I3;
    int a, b, d,c, e,  result, *cArg, i;
    int tests=0, testpassed=0;
    void *removedItem;
    int * resultPtr;
    a= 44;
    b=55;
    d=70;
    e=18;
    c=99;
    I1=&a;
    I2=&b;    
    I4=&d;
    I5=&e;
    I3=&c;

    printf("MIN_LIST= %d\n", MIN_LISTS);
    printf("MIN_NODES= %d\n", MIN_NODES);
    printf("____________TESTING PARTC: LIST LIBRARY_________\n");

    printf("______Testing_ListCreate()________\n");

    /* testing normal case: creating a list*/
    LTest= ListCreate();
    if (LTest ==NULL){
        printf("TEST CASE FAILED: ListCreate returned NULL on new list\n");
    }
    else {
        printf("TEST CASE SUCCESS: ListCreate() on new list\n");
    }

    /* testing normal case: creating several lists*/
    for (i=0; i<5; i++){
        LTest= ListCreate();
        if (LTest ==NULL){
            printf("TEST CASE FAILED: ListCreate returned NULL on several list: list %d\n", i+1);
        }
        else {
            printf("TEST CASE SUCCESS: ListCreate() on several list\n");
        }
    }

        
/*     testing egde case: creating several lists for doubling memory
*/
    printf("bonus marks\n");
    for (i=MIN_LISTS; i<9; i++){
        LTest= ListCreate();
        if (LTest ==NULL){
            printf("TEST CASE FAILED: ListCreate returned NULL AFTER DOUBLING: list %d\n", i+1);
        }
        else {
            printf("TEST CASE SUCCESS: ListCreate() after doubling\n");
        }
    }

    L1= ListCreate();
    L2= ListCreate();
    L3= ListCreate();
    L4= ListCreate();
    L5= ListCreate();
    

    /* testing with empty list*/

    printf("test:_________ Empty list_________\n");
    tests++;
    if (ListCount(L1) ==0){
        printf("ListCount() successful!! with empty \n");
        testpassed++;
    }else {
        printf("ListCount() FAILED! with empty \n");        
        printf("list count:%d\n",ListCount(L2));

    }

    tests++;
    if (ListFirst(L1) == NULL){
        printf("ListFirst() successful!! with empty \n");
        testpassed++;
    }else {
        printf("ListFirst() FAILED! with empty \n");
    }

    tests++;
    if (ListLast(L1) == NULL){
        printf("ListLast() successful!! with empty \n");
        testpassed++;
    }else {
        printf("ListLast() FAILED! with empty \n");
    }

    tests++;
    if (ListNext(L1) == NULL){
        printf("ListNext() successful!! with empty \n");
        testpassed++;
    }else {
        printf("ListNext() FAILED! with empty \n");
    }

    tests++;
    if (ListPrev(L1) == NULL){
        printf("ListPrev() successful!! with empty\n ");
        testpassed++;
    }else {
        printf("ListPrev() FAILED! with empty\n ");
    }

    tests++;
    if (ListCurr(L1) == NULL){
        printf("ListCurr() successful!! with empty\n ");
        testpassed++;
    }else {
        printf("ListCurr() FAILED! with empty\n ");
    }


    tests++;
    if (ListRemove(L1) == NULL){
        printf("ListRemove() successful!! with empty\n ");
        testpassed++;
    }else {
        printf("ListRemove() FAILED! with empty\n ");
    }

    tests++;
    if (ListTrim(L1) == NULL){
        printf("ListTrim() successful!! with empty\n ");
        testpassed++;
    }else {
        printf("ListTrim() FAILED! with empty\n ");
    }

    tests++;
    ListConcat(L1,L2);
    if (ListCurr(L1) == NULL){
        printf("ListConcat() successful!! with empty\n ");
        testpassed++;
    }else {
        printf("Listconcat() FAILED! with empty\n ");
    }


    cArg= I4;
    ListFirst(L1);
    tests++;
    resultPtr= (int*) ListSearch(L1, testComp,cArg);
    if (resultPtr==NULL){
        printf("ListSearch() sucessfull on finding an item in an empty list\n");
        testpassed++;
    } else {
        printf("ListSearch() Failed on finding an item in an empty list\n");
        printf("item to be seacrched: %d\n", *cArg);
        printf("item found: %d\n",*resultPtr);
    }

    printf("________ListADD()___________\n");
    printf("test: Empty list()\n");
    tests++;
    result=ListAdd(L1, I1);
    if (result !=0){
        printf("listAdd FAILED for empty list   \n");
        printf("list1=");
        Print_List(L1);
    }
    else {
        printf("ListAdd() successful for empty list!!\n");
        testpassed++;
    }

    printf("test: adding with one item \n");
    result=ListAdd(L1, I5);
    tests++;
    if (result !=0){
        printf("listAdd() FAILED  with one item.\n");
        printf("list1=");
        Print_List(L1);
    }
        else{
             printf("ListAdd() successful!! with one item\n");
             testpassed++;
        }
    ListAdd(L1, I2);
    ListAdd(L1, I1);   

    printf("test: adding with at tail \n");
    ListLast(L1);
    tests++;
    result=ListAdd(L1, I3);
    if (L1->tail->item !=I3){
        printf("listAdd() FAILED AT TAIL.\n");
        printf("list1=");
        Print_List(L1);
    }
        else {
            printf("ListAdd() successful!! with AT TAIL\n");
            printf("ListLast() successful!! tested with ListAdd(), curser was at last \n");
            testpassed++;
        }

    printf("test: adding with at head \n");
    ListFirst(L1);
    tests++;
    result=ListAdd(L1, I3);
    if (L1->head->next->item !=I3){
        printf("listAdd() FAILED after head.\n");
        printf("list1=");
        Print_List(L1);
    }
        else {
            printf("ListAdd() successful!! after head\n");
            printf("ListFirst() successful!! tested with ListAdd(),");
            printf(" curser was at start \n");
            testpassed++;
            }

    printf("test: adding at the middle \n");
    ListFirst(L1);
    ListNext(L1);
    ListNext(L1);
    tests++;
    result=ListAdd(L1, I3);
    if (L1->head->next->next->next->item !=I3){
        printf("listAdd() FAILED in the middle\n");
        printf("list1=");
        Print_List(L1);
    }
        else{
            printf("ListAdd() successful!! in the middle\n");
            printf("ListNext() successful!! tested with ListAdd(),");
            printf(" curser is where its supposed to be \n");
            testpassed++;
        }
    Print_List(L1);


    printf("test: adding with to a null list \n");
    result=ListAdd(NULL, I5);
    tests++;
    if (result !=-1){
        printf("listAdd() FAILED with NULL LIST.\n");
    }
    else {
        printf("ListAdd() successful!! with NULL list\n");
        testpassed++;
}
    
    printf("________ListInsert()___________\n");
    printf("test: inserting with one item \n");
    result=ListInsert(L2, I2);
    tests++;
    if (result !=0){
        printf(" ListInsert FAILED on empty list.\n");
        printf("list2=");
        Print_List(L2);
    }
    else {
        printf("ListInsert() successful on empty list\n");
        testpassed++;
        }

   /*listcount after item is added to empty list*/ 
    printf("test: listcount when list is not empty and have one item" );
    tests++;
    if (ListCount(L2) ==1){
        printf("ListCount() successful!! with one item in empty ");
        testpassed++;
    }
    else {
        printf("ListCount() FAILED! with empty ");
        printf("list count:%d\n",ListCount(L2));}
    
    printf("test: inserting with one item \n");
    result=ListInsert(L2, I5);
    tests++;
    if (result !=0){
        printf("listInsert() FAILED with one item.\n");
        printf("list2=");
        Print_List(L2);
    }
        else{
             printf("ListInsert() successful!! with one item\n");
             testpassed++;
        }
    ListInsert(L2, I2);
    ListInsert(L2, I1);
    printf("test: inserting at tail \n");
    ListLast(L2);
    tests++;
    result=ListInsert(L2, I3);
    if (L2->tail->prev->item != I3){
        printf("listInsert() FAILED AT TAIL.\n");
        printf("list2=");
        Print_List(L2);
    }
        else {
            printf("ListInsert() successful!! with AT TAIL\n");
            printf("ListLast() successful!! tested with ListInsert(), curser was at last \n");
            testpassed++;
        }

    printf("test: insert with at head \n");
    ListFirst(L2);
    tests++;
    result=ListInsert(L2, I3);
    if (L2->head->item !=I3){
        printf("listAdd() FAILED after head.\n");
        printf("list2=");
        Print_List(L2);
    }
        else {
            printf("ListInsert() successful!! after head\n");
            printf("ListFirst() successful!! tested with ListInsert(),");
            printf(" curser was at start \n");
            testpassed++;
            }



    printf("test: inserting at the middle \n");
    ListLast(L2);
    ListPrev(L2);
    tests++;
    result=ListInsert(L2, I3);
    if (L2->head->prev->prev->item !=I3){
        printf("listinsert() FAILED in the middle\n");
        printf("list2=");
        Print_List(L2);
    }
        else{
            printf("ListInsert() successful!! in the middle\n");
            printf("ListPrev() successful!! tested with ListInsert(),");
            printf(" curser is where its supposed to be \n");
            testpassed++;
        }
    Print_List(L2);
       /*listcount after item is added to empty list*/
    printf("test: listcount when list is not empty" );
    tests++;
    if (ListCount(L2) ==7){
        printf("ListCount() successful!! with items in list ");
        testpassed++;
    }
    else {
        printf("ListCount() FAILED! with empty ");
        printf("list count:%d\n",ListCount(L2));}


    printf("test: inserting with to a null list \n");
    result=ListInsert(NULL, I5);
    tests++;
    if (result !=-1){
        printf("listInsert() FAILED with NULL LIST.\n");
    }
    else {
        printf("ListInsert() successful!! with NULL list\n");
        testpassed++;
    }    
	

    printf("________ListAppend()___________\n");
    printf("test: Empty list()\n");
    tests++;
	result=ListAppend(L3, I1);
    if (result !=0){
        printf("listAppend FAILED to an empty list.\n");
        printf("list3=");
        Print_List(L3);
    }
    else {
        printf("ListAppend() successful!!\n");
        testpassed++;
        }

    printf("test: non Empty list()\n");
    tests++;
    ListFirst(L2);
    ListAppend(L2, I3);
    if (result !=0 && L2->tail->item !=I3){
        printf(" listAppend() FAILED when there are multiple items.\n");
        printf("list2=");
        Print_List(L2);
    }
    else {
        printf("ListAppend() successful!! when there are multiple items\n");
        testpassed++;
    }

    tests++;
    if (ListCurr(L2) !=I3){
        printf(" listCurr with ListAppend() FAILED when there are multiple");
        printf(" items.\n");
        printf("list2=");
        Print_List(L2);
    }
    else {
        printf("ListCurr() successful!! with ListAppend() when");
        printf(" there are multiple item \n");
        testpassed++;
    }

    printf("________ListPrepend()___________\n");
    printf("Test: Empty list()\n");
    tests++;
    result=ListPrepend(L4, I4);
    if (result !=-0){ 
        printf("listPrepend FAILED on an empty list.\n");
        printf("list4=");
        Print_List(L4);
    }
    else {
        printf("ListPrepend() successful!! on empty list\n");
        testpassed++;
    }

    printf("test: non Empty list() and curser at random place\n");
    ListPrepend(L4, I1);
    ListPrepend(L4, I3);
    ListLast(L4);
    ListPrev(L4);
    tests++;
    result=ListPrepend(L4, I2);
    if (result !=0 && L2->head->item !=I2  ){
        printf("listPrepend() FAILED on non empty list  and curser\
 at random place .\n");
        printf("list4=");
        Print_List(L4);
    }
    else {
        printf("ListPrepend() successful!! on non empty list and curser at\
 random place\n");
            testpassed++;
    }
    Print_List(L4);

    /*using the listLast to go to list's tail and test ListNext and Listprev */
    printf("----------------ListNext()_and ListPrev()____________\n");
    printf("testing ListPrev when current node is list's tail\n");
    tests++;
    ListLast(L2);
    ListPrev(L2);
    if (L2->curser->item != L2->tail->prev->item){
        printf(" listPrev FAILED when current node is list's tail\n");
        printf("list2=");
        Print_List(L2);
        printf("curser item:%d  expected item:%d\n ",
*(int *) L2->curser->item,*(int *) L2->tail->prev->item);
    }
    else {
        printf("ListPrev() successful!! when current node is list's tail\n");
        testpassed++;
    }
    printf("testing ListNext() when current node is list's tail\n");
    tests++;
    ListLast(L2);
    if (ListNext(L2) != NULL){
        printf(" listNext FAILED when current node is list's tail\n");
        printf("list2=");
        Print_List(L2);
    }
    else {
        printf("ListNext() successful!! when current node is list's tail\n ");
        testpassed++;
    }

    printf("testing ListNext when current node is list's head\n");
    tests++;
    ListFirst(L2);
    ListNext(L2);
    printf("hhh\n");
    if (L2->curser->item != L2->head->next->item){
        printf(" listNext() FAILED when current node is list's head\n");
        printf("list2=");
        Print_List(L2);
        printf("curser item:%d  expected item:%d\n ",
*(int *) L2->curser->item,*(int *) L2->tail->next->item);
    }
    else {
        printf("ListNext() successful!! when current node is list's head\n");
        testpassed++;
    }
    printf("testing ListPrev() when current node is list's head\n");
    tests++;
    ListFirst(L2);
    if (ListPrev(L2) != NULL){
        printf(" listPrev FAILED when current node is list's head\n");
        printf("list2=");
        Print_List(L2);
    }
    else {
        printf("ListPrev() successful!! when current node is list's head\n ");
        testpassed++;
    }

    
    printf("________________ListRemove()___________________\n");
    printf("test: remove from start of the list\n");
    ListFirst(L1);
    Itemcheck= L1->head->item;
    removedItem=ListRemove(L1);
    tests++;
    if (Itemcheck == ((int *)removedItem)){
        printf("ListRemove() sucessfull on removing the head\n");
        testpassed++;
    } else {
        printf("ListRemove() FAILED on removing the head\n");
        printf("item to be removed: %d\n", *Itemcheck);
        printf("item now in head: %d\n",*(int *) L1->head->item);
    }


    printf("test: remove from tail of the list\n");
    ListLast(L1);
    Itemcheck= L1->tail->item;
    removedItem=ListRemove(L1);
    tests++;
    if (Itemcheck == ((int *) removedItem)){
        printf("ListRemove() sucessfull on removing the tail\n");
        testpassed++;
    } else {
        printf("ListRemove() FAILED on removing the tail\n");
        printf("item to be removed: %d\n", *Itemcheck);
        printf("item now in tail: %d\n",*(int *) L1->tail->item);
    }

    printf("test: remove from middle of the list\n");
    ListFirst(L1);
    ListNext(L1);
    ListNext(L1);
    Itemcheck= L1->head->next->next->item;
    removedItem=ListRemove(L1);
    tests++;
    if (Itemcheck == ((int *) removedItem)){
        printf("ListRemove() sucessfull on removing from middle\n");
        testpassed++;
    } else {
        printf("ListRemove() FAILED on removing from middle\n");
        printf("item to be removed: %d\n", *Itemcheck);
        printf("item now: %d\n",*(int *) L1->head->next->next->item);
    }

    printf("test: Remove the list when only one item\n");
    ListRemove(L4);
    ListRemove(L4);
    ListRemove(L4);
    Itemcheck= L4->tail->item;
    removedItem=ListRemove(L4);
    tests++;
    if (Itemcheck == ((int *) removedItem)){
        printf("ListRemove() sucessfull on removing the tail when one item\n");
        testpassed++;
    } else {
        printf("ListRemove() FAILED on removing the tail when one item \n");
        printf("item to be removed: %d\n", *Itemcheck);
        printf("item now in tail: %d\n",*(int *) L4->tail->item);
    }

    printf("________________ListConcat()___________________\n");
    
    printf("test: TWO LISTS with content\n");
    ListConcat(L1, L2);
    tests++;
    if (ListCount(L2) == 0){
        printf("ListConcat() successfull with two lists with content\n");
        testpassed++;
    } else{
        printf("ListConcat() Failed with two lists with content\n");
        printf("List1 size:%d  List2 size: %d\n",ListCount(L1),ListCount(L2)); 
    }

    printf("test: L1 empty\n");
    ListConcat(L5, L1);
    tests++;
    if (ListCount(L1) == 0){
        printf("ListConcat() successful with one list empty\n");
        testpassed++;
    } else{
        printf("ListConcat() failed with one list empty\n");
    }
    ListConcat(L1, L5);
    printf("_______________ListTrim()___________________\n");

    printf("test: Trim the list when curser at random place\n");
   ListLast(L1);
    ListPrev(L1);
    ListPrev(L1);
       Itemcheck= L1->tail->item;
    removedItem=ListTrim(L1);
    tests++;
    if (Itemcheck == ((int *) removedItem)){
        printf("ListTrim sucessfull on Triming the tail when multiple item\n");
        testpassed++;
    } else {
        printf("ListTrim() FAILED on Triming the tail when multiple item\n");
        printf("item to be removed: %d\n", *Itemcheck);
        printf("item now in tail: %d\n",*(int *) L1->tail->item);
    }

    printf("test: Trim the list when only one item\n");
    Itemcheck= L3->tail->item;
    removedItem=ListTrim(L3);
    tests++;
    if (Itemcheck == ((int *) removedItem)){
        printf("ListTrim() sucessfull on Triming the tail when one item\n");
        testpassed++;
    } else {
        printf("ListTrim() FAILED on Triming the tail when one item \n");
        printf("item to be removed: %d\n", *Itemcheck);
        printf("item now in tail: %d\n",*(int *) L3->tail->item);
    }

    printf("________________ListSearch()___________________\n");
    printf("test:finding an item in list with mulpiple items\n");
    cArg= I2;  
    ListFirst(L1);
    tests++;
    resultPtr= (int*) ListSearch(L1, testComp,cArg);
    if (resultPtr==cArg){
        printf("ListSearch() sucessfull on finding an item in list with\
 mulpiple items\n");
        testpassed++;
    } else {
        printf("ListSearch() Failed on finding an item in list with\
 mulpiple items\n");
        printf("item to be seacrched: %d\n", *cArg);
        printf("item found: %d\n",*resultPtr);
    }
    
    printf("test:finding an item not in list\n");
    cArg= I4;
    ListFirst(L1);
    tests++;
    resultPtr= (int*) ListSearch(L1, testComp,cArg);
    if (resultPtr==NULL){
        printf("ListSearch() sucessfull on finding an item in list with\
 mulpiple items\n");
        testpassed++;
    } else {
        printf("ListSearch() Failed on finding an item in list with\
 mulpiple items\n");
        printf("item to be seacrched: %d\n", *cArg);
        printf("item found: %d\n",*resultPtr);
    }

    printf("________________ListFree()___________________\n");
    printf("test:freeing list with multiple item\n");
    ListFirst(L1);
    tests++;
    ListFree(L1,testItemFree);
    if (L1->size==0){
        printf("ListFree() sucessfull on list with mulpiple items\n");
        testpassed++;
    } else {
        printf("ListSearch() Failed on list withmulpiple items\n");
        printf("List size: %d\n", ListCount(L1));
    }

    printf("test:freeing list with no item\n");
    ListFirst(L2);
    tests++;
    ListFree(L2,testItemFree);
    if (L2->size==0){
        printf("ListFree() sucessfull on list with no items\n");
        testpassed++;
    } else {
        printf("ListSearch() Failed on list with no items\n");
        printf("List size: %d\n", ListCount(L2));
    }
      
    printf("-----------------------------------------------------------\n");
    printf("tests passes: %d  out of %d\n", testpassed, tests);
    return 0;
}

void testItemFree(void *item){
    ((NODE *)item)->item = NULL;
    ((NODE *)item)->prev = NULL;
}
int testComp(void *item1,void *item2 ){
    int i1= *(int*) item1;
    int i2= *(int*) item2;
    
    if (i1 == i2){
        return 1;
    } 
    else{
        return 0;
    }
}

/* print list for testing*/
void Print_List(LIST *list){
    NODE *printing_node= list->head;
    printf("size: %d\n", list->size);
    printf("[");
    if (list->size != 0){
        while (printing_node != NULL){
            printf("%d ", *((int*) printing_node->item ));
            printing_node= printing_node->next;
        }
    }
    printf("]\n");
}

/*
 *@author Wahhaj Javed, muj975, 11135711
 *@author Nakhba Mubashir, epl482, 11317060
 *@date 2024-09-16
 */

#include"list.h"

/* print list for testing*/
void Print_List(LIST *list);

int main(void){
    LIST *L1, *L2, *L3, *L4 ;
    int *I1, *I2, *I4, *I5, *I6;
    int a, b, d, e, f, result;
    a= 44;
    b=55;
    d=70;
    e=18;
    f=9;
    I1=&a;
    I2=&b;    
    I4=&d;
    I5=&e;
    I6=&f;

/*    
    int (*testCOMPARATOR)(void *V, void *I);
    void (*testITEMFREE)(void *I);    
*/  
    printf("____________TESTING PARTC: LIST LIBRARY_________\n");

    printf("______ListCreate()________\n");
    L1= ListCreate();
    Print_List(L1);
    L2= ListCreate();
    Print_List(L2);
    L3= ListCreate();
    Print_List(L3);
    L4= ListCreate();
    Print_List(L4);
    
/*
	ListCount(L1);
	printf("got to procedure ListCount()\n");

	I1 = ListFirst(L1);
	printf("got to procedure ListFirst()\n");

	I1 = ListLast(L1);
	printf("got to procedure ListLast()\n");

	I1 = ListNext(L1);
	printf("got to procedure ListNext()\n");

	I1 = ListPrev(L1);
	printf("got to procedure ListPrev()\n");

	I1 = ListCurr(L1);
	printf("got to procedure ListCurr()\n");
	
*/
    printf("________ListADD()___________\n");
    printf("Empty list()\n");
    result=ListAdd(L1, I1);
/*    Print_List(L1);*/
    if (result !=0){
        printf("ERROR : listAdd.\n");
        printf("list1=");
        Print_List(L1);
    }
    else printf("ListAdd() successful!!\n");

    printf("NON Empty lis()\n");
    result=ListAppend(L1, I5);
    if (result !=0){
        printf("ERROR : listAdd().\n");
        printf("list1=");
        Print_List(L1);
    }
    else printf("ListAdd() successful!!\n");
    Print_List(L1);

    printf("________ListInsert()___________\n");
    printf("Empty list()\n");
    result=ListInsert(L2, I2);
    if (result !=0){
        printf("ERROR : ListInser.\n");
        printf("list2=");
        Print_List(L2);
    }
    else printf("ListInsert() successful!!\n");

    printf("NON Empty lis()\n");
    result=ListInsert(L2, I6);
    if (result !=0){
        printf("ERROR : ListInsert.\n");
        printf("list2=");
        Print_List(L2);
    }
    else printf("ListInsert() successful!!\n");
    Print_List(L2);
	

    printf("________ListAppend()___________\n");
    printf("Empty lis()\n");
	result=ListAppend(L3, I1);
    if (result !=0){
        printf("ERROR : list append.\n");
        printf("list3=");
        Print_List(L3);
    }
    else printf("ListAppend() successful!!\n");

    printf("NON Empty lis()\n");
    result=ListAppend(L3, I2);
    if (result !=0){ 
        printf("ERROR : listAppend().\n");
        printf("list3=");
        Print_List(L3);
    }
    else printf("ListAppend() successful!!\n");
    Print_List(L3);    

    printf("________ListPrepend()___________\n");
    printf("Empty lis()\n");
    result=ListPrepend(L4, I4);
    if (result !=0){ 
        printf("ERROR : listPrepend.\n");
        printf("list4=");
        Print_List(L4);
    }
    else printf("ListPrepend() successful!!\n");

    printf("NON Empty lis()\n");
    result=ListAppend(L4, I2);
    if (result !=0){
        printf("ERROR : listPrepend().\n");
        printf("list4=");
        Print_List(L4);
    }
    else printf("ListPrepend() successful!!\n");
    Print_List(L4);

/*
	I1 = ListRemove(L1);
	printf("got to procedure ListRemove()\n");

	ListConcat(L1, L2);
	printf("got to procedure ListConcat()\n");

	I1 = ListTrim(L1);
	printf("got to procedure ListTrim()\n");

	ListFree(L2, &testITEMFREE);
	printf("got to procedure ListFree()\n");

	I1 = ListSearch(L1, &testCOMPARATOR, I1);
	printf("got to procedure ListSearch()\n");
*/
	return 0;

}
/* print list for testing*/
void Print_List(LIST *list){
    NODE *printing_node= list->head;
    printf("[");
    if (ListCount(list)>0){
        while (printing_node != NULL){
            printf("%d ", *((int*) printing_node->item ));
            printing_node= printing_node->next;
        }
    }
    printf("]\n");
}

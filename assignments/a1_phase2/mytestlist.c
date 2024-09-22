/*
 *@author Wahhaj Javed, muj975, 11135711
 *@author Nakhba Mubashir, epl482, 11317060
 *@date 2024-09-16
 */

#include"list.h"

int main(void){
    LIST *L1, *L2, *L3, *L4;
    int *I1, *I2, *I3;
    int a, b,c;
    a= 44;
    b=55;
    c=6;
    I1=&a;
    I2=&b;
    I3=&c;    

    int (*testCOMPARATOR)(void *V, void *I);
    void (*testITEMFREE)(void *I);    
    printf("____________TESTING PARTC: LIST LIBRARY_________\n");

    printf("______ListCreate()________\n");
    L1= ListCreate();
    L2= ListCreate();
    L3= ListCreate();
    L4= ListCreate();
    L5= ListCreate();

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
	
	ListAdd(L1, I1);
	printf("got to procedure ListAdd()\n");

	ListInsert(L1, I1);
	printf("got to procedure ListInsert()\n");
	

    printf("________ListAppend()___________\n");
    printf("Empty lis()\n");
	result=ListAppend(L1, I1);
    if (result !=0) printf("ERROR : list append.\n"0
    else printf("ListAppend() successful!!"


	ListPrepend(L1, I1);
	printf("got to procedure ListPrepend()\n");

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

	return 0;

}

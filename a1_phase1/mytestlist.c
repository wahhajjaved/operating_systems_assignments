/* Authors
 *Wahhaj Javed, muj975, 11135711
 *Nakhba Mubashir, epl482, 11317060
 *
 */
#include"list.h"

int main(void){
    LIST *L1;
    LIST *L2;
    void *I1;
    int (*testCOMPARATOR)(void *V, void *I);
    void (*testITEMFREE)(void *I);    

    L1= ListCreate();
	printf("got to procedure ListCreate()\n");

    L2= ListCreate();
    printf("got to procedure ListCreate()\n");

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
	
	ListAppend(L1, I1);
	printf("got to procedure ListAppend()\n");

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

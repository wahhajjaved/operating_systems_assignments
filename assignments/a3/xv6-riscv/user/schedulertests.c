#include "kernel/types.h"
#include "user/user.h"


void test1() {
    printf("******************** Test 1 ********************\n");
    procdump();
    printf("************************************************\n");
}

void test2() {
    int r;
    printf("******************** Test 2 ********************\n");
    r = setprocessgroup(-1, 1);
    procdump();
    printf("***************** Test 2 ");
    if(r != -1)
        printf("Failed");
    else
        printf("Passed");
    printf(" *****************\n");
}

void test3() {
    int r;
    printf("******************** Test 3 ********************\n");
    r = setprocessgroup(10, 1);
    procdump();
    printf("***************** Test 3 ");
    if(r != -1)
        printf("Failed");
    else
        printf("Passed");
    printf(" *****************\n");
}

void test4() {
    int r;
    printf("******************** Test 4 ********************\n");
    r = setprocessgroup(getpid(), -1);
    procdump();
    printf("***************** Test 4 ");
    if(r != -1)
        printf("Failed");
    else
        printf("Passed");
    printf(" *****************\n");
}

void test5() {
    int r;
    printf("******************** Test 5 ********************\n");
    r = setprocessgroup(getpid(), 20);
    procdump();
    printf("***************** Test 5 ");
    if(r != -1)
        printf("Failed");
    else
        printf("Passed");
    printf(" *****************\n");
}

void test6() {
    int r;
    printf("******************** Test 6 ********************\n");
    r = setprocessgroup(getpid(), 5);
    procdump();
    printf("***************** Test 6 ");
    if(r != 0)
        printf("Failed");
    else
        printf("Passed");
    printf(" *****************\n");
}

void test7() {
    int r;
    int remainingshares = -1;
    printf("******************** Test 7 ********************\n");
    r = setshare(-1, 2, &remainingshares);
    printf("***************** Test 7 ");
    if(r == -1 && remainingshares != 90)
        printf("Failed");
    else
        printf("Passed");
    printf(" *****************\n");
}

void test8() {
    int r;
    int remainingshares = -1;
    printf("******************** Test 8 ********************\n");
    r = setshare(20, 2, &remainingshares);
    printf("***************** Test 8 ");
    if(r == -1 && remainingshares != 90)
        printf("Failed");
    else
        printf("Passed");
    printf(" *****************\n");
}

void test9() {
    int r;
    int remainingshares = -1;
    printf("******************** Test 9 ********************\n");
    r = setshare(0, -2, &remainingshares);
    printf("***************** Test 9 ");
    if(r == -1 && remainingshares != 90)
        printf("Failed");
    else
        printf("Passed");
    printf(" *****************\n");
}

void test10() {
    int r;
    int remainingshares = -1;
    printf("******************** Test 10 ********************\n");
    r = setshare(0, 100, &remainingshares);
    printf("***************** Test 10 ");
    if(r == -1 && remainingshares != 90)
        printf("Failed");
    else
        printf("Passed");
    printf(" *****************\n");
}

void test11() {
    int r;
    int remainingshares = -1;
    printf("******************** Test 11 ********************\n");
    r = setshare(0, 5, &remainingshares);
    printf("***************** Test 11 ");
    if(r == -1 && remainingshares != 90)
        printf("Failed");
    else
        printf("Passed");
    printf(" *****************\n");
}

int main() {
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    test10();
    test11();
}

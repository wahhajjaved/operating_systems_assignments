#include "kernel/types.h"
#include "user/user.h"

/* from grind.c. */
int
do_rand(unsigned long *ctx)
{
/*
 * Compute x = (7^5 * x) mod (2^31 - 1)
 * without overflowing 31 bits:
 *      (2^31 - 1) = 127773 * (7^5) + 2836
 * From "Random number generators: good ones are hard to find",
 * Park and Miller, Communications of the ACM, vol. 31, no. 10,
 * October 1988, p. 1195.
 */
    long hi, lo, x;

    /* Transform to [1, 0x7ffffffe] range. */
    x = (*ctx % 0x7ffffffe) + 1;
    hi = x / 127773;
    lo = x % 127773;
    x = 16807 * lo - 2836 * hi;
    if (x < 0)
        x += 0x7fffffff;
    /* Transform to [0, 0x7ffffffd] range. */
    x--;
    *ctx = x;
    return (x);
}

unsigned long rand_next = 1;

int
rand(void)
{
    return (do_rand(&rand_next));
}

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
    printf("r = %d, remainingshares = %d\n", r, remainingshares);
    printf("***************** Test 7 ");
    if(r == -1 && remainingshares == 90)
        printf("Passed");
    else
        printf("Failed");
    printf(" *****************\n");
}

void test8() {
    int r;
    int remainingshares = -1;
    printf("******************** Test 8 ********************\n");
    r = setshare(20, 2, &remainingshares);
    printf("r = %d, remainingshares = %d\n", r, remainingshares);
    printf("***************** Test 8 ");
    if(r == -1 && remainingshares == 90)
        printf("Passed");
    else
        printf("Failed");
    printf(" *****************\n");
}

void test9() {
    int r;
    int remainingshares = -1;
    printf("******************** Test 9 ********************\n");
    r = setshare(0, -2, &remainingshares);
    printf("r = %d, remainingshares = %d\n", r, remainingshares);
    printf("***************** Test 9 ");
    if(r == -1 && remainingshares == 90)
        printf("Passed");
    else
        printf("Failed");
    printf(" *****************\n");
}

void test10() {
    int r;
    int remainingshares = -1;
    printf("******************** Test 10 ********************\n");
    r = setshare(0, 100, &remainingshares);
    printf("r = %d, remainingshares = %d\n", r, remainingshares);
    printf("***************** Test 10 ");
    if(r == -1 && remainingshares == 90)
        printf("Passed");
    else
        printf("Failed");
    printf(" *****************\n");
}

void test11() {
    int r;
    int remainingshares = -1;
    printf("******************** Test 11 ********************\n");
    r = setshare(0, 5, &remainingshares);
    printf("r = %d, remainingshares = %d\n", r, remainingshares);
    printf("***************** Test 11 ");
    if(r == 0 && remainingshares == 86)
        printf("Passed");
    else
        printf("Failed ");
    printf(" *****************\n");
}

void test12() {
    int r, s;
    printf("******************** Test 12 ********************\n");
    r = fork();
    if(r == 0) {
        procdump();
        exit(0);
    }
    wait(&s);
    printf("************************************************\n");
}



void test13child() {
    int times, i, square;

    sleep(rand() % 1000 + 10);
    times = rand() % 10000;
    times += 10;
    square = 0;
    for(i = 0; i < times; i++) {
        square = i * i;
    }
    printf("process %d: square of %d = %d\n", getpid(), times, square);
}


void test13() {
    int r, s, numchildren, i;
    numchildren = 10;
    printf("******************** Test 13 ********************\n");

    for(i = 0; i < numchildren; i++) {
        r = fork();

        /*child*/
        if(r == 0) {
            test13child();
            exit(0);
        }
    }
    for(i = 0; i < numchildren; i++) {
        wait(&s);
    }
    printf("************************************************\n");
}

int main() {
    test1();
    printf("\n");
    test2();
    printf("\n");
    test3();
    printf("\n");
    test4();
    printf("\n");
    test5();
    printf("\n");
    test6();
    printf("\n");
    test7();
    printf("\n");
    test8();
    printf("\n");
    test9();
    printf("\n");
    test10();
    printf("\n");
    test11();
    printf("\n");
    test12();
    printf("\n");
    test13();
    printf("\n");
}

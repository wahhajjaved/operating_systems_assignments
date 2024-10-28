/*
 *@author Wahhaj Javed, muj975, 11135711
 *@author Nakhba Mubashir, epl482, 11317060
 */

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

/* from uthread.c*/
/* Possible states of a thread: */
#define FREE        0x0
#define RUNNING     0x1
#define RUNNABLE    0x2

/*#define STACK_SIZE  8192*/
#define STACK_SIZE  8180
#define MAX_THREAD  4


struct thread {

    /* CMPT 332 GROUP 67 Change, Fall 2024 */
    uint64 ra;
    uint64 sp;

    /* save/restore the registers */
    uint64 s0;
    uint64 s1;
    uint64 s2;
    uint64 s3;
    uint64 s4;

    uint64 s5;
    uint64 s6;
    uint64 s7;
    uint64 s8;
    uint64 s9;
    uint64 s10;
    uint64 s11;

  char       stack[STACK_SIZE]; /* the thread's stack */
  int        state;             /* FREE, RUNNING, RUNNABLE */
};

/*uthread_switch.S*/
void thread_switch(struct thread*, struct thread*);

/* uthread.c*/
void thread_init(void);
void thread_schedule(void);
void thread_create(void (*func)());
void thread_yield(void);
void thread_free(void);
/*
void thread_a(void);
void thread_b(void);
void thread_c(void);
*/


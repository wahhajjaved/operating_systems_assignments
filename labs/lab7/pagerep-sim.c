/*
Identification:

Author: Jarrod Pas
Modified by students:  Wahhaj Javed
		muj975
		11135711
 */

/* Note: code intentionally not commented */


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <unistd.h>

struct page {
    int number; /* number == -1 means unused */
    bool reference;
    bool dirty;
};

int npages;
int next_slot;
int nslots;
struct page *slots;

int oldestSlot;
/* Handles a page fault via the second-chance algorithm.
 * Returns the pointer to the slot the victim is in. */
struct page *find_victim_slot() {
    /* TODO: implement second chance page replacement algorithm */
    struct page *p;
    if (next_slot < nslots) {
        oldestSlot = next_slot;
        return slots + next_slot;
    }

    while(1) {
        oldestSlot = (oldestSlot+1) % nslots;
        p = &slots[oldestSlot];
        if(p->reference == 0 && p->dirty == 0) {
            return p;
        }
        else if(p->reference == 0 && p->dirty == 1) {
            p->reference = 0;
            p->dirty = 0;
        }
        else if(p->reference == 1 && p->dirty == 0) {
            p->reference = 0;
            p->dirty = 0;
        }
        else if(p->reference == 1 && p->dirty == 1) {
            p->reference = 0;
            p->dirty = 1;
        }
    }
}


/*Function to print the state of the page table*/
void printSlots() {
    int i;
    for(i = 0; i < nslots; i++) {
        printf(
            "number = %d, R = %d, D = %d.\n"
            ,slots[i].number
            ,slots[i].reference
            ,slots[i].dirty
        );
    }
    printf("\n\n");
}

/*
* Function that tests the algorithm using a predefined page order.
* Results compared with the interactive exercise on Canvas
*/
void testLoop() {
    int page;
    bool fault;
    bool write;
    struct page *p;
    int pagesRead[10]  = {5, 7, 7, 2, 9, 3, 1, 5, 5, 1};
    int pagesWrite[10] = {0, 0, 0, 1, 0, 0, 1, 0, 0, 0};
    int i;
    
    printf(
        "Testing second change algorithm with the following page order.\n"
        "5, 7, 7, 2/W, 9, 3, 1/W, 5, 5, 1\n\n"
    );
    
    for(i = 0; i < 10; i++) {
        page = pagesRead[i];
        write = pagesWrite[i];
        if (write) {
            printf("RW on page %d.", page);
        } else {
            printf("R  on page %d.", page);
        }

        fault = true;
        for (p = slots; p < &slots[nslots]; p++) {
            if (p->number != page) continue;
            p->reference = true;
            p->dirty |= write;
            fault = false;
            break;
        }

        if (fault) {
            printf(" This triggered a page fault.");
            p = find_victim_slot();
            if (next_slot < nslots) {
                printf(" There was a free slot!");
                p = slots + next_slot++;
            } else {
                printf(" The chosen victim was page %d.", p->number);
            }
            p->number = page;
            p->reference = true;
            p->dirty = write;
        }
        printf("\n");
        printf("--------------------------------------------\n");
        printSlots();
    }
    exit(0);
}


int main(int argc, char **argv) {
    int times;
    int page;
    bool fault;
    bool write;
    struct page *p;
    
    if (argc != 3 && argc != 4) {
        printf("usage: %s npages nslots <times>\n", argv[0]);
        exit(1);
    }

    npages = atoi(argv[1]);
    if (npages <= 0) {
        printf("npages must be greater than 0\n");
        exit(1);
    }

    nslots = atoi(argv[2]);
    if (nslots <= 0) {
        printf("nslots must be greater than 0\n");
        exit(1);
    }
    next_slot = 0;
    slots = malloc(sizeof(struct page) * nslots);

    if (argc == 4) {
        times = atoi(argv[3]);
        if (times <= 0) {
            printf("times must be greater than 0.\n");
            exit(1);
        }
    } else {
        times = -1;
    }

    for (p = slots; p < &slots[nslots]; p++) {
        p->number = -1;
        p->reference = false;
        p->dirty = false;
    }
    
    /* test code. Must be run as ./pagerep-sim 10 3 */
    /* testLoop(); */
    
    while (times < 0 || times-- > 0) {
        page = npages * sqrt((double) rand() / RAND_MAX);
        write = rand() % 2;

        if (write) {
            printf("RW on page %d.", page);
        } else {
            printf("R  on page %d.", page);
        }

        fault = true;
        for (p = slots; p < &slots[nslots]; p++) {
            if (p->number != page) continue;
            p->reference = true;
            p->dirty |= write;
            fault = false;
            break;
        }

        if (fault) {
            printf(" This triggered a page fault.");
            p = find_victim_slot();
            if (next_slot < nslots) {
                printf(" There was a free slot!");
                p = slots + next_slot++;
            } else {
                printf(" The chosen victim was page %d.", p->number);
            }
            p->number = page;
            p->reference = true;
            p->dirty = write;
        }

        if (times < 0) usleep(100 * 1000);

        putchar('\n');
    }

    return 0;
}


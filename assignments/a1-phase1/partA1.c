/*
* @author Wahhaj Javed, muj975, 11135711
* @author Nakhba Mubashir, epl482, 11317060
* @date 2024-09-14
*/

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#include "square.h"



int main(int argc, char* argv[]) {

    if (argc != 4) {
        printf("Invalid number of arguments.\n");
        printf("Usage: ./partA1 threads deadline size.\n");
        return 1;
    }

    char *p;
	long threads = strtol(argv[1], &p, 10);
	double deadline = strtod(argv[2], &p);
	long size = strtol(argv[3], &p, 10);
	printf("threads %d, deadline %.2f, size %d\n", threads, deadline, size);

    HANDLE threadHandles = malloc(sizeof(HANDLE) * threads);
    DWORD threadIDs = malloc(sizeof(DWORD) * threads);

    for(int i=0; i<threads; i++) {
        HANDLE handle = CreateThread(
            NULL,
			0,
			tmain,
			&size,
			CREATE_SUSPENDED,
			&threadIDs[i]
		);

        if (handle == NULL) {
            printf("CreateThread failed. Error: %lu\n", GetLastError());
            return 1;
        }

        //15 is enough to store each digit of int32 with some room to spare
        wchar_t desc[15];
        swprintf(desc, 15, L"%d", i);
		HRESULT result = SetThreadDescription(handle, desc);
		if(!SUCCEEDED(result)) {
			printf("ERROR: Couldn't set thread description.\n");
			return 1;
		}
    }

    for(int i = 0; i < threads; i++) {
		printf("Resuming thread %d\n", i);
		ResumeThread(threadHandles[i]);
	}

	Sleep(deadline*1000);



    free(threadHandles);
    free(threadIDs);

}
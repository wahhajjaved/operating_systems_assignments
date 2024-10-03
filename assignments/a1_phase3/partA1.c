/*
* @author Wahhaj Javed, muj975, 11135711
* @author Nakhba Mubashir, epl482, 11317060
* @date 2024-09-22
*/

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#include "square.h"

#define CHILD_STACK_SIZE 5000000

DWORD tlsIndex;

int getIndex() {
	int index;
	LPVOID data = TlsGetValue(tlsIndex);
	if ((data == 0) && (GetLastError() != ERROR_SUCCESS))
      return -1;
	index = *(int*)data;
	return index;
}

/* Entry point of the thread

	Parameters
		LPVOID lpParam: Array of ints. lpParam[0] is index of pSquareCount at
			which Square()'s call count is stored. lpParam[0] is the value
			passed to Square() when it is called

	Return
		0. Return value doesn't mean anything. It only exists to conform with
		the windows api
*/
DWORD WINAPI tmain(LPVOID lpParam) {
	int n, index, elapsedTimeMs;
	double elapsedTime;
	LARGE_INTEGER frequency, startTime, endTime;
	int* params;

	params = (int*)lpParam;
	index = params[0];
	n = params[1];
	TlsSetValue(tlsIndex, (LPVOID)&index);

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&startTime);
	pStartTime[index] = (startTime.QuadPart * 1000000) / frequency.QuadPart;

	Square(n);

	QueryPerformanceCounter(&endTime);
	endTime.QuadPart = (endTime.QuadPart * 1000000) / frequency.QuadPart;
	elapsedTimeMs = endTime.QuadPart - pStartTime[index];
	elapsedTime = elapsedTimeMs / 1000000.0;

	printf("Thread %d finished. Square called %d times. "
		"Thread ran for %.10f seconds.\n",
		index, pSquareCount[index], elapsedTime);

	return 0;

}

int main(int argc, char* argv[]) {
	int32_t threads, size, deadline, *args;
	HANDLE *threadHandles;
	DWORD *threadIDs;
	int i;
	int32_t** threadParams;

	args = parseArgs(argc, argv);
    if (args == NULL){
        return 1;
    }
    threads = args[0];
	deadline = args[1];
	size = args[2];


	tlsIndex = TlsAlloc();
	if (tlsIndex == TLS_OUT_OF_INDEXES) {
        printf("Failed to allocate TLS index\n");
        return 1;
    }

	threadHandles = (HANDLE *)malloc(sizeof(HANDLE) * threads);
	threadIDs = (DWORD *)malloc(sizeof(DWORD) * threads);
	pSquareCount = (int32_t *)calloc(threads, sizeof(int32_t));
	pStartTime = (int64_t *)calloc(threads, sizeof(int64_t));


	threadParams = malloc(threads * sizeof(int32_t*));
	for(i=0; i<threads; i++) {
		HANDLE handle;
		threadParams[i] = malloc(sizeof(int32_t) * 2);
		threadParams[i][0] = i;
		threadParams[i][1] = size;

		handle = CreateThread(
			NULL,
			CHILD_STACK_SIZE,
			tmain,
			threadParams[i],
			CREATE_SUSPENDED,
			&threadIDs[i]
		);

		if (handle == NULL) {
			printf("CreateThread failed. Error: %u\n", GetLastError());
			return 1;
		}
		threadHandles[i] = handle;
	}

	for(i = 0; i < threads; i++) {
		ResumeThread(threadHandles[i]);
	}

	Sleep(deadline*1000);
	stopSquare = 1;

	/*potential segfault if child threads don't stop fast enough before the
	arrays are freed. A small delay before freeing shoudl prevent this.*/
	Sleep(1000);


	free(threadHandles);
	free(threadIDs);
	free(pSquareCount);
	free(pStartTime);

	return 0;
}
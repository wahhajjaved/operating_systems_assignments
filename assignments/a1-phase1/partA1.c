/*
* @author Wahhaj Javed, muj975, 11135711
* @author Nakhba Mubashir, epl482, 11317060
* @date 2024-09-14
*/

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#include "square.h"

int get_index() {
	PWSTR desc = NULL;
	HRESULT result = GetThreadDescription(GetCurrentThread(), &desc);
	if(!SUCCEEDED(result)) {
		printf("ERROR: Couldn't get thread description.\n");
		return -1;
	}
	wchar_t *p = NULL;
	int index = wcstol(desc, &p, 10);
	return index;
}

DWORD WINAPI tmain(LPVOID lpParam) {
	int n = *(int*)lpParam;
	int index = get_index()
	if (index < 0){
		printf("ERROR: Thread %d could not get index\n", index);

	}

	LARGE_INTEGER frequency, startTime; endTime;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&startTime);
	pStartTime[index] = (startTime.QuadPart * 1000000) / frequency.QuadPart;

	int64_t result = square(n);

	QueryPerformanceCounter(&endTime);
	endTime.QuadPart = (endTime.QuadPart * 1000000) / frequency.QuadPart;

	int64_t elapsedTime = endTime.QuadPart - pStartTime[index];

	printf("Thread %d finished. Square called %d times. "
		"Thread ran for %lli micro seconds.\n",
		index, squareCount[index], elapsedTime.QuadPart);
	return 0;

}

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

	HANDLE threadHandles = (HANDLE *)malloc(sizeof(HANDLE) * threads);
	DWORD threadIDs = (DWORD *)malloc(sizeof(DWORD) * threads);
	pSquareCount = (int32_t *)malloc(sizeof(int32_t) * threads);
	pStartTime = (int64_t *)malloc(sizeof(int64_t) * threads);

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
	stopSquare = 1;

	// potential segfault if child threads don't stop fast enough before the
	// arrays are freed. A small delay before freeing shoudl prevent this.
	Sleep(100);


	free(threadHandles);
	free(threadIDs);
	free(pSquareCount);
	free(pStartTime);

}
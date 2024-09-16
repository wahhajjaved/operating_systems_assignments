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
	PWSTR desc;
	HRESULT result;
	int index;
	wchar_t *p;
	
	desc = NULL;
	result = GetThreadDescription(GetCurrentThread(), &desc);
	if(!SUCCEEDED(result)) {
		printf("ERROR: Couldn't get thread description.\n");
		return -1;
	}
	p = NULL;
	index = wcstol(desc, &p, 10);
	return index;
}

DWORD WINAPI tmain(LPVOID lpParam) {
	int n, index, elapsedTimeMs;
	double elapsedTime;
	LARGE_INTEGER frequency, startTime, endTime;
	
	n = *(int*)lpParam;
	index = get_index();
	if (index < 0){
		printf("ERROR: Thread %d could not get index\n", index);

	}

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&startTime);
	pStartTime[index] = (startTime.QuadPart * 1000000) / frequency.QuadPart;

	square(n);

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
	char *p;
	int32_t threads, size;
	double deadline;
	HANDLE *threadHandles;
	DWORD *threadIDs;
	int i;
	wchar_t desc[15];

	if (argc != 4) {
		printf("Invalid number of arguments.\n");
		printf("Usage: ./partA1 threads deadline size.\n");
		return 1;
	}

	
	threads = strtol(argv[1], &p, 10);
	deadline = strtod(argv[2], &p);
	size = strtol(argv[3], &p, 10);
	printf("threads %d, deadline %.2f, size %d\n", threads, deadline, size);

	threadHandles = (HANDLE *)malloc(sizeof(HANDLE) * threads);
	threadIDs = (DWORD *)malloc(sizeof(DWORD) * threads);
	pSquareCount = (int32_t *)malloc(sizeof(int32_t) * threads);
	pStartTime = (int64_t *)malloc(sizeof(int64_t) * threads);
	
	for(i=0; i<threads; i++) {
		HANDLE handle;
		HRESULT result;
		
		handle = CreateThread(
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
		threadHandles[i] = handle;

		/*15 is enough to store each digit of int32 with some room to spare*/
		swprintf(desc, 15, L"%d", i);
		result = SetThreadDescription(handle, desc);
		if(!SUCCEEDED(result)) {
			printf("ERROR: Couldn't set thread description.\n");
			return 1;
		}
	}

	for(i = 0; i < threads; i++) {
		printf("Resuming thread %d\n", i);
		ResumeThread(threadHandles[i]);
	}

	Sleep(deadline*1000);
	stopSquare = 1;

	/*potential segfault if child threads don't stop fast enough before the
	arrays are freed. A small delay before freeing shoudl prevent this.*/
	Sleep(100);


	free(threadHandles);
	free(threadIDs);
	free(pSquareCount);
	free(pStartTime);
	
	return 0;
}
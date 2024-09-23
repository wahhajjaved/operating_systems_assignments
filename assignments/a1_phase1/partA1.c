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
	printf("get_index() called with valid arguments\n");
	return 0;
	/*
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
	*/
}

DWORD WINAPI tmain(LPVOID lpParam) {
	/*
	int n, index, elapsedTimeMs;
	double elapsedTime;
	LARGE_INTEGER frequency, startTime, endTime;
	*/
	
	int n;
	n = *(int*)lpParam;
	if (n >= 0) {
		printf("Got to tmain. Arguments valid\n");
	}
	else
		printf("Got to tmain. Arguments invalid\n");
	/*	
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
	*/
	return 0;

}

int main(int argc, char* argv[]) {
	char *p;
	int32_t threads, size;
	double deadline;
	/*
	HANDLE *threadHandles;
	DWORD *threadIDs;
	int i;
	wchar_t desc[15];
	*/
	

	if (argc != 4) {
		printf("Invalid number of arguments.\n");
		printf("Usage: ./partA1 threads deadline size.\n");
		return 1;
	}
	

	
	threads = strtol(argv[1], &p, 10);
	deadline = strtod(argv[2], &p);
	size = strtol(argv[3], &p, 10);
	
	if (threads < 1){
		printf("Invalid value %d for number of threads. Must be at least 1.\n",
			threads
		);
		return 1;
	}
	if (deadline <= 0){
		printf("Invalid value %.2f for deadline . Must be greater than 0\n",
			deadline
		 );
		return 1;
	}
	if (size < 0){
		printf("Invalid value %d for size. Must be at least 0\n", size);
		return 1;
	}
	printf("PartA1 main arguments valid. Now calling all other functions\n");
	tmain(&size);
	get_index();
	square(size);
	
	/*
	printf("threads %d, deadline %.2f, size %d\n", threads, deadline, size);

	threadHandles = (HANDLE *)malloc(sizeof(HANDLE) * threads);
	threadIDs = (DWORD *)malloc(sizeof(DWORD) * threads);
	pSquareCount = (int32_t *)calloc(threads, sizeof(int32_t));
	pStartTime = (int64_t *)calloc(threads, sizeof(int64_t));
	
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
	*/
	/*potential segfault if child threads don't stop fast enough before the
	arrays are freed. A small delay before freeing shoudl prevent this.*/
	/*
	Sleep(1000);


	free(threadHandles);
	free(threadIDs);
	free(pSquareCount);
	free(pStartTime);
	*/	
	return 0;
}
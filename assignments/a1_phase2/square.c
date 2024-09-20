/*
* @author Wahhaj Javed, muj975, 11135711
* @author Nakhba Mubashir, epl482, 11317060
* @date 2024-09-14
*/

#include "square.h"
#include <stdio.h>


int32_t *pSquareCount;
int64_t *pStartTime;
int stopSquare = 0;

int64_t square(int n) {
	if (n < 0){
		printf("Invalid value %d for n. Must be at least 0\n", n);
		return -1;
	} 
	printf("square() called with valid argument\n");
	return 0;
	/*
	int index;
    index = get_index();
    if (n == 0 || stopSquare != 0){
		return 0;
	}
	pSquareCount[index]++;
	return (square(n - 1) + n + n - 1);
	*/
}
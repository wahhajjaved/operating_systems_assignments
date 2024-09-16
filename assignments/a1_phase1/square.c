/*
* @author Wahhaj Javed, muj975, 11135711
* @author Nakhba Mubashir, epl482, 11317060
* @date 2024-09-14
*/

#include "square.h"


int32_t *pSquareCount;
int64_t *pStartTime;
int stopSquare = 0;

int64_t square(int n) {
	int index;
    index = get_index();
    if (n == 0 || stopSquare != 0){
		return 0;
	}
	pSquareCount[index]++;
	return (square(n - 1) + n + n - 1);
}
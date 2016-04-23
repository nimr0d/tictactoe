#include "time.h"

#include <time.h>

i64 moveTime(i64 timebank, i64 timePerMove, i64 time, i8 numFree) {
	time = (9 * time) / 10;
	return time / numFree + timePerMove - 30;
}
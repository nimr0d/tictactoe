#include "time_mgmt.h"

#include <ctime>

i64 moveTime(i64 timebank, i64 timePerMove, i64 time, u8 numFree) {
	time = (9 * time) / 10;
	return time / numFree + timePerMove - 30;
}
#include "time_mgmt.h"

i64 moveTime(i64 time, i64 timePerMove, u8 numFree) {
	time = (9 * time) / 10;
	return (time - timePerMove) / numFree + timePerMove - 30;
}
#include "time_mgmt.h"

i64 moveTime(Position *pos, i64 time, i64 timePerMove) {
	/*time = (9 * time) / 10;
	return (time - timePerMove) / (numFree - 20) + timePerMove - 30;*/
	return 3000 > time ? time / 2 : 1500;

}
#ifndef _H_BASE_
#define _H_BASE_

#include "board.h"
#include "types.h"

extern i64 wbase[2][262144];
extern i64 dbase[262144];

namespace Base {
void init();
}

#endif
#ifndef _BASE_H_
#define _BASE_H_

#include "board.h"
#include "types.h"

extern i64 wbase[2][262144];
extern i64 dbase[262144];

namespace Base {
void init();
}

#endif
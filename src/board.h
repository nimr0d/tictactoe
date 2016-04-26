#ifndef _H_BOARD_
#define _H_BOARD_

#include "types.h"

extern Square LStS[9][9];
extern Square StLS1[81];
extern Square StLS2[81];

namespace Boards {
void init();
}

#endif
#ifndef _H_SEARH_
#define _H_SEARCH_

#include <ctime>

#include "types.h"

Square think(Piece *field, Bitboard macroboard, u8 *lsCount, u8 numFin, Piece player, time_t max_time);

#endif
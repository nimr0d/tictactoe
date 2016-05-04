#ifndef _H_SEARH_
#define _H_SEARCH_

#include "types.h"

Square think(Piece *field, Bitboard macroboard, u8 *lsCount, u8 numFin, Piece player, i64 max_time, u32 move);

#endif
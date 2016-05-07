#ifndef _H_SEARH_
#define _H_SEARCH_

#include "types.h"

Square think(Piece *field, Bitboard macroboard, u8 *lsCount, u8 numFin, u8 numFree,
		Piece player, i64 time, i64 timePerMove, u32 move);

#endif
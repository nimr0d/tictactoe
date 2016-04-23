#ifndef _H_BOARD_
#define _H_BOARD_

#include "bitboard.h"
#include "types.h"

struct Board {
	Bitboard b0, b1;
	Bitboard free;
	Square move;
};

#endif
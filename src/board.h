#ifndef _H_BOARD_
#define _H_BOARD_

#include "types.h"

extern Square LStS[9][9];
extern Square StLS1[81];
extern Square StLS2[81];

extern Bitboard DSquareBB[9];		
extern Bitboard DColumnBB[3];		
extern Bitboard DRowBB[3];		
extern Bitboard DDiagBB[2];

extern Bitboard P0SquareBB[9];		
extern Bitboard P0ColumnBB[3];		
extern Bitboard P0RowBB[3];		
extern Bitboard P0DiagBB[2];

extern Bitboard SquareBB[9];		
extern Bitboard ColumnBB[3];		
extern Bitboard RowBB[3];		
extern Bitboard DiagBB[2];

namespace Boards {
void init();
}

Piece bb_get(Bitboard b, i32 i);
void bb_set(Bitboard &b, Piece p, i32 i);

void print(Bitboard b);

#endif
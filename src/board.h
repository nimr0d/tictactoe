#ifndef _H_BOARD_
#define _H_BOARD_

#include "types.h"

extern Square LStS[9][9];
extern SSquare StLS[81][2];

extern Bitboard RSquareBB[9];		
extern Bitboard RColumnBB[3];		
extern Bitboard RRowBB[3];		
extern Bitboard RDiagBB[2];

extern Bitboard LSquareBB[9];		
extern Bitboard LColumnBB[3];		
extern Bitboard LRowBB[3];		
extern Bitboard LDiagBB[2];

extern Bitboard SquareBB[9];		
extern Bitboard ColumnBB[3];		
extern Bitboard RowBB[3];		
extern Bitboard DiagBB[2];

const Bitboard flipMask = 0x15555;

namespace Boards {

void init();

}

Piece bb_get(Bitboard b, i32 i);
void bb_set(Bitboard &b, Piece p, i32 i);
void bb_clear(Bitboard &b, i32 i);

namespace Bitboards {

void print(Bitboard b);

}
#endif
#include "board.h"
#include <iostream>

Square LStS[9][9];
Square StLS1[81];
Square StLS2[81];

Bitboard DSquareBB[9];		
Bitboard DColumnBB[3];		
Bitboard DRowBB[3];		
Bitboard DDiagBB[2];

Bitboard P0SquareBB[9];		
Bitboard P0ColumnBB[3];		
Bitboard P0RowBB[3];		
Bitboard P0DiagBB[2];

Bitboard SquareBB[9];		
Bitboard ColumnBB[3];		
Bitboard RowBB[3];		
Bitboard DiagBB[2];


void Boards::init() {

	for (Square i = 0; i < 9; ++i) {
		DSquareBB[i] = 1 << (i << 1);
		P0SquareBB[i] = 2 << (i << 1);
		SquareBB[i] = 3 << (i << 1);
	}

	for (Square i = 0; i < 3; ++i) {
		for (Square j = 0; j < 3; ++j) {
			Square p = 3 * i + j;

			DColumnBB[j] |= DSquareBB[p];
			DRowBB[i] |= DSquareBB[p];
			
			P0ColumnBB[j] |= P0SquareBB[p];
			P0RowBB[i] |= P0SquareBB[p];
			
			ColumnBB[j] |= SquareBB[p];
			RowBB[i] |= SquareBB[p];
		}
		DDiagBB[0] |= DSquareBB[4 * i];
		DDiagBB[1] |= DSquareBB[2 * i + 2];

		P0DiagBB[0] |= P0SquareBB[4 * i];
		P0DiagBB[1] |= P0SquareBB[2 * i + 2];
		
		DiagBB[0] |= SquareBB[4 * i];
		DiagBB[1] |= SquareBB[2 * i + 2];
	}

	for (Square i = 0; i < 9; ++i) {
		for (Square j = 0; j < 9; ++j) {
			LStS[i][j] =  27 * (i / 3) + 3 * (i % 3) + 9 * (j / 3) + (j % 3);
		}
	}

	for (Square i = 0; i < 81; ++i) {
		StLS1[i] = 3 * ((i / 9) % 3) + i % 3;
		StLS2[i] = 3 * (i / 27) + (i / 3) % 3;
	}
}

Piece bb_get(Bitboard b, i32 i) {
	return static_cast<Piece>(i32((b >> (i << 1)) & 3) - 1);
}

void bb_set(Bitboard &b, Piece p, i32 i) {
	b = (b & ~(3 << (i << 1))) | ((p + 1) << (i << 1));
}

void print(Bitboard b) {
	for (Square i = 0; i < 3; ++i) {
	    for (Square j = 0; j < 3; ++j) {
	        std::cerr << bb_get(b, 3 * i + j) << " ";
	    }
	    std::cerr << "\n";
	}
}
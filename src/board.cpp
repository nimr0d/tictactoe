#include "board.h"
#include <iostream>

Square LStS[9][9];
SSquare cntLS[81];
SSquare posLS[81];

Bitboard RSquareBB[9];		
Bitboard RColumnBB[3];		
Bitboard RRowBB[3];		
Bitboard RDiagBB[2];

Bitboard LSquareBB[9];		
Bitboard LColumnBB[3];		
Bitboard LRowBB[3];		
Bitboard LDiagBB[2];

Bitboard SquareBB[9];		
Bitboard ColumnBB[3];		
Bitboard RowBB[3];		
Bitboard DiagBB[2];

Bitboard flipMask = 0x15555;

void Boards::init() {

	for (Square i = 0; i < 9; ++i) {
		RSquareBB[i] = 1 << (i << 1);
		LSquareBB[i] = 2 << (i << 1);
		SquareBB[i] = 3 << (i << 1);
	}

	for (Square i = 0; i < 3; ++i) {
		for (Square j = 0; j < 3; ++j) {
			Square p = 3 * i + j;

			RColumnBB[j] |= RSquareBB[p];
			RRowBB[i] |= RSquareBB[p];
			
			LColumnBB[j] |= LSquareBB[p];
			LRowBB[i] |= LSquareBB[p];
			
			ColumnBB[j] |= SquareBB[p];
			RowBB[i] |= SquareBB[p];
		}
		RDiagBB[0] |= RSquareBB[4 * i];
		RDiagBB[1] |= RSquareBB[2 * i + 2];

		LDiagBB[0] |= LSquareBB[4 * i];
		LDiagBB[1] |= LSquareBB[2 * i + 2];
		
		DiagBB[0] |= SquareBB[4 * i];
		DiagBB[1] |= SquareBB[2 * i + 2];
	}

	for (Square i = 0; i < 9; ++i) {
		for (Square j = 0; j < 9; ++j) {
			LStS[i][j] =  27 * (i / 3) + 3 * (i % 3) + 9 * (j / 3) + (j % 3);
		}
	}

	for (Square i = 0; i < 81; ++i) {
		posLS[i] = 3 * ((i / 9) % 3) + i % 3;
		cntLS[i] = 3 * (i / 27) + (i / 3) % 3;
	}
}

Piece bb_get(Bitboard b, i32 i) {
	return static_cast<Piece>(i32((b >> (i << 1)) & 3));
}

void bb_set(Bitboard &b, Piece p, i32 i) {
	b = (b & ~SquareBB[i]) | (p << (i << 1));
}

void bb_clear(Bitboard &b, i32 i) {
	b &= ~SquareBB[i];
}


Bitboard LSquare(Piece *field, Square i) {
	Square *ls = LStS[i];
	return (field[ls[0]] + 1) | ((field[ls[1]] + 1) << 2) | ((field[ls[2]] + 1) << 4)
			| ((field[ls[3]] + 1) << 6) | ((field[ls[4]] + 1) << 8)
			| ((field[ls[5]] + 1) << 10) | ((field[ls[6]] + 1) << 12)
			| ((field[ls[7]] + 1) << 14) | ((field[ls[8]] + 1) << 16);
}

void print(Bitboard b) {
	for (Square i = 0; i < 3; ++i) {
	    for (Square j = 0; j < 3; ++j) {
	        std::cerr << bb_get(b, 3 * i + j) << " ";
	    }
	    std::cerr << "\n";
	}
}
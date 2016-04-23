#include "bitboard.h"
#include <iostream>

void Bitboard::print() const {
	for (int i = 8; i >= 0; --i) {
		for (int j = 0; j < 9; ++j) {
			char c = 9 * i + j;
			if (c < 64) {
				std::cout << ((b_[0] >> c) & 1) << " ";
			} else {
				std::cout << ((b_[1] >> (c - 64)) & 1) << " ";
			}
		}
		std::cout << "\n";
	}
}

void print(SBitboard bb) {
	for (int i = 2; i >= 0; --i) {
		for (int j = 0; j < 3; ++j) {
			char c = 3 * i + j;
			std::cout << ((bb >> c) & 1) << " ";
		}
		std::cout << "\n";
	}
}

u8 PopCnt16[1 << 16];

Bitboard SquareBB[81];
Bitboard AdjacentSquaresBB[81];
Bitboard ColumnBB[9];
Bitboard RowBB[9];
Bitboard LSquareBB[9];
Bitboard CrosshairBB[81];

SBitboard SquareSBB[9];
SBitboard ColumnSBB[3] = {0x49, 0x92, 0x124};
SBitboard RowSBB[3] = {0x7, 0x38, 0x1c0};
SBitboard DiagSBB[2] = {0x111, 0x54};

void Bitboards::init() {
	for (u8 i = 0; i < 9; ++i) {
		RowBB[i] = Bitboard(0x1ffULL, 0ULL) << 9 * i;
		ColumnBB[i] = Bitboard(0x8040201008040201ULL, 0x100ULL) << i;
		LSquareBB[i] = Bitboard(0x1c0e07ULL, 0ULL) << 27 * (i / 3) + 3 * (i % 3);

		SquareSBB[i] = 1 << i;
	}

	for (u8 s = 0; s < 81; ++s) {
		SquareBB[s] = Bitboard(1ULL, 0ULL) << s;
		AdjacentSquaresBB[s] = Bitboard(0ULL, 0ULL);

		CrosshairBB[s] = RowBB[s / 9] ^ ColumnBB[s % 9];
	}

	for (u8 s = 0; s < 81; ++s) {
		if (s < 72) {
		  AdjacentSquaresBB[s + 9] |= SquareBB[s];
		}
		if (s >= 9) {
		  AdjacentSquaresBB[s - 9] |= SquareBB[s];
		}
		if (s % 9 < 8) {
		  AdjacentSquaresBB[s + 1] |= SquareBB[s];
		}
		if (s % 9 > 0) {
		  AdjacentSquaresBB[s - 1] |= SquareBB[s];
		}
	}
}
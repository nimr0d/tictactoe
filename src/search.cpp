#include "search.h"

#include "s_base.h"

Square slSquare(Square s) {
	return 3 * ((s / 9) % 3) + s % 3;
}

Square think(Board &b, int max_time) {
	if (b.move != SQUARE_NONE) {
		// LSquareBB[slSquare(b.move)].print();
		i8 i = (b.free & LSquareBB[slSquare(b.move)]).lsb();
		if (i != 0) {
			return i - 1;
		}
	}
	return b.free.lsb() - 1;
}

i64 search(const Board &b, u32 depth, i64 alpha, i64 beta, i8 player) {
	if (depth == 0) {
		return player;
	}
	Bitboard moves;
	if (b.move != SQUARE_NONE) {
		moves = b.free & LSquareBB[slSquare(b.move)];
	}
	if (!moves) {
		moves = b.free;
	}

	i64 bv = -INFTY;
	Square s;
	while (s = moves.unset_lsb()) {
		Board child;
    	child.move = s;
    	child.free &= ~SquareBB[s];

    	Square ls = lSquare(s);

		if (player > 0) {
			child.b0 |= SquareBB[s];
			if (EndBase[SBitboard((LSquareBB[ls] & child.b0) >> (27 * (ls / 3) + 3 * (ls % 3)))]) {
				child.free &= ~LSquareBB[ls];
			}
		} else {
			child.b1 |= SquareBB[s];
			if (EndBase[SBitboard((LSquareBB[ls] & child.b1) >> (27 * (ls / 3) + 3 * (ls % 3)))]) {
				child.free &= ~LSquareBB[ls];
			}
		}

		i64 v = search(child, depth - 1, -beta, -alpha, -player);
		if (v > bv) bv = v;
		if (v > alpha) alpha = v;
		if (alpha >= beta) break;
	}
	return bv;
}
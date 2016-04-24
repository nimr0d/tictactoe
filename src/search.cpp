#include "search.h"

int think(Board &b, int max_time) {
	Bitboard x = ~(b.b0 | b.b1);
	i8 i = lsb(x & LSquareBB[lSquare(b.move)]);
	if (i != 0) {
		return i - 1;
	}
	return (x & b.free).lsb() - 1;
}
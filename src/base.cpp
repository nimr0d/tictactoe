#include "base.h"

#include <iostream>

i64 wbase[2][262144];
i64 dbase[262144];

bool P0winning(Bitboard bb) {	
	for (Square i = 0; i < 3; ++i) {
		if ((bb & ColumnBB[i]) == P0ColumnBB[i] || (bb & RowBB[i]) == P0RowBB[i]) {
			return true;
		}
	}

	if ((bb & DiagBB[0]) == P0DiagBB[0] || (bb & DiagBB[1]) == P0DiagBB[1]) {
		return true;
	}

 	return false;
}

bool P1winning(Bitboard bb) {	
	for (Square i = 0; i < 3; ++i) {
		if ((bb & ColumnBB[i]) == ColumnBB[i] || (bb & RowBB[i]) == RowBB[i]) {
			return true;
		}
	}

	if ((bb & DiagBB[0]) == DiagBB[0] || (bb & DiagBB[1]) == DiagBB[1]) {
		return true;
	}

 	return false;
}

void fillLine(Bitboard bb, i64 *p0_vals, i64 *p1_vals, Square *line) {

	i64 c0 = 0, c1 = 0;

	for (Square i = 0; i < 3; ++i) {

		Square s = line[i];
		Piece pt = bb_get(bb, s);

		if (pt == P0) {
			++c0;
		} else if (pt == P1) {
			++c1;
		}
	}
	if (c0 > 0 && c1 == 0) {
		for (Square i = 0; i < 3; ++i) {
			Square s = line[i];
			Piece pt = bb_get(bb, s);
			if (c0 > p0_vals[s]) {
				p0_vals[s] = c0;
			}
		}
	}
	if (c0 == 0 && c1 > 0) {
		for (Square i = 0; i < 3; ++i) {
			Square s = line[i];
			Piece pt = bb_get(bb, s);
			if (c1 > p1_vals[s]) {
				p1_vals[s] = c1;
			}
		}
	}
}

void Base::init() {

	for (Bitboard b = 0; b < 262144; ++b) {

		i64 count = 0;

		i64 p0_vals[9] = { 0 };
		i64 p1_vals[9] = { 0 };

		for (Square i = 0; i < 3; ++i) {
			Square line[3];
			for (Square j = 0; j < 3; ++j) {
				line[j] = 3 * i + j;
			}
			fillLine(b, p0_vals, p1_vals, line);
		}

		for (Square j = 0; j < 3; ++j) {
			Square line[3];
			for (Square i = 0; i < 3; ++i) {
				line[i] = 3 * i + j;
			}
			fillLine(b, p0_vals, p1_vals, line);
		}

		{
			Square line[3];
			for (Square d = 0; d < 3; ++d) {
				line[d] = 4 * d;
			}	
			fillLine(b, p0_vals, p1_vals, line);
		}

		{
			Square line[3];
			for (Square d = 0; d < 3; ++d) {
				line[d] = 2 * d + 2;
			}	
			fillLine(b, p0_vals, p1_vals, line);
		}			 			 

		for (Square s = 0; s < 9; ++s) {
			count += p0_vals[s] - p1_vals[s];
		}

		dbase[b] = count;

		wbase[0][b] = P0winning(b);
		wbase[1][b] = P1winning(b);

	}

}
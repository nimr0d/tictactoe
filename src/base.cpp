#include "base.h"

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

void Base::init() {

	for (Bitboard b = 0; b < 262144; ++b) {

		i64 count = 0;

		Bitboard bc = b;

		Piece arr[9];
		for (Square i = 0; i < 9; ++i) {
			arr[i] = bb_get(b, i);
		}

		for (Square i = 0; i < 3; ++i) {
			i64 c = 0;
			bool s1 = false, s2 = false;

			for (Square j = 0; j < 3; ++j) {
				Piece pt = arr[3 * i + j];
				if (pt == P0) {
					++c;
					s1 = true;
				} else if (pt == P1) {
					--c;
					s2 = true;
				}
			}
			if (!s1 || !s2) {
				count += c;
			}
		}

		for (Square j = 0; j < 3; ++j) {
			i64 c = 0;
			bool s1 = false, s2 = false;

			for (Square i = 0; i < 3; ++i) {
				Piece pt = arr[3 * i + j];
				if (pt == P0) {
					++c;
					s1 = true;
				} else if (pt == P1) {
					--c;
					s2 = true;
				}
			}
			if (!s1 || !s2) {
				count += c;
			}
		}

		{
			i64 c = 0;
			bool s1 = false, s2 = false;

			for (Square d = 0; d < 3; ++d) {
				Piece pt = arr[4 * d];
				if (pt == P0) {
					++c;
					s1 = true;
				} else if (pt == P1) {
					--c;
					s2 = true;
				}
			}
			if (!s1 || !s2) {
				count += c;
			}
		}

		{
			i64 c = 0;
			bool s1 = false, s2 =false;

			for (Square d = 0; d < 3; ++d) {
				Piece pt = arr[2 * d + 2];
				if (pt == P0) {
					++c;
					s1 = true;
				} else if (pt == P1) {
					--c;
					s2 = true;
				}
			}
			if (!s1 || !s2) {
				count += c;
			}
		}

		loop: 

		dbase[b] = count;
		wbase[0][b] = P0winning(b);
		wbase[1][b] = P1winning(b);

	}

}
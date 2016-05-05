#include "evaluation.h"

#include "base.h"
#include "board.h"

i64 lineVal(i64 *vals, Bitboard mb, Square *line) {

	i64 count = 0;

	bool w0 = true, w1 = true;

	for (Square i = 0; i < 3; ++i) {

		Square s = line[i];
		Piece pt = bb_get(mb, s);

		if (pt == NONE) {
			w0 = false;
			w1 = false;
		} else if (pt == P0) {
			w1 = false;
			count += 16;
		} else if (pt == P1) {
			w0 = false;
			count -= 16;
		} else {
			count += vals[s];
		}
	}

	return (w0 || w1) ? count : 0;
}

i64 eval(Piece *field, Bitboard macroboard, u8 *lsCount) {

	i64 vals[9];

	for (Square t = 0; t < 9; ++t) {
		vals[t] = dbase[LSquare(field, t)];
	}

	for (Square s = 0; s < 9; ++s) {
		if (bb_get(macroboard, s) == NONE && lsCount[s] < 9) {
			bb_set(macroboard, FR, s);
		} 
	}

	i64 count = 0;

	for (Square i = 0; i < 3; ++i) {
		Square line[3];
		for (Square j = 0; j < 3; ++j) {
			line[j] = 3 * i + j;
		}
		count += lineVal(vals, macroboard, line);
	}

	for (Square j = 0; j < 3; ++j) {
		Square line[3];
		for (Square i = 0; i < 3; ++i) {
			line[i] = 3 * i + j;
		}
		count += lineVal(vals, macroboard, line);
	}

	{
		Square line[3];
		for (Square d = 0; d < 3; ++d) {
			line[d] = 4 * d;
		}	
		count += lineVal(vals, macroboard, line);
	}

	{
		Square line[3];
		for (Square d = 0; d < 3; ++d) {
			line[d] = 2 * d + 2;
		}	
		count += lineVal(vals, macroboard, line);
	}			 			 

	return count;
}
#include "evaluation.h"

#include "base.h"
#include "board.h"

i64 lineVal(i64 *p0vals, i64 *p1vals, Bitboard mb, Square *line) {

	i64 p0count = 0, p1count = 0;

	bool w0 = true, w1 = true;

	for (Square i = 0; i < 3; ++i) {

		Square s = line[i];
		Piece pt = bb_get(mb, s);

		if (pt == NONE) {
			w0 = false;
			w1 = false;
		} else if (pt == P0) {
			w1 = false;
			p0count += 16;
		} else if (pt == P1) {
			w0 = false;
			p1count += 16;
		} else {
			p0count += p0vals[s];
			p1count += p1vals[s];
		}
	}

	i64 count = p0count - p1count;
	if (w0) count += p0count;
	if (w1) count -= p1count;
	return (w0 || w1) ? count : 0;
}
i64 eval(Piece *field, Bitboard macroboard, u8 *lsCount) {

	i64 p0vals[9], p1vals[9];


	for (Square t = 0; t < 9; ++t) {
		Bitboard ls = LSquare(field, t);
		p0vals[t] = dbase[ls];
		p1vals[t] = dbase[ls ^ flipMask];
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
		count += lineVal(p0vals, p1vals, macroboard, line);
	}

	for (Square j = 0; j < 3; ++j) {
		Square line[3];
		for (Square i = 0; i < 3; ++i) {
			line[i] = 3 * i + j;
		}
		count += lineVal(p0vals, p1vals, macroboard, line);
	}

	{
		Square line[3];
		for (Square d = 0; d < 3; ++d) {
			line[d] = 4 * d;
		}	
		count += lineVal(p0vals, p1vals, macroboard, line);
	}

	{
		Square line[3];
		for (Square d = 0; d < 3; ++d) {
			line[d] = 2 * d + 2;
		}	
		count += lineVal(p0vals, p1vals, macroboard, line);
	}			 			 

	return count;
}
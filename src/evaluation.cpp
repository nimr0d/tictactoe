#include "evaluation.h"

#include "base.h"
#include "board.h"

i64 lineVal(Position *pos, Square *line, i64 *p0vals, i64 *p1vals) {
	i64 p0count = 0, p1count = 0;
	bool w0 = true, w1 = true;
	for (Square i = 0; i < 3; ++i) {
		Square s = line[i];
		Piece pt = pos->lpiece(s);
		if (pt == NA) {
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
i64 eval(Position *pos) {
	i64 p0vals[9], p1vals[9];
	for (Square t = 0; t < 9; ++t) {
		p0vals[t] = dbase[pos->board(t)];
		p1vals[t] = dbase[pos->board(t) ^ 262143];
	}
	i64 count = 0;
	for (Square i = 0; i < 3; ++i) {
		Square line[3];
		for (Square j = 0; j < 3; ++j) {
			line[j] = 3 * i + j;
		}
		count += lineVal(pos, line, p0vals, p1vals);
	}
	for (Square j = 0; j < 3; ++j) {
		Square line[3];
		for (Square i = 0; i < 3; ++i) {
			line[i] = 3 * i + j;
		}
		count += lineVal(pos, line, p0vals, p1vals);
	}
	{
		Square line[3];
		for (Square d = 0; d < 3; ++d) {
			line[d] = 4 * d;
		}	
		count += lineVal(pos, line, p0vals, p1vals);
	}
	{
		Square line[3];
		for (Square d = 0; d < 3; ++d) {
			line[d] = 2 * d + 2;
		}	
		count += lineVal(pos, line, p0vals, p1vals);
	}			 			 
	return count;
}
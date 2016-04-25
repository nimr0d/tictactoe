/*#include "evaluation.h"

i64 evaluate(const Board &b, bool p0) {

	i64 eval = 0;

	i64 count = 0;

	SBitboard sr0 = 0, sr1 = 0;
	for (Square i = 0; i < 9; ++i) {
		if (EndBase[Smallboard[b.b0]]) {
			sr0 |= SquareSBB[i];
			count += 1;
		}
		if (EndBase[Smallboard[b.b1]]) {
			sr1 |= SquareSBB[i];
			count -= 1;
		}
	}

	if (EndBase[sr0]) {
		eval = WIN;
	}

}*/
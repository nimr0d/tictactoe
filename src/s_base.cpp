#include "s_base.h"

#include "bitboard.h"

i8 SmallBase[512][512] = {{ 0 }};

bool winning(SBitboard b0, SBitboard b1) {
	for (u8 i = 0; i < 3; ++i) {
		if ((b0 & ColumnSBB[i]) == ColumnSBB[i] || (b0 & RowSBB[i]) == RowSBB[i]) {
			return true;
		}
	}
	if ((b0 & DiagSBB[0]) == DiagSBB[0] || (b0 & DiagSBB[1]) == DiagSBB[1]) {
		return true;
	}
	return false;
}

void SBase::init() {
	int count = 0;

	for (SBitboard x = 511; x != -1U; --x) {
		for (SBitboard b0 = 0; b0 <= x; ++b0) {
			if ((x & b0) == b0) {
				SBitboard b1 = x ^ b0;
				i8 w0 = winning(b0, b1), w1 = winning(b1, b0);
				i8 w =  w0 - w1;
				if (!w0 && !w1 && x != 511) {
					w = -1;
					SBitboard y = (~x) & 511;
					Square s;
					while (s = unset_lsb(y)) {
						i8 v = -SmallBase[b1][b0 | SquareSBB[s - 1]];
						if (v > w) {
							w = v;
						}
					}
				} 

				SmallBase[b0][b1] = w;

				++count;
			}

		}
	}
}

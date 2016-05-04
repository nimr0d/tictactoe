#include "search.h"

#include <cstring>
#include <iostream>
#include "board.h"
#include "base.h"
#include "evaluation.h"

void printfield(Piece *field) {
    for (Square i = 0; i < 9; ++i) {
        for (Square j = 0; j < 9; ++j) {
            std::cerr << field[9 * i + j] << " ";
        }
        std::cerr << "\n";
    }
}

void printlsc(u8 *lsc) {
    for (Square i = 0; i < 3; ++i) {
        for (Square j = 0; j < 3; ++j) {
            std::cerr << int(lsc[3 * i + j]) << " ";
        }
        std::cerr << "\n";
    }
}

i64 search(Piece *field, Bitboard macroboard, u8 *lsCount, u8 numFin, u32 depth, i64 alpha, i64 beta, Piece player, bool ret) {

	if (depth == 0 || numFin >= 9) {

		/*if (ret) {
			// Return some legal square.
			for (Square b = 0; b < 9; ++b) {
				if (bb_get(macroboard, b) == FR) {
					for (Square c = 0; c < 9; ++c) {
						Square s = LStS[b][c];
						if (field[s] == NONE) {
							return s;
						}
					}
				}
			}
		}*/

		return eval(field, macroboard, lsCount) * (3 - 2 * player);

	}

	i64 bv = -INFTY;
	Square bs;

	for (Square b = 0; b < 9; ++b) {
		if (bb_get(macroboard, b) == FR) {
			for (Square c = 0; c < 9; ++c) {

				Square s = LStS[b][c];
				if (field[s] == NONE) {

					field[s] = player;

					Square x1 = StLS1[s], x2 = StLS2[s];

					Bitboard mb = macroboard;
					
					u8 nf = numFin;
					
					bool w = wbase[player - 1][LSquare(field, x2)];

				 	if ((++lsCount[x2]) >= 9) {
						bb_set(mb, NONE, x2);
						++nf;
					} else if (w) {
						++nf;
					}

				 	if (w) {

						bb_set(mb, player, x2);

						bool fw = wbase[player - 1][mb];

				 		if (fw) {
				 			field[s] = NONE;
				 			--lsCount[x2];
				 			bv = WIN;
				 			bs = s;
				 			goto finish;
				 		}

				 	}

				 	if (lsCount[x1] < 9 && bb_get(mb, x1) != P0 && bb_get(mb, x1) != P1) {
				 		for (Square g = 0; g < 9; ++g) {
				 			if (bb_get(mb, g) == FR) {
				 				bb_set(mb, NONE, g);
				 			}
				 		}
				 		bb_set(mb, FR, x1);

				 	} else {
				 		for (Square g = 0; g < 9; ++g) {
				 			if (bb_get(mb, g) == NONE && lsCount[g] < 9) {
				 				bb_set(mb, FR, g);
				 			}
				 		}
				 	}
				 	i64 v = -search(field, mb, lsCount, nf, depth - 1, -beta, -alpha, player == P0 ? P1 : P0, false);

					field[s] = NONE;
					--lsCount[x2];

					if (v > bv) {
				 		bv = v;
				 		bs = s;
				 	}
				 	if (v > alpha) alpha = v;
				 	if (alpha >= beta) goto finish;
				}
			}
		}
	}

	finish:
	if (ret) {
		std::cerr << "Value: " << bv << "\n";
		return bs;
	}
	return bv;
}

Square think(Piece *field, Bitboard macroboard, u8 *lsCount, u8 numFin, Piece player, i64 time, u32 move) {
	u32 depth = 9;

	if (move == 1) {
		return 40;
	} else if (time < 800) {
		depth = 6;
	} else if (time < 2000) {
		depth = 8;
	} else if (move >= 32 && time >= 3500) {
		depth = 10;
	}

	return search(field, macroboard, lsCount, numFin, depth, -INFTY, INFTY, player, true);
}

